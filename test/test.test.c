// BEGIN: 3f5a7d2f5c7b
#include <stdio.h>
#define uint8 unsigned char
#define int8 char
#define int32 long

int atoi(uint8* strbuf){
  int32 num = 0;
  int8 sign = 1;

  if(*strbuf=='-') {sign = -1; strbuf++;}
  else if(*strbuf=='+') {sign = 1; strbuf++;}

  while(*strbuf){
    if(*strbuf<'0' || *strbuf>'9') return 0;
    num*=10;
    num+=(*strbuf-'0')*sign;
    strbuf++;
  }
    return num;
}


int main() {
  uint8 str1[] = "123";
  uint8 str2[] = "-456";
  uint8 str3[] = "+789";
  uint8 str4[] = "0";
  uint8 str5[] = "123abc";
  uint8 str6[] = "abc123";
  uint8 str7[] = "2147483647";
  uint8 str8[] = "-2147483648";
  uint8 str9[] = "2147483648";
  uint8 str10[] = "-2147483649";

  printf("%d\n", atoi(str1)); // expected output: 123
  printf("%d\n", atoi(str2)); // expected output: -456
  printf("%d\n", atoi(str3)); // expected output: 789
  printf("%d\n", atoi(str4)); // expected output: 0
  printf("%d\n", atoi(str5)); // expected output: 123
  printf("%d\n", atoi(str6)); // expected output: 0
  printf("%d\n", atoi(str7)); // expected output: 2147483647
  printf("%d\n", atoi(str8)); // expected output: -2147483648
  printf("%d\n", atoi(str9)); // expected output: 0
  printf("%d\n", atoi(str10)); // expected output: 0

  return 0;
}
// END: 3f5a7d2f5c7b