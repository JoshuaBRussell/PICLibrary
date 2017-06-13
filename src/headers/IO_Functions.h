#ifndef _IO_FUNCTIONS_H
#define _IO_FUNCTIONS_H

#include "IO_Defines.h"
#include <stdint.h>

/*----------------------------------------------------------------------------//
// Functions for manipulating GPIO pins. Input params are assumed to be valid.
// NOTE: No bounds checking is performed! (That may change at a later date.)
//----------------------------------------------------------------------------*/

//Sets a port's pin to output
void setPinOut(uint16_t port, uint16_t pin);

//Sets a port's pin high
void setPinHigh(uint16_t port, uint16_t pin);

//Sets a port's pin low
void setPinLow(uint16_t port, uint16_t pin);

//Toogle's a port's pin (H to L/L to H)
void togglePin(uint16_t port, uint16_t pin);

#endif // _IO_FUNCTIONS_H
