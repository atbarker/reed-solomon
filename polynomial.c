#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "polynomial.h"

Polynomial* init(uint8_t size, uint8_t length, uint8_t* byte_array){
    Polynomial *p = malloc(sizeof(Polynomial));
    p->size = size;
    p->array_length = length;
    p->byte_array = byte_array;
    return p;
}

Polynomial* new_poly(){
    Polynomial *p = malloc(sizeof(Polynomial));
    p->byte_array = malloc(256);
    p->size = 0;
    p->array_length = 256;
    return p;
}

//TODO:Something wrong here
void free_poly(Polynomial *p){
    free(p->byte_array);
    free(p);
}

int32_t append(Polynomial* p, uint8_t x){
    if(p->size + 1 <= p->array_length){
        p->byte_array[p->size + 1] = x;
	p->size++;
	return 0;
    }else{
        return -1;
    }
}

int32_t reset(Polynomial* p){
    if(p){
        memset(p->byte_array, 0, p->size);
        return 0;
    }else{
        return -1;
    }
}

int32_t set(Polynomial* p, uint8_t* byte_seq, uint8_t size){
    if(p && byte_seq){
        p->byte_array = byte_seq;
	p->size = size;
	return 0;
    }else{
        return -1;
    }
}

int32_t poly_copy(Polynomial* src, Polynomial* dest){
    if(src && dest){
        dest->size = src->size;
	dest->array_length = src->array_length;
        memcpy(dest->byte_array, dest->byte_array, dest->array_length);
	return 0;
    }else{
        return -1;
    }
}

uint8_t length(Polynomial* p){
    return p->array_length;
}

uint8_t size(Polynomial* p){
    return p->size;
}

uint8_t value_at(Polynomial* p, uint32_t i){
    if(i <= p->size){
        return p->byte_array[i];
    }else{
        return 0;
    }
}

uint8_t* mem(Polynomial* p){
    return p->byte_array;
}

void print_polynomial(Polynomial* p){
    int i;
    printf("Polynomial size: %d\n", p->size);
    printf("[");
    for(i = 0; i < p->size; i++){
        printf(" %d, ", p->byte_array[i]);
    }
    printf("]\n");
}
