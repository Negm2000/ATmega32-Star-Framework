#include <stdio.h>
#include <stdint.h>
#include "LIB/CircularBuffer/CircBuffer.h"


void main(void){
    MAKE_CBUFFER(cb);
    CircBuffer_push(&cb, 1);
    CircBuffer_push(&cb, 2);
    CircBuffer_push(&cb, 3);
    CircBuffer_push(&cb, 4);
    CircBuffer_push(&cb, 5);
    printf("empty? %d\n", CircBuffer_isEmpty(&cb));
    printf("%d\n", CircBuffer_pop(&cb));
    printf("%d\n", CircBuffer_pop(&cb));
    printf("%d\n", CircBuffer_pop(&cb));
    printf("empty? %d\n", CircBuffer_isEmpty(&cb));
    printf("%d\n", CircBuffer_pop(&cb));
}