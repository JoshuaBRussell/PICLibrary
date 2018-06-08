
////////////////////////////////////////////////////////////////////
//
//  Example PID Motor Controller.
//
////////////////////////////////////////////////////////////////////
#include "xc.h"
#include "IO_Functions.h"
#include "IO_Defines.h"
#include "timer_functions.h"
#include "timer_defines.h"
#include "PID.h"
#include "pwm_module.h"
#include "encoders.h"
#include "motor_driver.h"

#pragma config ICS = PGD1               // ICD Communication Channel Select bits (Communicate on PGEC1 and PGED1)
#pragma config JTAGEN = OFF             // JTAG Enable bit (JTAG is disabled)

// FPOR
#pragma config ALTI2C1 = OFF            // Alternate I2C1 pins (I2C1 mapped to SDA1/SCL1 pins)
#pragma config ALTI2C2 = OFF            // Alternate I2C2 pins (I2C2 mapped to SDA2/SCL2 pins)
#pragma config WDTWIN = WIN25           // Watchdog Window Select bits (WDT Window is 25% of WDT period)

// FWDT
#pragma config WDTPOST = PS32768        // Watchdog Timer Postscaler bits (1:32,768)
#pragma config WDTPRE = PR128           // Watchdog Timer Prescaler bit (1:128)
#pragma config PLLKEN = OFF             // PLL Lock Enable bit (Clock switch will not wait for the PLL lock signal.)
#pragma config WINDIS = OFF             // Watchdog Timer Window Enable bit (Watchdog Timer in Non-Window mode)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable bit (Watchdog timer enabled/disabled by user software)

// FOSC
#pragma config POSCMD = NONE            // Primary Oscillator Mode Select bits (Primary Oscillator disabled)
#pragma config OSCIOFNC = OFF           // OSC2 Pin Function bit (OSC2 is clock output)
#pragma config IOL1WAY = ON             // Peripheral pin select configuration (AlHIGH only one reconfiguration)
#pragma config FCKSM = CSDCMD           // Clock Switching Mode bits (Both Clock switching and Fail-safe Clock Monitor are disabled)

// FOSCSEL
#pragma config FNOSC = FRC              // Oscillator Source Selection (Internal Fast RC (FRC))
#pragma config IESO = OFF                // Two-speed Oscillator Start-up Enable bit (Start up device with FRC, then switch to user-selected oscillator source)

// FGS
#pragma config GWRP = OFF               // General Segment Write-Protect bit (General Segment may be written)
#pragma config GCP = OFF                // General Segment Code-Protect bit (General Segment Code protect is Disabled)

#define MOTOR_VOLTAGE 6.0
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

    //Setup Sample Timer
    setPrescaler(TIMER_3, PRE64);
    setPeriodTicks(TIMER_3, ms_to_ticks(10, 64));
    clearTimer3IntFlag();
    setTimer3IntPriority(1);
    setTimer3IntEn(true);

    //Configure PID Settings
    PID_Init(&motor_PID);
    setCoeff(&motor_PID, 0.0, 0.0, 0.0);
    setDeltaT(&motor_PID, 0.01);
    setSetpoint(&motor_PID, 300.0);

    //Makes sure that Timer2 is Off(used for PWM)
    T2CONbits.TON = 0;

    PWM_Init(7, usPeriod);
    setHighTime(0); //Start PWM w/ zero high time
    
    startPWM();

    turnTimerOn(TIMER_3);

    //Infinite Loop
    while(1){

    }

}

void _ISR _T3Interrupt(void){
    togglePin(1, 15);

    // //Get Sensor Reading
    // float motor_speed = getEncoder_Rads_per_sec(0.01);

    // //Compute Output
    // float control_signal = Compute(&motor_PID, motor_speed);

    //Set Output
    MOTOR_setOutput(&motor1, 3.0);
    
    togglePin(1, 15);
    clearTimer3IntFlag();
}