
#ifndef LIB_BITS_H_
#define LIB_BITS_H_



// Single bit manipulation
#define set_bit(data,bitNumber) ( (data) |=  (1<<(bitNumber)) ) 
#define clr_bit(data,bitNumber) ( (data) &= ~(1<<(bitNumber)) )
#define tog_bit(data,bitNumber) ( (data) ^=  (1<<(bitNumber)) )
#define get_bit(data,bitNumber) ( ((data) >> (bitNumber)) & 1 )


// Multi bit manipulation.

#define set_bits(data,bits)     ( (data) |=  (bits)) 
#define clr_bits(data,bits)     ( (data) &= ~(bits))
#define tog_bits(data,bits)     ( (data) ^=  (bits))
#define get_bit_r(reg, bit)     ( ((reg) & (bit))>0)

// Useful math tricks


/**
 * @brief Calculates the modulo of a number using a power of two as the divisor.
 * 
 * This macro calculates the modulo of a number using a power of two as the divisor.
 * It is equivalent to the expression `(n) % (even_modulo)`, but faster for powers of two.
 * 
 * @param n The number to calculate the modulo of.
 * @param even_modulo The power of two divisor to use.
 * @return The modulo of `n` using `even_modulo` as the divisor.
 */
#define fast_modulo(n,even_modulo) ((n) & (even_modulo-1))


#endif // LIB_BITS_H_