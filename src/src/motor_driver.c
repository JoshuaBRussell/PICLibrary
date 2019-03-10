#include "motor_driver.h"
#include "IO_Functions.h"
#include "pwm_module.h"

#include <stdbool.h>
#include <math.h>

struct MOTOR_Driver{
    float max_voltage;
    
    PIN_Channel output_pin;
    PIN_Channel dir_pin_1;
    PIN_Channel dir_pin_2;

    bool motor_dir;
    
};

static struct MOTOR_Driver mtr_drv1; //The motor driver definition. 
/*----------------------------------------------------------------------------//
// PID Implementation 
//----------------------------------------------------------------------------*/

//Helper function that converts a float input with an expected float max value to a proportional high time 
//for the PWM. 
static uint16_t getPWM_High_Time_from_Float(float input, float max_input, uint16_t us_max_period){
    return ((uint16_t)((input/max_input) * (float)us_max_period) + 0.5);
}

MOTOR_Handle MOTOR_Init(float max_voltage, PIN_Channel output_pin, PIN_Channel dir_pin_1, PIN_Channel dir_pin_2){
    
    //Initializes data members
    mtr_drv1.motor_dir = DIR_1;
    mtr_drv1.max_voltage = max_voltage;
    mtr_drv1.output_pin = output_pin;
    mtr_drv1.dir_pin_1 = dir_pin_1;
    mtr_drv1.dir_pin_2 = dir_pin_2;

    //Inits directional pins to defaults state
    IO_setPinOut(0, mtr_drv1.dir_pin_1);
    IO_setPinOut(0, mtr_drv1.dir_pin_2);
    IO_setPinHigh(0, mtr_drv1.dir_pin_1);
    IO_setPinLow(0,  mtr_drv1.dir_pin_2);

    return &mtr_drv1;
}

bool MOTOR_getDirection(MOTOR_Handle motor){
    return motor->motor_dir;
}

void MOTOR_setDirection(MOTOR_Handle motor, bool direction){
    motor->motor_dir = direction;
    
    if(motor->motor_dir == DIR_1){
        IO_setPinHigh(0, motor->dir_pin_1);
        IO_setPinLow(0,  motor->dir_pin_2);
    }
    //DIR_2
    else {
        IO_setPinLow(0,  motor->dir_pin_1);
        IO_setPinHigh(0, motor->dir_pin_2);
        
    }

}

void MOTOR_setOutput(MOTOR_Handle motor, float motor_voltage){
    
    //Set Direction
    MOTOR_setDirection(motor, signbit(motor_voltage));

    //Set Output
    PWM_setHighTime(((uint16_t)((fabs(motor_voltage)/motor->max_voltage) * (float)PWM_getPeriod(PWM_0)) + 0.5));//getPWM_High_Time_from_Float(motor_voltage, motor->max_voltage, PWM_getPeriod()));
}