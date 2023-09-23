#include "MCAL/UART/UART_interface.h"
// #include "MCAL/TMR/TMR0_interface.h"
#include "MCAL/INT/INT_interface.h"
#include "MCAL/DIO/DIO_interface.h"

void itoa(uint32 num, uint8* strbuf){
  int i = 0;

  while(num>0){
    strbuf[i++] = num%10 + '0';
    num/=10;
  }

  i--;
  for(int j=0; j<i; i--, j++){
    uint8 temp = strbuf[i];
    strbuf[i] = strbuf[j];
    strbuf[j] = temp;
  }
}


int main(void){
  UART_Init(9600);
  DIO_PortMode(PORTC, OUTPUT);
  // TMR0_Config(&ST_TMR0_Default_Config);
  // DIO_PinMode(PORTD,PIN1,OUTPUT);
  SEI();
  while (1){
    if (UART_DataAvailable()) 
    {
      uint8 i=0,ch[100], word[] = "1234" , sz[4]={0};
      uint8 str_len = UART_ReadString(ch,'\n');
      bool word_is_pass=true;
      while (ch[i]!='\0' || word[i]!='\0')
      {
        if (ch[i] != word[i]) word_is_pass = false;
        ++i;
      }
      UART_WriteString("Password correct? ");
      UART_WriteCharacter(word_is_pass+'0');
      UART_WriteCharacter('\n');

      if (word_is_pass) DIO_PinDigitalToggle(PORTC,PIN0);
      UART_WriteString("Sent: ");
      UART_WriteString(ch);
      UART_WriteString("Word size: ");
      itoa(str_len,sz);
      UART_WriteString(sz);
      UART_WriteCharacter('\n');
      // TMR0_Delay_ms(1000);
    } 
  }
}
