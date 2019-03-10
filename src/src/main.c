#include "xc.h"
#include "main.h"
#include "IO_Functions.h"
#include "timer_functions.h"
#include "pwm_module.h"
#include "stdint.h"
#include "motor_driver.h"

#define usPeriod 40
#define timeHigh1 1340
#define timeHigh2 2000


int main(){

    IO_setPinOut(PORT_B, PIN_B6);
    IO_setPinOut(PORT_B, PIN_B5);
    PWM_Init(7, usPeriod);
    MOTOR_Handle motor1 = MOTOR_Init(12.0, PORT_B, PIN_B7, PORT_B, PIN_B5, PORT_B, PIN_B6, PWM_0);


    //Output starts on first call
    //IO_togglePin(PORT_B, PIN_B5);
    //PWM_setHighTime(timeHigh1);
    MOTOR_setOutput(motor1, 3.5);
    //PWM_setScaledOutput(PWM_0, 0.5);

    //startPWM();
    
    while(1){
    //IO_togglePin(PORT_B, PIN_B5);
    }    




}