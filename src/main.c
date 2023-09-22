#include "MCAL/UART/UART_interface.h"
#include "MCAL/TMR/TMR0_interface.h"
#include "MCAL/INT/INT_interface.h"
#include "MCAL/DIO/DIO_interface.h"
#include "string.h"
int main(void){
  UART_Init(9600);
  DIO_PortMode(PORTC, OUTPUT);
  TMR0_Config(&ST_TMR0_Default_Config);
  // DIO_PinMode(PORTD,PIN1,OUTPUT);
  SEI();
  while (1){
    if (UART_DataAvailable()) 
    {
      uint8 ch = UART_ReadCharacter();
      UART_WriteCharacter(ch+1);
      UART_WriteCharacter('\n');
      TMR0_Delay_ms(100);
    }
  }
}