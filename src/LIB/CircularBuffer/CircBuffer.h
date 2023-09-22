#ifndef LIB_CircBuffer_H_
#define LIB_CircBuffer_H_
#include "LIB/datatypes.h"

// Change this to make the CircBuffer hold different types
#define BUFFER_DATA_TYPE uint8

#define IGNORE 0
#define OVERWRITE 1 // NOT THREAD/INTERRUPT SAFE
#define FLUSH 2
#define BUFFER_OVERRUN_BEHAVIOUR FLUSH


/*------------------------------------------------------------------------------------
When allocating memory for a buffer, you MUST choose a buffer size thats a multiple of two.
This allows us to get the wraparound effect with an extremely fast bitwise operation
Rather than using the significantly slower modulo or if-compare with buffer size.
------------------------------------------------------------------------------------*/ 

typedef struct CircBuffer
{
  BUFFER_DATA_TYPE* buffer;
  uint8 write_idx;
  uint8 read_idx;
  uint8 buffer_sz; // For: https://jameshfisher.com/2016/12/10/bitmask-wraparound/
} volatile CircBuffer;


void CB_setup(CircBuffer* CB, BUFFER_DATA_TYPE* buff, uint8 buffer_bize);
// Will return 1 if successful, 0 if failed (buffer full)
bool  CB_push(CircBuffer* this, BUFFER_DATA_TYPE val);
// Will return 1 if successful, 0 if failed (buffer empty)
bool CB_pop(CircBuffer* this, volatile BUFFER_DATA_TYPE* output);
bool CB_isEmpty( CircBuffer* this);
BUFFER_DATA_TYPE CB_peek( CircBuffer* this);






#endif // LIB_CircBuffer_H_