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
    Pin_A0,
    Pin_A1,
    Pin_A2,
    Pin_A3,
    Pin_A4,
    Pin_A5,
    Pin_A6,
    Pin_A7,
    Pin_A8,
    Pin_A9,
    Pin_A10,
    Pin_A11,
    Pin_A12,
    Pin_A13,
    Pin_A14,
    Pin_A15,
    Pin_B0,
    Pin_B1,
    Pin_B2,
    Pin_B3,
    Pin_B4,
    Pin_B5,
    Pin_B6,
    Pin_B7,
    Pin_B8,
    Pin_B9,
    Pin_B10,
    Pin_B11,
    Pin_B12,
    Pin_B13,
    Pin_B14,
    Pin_B15
} Pin_Channel;

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
void setPinOut(uint16_t port, uint16_t pin);

//Sets a port's pin to input
void setPinIn(uint16_t port, uint16_t pin);

//Sets a port's pin high
void setPinHigh(uint16_t port, uint16_t pin);

//Sets a port's pin low
void setPinLow(uint16_t port, uint16_t pin);

//Toogle's a port's pin (H to L/L to H)
void togglePin(uint16_t port, uint16_t pin);

//Set's a pin to use the open drain configuration
void setPinOD(uint16_t port, uint16_t pin);

//Set's a pin's pullup resistor
void setPinPU(uint16_t port, uint16_t pin);

//Set's a pin's pulldown resistor
void setPinPD(uint16_t port, uint16_t pin);

//Reads a pins state
bool readPin(uint16_t port, uint16_t pin);


#endif // _IO_FUNCTIONS_H
