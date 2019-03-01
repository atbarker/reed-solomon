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

    //test polynomial scalar multiplication
    
    //polynomial addition
    
    //polynomial multiplication
    
    //polynomial division
    
    //polynomial evaluation
    
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
