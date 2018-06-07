
////////////////////////////////////////////////////////////////////
//
//  Example using the Encoders. Outputs count value onto PWM output
//
////////////////////////////////////////////////////////////////////
#include "xc.h"
#include "IO_Functions.h"
#include "IO_Defines.h"
#include "timer_functions.h"
#include "timer_defines.h"
#include "encoders.h"
#include "pwm_module.h"

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


void _ISR _T3Interrupt(void){
    togglePin(1, 15);
    clearTimer3IntFlag();

    if(getEncoderCount() >= 0){
        setHighTime(getEncoderCount());
    }
    else {
        setHighTime(-1*getEncoderCount());
    }
    
}

int main(){
    setPinOut(1, 15);

    setupEncoders(1, 5, 6);


    setPrescaler(TIMER_3, PRE64);
    setPeriodTicks(TIMER_3, ms_to_ticks(10, 64));
    clearTimer3IntFlag();
    setTimer3IntPriority(1);
    setTimer3IntEn(true);

    turnTimerOn(TIMER_3);

    T2CONbits.TON = 0;

    PWM_Init(7, 2000);
    setHighTime(0);
    
    startPWM();

    while(1){

    }




}