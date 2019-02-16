#ifndef _IO_FUNCTIONS_H
#define _IO_FUNCTIONS_H

/*----------------------------------------------------------------------------//
// Input/Output Header: Contains defines and function declarations to control
// HIGH/LOW state of various pins and also read them. 
// Eventually will be used to set all different states of pins (e.g. set a pin 
// to be used as the UART data line, or set a pin as the PWM out.)
//----------------------------------------------------------------------------*/

#include <stdint.h>
#include <stdbool.h>

/*----------------------------------------------------------------------------//
// Defines
//----------------------------------------------------------------------------*/
#define NUM_PORTS 2
#define IO_PINS_PER_PORT 16
#define TOTAL_IO_PINS 32

#define INPUT 1
#define OUTPUT 0

#define HIGH 1
#define LOW 0


/*----------------------------------------------------------------------------//
// Enums
//----------------------------------------------------------------------------*/

//Enum for the various pins
typedef enum
{
    PIN_A0,
    PIN_A1,
    PIN_A2,
    PIN_A3,
    PIN_A4,
    PIN_A5,
    PIN_A6,
    PIN_A7,
    PIN_A8,
    PIN_A9,
    PIN_A10,
    PIN_A11,
    PIN_A12,
    PIN_A13,
    PIN_A14,
    PIN_A15,
    PIN_B0 = 0,
    PIN_B1,
    PIN_B2,
    PIN_B3,
    PIN_B4,
    PIN_B5,
    PIN_B6,
    PIN_B7,
    PIN_B8,
    PIN_B9,
    PIN_B10,
    PIN_B11,
    PIN_B12,
    PIN_B13,
    PIN_B14,
    PIN_B15
} PIN_Channel;

typedef enum {
    PORT_A,
    PORT_B
} PORT_Channel;

//Pin Configuration Struct
typedef struct {
    unsigned Pin:5;       //Pin Number
    unsigned Direction:1; //Input  | Output
    unsigned State:1;     //HIGH | LOW
} PIN_CONFIG;


/*----------------------------------------------------------------------------//
// Functions for manipulating GPIO pins. Input params are assumed to be valid.
// NOTE: No bounds checking is performed! (That may change at a later date.)
//----------------------------------------------------------------------------*/

//Configures GPIO Pins to a desired state.
//This can be done with all the supporting functions below, one step at a time.
void IO_Config(const PIN_CONFIG * config);

//Sets a port's pin to output
void IO_setPinOut(PORT_Channel port, PIN_Channel pin);

//Sets a port's pin to input
void IO_setPinIn(PORT_Channel port, PIN_Channel pin);

//Sets a port's pin high
void IO_setPinHigh(PORT_Channel port, PIN_Channel pin);

//Sets a port's pin low
void IO_setPinLow(PORT_Channel port, PIN_Channel pin);

//Toogle's a port's pin (H to L/L to H)
void IO_togglePin(PORT_Channel port, PIN_Channel pin);

//Set's a pin to use the open drain configuration
void IO_setPinOD(PORT_Channel port, PIN_Channel pin);

//Set's a pin's pullup resistor
void IO_setPinPU(PORT_Channel port, PIN_Channel pin);

//Set's a pin's pulldown resistor
void IO_setPinPD(PORT_Channel port, PIN_Channel pin);

//Reads a pins state
bool IO_readPin(PORT_Channel port, PIN_Channel pin);


#endif // _IO_FUNCTIONS_H
