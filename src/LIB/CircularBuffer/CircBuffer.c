#include "CircBuffer.h"
#include "LIB/bits.h"


// Constructor
void CB_setup(CircBuffer* circular_buffer, BUFFER_DATA_TYPE* buff, uint8 buffer_bize){
    circular_buffer->buffer = buff;
    circular_buffer->buffer_sz = buffer_bize;
}


// Note: fast_modulo is used extensively to find the next write position with wraparound effect.

bool CB_push(CircBuffer *this, BUFFER_DATA_TYPE val) {
    // 1. We copy over the values of head and tail in case they are changed by an interrupt during execution
    uint8 local_read_idx = this->read_idx , local_write_idx = this->write_idx;
    // 2. Check if the buffer is full, return a status error.
    uint8 next_write_idx = fast_modulo(local_write_idx+1, this->buffer_sz);

    if (next_write_idx == local_read_idx){
        // Discard new data (Thread-safe)
        #if BUFFER_OVERRUN_BEHAVIOUR == IGNORE
            return false;
        #endif

        // Dont use, bad in interrupt driven code.
        #if BUFFER_OVERRUN_BEHAVIOUR == OVERWRITE
            this->buffer[local_write_idx] = val;
            this->write_idx = next_write_idx;
            this->read_idx = fast_modulo(local_read_idx+1, this->buffer_sz);
            return true;
        #endif
        // else: flush the buffer, all old data is discarded(Thread-safe)
        this->write_idx = next_write_idx;
        return false;
    }
    //3. If not full, place the data in the buffer and update the write index.
    this->buffer[local_write_idx] = val;
    this->write_idx = next_write_idx;
    return true;

}

bool CB_pop(CircBuffer *this, volatile BUFFER_DATA_TYPE* output ){
    uint8 local_read_idx = this->read_idx , local_write_idx = this->write_idx;

    // Check if buffer empty, return error.
    if (local_read_idx == local_write_idx) return false;

    // Not empty, place value in output and adjust read index.
    *output = this->buffer[local_read_idx];
    this->read_idx = fast_modulo(local_read_idx+1, this->buffer_sz);
    return true;
}

bool CB_isEmpty(CircBuffer *this) { return (this->read_idx == this->write_idx);}
BUFFER_DATA_TYPE CB_peek( CircBuffer *this)   { return this->buffer[this->read_idx];}