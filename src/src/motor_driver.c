#include "motor_driver.h"
#include "IO_Functions.h"

#include <stdbool.h>

void MOTOR_Init(MOTOR* motor, float max_voltage, uint16_t output_pin, uint16_t dir_pin_1, uint16_t dir_pin_2){
    
    //Initializes data members
    motor->motor_dir = DIR_1;
    motor->dir_pin_1 = dir_pin_1;
    motor->dir_pin_2 = dir_pin_2;

    //Inits directional pins to defaults state
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

    if(motor->motor_dir == DIR_2){
        setPinLow(0,  motor->dir_pin_1);
        setPinHigh(0, motor->dir_pin_2);
        
    }

}

void MOTOR_setOutput(float motor_voltage){

}