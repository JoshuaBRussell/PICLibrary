#ifndef _IO_DEFINES_H_
#define _IO_DEFINES_H_


#include <stdint.h>
#define NUM_PORTS 2
#define IO_PINS_PER_PORT 16
#define TOTAL_IO_PINS 32

#define INPUT 1
#define OUTPUT 0

#define HIGH 1
#define LOW 0


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


typedef struct {
    unsigned Pin:5;       //Pin Number
    unsigned Direction:1; //Input  | Output
    unsigned State:1;     //  HIGH | LOW
} PIN_CONFIG;

#endif
