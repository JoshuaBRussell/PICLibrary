#ifndef _MOTOR_DRIVER_H_
#define _MOTOR_DRIVER_H_

/*----------------------------------------------------------------------------//
// Motor Driver Interface: Used to interact with a motor.
//----------------------------------------------------------------------------*/

#include <stdint.h>
#include <stdbool.h>
#include <IO_Functions.h>

/*----------------------------------------------------------------------------//
// Defines
//----------------------------------------------------------------------------*/

//Direction defines
#define DIR_1 false
#define DIR_2 true


//
typedef struct MOTOR_Driver* MOTOR_Handle;



/*----------------------------------------------------------------------------//
// Functions for manipulating a motor.
//----------------------------------------------------------------------------*/

//----Motor Init----//
// max_voltage - max output voltage to the motor
// output_pin - pin used to send PWM output to the motor
// dir_pin_1/2 - pins used to set the direction the motor spins (These pins must be set as output)
MOTOR_Handle MOTOR_Init(float max_voltage, PIN_Channel output_pin, PIN_Channel dir_pin_1, PIN_Channel dir_pin_2);

//Gets the direction a motr is spinning. (DIR_1 or DIR_2)
bool MOTOR_getDirection(MOTOR_Handle motor);

//Sets the dir a motor is spins (DIR_1 or DIR_2)
void MOTOR_setDirection(MOTOR_Handle motor, bool dir);

//Takes sign and magnitude of input and applies it to motor driver electronics.
//In case of using PWM, sets pulse width proportional to desired motor voltage
void MOTOR_setOutput(MOTOR_Handle motor, float motor_voltage);

#endif // _MOTOR_DRIVER_H_
