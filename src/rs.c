
#include "rs.h"
#include <stdlib.h>
#include <stdint.h>

//lookup tables for multiplication
static uint8_t gf_exp[512];
static uint8_t gf_log[256];
//our generator polynomial
static uint8_t* gg;

//performs galois field arithmetic between x and y, no lookup tables
uint8_t gf_mult(uint8_t x, uint8_t y, uint16_t prim_poly){
    //uint8_t size = 256;
    uint8_t r = 0;

    while(y){
        if(y & 1){
            r = r ^ x;
        }
        y = y >> 1;
        x = x << 1;
        if((prim_poly > 0) && (x & 256)){
            x = x ^ prim_poly;
        }
    }
    
    return r;
}

//populate our two lookup tables to speed up the process
uint8_t init_tables(uint16_t prim_poly){
    uint8_t x = 1;
    int i;
    for(i = 0; i < 256; i++){
        gf_exp[i] = x;
        gf_log[x] = i;
        x = gf_mult(x, 2, prim_poly);
    }
    for(i = 255; i < 512; i++){
        gf_exp[i] = gf_exp[i - 255];
    }
    return 0;
}

uint8_t gf_add(uint8_t x, uint8_t y){
    return x ^ y;
}

uint8_t gf_mult_table(uint8_t x, uint8_t y){
    if(x == 0 || y == 0){
        return 0;
    }
    return gf_exp[gf_log[x] + gf_log[y]];
}

uint8_t gf_div(uint8_t x, uint8_t y){
    //should be a divide by zero error
    if(y == 0) return 0;
    if(x == 0) return 0;
    return gf_exp[(gf_log[x] + 255 - gf_log[y]) % 255];
}

uint8_t gf_pow(uint8_t x, uint8_t pow){
    return gf_exp[(gf_log[x] * pow) % 255];
}

uint8_t gf_inv(uint8_t x){
    return gf_exp[255 - gf_log[x]];
}

uint8_t gf_poly_scale(uint8_t* p, uint8_t* result, uint8_t length, uint8_t x){
    int i = 0;
    for(i = 0; i < length; i++){
        result[i] = gf_mult_table(p[i], x);
    }
    return 0;
}

//r_length should be the maximum of the two polynomials
uint8_t gf_poly_add(uint8_t* p, uint8_t* q, uint8_t p_length, uint8_t q_length, uint8_t* r, uint8_t r_length){
    int i;
    for(i = 0; i < p_length; i++){
        r[i+r_length-p_length] = p[i];
    }
    for(i = 0; i < q_length; i++){
        r[i+r_length-q_length] ^= q[i]; 
    }
}

uint8_t* gf_poly_mul(uint8_t* p, uint8_t* q, uint8_t p_len, uint8_t q_len){
    uint8_t* r = malloc(p_len + q_len - 1);
    int i, j;
    for(i = 0; i < q_len; i++){
        for(j = 0; j < p_len; j++){
            r[i+j] ^= gf_mult_table(p[j], q[i]);
	}
    }
    return r;
}

uint8_t gf_poly_eval(uint8_t* p, uint8_t x, uint8_t p_len){
    uint8_t y = p[0];
    int i;
    for(i = 0; i < p_len; i++){
        y = gf_mult_table(y, x) ^ p[i];
    }
    return y;
}
