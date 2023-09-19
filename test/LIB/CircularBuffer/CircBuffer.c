#include "CircBuffer.h"

void CircBuffer_push(CircBuffer *this, Q_TYPE val)
{
    this->arr[this->tail] = val;
    // Modulo resets tail to 0 when exceeding buffer size
    this->tail = (this->tail + 1) % BUFFER_SIZE;
    // New data overwrites old data when buffer is full, head is moved to the next oldest.
    if (this->size == BUFFER_SIZE)
    {
        this->head = (this->head + 1) % BUFFER_SIZE;
        return;
    }
    this->size++;
}

Q_TYPE CircBuffer_pop(CircBuffer *this)
{

    if (!this->size)
        return EMPTY_BUFFER_ERROR;
    this->size--;
    Q_TYPE val = this->arr[this->head];
    this->head = (this->head + 1) % BUFFER_SIZE;
    return val;
}
uint8 CircBuffer_isEmpty(CircBuffer *this) { return this->size == 0; }
uint16 CircBuffer_size(CircBuffer *this) { return this->size; }
Q_TYPE CircBuffer_front(CircBuffer *this)
{
    return (this->size > 0) ? this->arr[this->head] : EMPTY_BUFFER_ERROR;
}
Q_TYPE CircBuffer_back(CircBuffer *this)
{
    return (this->size > 0) ? this->arr[this->tail] : EMPTY_BUFFER_ERROR;
}
