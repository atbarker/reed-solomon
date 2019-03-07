#ifndef RS_H
#define RS_H

#include <stdint.h>
#include "polynomial.h"

//The generator polynomial, only one instance of this
static Polynomial* gen_poly;

//Single number galois field functions
uint8_t init_tables(void);
uint8_t gf_add(uint8_t x, uint8_t y);
uint8_t gf_mult(uint8_t x, uint8_t y, uint16_t prim_poly);
uint8_t gf_mult_table(uint8_t x, uint8_t y);
void populate_mult_lookup(void);
uint8_t gf_mult_lookup(uint8_t x, uint8_t y);
uint8_t gf_div(int x, int y);
uint8_t gf_pow(int x, int pow);
uint8_t gf_inv(uint8_t x);

//polynomial galois field functions
int32_t gf_poly_scalar(Polynomial *p, Polynomial *output, uint8_t scalar);
int32_t gf_poly_add(Polynomial *a, Polynomial *b, Polynomial *output);
int32_t gf_poly_mult(Polynomial *a, Polynomial *b, Polynomial *output);
int32_t gf_poly_div(Polynomial *a, Polynomial *b, Polynomial *output, Polynomial *remainder);
uint8_t gf_poly_eval(Polynomial *p, uint8_t x);

//Reed-Solomon functions
void rs_generator_poly(uint8_t n_symbols);
//make sure that the two arrays are already allocated
void encode(const void* data, uint8_t data_length, void* parity, uint8_t parity_length);

Polynomial* calc_syndromes(Polynomial* message, uint8_t parity_length);
Polynomial* find_error_locator(Polynomial* error_positions);
Polynomial* find_error_evaluator(Polynomial* synd, Polynomial* error_loc, uint8_t parity_length);
Polynomial* correct_errors(Polynomial* syn, Polynomial* err_pos, Polynomial* message);

int decode(const uint8_t* src, const uint8_t* parity, uint8_t data_size, uint8_t parity_size, uint8_t* dest, uint8_t* erasure_pos, uint8_t erasure_count);

#endif
