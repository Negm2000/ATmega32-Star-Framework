#include "CircBuffer.h"

void CB_push(CircBuffer *this, Q_TYPE val)
{
    this->arr[this->tail] = val;
    // Modulo resets tail to 0 when exceeding buffer size
    this->tail = (this->tail + 1) % BUFFER_SIZE;
    
    // New data overwrites old data when buffer is full, head is moved to the next oldest.
    #if BUFFER_FULL_BEHAVIOUR == OVERWRITE
        if (this->size == BUFFER_SIZE)
        {
            this->head = (this->head + 1) % BUFFER_SIZE;
            return;
        }
    #else
        if (this->size == BUFFER_SIZE) return;
    #endif
    
    this->size++;

}

Q_TYPE CB_pop(CircBuffer *this){
    this->size--;
    Q_TYPE val = this->arr[this->head];
    this->head = (this->head + 1) % BUFFER_SIZE;
    return val;
}
uint8 CB_isEmpty(CircBuffer *this) { return this->size == 0; }
uint16 CB_size(CircBuffer *this)   { return this->size; }
Q_TYPE CB_front(CircBuffer *this)  { return this->arr[this->head];}
Q_TYPE CB_back(CircBuffer *this)   { return this->arr[this->tail];}
