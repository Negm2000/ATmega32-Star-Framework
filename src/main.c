
#include "HAL/LCD/LCD_interface.h"
#include "MCAL/TMR/TMR0_interface.h"
#include "MCAL/UART/UART_interface.h"
#include "LIB/string/string.h"
int main(void){
    TMR0_Config(&ST_TMR0_Default_Config);
    UART_Init(9600);
    uint64 previous_time = 0;
    SEI();
    LCD_init();
    LCD_WriteString("Time: ");
    uint64 hr = 4 , min = 34, sec = 0;
    while(1){
        uint64 current_time = TMR0_Millis();
        if (current_time-previous_time >= 1000){
            LCD_SetCursor(1,0);
            sec++;
            if (sec == 60){
                sec = 0;
                min++;
                if (min == 60){
                    min = 0;
                    hr++;
                    if (hr == 24){
                        hr = 0;
                    }
                }
            }
            LCD_Clear();
            LCD_Printf("Time:\n%2d:%2d:%2d\r\t--NEGM--",hr,min,sec);
            previous_time = current_time;
        }
    }
}
