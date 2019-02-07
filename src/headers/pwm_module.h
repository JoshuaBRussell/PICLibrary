#ifndef _PWM_MODULE_H
#define _PWM_MODULE_H

#include "stdint.h"

void PWM_Init(uint16_t pin, uint16_t usPeriod);

void startPWM();

//Set Duty Cycle
void PWM_setHighTime(uint16_t usHigh);

uint16_t PWM_getPeriod();

#endif // _PWM_MODULE_H
