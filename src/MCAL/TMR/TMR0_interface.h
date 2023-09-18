#ifndef MCAL_TMR_TMR0_INTERFACE_H_
#define MCAL_TMR_TMR0_INTERFACE_H_
#include "LIB/datatypes.h"
#include "TMR0_registers.h"
#include "MCAL/INT/INT_interface.h"


// Bits [3 and 6] TCCR0 Register
typedef enum EN_TMR_Waveform_Modes
{
    NORMAL = 0,
    PHASE_CORRECT =  _WGM00,
    CTC = _WGM01,
    FAST_PWM = _WGM00 | _WGM01

} EN_TMR_Waveform_Modes;

// Bits [4-5] TCCR0 Register
typedef enum EN_TMR_Output_Compare_Modes
{
    OC_DISABLE = 0,
    OC_TOGGLE = _COM00,
    OC_CLEAR = _COM01,
    OC_SET = _COM00 | _COM01

} EN_TMR_Output_Compare_Modes;

// Bits [0-2] TCCR0 Register
typedef enum EN_TMR_Clock_Select
{
   CLK_STOPPED,
   PRESCALER_1,
   PRESCALER_8,
   PRESCALER_64,
   PRESCALER_256,
   PRESCALER_1024,
   EXTERNAL_CLK_FALLING,
   EXTERNAL_CLK_RISING
} EN_TMR_Clock_Select;

// TIMSK Register
typedef enum EN_TMR_Interrupts
{
    DISABLE_ALL,
    OVERFLOW_INTERRUPT_ENABLE,
    OC_MATCH_INTERRUPT_ENABLE,
    ENABLE_ALL
} EN_TMR_Interrupts;

/// @brief Struct that defines how the timer will be configured.
typedef struct ST_TMR0_Config
{
    EN_TMR_Waveform_Modes waveform_generation_mode;
    EN_TMR_Output_Compare_Modes compare_match_output_mode;
    EN_TMR_Clock_Select prescaler_select;
    EN_TMR_Interrupts enabled_interrupts;
} ST_TMR0_Config;

extern ST_TMR0_Config ST_TMR0_Default_Config;



/// @brief Initialize timer0
/// @param config Use and modify ST_TMR0_Default_Config or pass in your own config as a parameter
void TMR0_Config(ST_TMR0_Config* config);
void TMR0_SetOverflowPeriod_ms(float time_ms);
void TMR0_Delay_ms(float time_ms);
void TMR0_SetOverflowCallback(void(*callback_func)(void));
void TMR0_SetCompareCallback(void(*callback_func)(void));
void TMR0_SetPWM(uint8 duty_cycle_percentage);
void TMR0_SetFrequency(uint32 frequency);
uint32 TMR0_Millis(void);
ISR(TMR0_OVF);
ISR(TMR0_CMP);






#endif // MCAL_TMR_TMR0_INTERFACE_H_