#ifndef MCAL_INT_INT_INTERFACE_H_
#define MCAL_INT_INT_INTERFACE_H_

#include "INT_registers.h"

// Global Interrupt Enable
#define SEI()  __asm__ __volatile__ ("sei" ::: "memory")
// Global Interrupt Disable
#define CLI()  __asm__ __volatile__ ("cli" ::: "memory")


#define ISR(Vector) void Vector(void) __attribute__((signal,used))

#define ISR_EXT_INT0  __vector_1
#define ISR_EXT_INT1  __vector_2
#define ISR_EXT_INT2  __vector_3 
#define ISR_TMR0_CMP __vector_10
#define ISR_TMR0_OVF __vector_11
#define ISR_UART_DATA_RECIEVED __vector_13
#define ISR_UART_TRANSMIT_READY __vector_14


#endif // MCAL_INT_INT_INTERFACE_H_