#ifndef _ENCODERS_H
#define _ENCODERS_H

#include "stdint.h"
#include "stdbool.h"
#include "IO_Functions.h"

/*----------------------------------------------------------------------------//
//Defines                                                                     //
/*----------------------------------------------------------------------------*/


typedef struct{

    //Paramaters
    PORT_Channel port;
    PIN_Channel pinA;
    PIN_Channel pinB;

    volatile long prev_enc_count;
    volatile long enc_count;
    unsigned int enc_state;

    float TICKS_PER_REV;
    float TICKS_TO_RADS_SF;

} ENC;

/*----------------------------------------------------------------------------//
// Functions for using a Quad Encoder with interrupts. Currently uses x4
// Encoding.   
//----------------------------------------------------------------------------*/

//Initialize Encoders. Currently Pins must be on the same port and must be consecutive 
//to one another (e.g. pins 5/6). 
void ENC_setupEncoders(ENC* enc_obj, PORT_Channel port, PIN_Channel pinA, PIN_Channel pinB,
float TICKS_PER_REV);


//Getters
PORT_Channel ENC_getENCPort(ENC* enc);
PIN_Channel ENC_getENCPinA(ENC* enc);
PIN_Channel ENC_getENCPinB(ENC* enc);
long ENC_getENCCount(ENC* enc);
long ENC_getPrevENCCount(ENC* enc);
unsigned int ENC_getENCState(ENC* enc);
float ENC_getENCVel(float delta_t_sec);


bool isISRCalled();

#endif // _ENCODERS_H
