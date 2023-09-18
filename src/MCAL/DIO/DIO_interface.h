#ifndef MCAL_DIO_DIO_INTERFACE_H_
#define MCAL_DIO_DIO_INTERFACE_H_
#include "LIB/datatypes.h"
#include "LIB/bits.h"

typedef enum EN_Port_Number {PORTA,PORTB,PORTC,PORTD} EN_Port_Number;
typedef enum EN_Pin_Value {LOW, HIGH} EN_Pin_Value ;
typedef enum EN_Pin_State {INPUT, OUTPUT, PULLUP} EN_Pin_State;
// This trick allows us to chain multiple pins in a single command in our functions
typedef enum EN_Pin_Number 
{
    PIN0 = 1 << 0,
    PIN1 = 1 << 1,
    PIN2 = 1 << 2,
    PIN3 = 1 << 3,
    PIN4 = 1 << 4,
    PIN5 = 1 << 5,
    PIN6 = 1 << 6,
    PIN7 = 1 << 7,
} EN_Pin_Number;



void DIO_PinDigitalWrite(EN_Port_Number port,  EN_Pin_Number pin, EN_Pin_Value pin_value);
void DIO_PinDigitalToggle(EN_Port_Number port, EN_Pin_Number pin);
void DIO_PortDigitalWrite(EN_Port_Number port, uint8 value);

void DIO_PinMode(EN_Port_Number port, EN_Pin_Number pin, EN_Pin_State pin_state);
void DIO_PortMode(EN_Port_Number port, EN_Pin_State pin_state);

uint8 DIO_PinDigitalRead (EN_Port_Number port, EN_Pin_Number pin);
uint8 DIO_PortDigitalRead (EN_Port_Number port);







#endif // MCAL_DIO_DIO_INTERFACE_H_