#ifndef LIB_DATATYPES_H_
#define LIB_DATATYPES_H_

typedef unsigned char uint8; // 0 to 255
typedef unsigned short uint16; // 0 to 65,535
typedef unsigned long uint32; // 0 to 4,294,967,295 
typedef unsigned long long uint64;  // 0 to 18,446,744,073,709,551,615
typedef char int8; //-128 to 127
typedef short int16; // -32,768 to 32,767
typedef long int32; // -2,147,483,648 to 2,147,483,647
typedef long long int64; // Really big lol

typedef volatile uint8 *const register_address_t;  //  Pointer to a volatile 8 bit memory location (Location is constant)

#define NULL 0
#define NULLPTR (void*) 0 

#define TRUE 1
#define FALSE 0


#endif // LIB_DATATYPES_H_