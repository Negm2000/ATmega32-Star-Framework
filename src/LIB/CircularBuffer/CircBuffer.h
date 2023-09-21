#ifndef LIB_CircBuffer_H_
#define LIB_CircBuffer_H_
#include "LIB/datatypes.h"

// Change this to make the CircBuffer hold more elements before overwriting old data
#define BUFFER_SIZE 32
// Change this to make the CircBuffer hold different types
#define Q_TYPE uint8

#define IGNORE 0
#define OVERWRITE 1
#define FLUSH 2
#define BUFFER_OVERRUN_BEHAVIOUR OVERWRITE


typedef volatile struct CircBuffer
{
  uint8 arr[BUFFER_SIZE];
  uint8 head;
  uint8 tail;
  uint8 bitmask; // https://stackoverflow.com/questions/11606971/how-does-bit-masking-buffer-index-result-in-wrap-around
} CircBuffer;



void  CB_push(CircBuffer* this, Q_TYPE val);
Q_TYPE CB_pop(CircBuffer* this);
uint8 CB_isEmpty(const CircBuffer* this);
Q_TYPE CB_front(CircBuffer* this);
Q_TYPE CB_back(CircBuffer* this);






#endif // LIB_CircBuffer_H_