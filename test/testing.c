#include <stdio.h>
#include <stdint.h>
#include "LIB/CircularBuffer/CircBuffer.h"


void main(void){
    MAKE_CBUFFER(cb);
    CB_push(&cb, 1);
    CB_push(&cb, 2);
    CB_push(&cb, 3);
    CB_push(&cb, 4);
    CB_push(&cb, 5);
    #define F_CPU 8000000L
    uint16 Baudrate = 9600;
    uint16 UBBR = F_CPU/(16UL*Baudrate) - 1;

    uint8_t UBRRL = (uint8) UBBR;
    uint8_t UBRRH =  UBBR >> 8;
    while (!CB_isEmpty(&cb))
    {
        printf("%d, %d, %d, %d\n",CB_pop(&cb), UBBR, UBRRL, UBRRH);
    }
    
}