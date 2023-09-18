#ifndef MCAL_INT_INT_INTERFACE_H_
#define MCAL_INT_INT_INTERFACE_H_

#include "INT_registers.h"

// Global Interrupt Enable
#define SEI() (SREG |= (1<<7))
// Global Interrupt Disable
#define CLI() (SREG &= ~(1<<7))

#define ISR(Vector) void Vector(void) __attribute__ ((signal,used))

#define EXT_INT0  __vector_1
#define EXT_INT1  __vector_2
#define EXT_INT2  __vector_3 
#define TMR0_CMP __vector_10
#define TMR0_OVF __vector_11


#endif // MCAL_INT_INT_INTERFACE_H_