#ifndef _IO_FUNCTIONS_H
#define _IO_FUNCTIONS_H

#include "IO_Defines.h"
#include <stdint.h>

//Sets a ports pin to output
void setPinOut(uint16_t port, uint16_t pin);

//Sets a ports pin high
void setPinHigh(uint16_t port, uint16_t pin);

void togglePin(uint16_t port, uint16_t pin);

#endif // _IO_FUNCTIONS_H
