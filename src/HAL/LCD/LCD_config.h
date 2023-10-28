/**
 * @file LCD_config.h
 * @brief This file contains the configuration parameters for the LCD module.
 * 
 * This file defines the control and data ports for the LCD module, as well as the pins for the RS, RW, E, D0, D1, D2, D3, D4, D5, D6, and D7 pins.
 * 
 * @details
 * The file defines the control (RS,RW,E) and data (D0-D7) ports for the LCD module, as well as the pins for the RS, RW, E, D0, D1, D2, D3, D4, D5, D6, and D7 pins.
 * The control and data ports are defined using the PORTC macro, and the pins are defined using the PINx macros, where x is the pin number.
 * The file is used to configure the LCD module for use in an embedded system.
 * 
 * @note
 * Use bitwise OR to combine the command with the command parameters.
 * 
 * @attention
 * The user should ensure that the pins defined in this file match the actual pins used in the hardware setup.
 * 
 */

#ifndef HAL_LCD_LCD_CONFIG_H_
#define HAL_LCD_LCD_CONFIG_H_
#include "MCAL/DIO/DIO_interface.h"

#define NIBBLE_MODE 0
#define BYTE_MODE 1
#define LCD_ADDRESSING_MODE NIBBLE_MODE

#define _LCD_PRINTF_ENABLE 1

#define CTRL_PORT PORTA
#define DATA_PORT PORTA

#define _RS PIN1
#define _RW PIN2
#define _E  PIN3
// #define _D0 PIN0
// #define _D1 PIN1
// #define _D2 PIN2
// #define _D3 PIN3
#define _D4 PIN4
#define _D5 PIN5
#define _D6 PIN6
#define _D7 PIN7

//-----------------------------------------
// Command Section
//-----------------------------------------

#define CLEAR_DISPLAY 0x01
#define RETURN_HOME 0x02


#define ENTRY_MODE_SET 0x04
#define ENTRY_MODE_LEFT2RIGHT (1<<1)
#define ENTRY_MODE_DISPLAY_SHIFT_ON (1<<0)

#define DISPLAY_CONTROL 0x08
// Logical OR with the following bitmasks to create the command
#define DISPLAY_CONTROL_DISPLAY_ON (1<<2)
#define DISPLAY_CONTROL_CURSOR_ON (1<<1)
#define DISPLAY_CONTROL_BLINK_ON (1<<0)

#define CURSOR_DISPLAY_SHIFT 0x10
#define CURSOR_SHIFT_LEFT 0
#define CURSOR_SHIFT_RIGHT (1<<2)
#define CURSOR_DISPLAY_SHIFT_LEFT (1<<3)
#define CURSOR_DISPLAY_SHIFT_RIGHT (1<<3 | 1<<2)

#define FUNCTION_SET 0x20
#define FUNCTION_SET_8BIT (1<<4)
#define FUNCTION_SET_2LINES (1<<3)
#define FUNCTION_SET_5x10DOTS (1<<2)

// OR with 6 bit address to create the command
#define SET_CGRAM_ADDRESS 0x40

// OR with 7 bit address to create the command
#define SET_DDRAM_ADDRESS 0x80






#endif // HAL_LCD_LCD_CONFIG_H_