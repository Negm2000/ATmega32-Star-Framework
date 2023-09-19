#ifndef MCAL_UART_UART_REGISTERS_H_
#define MCAL_UART_UART_REGISTERS_H_
#include "LIB/datatypes.h"

#define _UDR     *(register_address_t) 0x2C
#define _UCSRA   *(register_address_t) 0x2B
#define _UCSRB   *(register_address_t) 0x2A
#define _UCSRC   *(register_address_t) 0x40
#define _UBRRL   *(register_address_t) 0x29
#define _UBRRH   *(register_address_t) 0x40

// UCSRA Bits
#define _RXC    1<<7    
#define _TXC    1<<6    
#define _UDRE   1<<5     
#define _FE     1<<4
#define _DOR    1<<3    
#define _PE     1<<2
#define _U2X    1<<1    
#define _MPCM   1<<0     

// UCSRA Bits
#define _RXC    1<<7    
#define _TXC    1<<6    
#define _UDRE   1<<5     
#define _FE     1<<4
#define _DOR    1<<3    
#define _PE     1<<2
#define _U2X    1<<1    
#define _MPCM   1<<0     

// UCSRB Bits
#define _RXCIE    1<<7    
#define _TXCIE    1<<6    
#define _UDRIE    1<<5     
#define _RXEN     1<<4
#define _TXEN     1<<3    
#define _UCSZ2    1<<2
#define _RXB8     1<<1    
#define _TXB8     1<<0     

// UCSRC Bits
#define _URSEL    1<<7    
#define _UMSEL    1<<6    
#define _UPM1     1<<5     
#define _UPM0     1<<4
#define _USBS     1<<3    
#define _UCSZ1    1<<2
#define _UCSZ0    1<<1    
#define _UCPOL    1<<0     

//UBRRL and UBRRH

#define _URSEL 1<<7







#endif // MCAL_UART_UART_REGISTERS_H_