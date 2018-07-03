////////////////////////////////////////////////////////////////////
//
//  Example PID Motor Controller.
//
////////////////////////////////////////////////////////////////////
#include "xc.h"
#include "main.h"
#include "IO_Functions.h"
#include "timer_functions.h"
#include "PID.h"
#include "pwm_module.h"
#include "encoders.h"
#include "motor_driver.h"
#include <limits.h>

#define MOTOR_VOLTAGE 12.0
#define DEBUG_PIN 15  //Port B Pin 15
#define MOTOR_OUTPUT_PIN 0 //Port B Pin 7 This is set by the PWM_Init
#define MOTOR_DIR_PIN_1 0  //Port A Pin 0
#define MOTOR_DIR_PIN_2 1  //Port A Pin 1

#define ENC_A_PIN 5 //Port B Pin 5
#define ENC_B_PIN 6 //Port B Pin 6

#define usPeriod 2000

PID motor_PID;
MOTOR motor1;

int main(){

    //Init Motor
    MOTOR_Init(&motor1, MOTOR_VOLTAGE, MOTOR_OUTPUT_PIN, MOTOR_DIR_PIN_1, MOTOR_DIR_PIN_2);

    //Init Motor Encoders
    setupEncoders(1, ENC_A_PIN, ENC_B_PIN);

    //Set Debug Pin
    setPinOut(1, DEBUG_PIN);
    setPinOut(1, 14);
    setPinOut(1, 13);

    //Setup Sample Timer
    setPrescaler(TIMER_3, PRE64);
    setPeriodTicks(TIMER_3, ms_to_ticks(10, 64));
    clearTimer3IntFlag();
    setTimer3IntPriority(1);
    setTimer3IntEn(true);

    //Configure PID Settings
    PID_Init(&motor_PID);
    setCoeff(&motor_PID, 0.2, 0.01, 0.0);
    setDeltaT(&motor_PID, 0.01);
    setOutputLimits(&motor_PID, -MOTOR_VOLTAGE, MOTOR_VOLTAGE);
    setSetpoint(&motor_PID, 450.0);

    //Makes sure that Timer2 is Off(used for PWM)
    T2CONbits.TON = 0;

    PWM_Init(7, usPeriod);
    
    startPWM();

    turnTimerOn(TIMER_3);
    
    while(1){

    }

}

void _ISR _T3Interrupt(void){
    togglePin(1, 15);

    //Get Sensor Reading
    float motor_speed = getEncoder_Rads_per_sec(0.01);
    
    //Compute Output
    float control_signal = Compute(&motor_PID, motor_speed);

    //Set Output
    MOTOR_setOutput(&motor1, control_signal);
    
    togglePin(1, 15);
    clearTimer3IntFlag();
}