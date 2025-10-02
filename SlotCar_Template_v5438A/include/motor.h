/*
 * motor.h
 *
 *  Created on: 29. 9. 2020
 *      Author: dosedel
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "stdint.h"
#include <msp430.h>

// macros definition
// H_Bridge port definition
#define H_MODE1_PORT  P10OUT     // break
#define H_ENABLE_PORT P8OUT     // in
#define H_PHASE_PORT  P10OUT     // direction

// H_Bridge pins definition
#define H_MODE1_PIN    BIT2
#define H_ENABLE_PIN   BIT4
#define H_PHASE_PIN    BIT1


#define H_MODE1_ON() (H_MODE1_PORT |= H_MODE1_PIN)      //hard stopping
#define H_MODE1_OFF() (H_MODE1_PORT &= ~H_MODE1_PIN)    //soft stopping


#define H_ENABLE_ON() (H_ENABLE_PORT |= H_ENABLE_PIN)   //go
#define H_ENABLE_OFF() (H_ENABLE_PORT &= ~H_ENABLE_PIN) //stop


#define H_PHASE_RV() (H_PHASE_PORT |= H_PHASE_PIN)      //direction backward
#define H_PHASE_FW() (H_PHASE_PORT &= ~H_PHASE_PIN)     //direction forward

#define PWM_COUNTER 640 // 16000000/25000 where 25000 kHz is pwm freq

void motor_init();
void motor_pwm_init();
void motor_duty(uint8_t duty);
void go_forward(uint8_t duty);


#endif /* MOTOR_H_ */
