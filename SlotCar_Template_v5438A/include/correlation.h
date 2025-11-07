#ifndef CORRELATION_H_
#define CORRELATION_H_


#include "stdint.h"
#include <msp430.h>

#define SCALE 100 // defines scale instead of 1 because of missing FPU
#define RANGE 20 // defines how many last samples
#define TRESHOLD 60 // treshold to detect new lap

void auto_correlation(uint16_t data_size, int8_t *data, int8_t *output);

#endif /* CORRELATION_H_ */
