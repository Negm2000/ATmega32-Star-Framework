#include "CircBuffer.h"

void CB_push(CircBuffer *this, Q_TYPE val)
{
    if (this->size == BUFFER_SIZE && BUFFER_OVERRUN_BEHAVIOUR == IGNORE) { return; }
    this->arr[this->tail] = val;
    this->tail = (this->tail + 1) % BUFFER_SIZE;
    // New data overwrites old data when buffer is full, head is moved to the next oldest available data.
    if (this->size ==  BUFFER_SIZE){
        this->head = (this->head + 1) % BUFFER_SIZE;
        return;
    }
    this->size++;
}

Q_TYPE CB_pop(CircBuffer *this){
    this->size--;
    Q_TYPE val = this->arr[this->head];
    this->head = (this->head + 1) % BUFFER_SIZE;
    return val;
}

uint8  CB_isEmpty(const CircBuffer *this) { return this->size == 0; }
Q_TYPE CB_front(CircBuffer *this)   { return this->arr[this->head];}
Q_TYPE CB_back(CircBuffer *this)    { return this->arr[this->tail];}
