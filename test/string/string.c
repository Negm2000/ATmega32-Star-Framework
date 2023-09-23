#include "string.h"


uint8 itoa(int32 num, uint8* strbuf, uint8 min_str_len){
  int i = 0;
  bool negative = false;
  if(num<0) {
    negative = true;
    num*=-1;
  }

  // Get last digit, convert to char, add to buffer
  while(num){
    strbuf[i++] = num%10 + '0';
    num/=10;
  }  
  while (i < min_str_len) strbuf[i++] = '0';
  if(negative) strbuf[i++]='-';
  uint8 str_sz = i; 
  
  // Reverse the string
  i--;
  for(int j=0; j<i; i--, j++){
    uint8 temp = strbuf[i];
    strbuf[i] = strbuf[j];
    strbuf[j] = temp;
  }
  strbuf[str_sz] = 0;
  return str_sz;
}



void ftoa(float num, uint8* strbuf, uint8 decimal_places){
  uint8 c = decimal_places;
  int32 int_part = (int32) num;
  if(num<0) num*=-1;
  num-=(int32) num;
  while (c--) num*=10;

  uint8 decimal_point = itoa(int_part,strbuf,decimal_places);
  strbuf[decimal_point] = '.';
  itoa(num,&strbuf[decimal_point+1],decimal_places);   
}