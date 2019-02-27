#ifndef RS_H
#define RS_H

#include <stdint.h>

uint8_t init_tables(uint16_t prim_poly);

uint8_t gf_add(uint8_t x, uint8_t y);

#endif
