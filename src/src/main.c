#include <xc.h>
#include <stdint.h>

#include "IO_Functions.h"
#include "IO_Defines.h"

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
#pragma config IOL1WAY = ON             // Peripheral pin select configuration (Allow only one reconfiguration)
#pragma config FCKSM = CSDCMD           // Clock Switching Mode bits (Both Clock switching and Fail-safe Clock Monitor are disabled)

// FOSCSEL
#pragma config FNOSC = FRC              // Oscillator Source Selection (Internal Fast RC (FRC))
#pragma config IESO = ON                // Two-speed Oscillator Start-up Enable bit (Start up device with FRC, then switch to user-selected oscillator source)

// FGS
#pragma config GWRP = OFF               // General Segment Write-Protect bit (General Segment may be written)
#pragma config GCP = OFF                // General Segment Code-Protect bit (General Segment Code protect is Disabled)

const PIN_CONFIG IO_CONFIG_TABLE[] =
{
//   -Pin-       -Direction-     -Init State-   //
    {Pin_B0,     INPUT,          LOW},
    {Pin_B1,     INPUT,          LOW},
    {Pin_B2,     INPUT,          LOW},
    {Pin_B3,     INPUT,          LOW},
    {Pin_B4,     INPUT,          LOW},
    {Pin_B5,     INPUT,          LOW},
    {Pin_B6,     INPUT,          LOW},
    {Pin_B7,     INPUT,          LOW},
    {Pin_B8,     INPUT,          LOW},
    {Pin_B9,     INPUT,          LOW},
    {Pin_B10,    INPUT,          LOW},
    {Pin_B11,    INPUT,          LOW},
    {Pin_B12,    INPUT,          LOW},
    {Pin_B13,    INPUT,          LOW},
    {Pin_B14,    INPUT,          LOW},
    {Pin_B15,    OUTPUT,         HIGH},

};


void simple_delay(){
    uint16_t i, j;
    for(i = 0; i < 800; i++){
        for(j = 0; j < 500; j++){
            //Do nothing
        }
    }
}


int main(void) {

    setPinOut(1, 15);
    setPinHigh(1, 15);
    while(1){
        simple_delay();
        setPinLow(1, 15);
        simple_delay();
        setPinHigh(1, 15);
    }

    return 0;
}
