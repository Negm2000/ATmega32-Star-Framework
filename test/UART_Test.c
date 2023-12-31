#include "MCAL/UART/UART_interface.h"
#include "MCAL/TMR/TMR0_interface.h"
#include "MCAL/INT/INT_interface.h"
#include "MCAL/DIO/DIO_interface.h"
#include "LIB/string/string.h"

int8* bool_LUT[] = {"False!", "True!"};

int main(void){
  UART_Init(9600);
  TMR0_Config(&ST_TMR0_Default_Config);
  DIO_PortMode(PORTC, OUTPUT);
  uint32 previous_time = 0;
  SEI();
  UART_WriteString("Enter your password, if correct, a LED will turn toggle!\n");
  while (1){
    uint32 current_time = TMR0_Millis()/1000;
    if (current_time > previous_time){
      UART_Printf("Time since system startup: %ds\n", current_time);
      previous_time = current_time;
    }

    if (UART_DataAvailable()) 
    {
      uint8 i=0,ch[32] = {0}, word[] = "password";
      uint8 str_len = UART_ReadString(ch,'\n');
      if (!str_len) continue;
      bool word_is_pass=true;
      while (ch[i]!='\0' || word[i]!='\0')
      {
        if (ch[i] != word[i]) word_is_pass = false;
        ++i;
      }

      UART_Printf("You sent %s, which is %d characters long. Password? %s\n", ch, str_len, bool_LUT[word_is_pass]);
      if (!word_is_pass) continue;
      UART_Printf("Password Correct! Enter a pin number (0-7) to toggle\n");
      while (!UART_DataAvailable());
      EN_Pin_Number pin = (UART_ReadCharacter() - '0');
      UART_Printf("Toggling Pin %d..\n", pin);
      DIO_PinDigitalToggle(PORTC, 1<<pin);

    } 
  }
}
