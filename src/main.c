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
      uint8 ch[100];
      uint8 str_len = UART_ReadString(ch,'\n');
      for (int i=0;i<str_len-1; i++) ++ch[i];
      UART_WriteString(ch);
      // UART_WriteCharacter(ch+1);
      // UART_WriteCharacter('\n');
      // TMR0_Delay_ms(1000);
    } 
  }
}