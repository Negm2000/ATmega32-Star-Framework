#include "DIO_interface.h"
#include "DIO_registers.h"


typedef enum EN_Mode {OUTPUT_REG, DIRECTION_REG, INPUT_REG} EN_Mode;

// Instead of using a switch case, we can get the register address from this equation and cast it as a register address
#define PortNumberToPortAddress(PortNumber, register_type) (register_address_t)(_PORTA - 3*PortNumber - register_type)



void DIO_PinDigitalWrite(EN_Port_Number port, EN_Pin_Number pins, EN_Pin_Value pin_value){

    register_address_t port_address = PortNumberToPortAddress(port,OUTPUT_REG);

    pin_value ? set_bits(*port_address,pins): clr_bits(*port_address, pins);
}

void DIO_PinDigitalToggle(EN_Port_Number port, EN_Pin_Number pins){
    tog_bits(*PortNumberToPortAddress(port,OUTPUT_REG), pins);
}


void DIO_PortDigitalWrite(EN_Port_Number port, uint8 value){
    *PortNumberToPortAddress(port,OUTPUT_REG) = value;
}

void DIO_PinMode(EN_Port_Number port, EN_Pin_Number pins, EN_Pin_State pin_state){

    register_address_t direction_address = PortNumberToPortAddress(port,DIRECTION_REG);
    register_address_t output_address = PortNumberToPortAddress(port,OUTPUT_REG);

    switch (pin_state){
        case INPUT:  clr_bits(*direction_address,pins); return;
        case OUTPUT: set_bits(*direction_address,pins); return;
        case PULLUP: 
            clr_bits(*direction_address, pins); 
            set_bits(*output_address,pins); 
            return;
        default: return;
    }
}

void DIO_PortMode(EN_Port_Number port, EN_Pin_State pin_state){

    register_address_t direction_address = PortNumberToPortAddress(port,DIRECTION_REG);
    register_address_t output_address = PortNumberToPortAddress(port,OUTPUT_REG);

    switch (pin_state){
        case INPUT:  *direction_address = 0; return;
        case OUTPUT: *direction_address = 255; return;
        case PULLUP: 
            *direction_address = 0;
            *output_address = 255;
            return;
        default: return;
    }
}

uint8 DIO_PinDigitalRead (EN_Port_Number port, EN_Pin_Number pin){
    return ((*PortNumberToPortAddress(port,INPUT_REG) & pin) > 0);
}
uint8 DIO_PortDigitalRead (EN_Port_Number port) {
    return *PortNumberToPortAddress(port,INPUT_REG);
}
