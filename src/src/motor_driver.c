#include "motor_driver.h"
#include "IO_Functions.h"
#include "pwm_module.h"

#include <stdbool.h>
#include <math.h>

struct MOTOR_Driver{
    //Generic Motor Driver params -- for info that is generic to any motor being driven
    float max_voltage;
    bool motor_dir;

    //Implementation specific datamembers.
    //In this case it uses 2 pins to choose direction, and one pin for the PWM output.

    //It's possible that this could be changed to be a HAL for an even lower level hardware motor driver. 
    PIN_Channel output_pin;

    PORT_Channel dir_pin_1_port;
    PIN_Channel dir_pin_1;

    PORT_Channel dir_pin_2_port;
    PIN_Channel dir_pin_2;

    PWM_Channel pwm_sel;


    
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

MOTOR_Handle MOTOR_Init(float max_voltage, PORT_Channel output_pin_port, PIN_Channel output_pin,
                        PORT_Channel dir_pin_1_port, PIN_Channel dir_pin_1, PORT_Channel dir_pin_2_port, PIN_Channel dir_pin_2, PWM_Channel pwm_sel){
    
    //Initializes data members
    mtr_drv1.motor_dir = DIR_1;
    mtr_drv1.max_voltage = max_voltage;

    mtr_drv1.output_pin = output_pin;
    
    mtr_drv1.dir_pin_1_port = dir_pin_1_port;
    mtr_drv1.dir_pin_1 = dir_pin_1;

    mtr_drv1.dir_pin_1_port = dir_pin_2_port;
    mtr_drv1.dir_pin_2 = dir_pin_2;

    mtr_drv1.pwm_sel = pwm_sel;

    //Inits directional pins to defaults state
    IO_setPinOut(mtr_drv1.dir_pin_1_port, mtr_drv1.dir_pin_1);
    IO_setPinOut(mtr_drv1.dir_pin_2_port, mtr_drv1.dir_pin_2);
    IO_setPinHigh(mtr_drv1.dir_pin_1_port, mtr_drv1.dir_pin_1);
    IO_setPinLow(mtr_drv1.dir_pin_2_port,  mtr_drv1.dir_pin_2);

    return &mtr_drv1;
}

bool MOTOR_getDirection(MOTOR_Handle motor){
    return motor->motor_dir;
}

void MOTOR_setDirection(MOTOR_Handle motor, bool direction){
    motor->motor_dir = direction;
    
    if(motor->motor_dir == DIR_1){
        IO_setPinHigh(PORT_A, motor->dir_pin_1);
        IO_setPinLow(PORT_A,  motor->dir_pin_2);
    }
    //DIR_2
    else {
        IO_setPinLow(PORT_A,  motor->dir_pin_1);
        IO_setPinHigh(PORT_A, motor->dir_pin_2);
        
    }

}

void MOTOR_setOutput(MOTOR_Handle motor, float motor_voltage){
    
    //Set Direction
    MOTOR_setDirection(motor, signbit(motor_voltage));

    //Set Output
    PWM_setHighTime(((uint16_t)((fabs(motor_voltage)/motor->max_voltage) * (float)PWM_getPeriod(motor->pwm_sel)) + 0.5));
}