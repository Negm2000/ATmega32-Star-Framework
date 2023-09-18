#include "TMR0_interface.h"
#include "TMR0_registers.h"
#include "LIB/bits.h"
#define SECONDS_PER_OVF(Prescaler) ((float)Prescaler/F_CPU * 256)

void (*OverflowCallback)(void);
void (*CompareCallback)(void);
volatile uint32 _OverflowCounter;
volatile uint64 OverflowsSinceSysStart;
uint32 _OverflowsTillCallback; 
ST_TMR0_Config Current_Config;
uint8 Preload;
// Lookup table, used to convert from prescaler enum value to actuale prescaler value
uint16 Prescaler_LUT[] = {0,1,8,64,256,1024,0,0} ;



ST_TMR0_Config ST_TMR0_Default_Config = 
{
    waveform_generation_mode : FAST_PWM,
    compare_match_output_mode: OC_CLEAR,
    prescaler_select : PRESCALER_8,
    enabled_interrupts : OVERFLOW_INTERRUPT_ENABLE
};


void TMR0_Config(ST_TMR0_Config* config){

    // Begin by setting all the bits we shall configure to 0s initially
    _TCCRO = 0;
    clr_bits(_TIMSK, _TOIE0 | _OCIE0);

    Current_Config = *config;

    // Create the bit mask based on the configurations chosen
    uint8 TCCR0_bitmask = config->prescaler_select | config->compare_match_output_mode | config->waveform_generation_mode;
    set_bits(_TCCRO, TCCR0_bitmask);
    set_bits(_TIMSK, config->enabled_interrupts);

}

void TMR0_SetOverflowPeriod_ms(float time_ms){
    
    uint16 prescaler = Prescaler_LUT[Current_Config.prescaler_select];
    float overflows_needed = (time_ms) / (SECONDS_PER_OVF(prescaler)*1000);
    if (ST_TMR0_Default_Config.waveform_generation_mode == PHASE_CORRECT) overflows_needed/=2;

    // Preload calculation
    _TCNT0 = (overflows_needed - (int32) overflows_needed) * 256; 
    _OverflowsTillCallback = overflows_needed;
}

void TMR0_Delay_ms(float time_ms){

    uint16 prescaler = Prescaler_LUT[Current_Config.prescaler_select];
    float overflows_needed = (time_ms) / (SECONDS_PER_OVF(prescaler)*1000);
    if (ST_TMR0_Default_Config.waveform_generation_mode == PHASE_CORRECT) overflows_needed/=2;

    // Preload calculation
    Preload = (overflows_needed - (int32) overflows_needed) * 256;
    uint32 Overflow_Counter = 0;
    
    while(Overflow_Counter < (int32) overflows_needed){
        if(get_bit(_TIFR,0)){
            set_bit(_TIFR,0);
            Overflow_Counter++;
        } 
    }
}


void TMR0_SetOverflowCallback(void(*callback_func)(void)){
    OverflowCallback = callback_func;
}
void TMR0_SetCompareCallback(void(*callback_func)(void)){
    CompareCallback = callback_func;
}

inline uint32 TMR0_Millis(void){
    uint16 prescaler = Prescaler_LUT[Current_Config.prescaler_select];
    return (SECONDS_PER_OVF(prescaler)*1000*OverflowsSinceSysStart);
}

void TMR0_PWM(uint8 duty_cycle_percentage){

    switch (Current_Config.compare_match_output_mode)
    {
    case OC_CLEAR:_OCR0 = (duty_cycle_percentage*255/100);return;
    case OC_SET: _OCR0 = 255 - (duty_cycle_percentage*255/100); return;
    default: return;
    }
}

void TMR0_SetFrequency(uint32 frequency){
    uint16 N = Prescaler_LUT[Current_Config.prescaler_select];
    if (frequency < F_CPU/(2*N)) _OCR0 = (F_CPU/(2*N*frequency)) - 1 ;
}

void TMR0_OVF(void){
    ++OverflowsSinceSysStart;
    
    if(_OverflowCounter < _OverflowsTillCallback) {
        _OverflowCounter++;
        return;
    }

    if (OverflowCallback) {
    OverflowCallback();
    _OverflowCounter = 0;
    _TCNT0 = Preload;
    }
}

void TMR0_CMP(void){
    if(CompareCallback) CompareCallback();
}
