#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "rs.h"

int test_galois_field(){
    //if addition (XOR) doesn't work then something is SERIOUSLY wrong
    if(gf_add(5, 6) != 3){
	printf("GF add failed\n");
        return -1;
    }
    //test the lookup table based multiplication
    if(gf_mult_table(0b10001001, 0b00101010) != 0b11000011){
        printf("GF multiplication failed\n");
        return -1;
    }
    //TODO add part for checking divide by zero errors
    if(gf_div(36, 6) != 14){
        printf("GF division failed\n");
	return -1;
    }
    //exponentiation
    if(gf_pow(4, 12) != 143){
        printf("GF exponentiation failed\n");
	return -1;
    }
    //Inverse (really 1/x)
    if(gf_inv(43) != 74){
        printf("GF inversion failed\n");
	return -1;
    }

    //Test polynomials
    Polynomial* a = new_poly();
    Polynomial* b = new_poly();

    a->byte_array[0] = 0x01;
    a->byte_array[1] = 0x0f;
    a->byte_array[2] = 0x36;
    a->byte_array[3] = 0x78;
    a->byte_array[4] = 0x40;
    a->size = 5;

    b->byte_array[0] = 0x40;
    b->byte_array[1] = 0x78;
    b->byte_array[2] = 0x36;
    b->byte_array[3] = 0x0f;
    b->byte_array[4] = 0x01;
    b->size = 5;

    //test polynomial scalar multiplication
    Polynomial *output = new_poly();
    gf_poly_scalar(a, output, 4);
    
    //polynomial addition
    gf_poly_add(a, b, output);
    
    //polynomial multiplication
    gf_poly_mult(a, b, output);
    
    //polynomial division
    gf_poly_div(a, b, output);
    
    //polynomial evaluation
    uint8_t out = gf_poly_eval(a, 4);
    
    //creating the RS generator polynomial
    printf("All test pass\n");
    free_poly(a);
    free_poly(b);
    return 0;
}

int main(){
    test_galois_field();
    return 0;
}
