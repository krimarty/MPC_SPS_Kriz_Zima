#ifndef CORRELATION_H_
#define CORRELATION_H_


#include "stdint.h"
#include <msp430.h>
#include <stdbool.h>

struct planes {
    uint8_t iLenght[20];
    uint8_t iNumber;
};


#define SCALE 20 // defines scale instead of 1 because of missing FPU
#define RANGE 20 // defines how many last samples
#define TRESHOLD 17 // treshold to detect new lap

bool auto_correlation(uint16_t data_size, int8_t *data, int8_t *output);
struct planes find_planes(uint16_t data_size, int8_t *data);

#endif /* CORRELATION_H_ */
