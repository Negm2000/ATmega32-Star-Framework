#ifndef MCAL_TMR_TMR0_INTERFACE_H_
#define MCAL_TMR_TMR0_INTERFACE_H_
#include "LIB/datatypes.h"
#include "TMR0_registers.h"
#include "MCAL/INT/INT_interface.h"
#include "TMR0_config.h"

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
void TMR0_Config(ST_TMR0_Config *config);
void TMR0_SetOverflowPeriod_ms(float time_ms);
void TMR0_Delay_ms(float time_ms);
void TMR0_SetOverflowCallback(void (*callback_func)(void));
void TMR0_SetCompareCallback(void (*callback_func)(void));
void TMR0_SetPWM(uint8 duty_cycle_percentage);
void TMR0_SetFrequency(uint32 frequency);
uint32 TMR0_Millis(void);
ISR(ISR_TMR0_OVF);
ISR(ISR_TMR0_CMP);

#endif // MCAL_TMR_TMR0_INTERFACE_H_