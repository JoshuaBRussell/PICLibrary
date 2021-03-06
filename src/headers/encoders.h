#ifndef _ENCODERS_H
#define _ENCODERS_H

#include "stdint.h"

/*----------------------------------------------------------------------------//
//Defines                                                                     //
/*----------------------------------------------------------------------------*/

#define TICKS_PER_REV 64.0
#define TICKS_TO_RADS_SF (6.283185/TICKS_PER_REV)

/*----------------------------------------------------------------------------//
// Functions for using a Quad Encoder with interrupts. Currently uses x4
// Encoding.   
//----------------------------------------------------------------------------*/

//Initialize Encoders. Currently Pins must be on the same port and must be consecutive 
//to one another (e.g. pins 5/6). 
void setupEncoders(uint16_t port, uint16_t pinA, uint16_t pinB);

//Returns the value of the current encoder count. 
int getEncoderCount(void);

float getEncoder_Rads_per_sec(float delta_t_sec);


#endif // _ENCODERS_H
