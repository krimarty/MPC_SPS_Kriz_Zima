/*
 * LED.c
 *
 *  Created on: 24. 9. 2020
 *      Author: dosedel
 */

#include "include/LED.h"

void LED_init(void){
    P5DIR |= 0x30;  // P5.4 and P5.5 as output
    P4DIR |= 0xC0;  // P4.6 and P4.7 as output
}

void RGB_LED_init(void){
    P8DIR |= BIT0;  // RED led as output
    P7DIR |= BIT3;  // GREEN led as output
    P7DIR |= BIT2;  // BLUE led as output
}

void led_toggle(bool var){
    if (var){
        LED_FL_ON();
        LED_FR_ON();
        LED_RL_OFF();
        LED_RR_OFF();
    }
    else{
        LED_FL_OFF();
        LED_FR_OFF();
        LED_RL_ON();
        LED_RR_ON();
    }
}

void blink_first_round(bool bit){
    if(bit){
        LED_FL_ON();
        LED_FR_ON();
        LED_RL_ON();
        LED_RR_ON();
        __delay_cycles(16000000)
        LED_FL_OFF();
        LED_FR_OFF();
        LED_RL_OFF();
        LED_RR_OFF();
        __delay_cycles(16000000)
    }
    // jinak by nemel delat nic a led se ridi pomoci jinych funkci
}
