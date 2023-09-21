#include "UART_interface.h"
#include "UART_registers.h"
#include "LIB/bits.h"
#include "LIB/CircularBuffer/CircBuffer.h"
#include "MCAL/DIO/DIO_interface.h"
MAKE_CBUFFER(RX_Buffer);
MAKE_CBUFFER(TX_Buffer);


/* In an interrupt driven transmission, the transmission isr must disable the data register empty interrupt
   that is to avoid the ISR being called over and over after data is sent.
   So we only enable UDRE when something is ready in the TX buffer.
   And when the data is finally transmitted by the ISR, UDRIE will be once again disabled.
*/
#define UDRE_INTERRUPT_ON()  set_bits(_UCSRB, _UDRIE);
#define UDRE_INTERRUPT_OFF() clr_bits(_UCSRB, _UDRIE);

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

}


uint8 UART_DataAvailable(void){return RX_Buffer.size;}
uint8 UART_ReadCharacter(void){return CB_pop(&RX_Buffer);}

void UART_ReadString(uint8* out_str, uint8 delimitter){
    uint8 i=0;
    while (CB_front(&RX_Buffer) != delimitter && RX_Buffer.size){
        out_str[i++] = CB_pop(&RX_Buffer);
    }
    // Pop off the delimitter that wasn't copied to our string.
    out_str[i]='\0';
}

void UART_WriteCharacter(uint8 ch){
    CB_push(&TX_Buffer, ch);
    UDRE_INTERRUPT_ON();
}
void UART_WriteString(uint8* str){
    uint8 i=0;
    while (str[i] != '\0'){
        UART_WriteCharacter(str[i++]);
    }
}

void ISR_UART_DATA_RECIEVED(void){
    CB_push(&RX_Buffer,_UDR);
}

void ISR_UART_TRANSMIT_READY(void){
    while (TX_Buffer.size)
        _UDR = CB_pop(&TX_Buffer);
    UDRE_INTERRUPT_OFF();
}