#ifndef POLY_H
#define POLY_H

typedef struct{
    int size; //size of the polynomial
    int offset; //offset
    int length; //length of the byte array
    uint8_t* byte_array; //actual storage of the byte array for the polynomial
} Polynomial;


//assumes an already malloc'd byte array to the desired length (max should be 256 so 8 bits is enough)
Polynomial* init(uint8_t size, uint8_t offset, uint8_t length, uint8_t* byte_array);

//append to an existing polynomial
int32_t append(Polynomial* p, uint8_t x);

//reset values to zero, really just zero the size, don't have to zero the memory
int32_t reset(Polynomial* p);

//set a polynomial to existing values
int32_t set(Polynomial* p, uint8_t* byte_seq, uint8_t size, uint8_t offset);

//make a copy of a polynomial
int32_t copy(Polynomial* src, Polynomial* dest);

//return the length of the length of the byte array
uint8_t length(Polynomial* p);

//return the size of polynomial
uint8_t size(Polynomial* p);

//coefficient at position i
uint8_t value_at(Polynomial* p, uint32_t i);

//return pointer to byte array
uint8_t* mem(Polynomial* p);

#endif
