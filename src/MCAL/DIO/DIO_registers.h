#ifndef MCAL_DIO_DIO_REGISTERS_H_
#define MCAL_DIO_DIO_REGISTERS_H_
#include "LIB/datatypes.h"

// Port Output Registers

#define _PORTA (register_address_t) 0x3B
#define _PORTB (register_address_t) 0x38
#define _PORTC (register_address_t) 0x35
#define _PORTD (register_address_t) 0x32

// Data Direction Registers

#define _DDRA (register_address_t) 0x3A
#define _DDRB (register_address_t) 0x37
#define _DDRC (register_address_t) 0x34
#define _DDRD (register_address_t) 0x31


// Port Input Registers

#define _PINA (register_address_t) 0x39
#define _PINB (register_address_t) 0x36
#define _PINC (register_address_t) 0x33
#define _PIND (register_address_t) 0x30


#endif // MCAL_DIO_DIO_REGISTERS_H_