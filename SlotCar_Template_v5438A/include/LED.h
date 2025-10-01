/*
 * LED.h
 *
 *  Created on: 24. 9. 2020
 *      Author: dosedel
 */

#ifndef LED_H_
#define LED_H_


#include "stdint.h"
#include <msp430.h>
// macros definition
// LED ports definition
#define LED_FL_PORT  P4OUT
#define LED_FR_PORT  P4OUT
#define LED_RL_PORT  P5OUT
#define LED_RR_PORT  P5OUT
// LED pins definition
#define LED_FL_PIN  0x40
#define LED_FR_PIN  0x80
#define LED_RL_PIN  0x10
#define LED_RR_PIN  0x20

// RGB LED definition
#define RGB_RED_PORT    P8OUT
#define RGB_GREEN_PORT  P7OUT
#define RGB_BLUE_PORT   P7OUT

#define RGB_RED_PIN     BIT0
#define RGB_GREEN_PIN   BIT3
#define RGB_BLUE_PIN    BIT2

/* LEDs control:
 * F = front, R = rear
 * L = left, R = right
 */

#define LED_FL_ON() (LED_FL_PORT |= LED_FL_PIN)
#define LED_FL_OFF() (LED_FL_PORT &= ~LED_FL_PIN)

#define LED_FR_ON() (LED_FR_PORT |= LED_FR_PIN)
#define LED_FR_OFF() (LED_FR_PORT &= ~LED_FR_PIN)

#define LED_RL_ON() (LED_RL_PORT |= LED_RL_PIN)
#define LED_RL_OFF() (LED_RL_PORT &= ~LED_RL_PIN)

#define LED_RR_ON() (LED_RR_PORT |= LED_RR_PIN)
#define LED_RR_OFF() (LED_RR_PORT &= ~LED_RR_PIN)

// RGB LEDs control
#define RGB_RED_ON() (RGB_RED_PORT |= RGB_RED_PIN)
#define RGB_RED_OFF() (RGB_RED_PORT &= ~RGB_RED_PIN)

#define RGB_GREEN_ON() (RGB_GREEN_PORT |= RGB_GREEN_PIN)
#define RGB_GREEN_OFF() (RGB_GREEN_PORT &= ~RGB_GREEN_PIN)

#define RGB_BLUE_ON() (RGB_BLUE_PORT |= RGB_BLUE_PIN)
#define RGB_BLUE_OFF() (RGB_BLUE_PORT &= ~RGB_BLUE_PIN)


// functions prototypes
void LED_init(void);
void RGB_LED_init(void);

// variables

#endif /* LED_H_ */
