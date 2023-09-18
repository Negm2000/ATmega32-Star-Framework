#ifndef MCAL_UART_UART_REGISTERS_H_
#define MCAL_UART_UART_REGISTERS_H_
#include "LIB/datatypes.h"

#define UDR     *(register_address_t) 0x2C
#define UCSRA   *(register_address_t) 0x2B
#define UCSRB   *(register_address_t) 0x2A
#define UCSRC   *(register_address_t) 0x40
#define UBRRL   *(register_address_t) 0x29
#define UBRRH   *(register_address_t) 0x40





#endif // MCAL_UART_UART_REGISTERS_H_