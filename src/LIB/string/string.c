#include "string.h"
#include "MCAL/UART/UART_interface.h"

/**
 * Converts an integer to a string and stores it in a buffer.
 * 
 * @param num The integer to be converted.
 * @param strbuf The buffer to store the resulting string.
 * @param min_str_len The minimum length of the resulting string. If the resulting string is shorter than this, it will be padded with zeros.
 * 
 * @return The length of the resulting string.
 */
uint8 itoa(int32 num, uint8* strbuf, uint8 min_str_len){
  if (!num) { *strbuf = '0'; return 1; }
  bool negative = false;
  if(num<0) {
    negative = true;
    num*=-1;
  }

  uint8 i = 0;
  // Get last digit, convert to char, add to buffer
  while(num){
    strbuf[i++] = num%10 + '0';
    num/=10;
  }  // Produces string form of our input in the buffer, but reversed.

  // If it doesnt meet minimum string length, pad with zeros
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

/**
 * Converts a float number to a string with a specified number of decimal places.
 * 
 * @param num The float number to be converted.
 * @param strbuf The buffer to store the resulting string.
 * @param decimal_places The number of decimal places to include in the resulting string.
 */
void ftoa(float num, uint8* strbuf, uint8 decimal_places){
  uint8 c = decimal_places;
  int32 int_part = (int32) num;
  if(num<0) num*=-1;
  num-=(int32) num;
  while (c--) num*=10;

  uint8 decimal_point = itoa(int_part,strbuf,1);
  strbuf[decimal_point] = '.';
  itoa(num,&strbuf[decimal_point+1],decimal_places);   
}

int32 atoi(uint8* strbuf){
  int32 num = 0;
  int8 sign = 1;
  if(*strbuf=='-') {sign=-1; strbuf++;}
  else if(*strbuf=='+') {sign=1; strbuf++;}
  while(*strbuf){
    if(*strbuf<'0' || *strbuf>'9') return 0;
    num*=10;
    num+=(*strbuf-'0')*sign;
    strbuf++;
  }
  return num;
}