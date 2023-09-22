#include "UART_interface.h"
#include "UART_registers.h"
#include "LIB/bits.h"
#include "LIB/CircularBuffer/CircBuffer.h"
#include "MCAL/DIO/DIO_interface.h"

#define BUFF_SZ 128
uint8 RX_Arr[BUFF_SZ];
CircBuffer RX_Buffer;


void UART_Init(uint32 Baudrate){
    // 0. Datasheet recommends interrupts be disabled during init.
    CLI();
    // 1. Enable RX and TX, and recieve interrupt.
    set_bits(_UCSRB, _RXEN | _TXEN | _RXCIE);
    // 2. Get UBBR from baudrate using equation from datasheet
    uint16 UBBR = F_CPU/(16UL*Baudrate) - 1;
    // 3. UBBR is 12 bits and lies across 2 registers
    _UBRRL = (uint8) UBBR;
    _UBRRH =  UBBR >> 8;
    // 4. USCRC requires all settings to be written in a single clock with the URSEL high
    // Frame is 8 bits, no parity, and 1 stop bit.
    set_bits(_UCSRC, _URSEL | _UCSZ0 | _UCSZ1);
    // 5. Setup buffers
    CB_setup(&RX_Buffer, RX_Arr, BUFF_SZ);

}


uint8 UART_DataAvailable(void){
    return !CB_isEmpty(&RX_Buffer);
}

uint8 UART_ReadCharacter(void){
    uint8 ch = 0;
    while (CB_isEmpty(&RX_Buffer));
    CB_pop(&RX_Buffer, &ch);
    return ch;
}

uint8 UART_ReadString(uint8* out_str, uint8 delimitter){
    uint8 i=0;
    while ((CB_peek(&RX_Buffer) != delimitter) ){
       out_str[i++] = UART_ReadCharacter();
    }
    // Pop off the delimitter that wasn't copied to our string.
    CB_pop(&RX_Buffer,&out_str[i]);
    out_str[i] = '\0';
    return(i);
}

void UART_WriteCharacter(uint8 ch){

    while (!get_bit_r(_UCSRA,_UDRE));
    _UDR = ch;

}
void UART_WriteString(uint8* str){
    uint8 i=0;
    while (str[i] != '\0'){
        UART_WriteCharacter(str[i++]);
    }
    UART_WriteCharacter('\n');
}

void UART_Flush(void){
    RX_Buffer.read_idx = RX_Buffer.write_idx;
}

void ISR_UART_DATA_RECIEVED(void){
    CB_push(&RX_Buffer,_UDR); 
    // Its possible to use the error return, to set some status flag.
}

