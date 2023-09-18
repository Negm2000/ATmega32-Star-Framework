#ifndef MCAL_TMR_TMR0_CONFIG_H_
#define MCAL_TMR_TMR0_CONFIG_H_
#include "TMR0_registers.h"

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

// Bits [0-1] TIMSK Register 
typedef enum EN_TMR_Interrupts
{
    DISABLE_ALL,
    OVERFLOW_INTERRUPT_ENABLE,
    OC_MATCH_INTERRUPT_ENABLE,
    ENABLE_ALL
} EN_TMR_Interrupts;



#endif // MCAL_TMR_TMR0_CONFIG_H_
