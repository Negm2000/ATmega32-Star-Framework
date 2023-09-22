#include <stdio.h>
#include <stdint.h>
#include "LIB/CircularBuffer/CircBuffer.h"


uint8 local_read_idx=65, read_idx, buffer_sz = 64;
#define fast_modulo(n,even_modulo) ((n) & (even_modulo-1))
void main(void){
    read_idx = fast_modulo(local_read_idx+1, buffer_sz);

    printf("%d\n",read_idx);
}