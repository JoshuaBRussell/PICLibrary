#ifndef _IO_DEFINES_H_
#define _IO_DEFINES_H_

#include <stdint.h>
#define NUM_PORTS 2

#define INPUT 1
#define OUTPUT 0

#define HIGH 1
#define LOW 0

typedef enum
{
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
    unsigned Pin:4;       //Pin Number
    unsigned Direction:1; //Input  | Output
    unsigned State:1;     //  HIGH | LOW
} PIN_CONFIG;

const PIN_CONFIG IO_CONFIG_TABLE[] =
{
//   -Pin-       -Direction-     -Init State-   //
    {Pin_B0,     INPUT,          LOW},
    {Pin_B1,     INPUT,          LOW},
    {Pin_B2,     INPUT,          LOW},
    {Pin_B3,     INPUT,          LOW},
    {Pin_B4,     INPUT,          LOW},
    {Pin_B5,     INPUT,          LOW},
    {Pin_B6,     INPUT,          LOW},
    {Pin_B7,     INPUT,          LOW},
    {Pin_B8,     INPUT,          LOW},
    {Pin_B9,     INPUT,          LOW},
    {Pin_B10,    INPUT,          LOW},
    {Pin_B11,    INPUT,          LOW},
    {Pin_B12,    INPUT,          LOW},
    {Pin_B13,    INPUT,          LOW},
    {Pin_B14,    INPUT,          LOW},
    {Pin_B15,    OUTPUT,         HIGH},

};

#endif
