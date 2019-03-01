#ifndef RS_H
#define RS_H

#include <stdint.h>

//tables for storing Galois field operation results, 2D arrays if requiring two operands, so 64KB each
uint8_t gf_mul_table[256][256];
uint8_t gf_inv_table[256];
uint8_t gf_pow_table;
uint8_t gf_div_table;

uint8_t gf_add(uint8_t x, uint8_t y);
uint8_t gf_mult_table(uint8_t x, uint8_t y);
uint8_t gf_div(uint8_t x, uint8_t y);
uint8_t gf_pow(uint8_t x, uint8_t pow);
uint8_t gf_inv(uint8_t x);


#endif
