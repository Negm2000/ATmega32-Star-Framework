#ifndef HAL_LCD_LCD_INTERFACE_H_
#define HAL_LCD_LCD_INTERFACE_H_
#include "LIB/datatypes.h"
#include "LCD_config.h"


void LCD_init(void);
void LCD_SendCommand(uint8 cmd);
void LCD_WriteChar(uint8 c);
void LCD_WriteString(uint8 *str);
void LCD_SetCursor(uint8 row, uint8 col);


#endif // HAL_LCD_LCD_INTERFACE_H_