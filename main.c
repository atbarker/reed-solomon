#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <syscall.h>
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
    uint8_t result[5] = {65, 119, 0, 119, 65};
    gf_poly_add(a, b, output);
    for(int i = 0; i < output->size; i++){
        if(output->byte_array[i] != result[i]){
            printf("Polynomial addition failed\n");
	    return -1;
	}
    }
    
    //polynomial multiplication
    uint8_t result_mul[9] = {64, 159, 165, 46, 0, 46, 165, 159, 64};
    gf_poly_mult(a, b, output);
    for(int i = 0; i < output->size; i++){
        if(output->byte_array[i] != result_mul[i]){
            printf("Polynomial multiplication failed\n");
            return -1;
        }
    }
    
    //polynomial division
    /*uint8_t result_div[1] = {192};
    gf_poly_div(a, b, output);
    for(int i = 0; i < output->size; i++){
        if(output->byte_array[i] != result_div[i]){
            printf("Polynomial division failed\n");
            return -1;
        }
    }*/
    
    //polynomial evaluation
    uint8_t out = gf_poly_eval(a, 4);
    
    printf("All test pass\n");
    free_poly(a);
    free_poly(b);
    return 0;
}

int test_multiplication_performance(){
    clock_t start, end;
    double cpu_time_used;
    

    start = clock();
    gf_mult(0b10001001, 0b00101010, 0x11d);
    end = clock();
    printf("Time to multiply %f\n", ((double) (end - start)));

    start = clock();
    gf_mult_table(0b10001001, 0b00101010);
    end = clock();
    printf("Time to multiply with lookup tables %f\n", ((double) (end - start)));

    return 0;
}

int test_encoding(){
    //uint8_t data[16] = {0x40, 0xd2, 0x75, 0x47, 0x76, 0x17, 0x32, 0x06, 0x27, 0x26, 0x96, 0xc6, 0xc6, 0x96, 0x70, 0xec};
    uint8_t parity[32];
    uint8_t data[223];
    uint8_t output[26];
    uint8_t errors[1] = {0};
    clock_t start, end;
    rs_generator_poly(32);

    syscall(SYS_getrandom, data, 223, 0);

    for(int i = 0; i < 16; i++){
        printf("%d, ", data[i]);
    }
    printf("\n");
    

    start = clock();
    //for(int i = 0; i < 134; i++){
        encode(data, 16, parity, 10);
    //}
    end = clock();
    printf("Time to encode %f\n", ((double) (end - start))/CLOCKS_PER_SEC);

    printf("[");
    for(int i = 0; i < 10; i++){
        printf("%d, ", parity[i]);
    }
    printf("]\n");
   
    data[0] = 0;

    start = clock();
    //for(int i = 0; i < 134; i++){
        decode(data, parity, 16, 10, output, errors, 1);
    //}
    end = clock();
    printf("Time to decode %f\n", ((double) (end - start))/CLOCKS_PER_SEC);

    printf("[");
    for(int i = 0; i < 26; i++){
        printf("%d, ", output[i]);
    }
    printf("]\n");
    return 0;
}

int main(){
    //test_galois_field();
    test_multiplication_performance();
    test_encoding();
    return 0;
}
