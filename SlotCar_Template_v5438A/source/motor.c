/*
 * motor.c
 *
 *  Created on: 29. 9. 2020
 *      Author: dosedel
 */


#include "include/motor.h"

void go_forward()
{
    H_PHASE_FW();
    H_MODE1_ON();
    H_ENABLE_ON();
}
