
#ifndef LIB_BITS_H_
#define LIB_BITS_H_



// Single bit manipulation
#define set_bit(data,bitNumber)  ( (data) |=  (1<<(bitNumber)) ) 
#define clr_bit(data,bitNumber)  ( (data) &= ~(1<<(bitNumber)) )
#define tog_bit(data,bitNumber)  ( (data) ^=  (1<<(bitNumber)) )
#define get_bit(data,bitNumber)  ( ((data) >> (bitNumber)) & 1 )


// Multi bit manipulation.

#define set_bits(data,bits)  ( (data) |=  (bits)) 
#define clr_bits(data,bits)  ( (data) &= ~(bits))
#define tog_bits(data,bits)  ( (data) ^=  (bits))


#endif // LIB_BITS_H_