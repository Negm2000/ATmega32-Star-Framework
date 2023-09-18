#ifndef MCAL_UART_UART_INTERFACE_H_
#define MCAL_UART_UART_INTERFACE_H_
#include "LIB/datatypes.h"


void UART_Config();
uint8 UART_IsAvailable(void);
uint8 UART_ReadCharacter(void);
uint8* UART_ReadString(void);
uint8 UART_WriteCharacter(void);
void UART_WriteString(uint8*);
#endif // MCAL_UART_UART_INTERFACE_H_