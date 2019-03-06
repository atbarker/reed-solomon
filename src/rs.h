#ifndef RS_H
#define RS_H

#include <stdint.h>
#include "polynomial.h"

//The generator polynomial, only one instance of this
static Polynomial* gen_poly;

//tables for storing Galois field operation results, 2D arrays if requiring two operands, so 64KB each
uint8_t gf_mul_table[256][256];
uint8_t gf_inv_table[256];
uint8_t gf_pow_table;
uint8_t gf_div_table;

//Single number galois field functions
uint8_t gf_add(uint8_t x, uint8_t y);
uint8_t gf_mult_table(uint8_t x, uint8_t y);
uint8_t gf_div(uint8_t x, uint8_t y);
uint8_t gf_pow(uint8_t x, uint8_t pow);
uint8_t gf_inv(uint8_t x);

//polynomial galois field functions
int32_t gf_poly_scalar(Polynomial *p, Polynomial *output, uint8_t scalar);
int32_t gf_poly_add(Polynomial *a, Polynomial *b, Polynomial *output);
int32_t gf_poly_mult(Polynomial *a, Polynomial *b, Polynomial *output);
int32_t gf_poly_div(Polynomial *a, Polynomial *b, Polynomial *output);
uint8_t gf_poly_eval(Polynomial *p, uint8_t x);

//Reed-Solomon functions
Polynomial* rs_generator_poly(uint8_t n_symbols);
//make sure that the two arrays are already allocated
void Encode(const void* data, uint8_t data_length, void* parity, uint8_t parity_length);

Polynomial* calc_syndromes(Polynomial* message, uint8_t parity_length);
Polynomial* find_errata_locator(Polynomial* error_positions);
Polynomial* find_error_evaluator(Polynomial* synd, Polynomial* errata_loc, uint8_t parity_length);
Polynomial* correct_errors(Polynomial* syn, Polynomial* err_pos, Polynomial* message);

void decode(void);


#endif
