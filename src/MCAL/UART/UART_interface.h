#ifndef MCAL_UART_UART_INTERFACE_H_
#define MCAL_UART_UART_INTERFACE_H_
#include "LIB/datatypes.h"
#include "MCAL/INT/INT_interface.h"

void UART_Init(uint32 Baudrate);
uint8 UART_DataAvailable(void);
uint8 UART_ReadCharacter(void);
// Will return number of characters read
uint8 UART_ReadString(uint8* out_str, uint8 delimitter);
void UART_WriteCharacter(uint8);
void UART_WriteString(uint8* str);
ISR(ISR_UART_DATA_RECIEVED);
ISR(ISR_UART_TRANSMIT_READY);

#endif // MCAL_UART_UART_INTERFACE_H_