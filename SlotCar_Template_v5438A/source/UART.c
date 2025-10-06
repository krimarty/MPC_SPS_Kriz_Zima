/*
 * UART.c
 *
 *  Created on: 28. 9. 2021
 *      Author: Ondra
 */


#include "include/UART.h"

void UART_init(void)
{
    UCA1CTL1 = UCSWRST; //UCA1 softwarovy reset -> ON

    P5SEL |= BIT7;
    P5SEL |= BIT6;

    P5OUT &= ~BIT7;
    P5OUT &= ~BIT6;

    UCA1CTL1 |= UCSSEL__SMCLK; //nastaveni zdrojoveho frekvence SMCLK

   //UCA1BR0 = 0x34;           //16MHz / 19200 baud
   //UCA1BR1 = 0x00;
   //UCA1MCTL = 0x11;          //UCOS16 = 1 / UCBRFx = 1 -> dle nastaveni v tabulce datasheetu

   UCA1BR0 = 0x08;           //16MHz / 115200 baud
   UCA1BR1 = 0x00;
   UCA1MCTL = UCBRF_11 + UCOS16; //UCOS16 = 1 / UCBRFx = 11 -> dle nastaveni v tabulce datasheetu

   //UCA1BR0 = 0x10;           //16MHz / 9600 baud
   //UCA1BR1 = 0x00;
   //UCA1MCTL = (4 << 4) | 0xD6 | UCOS16; // UCBRF=4, UCBRS=0xD6, UCOS16=1

   UCA1CTL1 &= ~UCSWRST;     //UCA1 softwarovy reset -> OFF

   UART_tx_timer_init();

   UCA1IE |= UCRXIE;         //Enable USCI_A1 RX interrupt
}

void UART_tx_timer_init(void)
{
    TA1CCR0 = 12500 - 1;              // 250000 Hz / 20 Hz = 12500
    TA1CTL = TASSEL_2 | MC_1 | ID_3;  // SMCLK (16 MHz), /8 -> 2 MHz
    TA1EX0 = TAIDEX_7;                // další dělička /8 => celkem /64
    TA1CCTL0 = CCIE;                  // povolit přerušení
}


void UART_prepare_buffer_bin(volatile UART_tx_buffer_t* buf, int16_t* imu_data, uint8_t len)
{
    if(buf->buffer_empty == false)
        return;
    uint8_t idx = 0;

    buf->length = 0;

    uint8_t i;
    for (i = 0; i < len && (idx + 2 + 1) <= sizeof(buf->data); i++)
    {
        buf->data[idx++] = imu_data[i] & 0xFF;
        buf->data[idx++] = (imu_data[i] >> 8) & 0xFF;
    }

    buf->data[idx++] = 0xAA;

    buf->index = 0;

    __disable_interrupt();
    buf->length = idx;
    buf->buffer_empty = false;
    __enable_interrupt();
}






