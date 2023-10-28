#ifndef HAL_LCD_LCD_INTERFACE_H_
#define HAL_LCD_LCD_INTERFACE_H_
#include "LIB/datatypes.h"
#include "LCD_config.h"


void LCD_init(void);
void LCD_SendCommand(uint8 cmd);
void LCD_WriteChar(uint8 c);
void LCD_WriteString(uint8 *str);

// Use this function over a direct clear command to avoid glitches 
// this is due to the extra delay as clear command takes more time to execute
void LCD_Clear(void);

void LCD_Printf(const char* format, ...);
void LCD_SetCursor(uint8 row, uint8 col);
void LCD_ShiftLeft(void);
void LCD_ShiftRight(void);
void LCD_AddCustomChar(uint8 location, uint8 *data);
void LCD_WriteCustomChar(uint8 location);
#endif // HAL_LCD_LCD_INTERFACE_H_