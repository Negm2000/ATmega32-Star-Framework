#ifndef LIB_CircBuffer_H_
#define LIB_CircBuffer_H_
#include "../datatypes.h"

// Change this to make the CircBuffer hold more elements before overwriting old data
#define BUFFER_SIZE 100
// Change this to make the CircBuffer hold different types
#define Q_TYPE uint8
#define BUFFER_FULL_BEHAVIOUR OVERWRITE

typedef struct CircBuffer
{
  Q_TYPE arr[BUFFER_SIZE];
  uint16 head;
  uint16 tail;
  uint16 size;
} CircBuffer;

// Macro to create a CircBuffer object that is properly initialized.
#define MAKE_CBUFFER(Q) CircBuffer Q = {.head = 0, .tail = 0, .size = 0}


void  CB_push(CircBuffer* this, Q_TYPE val);
Q_TYPE CB_pop(CircBuffer* this);
uint8 CB_isEmpty(CircBuffer* this);
uint16 CB_size(CircBuffer* this);
Q_TYPE CB_front(CircBuffer* this);
Q_TYPE CB_back(CircBuffer* this);






#endif // LIB_CircBuffer_H_