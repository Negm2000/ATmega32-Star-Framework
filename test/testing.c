#include <stdio.h>
#include <stdint.h>
#include "LIB/CircularBuffer/CircBuffer.h"
#include "string/string.h"



uint8 local_read_idx=65, read_idx, buffer_sz = 64;
#define fast_modulo(n,even_modulo) ((n) & (even_modulo-1))
void main(void){
    uint8 lol[20]={0};
    float c=-120.234;
    // read_idx = fast_modulo(local_read_idx+1, buffer_sz);
    ftoa(c,lol,2);
    // itoa(123,lol,5);
    printf("%d, %s\n",read_idx,lol);
}