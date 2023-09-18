#ifndef MCAL_TMR_TMR_REGISTERS_H_
#define MCAL_TMR_TMR_REGISTERS_H_
#include "LIB/datatypes.h"

// TMR0 Relevant Registers

#define _TCCRO *(register_address_t) 0x53
#define _TCNT0 *(register_address_t) 0x52
#define _OCR0  *(register_address_t) 0x5C
#define _TIMSK *(register_address_t) 0x59
#define _TIFR  *(register_address_t) 0x58

// Timer 0 Control Register Pins

#define _CS00     1
#define _CS01  1<<1
#define _CS02  1<<2
#define _WGM01 1<<3
#define _COM00 1<<4
#define _COM01 1<<5
#define _WGM00 1<<6


// TIMSK TMR0 Pins

#define _TOIE0 1
#define _OCIE0 1<<1



#endif // MCAL_TMR_TMR_REGISTERS_H_
