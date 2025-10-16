/*
 * LED.c
 *
 *  Created on: 24. 9. 2020
 *      Author: dosedel
 */

#include "include/LED.h"

void LED_init(void)
{
    P5DIR |= 0x30;  // P5.4 and P5.5 as output
    P4DIR |= 0xC0;  // P4.6 and P4.7 as output
}

void RGB_LED_init(void)
{
    P8DIR |= BIT0;  // RED led as output
    P7DIR |= BIT3;  // GREEN led as output
    P7DIR |= BIT2;  // BLUE led as output
}

void FR_on()
{
    LED_FL_OFF();
    LED_FR_ON();
    LED_RL_OFF();
    LED_RR_OFF();
}

void FL_on()
{
    LED_FL_ON();
    LED_FR_OFF();
    LED_RL_OFF();
    LED_RR_OFF();
}

void RR_on()
{
    LED_FL_OFF();
    LED_FR_OFF();
    LED_RL_OFF();
    LED_RR_ON();
}

void RL_on()
{
    LED_FL_OFF();
    LED_FR_OFF();
    LED_RL_ON();
    LED_RR_OFF();
}

void led_toggle(bool var)
{
    if (var)
    {
        LED_FL_ON();
        LED_FR_ON();
        LED_RL_OFF();
        LED_RR_OFF();
    }
    else {
        LED_FL_OFF();
        LED_FR_OFF();
        LED_RL_ON();
        LED_RR_ON();
    }
}


