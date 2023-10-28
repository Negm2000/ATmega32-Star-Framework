#include "TMR0_interface.h"
#include "TMR0_registers.h"
#include "LIB/bits.h"
#define SECONDS_PER_OVF(Prescaler) ((float)Prescaler / F_CPU * 256)

void (*OverflowCallback)(void);
void (*CompareCallback)(void);


volatile uint64 _OverflowCounter;
volatile uint64 OverflowsSinceSysStart;
uint32 _OverflowsTillCallback;

ST_TMR0_Config Current_Config;
uint8 Preload;
uint16 Current_Prescaler;


ST_TMR0_Config ST_TMR0_Default_Config =
    {
        waveform_generation_mode : NORMAL,
        compare_match_output_mode : OC_DISABLE,
        prescaler_select : PRESCALER_8,
        enabled_interrupts : OVERFLOW_INTERRUPT_ENABLE
    };

void TMR0_Config(ST_TMR0_Config *config)
{

    // Begin by setting all the bits we shall configure to 0s initially
    _TCCRO = 0;
    clr_bits(_TIMSK, _TOIE0 | _OCIE0);

    Current_Config = *config;
    // Lookup table, used to convert from prescaler enum value to actuale prescaler value
    uint16 Prescaler_LUT[] = {0, 1, 8, 64, 256, 1024, 0, 0};
    Current_Prescaler = Prescaler_LUT[config->prescaler_select];

    // Create the bit mask based on the configurations chosen
    uint8 TCCR0_bitmask = config->prescaler_select | config->compare_match_output_mode | config->waveform_generation_mode;
    set_bits(_TCCRO, TCCR0_bitmask);
    set_bits(_TIMSK, config->enabled_interrupts);
}

/**
 * @brief Sets the callback period of Timer0 in milliseconds.
 * 
 * @param time_ms The desired overflow period in milliseconds.
 */
void TMR0_SetCallbackPeriod_ms(float time_ms)
{
    float overflows_needed = (time_ms) / (SECONDS_PER_OVF(Current_Prescaler) * 1000);

    if (Current_Config.waveform_generation_mode == PHASE_CORRECT)
        overflows_needed /= 2;

    // Preload calculation
    Preload = _TCNT0 = (overflows_needed - (int32)overflows_needed) * 256;
    _OverflowsTillCallback = overflows_needed;
}


void TMR0_Delay_ms(uint32 time_ms){
    uint64 release_time = TMR0_Millis() + time_ms;
    while(TMR0_Millis() < release_time);
}

void TMR0_Delay_us(uint32 time_us){
    uint64 release_time = TMR0_Micros() + time_us;
    while(TMR0_Micros() < release_time);
}


void TMR0_SetOverflowCallback(void (*callback_func)(void))
{
    OverflowCallback = callback_func;
}
void TMR0_SetCompareCallback(void (*callback_func)(void))
{
    CompareCallback = callback_func;
}

inline uint32 TMR0_Millis(void)
{
    return (SECONDS_PER_OVF(Current_Prescaler) * 1000 * OverflowsSinceSysStart);
}

inline uint64 TMR0_Micros(void)
{
    return (SECONDS_PER_OVF(Current_Prescaler) * 1000000 * OverflowsSinceSysStart);
}

void TMR0_PWM(uint8 duty_cycle_percentage)
{

    switch (Current_Config.compare_match_output_mode)
    {
    case OC_CLEAR:
        _OCR0 = (duty_cycle_percentage * 255 / 100);
        return;
    case OC_SET:
        _OCR0 = 255 - (duty_cycle_percentage * 255 / 100);
        return;
    default:
        return;
    }
}

void TMR0_SetFrequency(uint32 frequency)
{
    if (frequency < F_CPU / (2 * Current_Prescaler))
        _OCR0 = (F_CPU / (2 * Current_Prescaler * frequency)) - 1;
}

void ISR_TMR0_OVF(void)
{
    ++OverflowsSinceSysStart;
    
    if (OverflowCallback){
        ++_OverflowCounter;
        if (_OverflowCounter < _OverflowsTillCallback) return;

        OverflowCallback();
        _OverflowCounter = 0;
        _TCNT0 = Preload;
    }
}

void ISR_TMR0_CMP(void)
{
    if (CompareCallback) CompareCallback();
}
