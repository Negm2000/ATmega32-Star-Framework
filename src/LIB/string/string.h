#ifndef LIB_STRING_STRING_H_
#define LIB_STRING_STRING_H_
#include "LIB/datatypes.h"

uint8 itoa(int64 num, uint8* strbuf, uint8 min_str_len);
void ftoa(float num, uint8* strbuf, uint8 decimal_places);
int32 atoi(uint8* strbuf);


#endif // LIB_STRING_STRING_H_
