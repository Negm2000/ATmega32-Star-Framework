#include <stdio.h>
#include <stdint.h>
#include "LIB/CircularBuffer/CircBuffer.h"


void main(void){
    MAKE_CBUFFER(cb);
    CircBuffer_push(&cb, 8);
    printf("%d", CircBuffer_pop(&cb));
}