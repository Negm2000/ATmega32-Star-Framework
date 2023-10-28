#include "LCD_interface.h"
#include "MCAL/DIO/DIO_interface.h"
#include "MCAL/TMR/TMR0_interface.h"

uint8 x,y;

// Helper function to send commands or data to LCD
void LCD_Send(uint8 cmd, bool Data_Mode, bool Read_Mode, bool isInit){

    DIO_PinDigitalWrite(CTRL_PORT,_RS, Data_Mode);
    DIO_PinDigitalWrite(CTRL_PORT,_RW, Read_Mode);

    #if LCD_ADDRESSING_MODE == NIBBLE
        // Send the higher nibble
        DIO_PinDigitalWrite(DATA_PORT,_D4, (cmd>>4)&1);
        DIO_PinDigitalWrite(DATA_PORT,_D5, (cmd>>5)&1);
        DIO_PinDigitalWrite(DATA_PORT,_D6, (cmd>>6)&1);
        DIO_PinDigitalWrite(DATA_PORT,_D7, (cmd>>7)&1);
    #else
        DIO_PortWrite(DATA_PORT, cmd);
    #endif

    // Start write sequence by trigerring falling edge on pin EN
    DIO_PinDigitalWrite(CTRL_PORT,_E, HIGH);
    // TMR0_Delay_us(300);
    DIO_PinDigitalWrite(CTRL_PORT,_E, LOW);

    #if LCD_ADDRESSING_MODE == NIBBLE
        // Send the lower nibble
        // TMR0_Delay_us(500);
        isInit? TMR0_Delay_ms(5) : TMR0_Delay_us(100);
        DIO_PinDigitalWrite(DATA_PORT,_D4, (cmd>>0)&1);
        DIO_PinDigitalWrite(DATA_PORT,_D5, (cmd>>1)&1);
        DIO_PinDigitalWrite(DATA_PORT,_D6, (cmd>>2)&1);
        DIO_PinDigitalWrite(DATA_PORT,_D7, (cmd>>3)&1);

        // Start write sequence by trigerring falling edge on pin EN
        DIO_PinDigitalWrite(CTRL_PORT,_E, HIGH);
        // TMR0_Delay_us(300);
        DIO_PinDigitalWrite(CTRL_PORT,_E, LOW);
    #endif

    TMR0_Delay_ms(1);
}



void LCD_init(void){
    DIO_PinMode(CTRL_PORT,_RS | _RW | _E, OUTPUT);
    TMR0_Delay_ms(100);
    #if LCD_ADDRESSING_MODE == NIBBLE
        DIO_PinMode(DATA_PORT,_D4 | _D5 | _D6 | _D7, OUTPUT);
        // Send 0x03 nibble 3 times then 0x02 to initialize LCD
        // Reference: https://web.alfredstate.edu/faculty/weimandn/lcd/lcd_initialization/lcd_initialization_index.html
        // This is a special sequence for 4-bit addressing mode
        LCD_Send(0x33,false,false,true);
        LCD_Send(0x32,false,false,true);
    #else
        DIO_PortMode(DATA_PORT,OUTPUT);
        LCD_SendCommand(FUNCTION_SET | FUNCTION_SET_8BIT | FUNCTION_SET_2LINES);
    #endif

    // Display ON, Cursor ON ,Blink ON
    LCD_SendCommand(DISPLAY_CONTROL | DISPLAY_CONTROL_DISPLAY_ON); 
    // Clear Display
    LCD_Clear();
    // Entry Mode Set
    LCD_SendCommand(ENTRY_MODE_SET | ENTRY_MODE_LEFT2RIGHT);
}

void LCD_SendCommand(uint8 cmd){
    LCD_Send(cmd, false, false, false);
}

void LCD_WriteChar(uint8 character){
    LCD_Send(character, true, false, false);
    x++;
    if (x == 40)
    {
        x = 0;
        y++;
        if (y == 4)
        {
            y = 0;
        }
    }
}

void LCD_WriteString(uint8 *str){
    while(*str){
        LCD_WriteChar(*str++);
    }
}

void LCD_SetCursor(uint8 row, uint8 col){
    uint8 address = 0;
    switch(row){
        case 0:
            address = 0x00 + col;
            break;
        case 1:
            address = 0x40 + col;
            break;
        case 2:
            address = 0x14 + col;
            break;
        case 3:
            address = 0x54 + col;
            break;
    }
    LCD_SendCommand(SET_DDRAM_ADDRESS | address);
    x = col;
    y = row;
}

#if _LCD_PRINTF_ENABLE == 1
#include <stdarg.h>
#include "LIB/string/string.h"

void LCD_Printf(const char* format, ...){
    va_list args;
    va_start(args,format);

    while (*format)
    {   

        if (*format == '\n'){
            LCD_SetCursor(1,0);
            format++;
            continue;
        }

        if (*format == '\r'){
            LCD_SetCursor(0,0);
            format++;
            continue;
        }

        if(*format == '\t'){
            LCD_SetCursor(y,8);
            format++;
            continue;
        }


        if (*format != '%') {
            LCD_WriteChar(*format++);
            continue;
         }

        // Else, we have a format specifier 
        format++;

        if (*format >= '0' && *format <= '9'){
            uint8 width = *format - '0';
            format++;
            if (*format == 'd'){
                uint8 str_buffer[20]={0};
                itoa(va_arg(args,int64),str_buffer,width);
                LCD_WriteString(str_buffer);
                format++;
                continue;
            }
            else if (*format == 'f'){
                uint8 str_buffer[20]={0};
                ftoa(va_arg(args,double),str_buffer,width);
                LCD_WriteString(str_buffer);
                format++;
                continue;
            }
        }

        switch (*format) {
            case 'd':{
                uint8 str_buffer[20]={0};
                itoa(va_arg(args,int64),str_buffer,0);
                LCD_WriteString(str_buffer);
                break;
            }

            case 'f':
            {
                uint8 str_buffer[20]={0};
                ftoa(va_arg(args,double),str_buffer,2);
                LCD_WriteString(str_buffer);
                break;
            }

            case 's':
                LCD_WriteString(va_arg(args,uint8*));
                break;

            case 'c':
                LCD_WriteChar(va_arg(args,int));
                break;

            case '%':
                LCD_WriteChar('%');
                break;

            default:
                format++;
                break;
        }
        format++;
    }
    va_end(args);
}
#endif


void LCD_ShiftLeft(void){
    LCD_SendCommand(CURSOR_DISPLAY_SHIFT | CURSOR_DISPLAY_SHIFT_LEFT);
    x--;
}


void LCD_ShiftRight(void){
    LCD_SendCommand(CURSOR_DISPLAY_SHIFT | CURSOR_DISPLAY_SHIFT_RIGHT);
    x++;
}

void LCD_Clear(){
    LCD_SendCommand(CLEAR_DISPLAY);
    x=y=0;
    TMR0_Delay_ms(2);
}

void LCD_AddCustomChar(uint8 location, uint8 *data){


}
void LCD_WriteCustomChar(uint8 location);

void LCD_Home(void){
    LCD_SendCommand(RETURN_HOME);
    x=y=0;
    TMR0_Delay_ms(2);
}