#include "UART_interface.h"
#include "UART_registers.h"
#include "UART_config.h"
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
    // while (CB_isEmpty(&RX_Buffer));
    CB_pop(&RX_Buffer, &ch);
    return ch;
}

uint8 UART_ReadString(uint8* out_str, uint8 delimitter){
    uint8 i=0;
    while (CB_peek(&RX_Buffer) != delimitter){
        CB_pop(&RX_Buffer, &out_str[i++]);
       // Wait for the next byte to be avalable to read
       while(CB_isEmpty(&RX_Buffer));
    }
    // Pop off the delimitter that wasn't copied to our string.
    CB_pop(&RX_Buffer,&out_str[i-1]);
    // Optional: Replace it with '\0', discarding the delimitter.
    out_str[i-1] = '\0';
    return (i-1);
}

void UART_WriteCharacter(uint8 ch){

    while (!get_bit_r(_UCSRA,_UDRE));
    _UDR = ch;
}
void UART_WriteString(uint8* str){
    uint8 i=0;
    while (str[i] != '\0' && i<99){
        UART_WriteCharacter(str[i++]);
    }
    // UART_WriteCharacter('\0');
}

void UART_Flush(void){
    CB_flush(&RX_Buffer);
}

#ifdef UART_PRINTF
#include <stdarg.h>
#include "LIB/string/string.h"

void UART_Printf(const char* format, ...){
    uint16 i=0;
    va_list args;
    va_start(args,format);

    while (format[i])
    {   

        if (format[i] != '%') {
            UART_WriteCharacter(format[i++]);
            continue;
         }


        if (format[i] == '%') {

            switch (format[i+1]) {
                case 'd':{
                    uint8 str_buffer[20]={0};
                    itoa(va_arg(args,int),str_buffer,0);
                    UART_WriteString(str_buffer);
                    break;
                }

                case 'f':
                {
                    uint8 str_buffer[20]={0};
                    ftoa(va_arg(args,double),str_buffer,2);
                    UART_WriteString(str_buffer);
                    break;
                }

                case 's':
                    UART_WriteString(va_arg(args,uint8*));
                    break;

                case 'c':
                    UART_WriteCharacter(va_arg(args,int));
                    break;

                case '%':
                    UART_WriteCharacter('%');
                    break;

                default:
                    i++;
                    break;
            }
            i+=2;
        }
    }
    va_end(args);
}
#endif

void ISR_UART_DATA_RECIEVED(void){
    CB_push(&RX_Buffer,_UDR); 
    // Its possible to use the error return, to set some status flag.
}

