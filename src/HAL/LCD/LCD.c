#include "LCD_interface.h"
#include "MCAL/DIO/DIO_interface.h"
#include "MCAL/TMR/TMR0_interface.h"


void LCD_init(void){
    DIO_PinMode(CTRL_PORT,_RS | _RW | _E, OUTPUT);
    TMR0_Delay_ms(200);
    #if LCD_ADDRESSING_MODE == NIBBLE
        DIO_PinMode(DATA_PORT,_D4 | _D5 | _D6 | _D7, OUTPUT);
            // 4 bits, 5x7, 2 lines
            LCD_SendCommand(FUNCTION_SET | FUNCTION_SET_2LINES);
            // Again, because its critical that the command does not fail
            LCD_SendCommand(FUNCTION_SET | FUNCTION_SET_2LINES);
            LCD_SendCommand(FUNCTION_SET | FUNCTION_SET_2LINES);
    #else
        DIO_PortMode(DATA_PORT,OUTPUT);
        LCD_SendCommand(FUNCTION_SET | FUNCTION_SET_8BIT | FUNCTION_SET_2LINES | FUNCTION_SET_5x10DOTS);
    #endif

    // Display ON, Cursor ON ,Blink ON
    LCD_SendCommand(DISPLAY_CONTROL | DISPLAY_CONTROL_DISPLAY_ON | DISPLAY_CONTROL_CURSOR_ON | DISPLAY_CONTROL_BLINK_ON); 
    // Clear Display
    LCD_SendCommand(CLEAR_DISPLAY);
    // Entry Mode Set
    LCD_SendCommand(ENTRY_MODE_SET | ENTRY_MODE_LEFT2RIGHT);
}

// Helper function to send commands or data to LCD
void LCD_Send(uint8 cmd, bool Data_Mode, bool Read_Mode){

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
    TMR0_Delay_ms(1);
    DIO_PinDigitalWrite(CTRL_PORT,_E, LOW);

    #if LCD_ADDRESSING_MODE == NIBBLE
        // Send the lower nibble
        TMR0_Delay_ms(1);
        DIO_PinDigitalWrite(DATA_PORT,_D4, (cmd>>0)&1);
        DIO_PinDigitalWrite(DATA_PORT,_D5, (cmd>>1)&1);
        DIO_PinDigitalWrite(DATA_PORT,_D6, (cmd>>2)&1);
        DIO_PinDigitalWrite(DATA_PORT,_D7, (cmd>>3)&1);

        // Start write sequence by trigerring falling edge on pin EN
        DIO_PinDigitalWrite(CTRL_PORT,_E, HIGH);
        TMR0_Delay_ms(1);
        DIO_PinDigitalWrite(CTRL_PORT,_E, LOW);
    #endif

    TMR0_Delay_ms(3);
}

void LCD_SendCommand(uint8 cmd){
    LCD_Send(cmd, false, false);
}

void LCD_WriteChar(uint8 character){
    LCD_Send(character, true, false);
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
}