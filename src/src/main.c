#include "xc.h"
#include "main.h"
#include "clock.h"
#include "IO_Functions.h"
#include "timer_functions.h"
#include "pwm_module.h"
#include "stdint.h"
#include "motor_driver.h"

#define usPeriod 40
#define timeHigh1 1
#define timeHigh2 2000


int main(){
    setup_FRC_w_PLL();

    IO_setPinOut(PORT_B, PIN_B6);
    // IO_setPinOut(PORT_B, PIN_B5);

    //Setup peripherals for PWM. 
    IO_setPinOut(PORT_B, PIN_B7);
    SET_PWM_TO_RB7();//TODO: make it mappable to any pin
    setPrescaler(TIMER_2, PRE1);
    PWM_Init(7, usPeriod);
    MOTOR_Handle motor1 = MOTOR_Init(40.0, PORT_B, PIN_B7, PORT_B, PIN_B5, PORT_B, PIN_B6, PWM_0);

    MOTOR_setOutput(motor1, 15.0);

    while(1){};



}