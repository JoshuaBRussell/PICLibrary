#include "motor_driver.h"
#include "IO_Functions.h"
#include "pwm_module.h"

#include <stdbool.h>
#include <math.h>

//Helper function that converts a float input with an expected float max value to a proportional high time 
//for the PWM. 
static uint16_t getPWM_High_Time_from_Float(float input, float max_input, uint16_t us_max_period){
    return ((uint16_t)((input/max_input) * (float)us_max_period) + 0.5);
}

void MOTOR_Init(MOTOR* motor, float max_voltage, uint16_t output_pin, uint16_t dir_pin_1, uint16_t dir_pin_2){
    
    //Initializes data members
    motor->motor_dir = DIR_1;
    motor->max_voltage = max_voltage;
    motor->output_pin = output_pin;
    motor->dir_pin_1 = dir_pin_1;
    motor->dir_pin_2 = dir_pin_2;

    //Inits directional pins to defaults state
    setPinOut(0, motor->dir_pin_1);
    setPinOut(0, motor->dir_pin_2);
    setPinHigh(0, motor->dir_pin_1);
    setPinLow(0,  motor->dir_pin_2);
}

bool MOTOR_getDirection(MOTOR* motor){
    return motor->motor_dir;
}

void MOTOR_setDirection(MOTOR* motor, bool direction){
    motor->motor_dir = direction;
    
    if(motor->motor_dir == DIR_1){
        setPinHigh(0, motor->dir_pin_1);
        setPinLow(0,  motor->dir_pin_2);
    }
    //DIR_2
    else {
        setPinLow(0,  motor->dir_pin_1);
        setPinHigh(0, motor->dir_pin_2);
        
    }

}

void MOTOR_setOutput(MOTOR* motor, float motor_voltage){
    
    //Set Direction
    MOTOR_setDirection(motor, signbit(motor_voltage));

    //Set Output
    setHighTime(((uint16_t)((motor_voltage/motor->max_voltage) * (float)PWM_getPeriod()) + 0.5));//getPWM_High_Time_from_Float(motor_voltage, motor->max_voltage, PWM_getPeriod()));
}