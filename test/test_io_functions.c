#include "unity.h"
//#include "IO_Functions.h"

#include "xc.h"
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



void setUp(void)
{
    //Inits SFR to default states
    TRISA = 0xFFFF;
    LATA = 0x0000;
}

void tearDown(void)
{


}

//----Test Port A TRIS as Output----//
void test_set_PinA0_as_Output(void)
{
    setPinOut(0, 0);
    TEST_ASSERT_BITS(0xFFFF, 0xFFFE, TRISA);

}

void test_set_PinA1_as_Output(void){
    setPinOut(0, 1);
    TEST_ASSERT_BITS(0xFFFF, 0xFFFD, TRISA);
}

void test_set_PinA15_as_Output(void){
    setPinOut(0, 15);
    TEST_ASSERT_BITS(0xFFFF, 0x7FFF, TRISA);
}

void test_set_multiple_Pins_as_Output(void){
    setPinOut(0, 15);
    setPinOut(0, 1);
    setPinOut(0, 0);
    TEST_ASSERT_BITS(0xFFFF, 0x7FFC, TRISA);
}

//----Test Port A LAT High----//

void test_set_PinA0_HIGH(void){
    setPinHigh(0, 0);
    TEST_ASSERT_BITS(0xFFFF, 0x0001, LATA);
}

void test_set_PinA1_HIGH(void){
    setPinHigh(0, 1);
    TEST_ASSERT_BITS(0xFFFF, 0x0002, LATA);
}

void test_set_PinA15_HIGH(void){
    setPinHigh(0, 15);
    TEST_ASSERT_BITS(0xFFFF, 0x8000, LATA);
}

void test_set_multiple_Pins_High(void){
    setPinHigh(0, 0);
    setPinHigh(0, 1);
    setPinHigh(0, 15);
    TEST_ASSERT_BITS(0xFFFF, 0x8003, LATA);
}

//---- Test Port A LAT Low ----//
void test_set_PinA0_Low(void){
    LATA = 0xFFFF;
    setPinLow(0, 0);
    TEST_ASSERT_BITS(0xFFFF, 0xFFFE, LATA);
}

void test_set_PinA1_Low(void){
    LATA = 0xFFFF;
    setPinLow(0, 1);
    TEST_ASSERT_BITS(0xFFFF, 0xFFFD, LATA);
}

void test_set_PinA15_Low(void){
    LATA = 0xFFFF;
    setPinLow(0, 15);
    TEST_ASSERT_BITS(0xFFFF, 0x7FFF, LATA);
}

void test_set_multiple_Pins_Low(void){
    LATA = 0xFFFF;
    setPinLow(0, 0);
    setPinLow(0, 1);
    setPinLow(0, 15);
    TEST_ASSERT_BITS(0xFFFF, 0x7FFC, LATA);
}

//----
void test_toggle_PinA0_Low_to_High(void){
    togglePin(0, 0);
    TEST_ASSERT_BITS(0xFFFF, 0x0001, LATA);
}

void test_toggle_PinA1_Low_to_High(void){
    togglePin(0, 1);
    TEST_ASSERT_BITS(0xFFFF, 0x0002, LATA);
}

void test_toggle_muli_pins_High(void){
    togglePin(0, 0);
    togglePin(0, 1);
    togglePin(0, 15);
    TEST_ASSERT_BITS(0xFFFF, 0x8003, LATA);
}


void test_toggle_muli_pins_Low(void){
    LATA = 0xFFFF;
    togglePin(0, 0);
    togglePin(0, 1);
    togglePin(0, 15);
    TEST_ASSERT_BITS(0xFFFF, ~(0x8003), LATA);
}

void test_toggle_muli_pins_mixed(void){
    togglePin(0, 0);
    togglePin(0, 1);
    togglePin(0, 0);
    TEST_ASSERT_BITS(0xFFFF, 0x0002, LATA);
}
