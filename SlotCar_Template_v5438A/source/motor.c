/*
 * motor.c
 *
 *  Created on: 29. 9. 2020
 *      Author: dosedel
 */


#include "include/motor.h"

void motor_init()
{
    P10DIR |= H_MODE1_PIN;
    P10DIR |= H_PHASE_PIN;
    motor_pwm_init();
}

void motor_pwm_init()
{
    // Map timer to enable pin
    P8DIR |= H_ENABLE_PIN;   
    P8SEL |= H_ENABLE_PIN;  

    // PWM freq settings 16000000/25000 = 640
    TA0CCR0 = PWM_COUNTER - 1;

    // PWM mode : PWM Reset/Set
    TA0CCTL4 = OUTMOD_7;

    //Duty 0%
    TA0CCR4 = 0;

    // Timer start
    TA0CTL = TASSEL_2 | MC_1;
}

void motor_duty(uint8_t duty)
{
    if (duty > 100) duty = 100;
    TA0CCR4 = ((uint32_t)(TA0CCR0 + 1) * duty) / 100;
}


void go_forward(uint8_t duty)
{
    // Set dir pin to forward
    H_PHASE_RV();

    // Hard stopping
    H_MODE1_ON();
    
    // Set duty on enable pin
    motor_duty(duty);
}

