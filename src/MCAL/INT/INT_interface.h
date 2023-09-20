#ifndef MCAL_INT_INT_INTERFACE_H_
#define MCAL_INT_INT_INTERFACE_H_

#include "INT_registers.h"

// Global Interrupt Enable
#define SEI() (SREG |= (1<<7))
// Global Interrupt Disable
#define CLI() (SREG &= ~(1<<7))

#define ISR(Vector) void Vector(void) __attribute__ ((signal,used))

#define ISR_EXT_INT0  __vector_1
#define ISR_EXT_INT1  __vector_2
#define ISR_EXT_INT2  __vector_3 
#define ISR_TMR0_CMP __vector_10
#define ISR_TMR0_OVF __vector_11
#define ISR_UART_DATA_RECIEVED __vector_15
#define ISR_UART_TRANSMIT_READY __vector_16


#endif // MCAL_INT_INT_INTERFACE_H_