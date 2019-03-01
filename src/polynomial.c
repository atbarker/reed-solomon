#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "polynomial.h"

Polynomial* init(uint8_t size, uint8_t offset, uint8_t length, uint8_t* byte_array){
    Polynomial *p = malloc(sizeof(Polynomial));
    p->size = size;
    p->offset = offset;
    p->length = length;
    p->byte_array = byte_array;
    return p;
}

int32_t append(Polynomial* p, uint8_t x){
    if(p->size + 1 <= p->length){
        p->byte_array[p->size + 1] = x;
	p->size++;
	return 0;
    }else{
        return -1;
    }
}

int32_t reset(Polynomial* p){
    if(p){
        p->size = 0;
        p->offset = 0;
        return 0;
    }else{
        return -1;
    }
}

int32_t set(Polynomial* p, uint8_t* byte_seq, uint8_t size, uint8_t offset){
    if(p && byte_seq){
        p->byte_array = byte_seq;
	p->size = size;
	p->offset = offset;
	return 0;
    }else{
        return -1;
    }
}

int32_t copy(Polynomial* src, Polynomial* dest){
    if(src && dest){
        dest->size = src->size;
	dest->offset = src->offset;
	dest->length = src->length;
        memcpy(dest->byte_array, dest->byte_array, dest->length);
	return 0;
    }else{
        return -1;
    }
}

uint8_t length(Polynomial* p){
    return p->length;
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
