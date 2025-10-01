/*
 * main.h
 *
 *  Created on: 16. 9. 2020
 *      Author: dosedel
 */

#ifndef MAIN_H_
#define MAIN_H_

// macros definition
#define CLOCK   1

// Sensor power port
#define SENSOR_POWER_PORT       P2OUT
#define SENSOR_POWER_DIRPORT    P2DIR
// Sensor power pins definition
#define  SENSOR_POWER_PIN    BIT1

#define  SENSOR_POWER_OFF() (SENSOR_POWER_PORT |= SENSOR_POWER_PIN)          // turn OFF sensor power
#define  SENSOR_POWER_ON() (SENSOR_POWER_PORT &= ~SENSOR_POWER_PIN)        // turn ON sensor power
// functions prototypes

// variables

#endif /* MAIN_H_ */
