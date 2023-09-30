
#include "HAL/LCD/LCD_interface.h"
#include "MCAL/TMR/TMR0_interface.h"
#include "MCAL/UART/UART_interface.h"
#include "LIB/string/string.h"
int main(void){
    UART_Init(9600);
    TMR0_Config(&ST_TMR0_Default_Config);
    SEI();
    UART_Printf("System started\n");
    LCD_init();
    LCD_SendCommand(DISPLAY_CONTROL | DISPLAY_CONTROL_DISPLAY_ON);
    uint8 xpos = 0;
    // LCD_WriteString("Hello World");
    LCD_WriteString("Startup Time: ");
    while(1){
        // uint8 ch[32] = {0};
        // if(UART_DataAvailable()){ 
        //     uint8 l = UART_ReadString(ch,'\n');
        //     xpos+=l;
        //     UART_Printf("You sent %s length %d\n", ch, l);
        //     LCD_WriteString(ch);
        //     if(strcmp(ch,"clear")==0) {LCD_SendCommand(CLEAR_DISPLAY); xpos=0; LCD_SetCursor(0,0);}

        //     if(xpos>15) {LCD_SetCursor(1,0); xpos=0;}




        // }

        uint8 time[12]= {0};

        uint32 current_time = TMR0_Millis();
        if (current_time%1000==0){
            itoa(current_time/1000,time,0);
            LCD_SetCursor(1,0);
            LCD_WriteString(time);
            LCD_WriteString("s");
        }
    }
}
