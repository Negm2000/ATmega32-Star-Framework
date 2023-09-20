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

    while (!CB_isEmpty(&cb))
    {
        printf("%d\n",CB_pop(&cb));
    }
    
}