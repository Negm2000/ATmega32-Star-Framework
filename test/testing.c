#include <stdio.h>
#include <stdint.h>
#include "LIB/CircularBuffer/CircBuffer.h"

void itoa(uint32 num, uint8* strbuf){
  uint32 d = num;
  int i = 0;
  while(d>0){
    strbuf[i++] = d%10 + '0';
    d/=10;
  }
  i--;
  for(int j=0; j<i; i--, j++){
    uint8 temp = strbuf[i];
    strbuf[i] = strbuf[j];
    strbuf[j] = temp;
  }
}


uint8 local_read_idx=65, read_idx, buffer_sz = 64;
#define fast_modulo(n,even_modulo) ((n) & (even_modulo-1))
void main(void){
    uint8 lol[4]={0,0,0,0};
    read_idx = fast_modulo(local_read_idx+1, buffer_sz);
    itoa(1234,lol);
    printf("%d, %s\n",read_idx,lol);
}