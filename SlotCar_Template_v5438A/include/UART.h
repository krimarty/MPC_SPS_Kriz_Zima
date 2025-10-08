/*
 * UART.h
 *
 *
 *  Created on: 28. 9. 2021
 *      Author: Ondrej Matula
 */
#ifndef UART_H_
#define UART_H_

#include <stdio.h>
#include "stdint.h"
#include <stdbool.h>
#include <msp430.h>

#define UART_BUFFER_SIZE 50

typedef struct {
    uint8_t data[UART_BUFFER_SIZE];
    uint8_t length;
    uint8_t index;
    bool buffer_empty;
} UART_tx_buffer_t;

void UART_init(void);     //initialization and initiation communication -- default baud rate is 19600
void UART_tx_timer_init(void);
void UART_prepare_buffer_bin(volatile UART_tx_buffer_t* buf, int16_t* imu_data, uint8_t len);


#endif /* UART_H_ */
