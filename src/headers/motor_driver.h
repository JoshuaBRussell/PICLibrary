#ifndef _MOTOR_DRIVER_H_
#define _MOTOR_DRIVER_H_


#include <stdint.h>
#include <stdbool.h>


//Direction defines
#define DIR_1 false
#define DIR_2 true


//Motor Object
typedef struct{
    float max_voltage;
    
    uint16_t output_pin;
    uint16_t dir_pin_1;
    uint16_t dir_pin_2;

    bool motor_dir;
    
} MOTOR;

//----Motor Init----//
// max_voltage - max output voltage to the motor
// output_pin - pin used to send PWM output to the motor
// dir_pin_1/2 - pins used to set the direction the motor spins (These pins must be set as output)

void MOTOR_Init(MOTOR* motor, float max_voltage, uint16_t output_pin, uint16_t dir_pin_1, uint16_t dir_pin_2);


bool MOTOR_getDirection(MOTOR* motor);

void MOTOR_setDirection(MOTOR* motor, bool dir);

//Takes sign and magnitude of input and applies it to motor driver electronics
void MOTOR_setOutput(MOTOR* motor, float motor_voltage);

#endif // _MOTOR_DRIVER_H_
