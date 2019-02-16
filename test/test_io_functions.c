#include "unity.h"
//#include "IO_Functions.h"

#include "xc.h"
#include "IO_Functions.h"

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
#pragma config IESO = ON                // Two-speed Oscillator Start-up Enable bit (Start up device with FRC, then switch to user-selected oscillator source)

// FGS
#pragma config GWRP = OFF               // General Segment Write-Protect bit (General Segment may be written)
#pragma config GCP = OFF                // General Segment Code-Protect bit (General Segment Code protect is Disabled)


#define PORTA_PIN_MASK 0x001F //A0-A4
#define PORTB_PIN_MASK 0xFFFF //B0-B15

void setUp(void)
{
    //Inits SFR to default states
    TRISA = 0xFFFF;
    LATA = 0x0000;
    LATB = 0x0000;
    TRISB = 0xFFFF;
}

void tearDown(void)
{


}

//----Test Port A TRIS as Output----//
void test_set_PinA0_as_Output(void)
{
    IO_setPinOut(PORT_A, PIN_A0);
    TEST_ASSERT_BITS(PORTA_PIN_MASK, 0xFFFE, TRISA);

}

void test_set_PinA1_as_Output(void){
    IO_setPinOut(PORT_A, PIN_A1);
    TEST_ASSERT_BITS(PORTA_PIN_MASK, 0xFFFD, TRISA);
}

void test_set_PinA4_as_Output(void){
    IO_setPinOut(PORT_A, PIN_A4);
    TEST_ASSERT_BITS(PORTA_PIN_MASK, 0xFFEF, TRISA);
}

void test_set_multiple_Pins_as_Output(void){
    IO_setPinOut(PORT_A, PIN_A4);
    IO_setPinOut(PORT_A, PIN_A1);
    IO_setPinOut(PORT_A, PIN_A0);
    TEST_ASSERT_BITS(PORTA_PIN_MASK, 0xFFEC, TRISA);
}

//----Test Port A TRIS as Input----//
void test_set_PinA0_as_Input(void)
{
    TRISA = 0x0000;
    IO_setPinIn(PORT_A, PIN_A0);
    TEST_ASSERT_BITS(PORTA_PIN_MASK, 0x0001, TRISA);

}

void test_set_PinA1_as_Input(void){
    TRISA = 0x0000;
    IO_setPinIn(PORT_A, PIN_A1);
    TEST_ASSERT_BITS(PORTA_PIN_MASK, 0x0002, TRISA);
}

void test_set_PinA4_as_Input(void){
    TRISA = 0x0000;
    IO_setPinIn(PORT_A, PIN_A4);
    TEST_ASSERT_BITS(PORTA_PIN_MASK, 0x0010, TRISA);
}

void test_set_multiple_Pins_as_Input(void){
    TRISA = 0x0000;
    IO_setPinIn(PORT_A, PIN_A4);
    IO_setPinIn(PORT_A, PIN_A1);
    IO_setPinIn(PORT_A, PIN_A0);
    TEST_ASSERT_BITS(PORTA_PIN_MASK, 0x0013, TRISA);
}

//----Test Port A Read----//
// void test_read_PinA0_as_High(void){
//     uint16_t PORTA_sim = 0x0001;
//     TEST_ASSERT_TRUE(readPin(0,0));
// }

//----Test Port A LAT High----//

void test_set_PinA0_HIGH(void){
    IO_setPinHigh(PORT_A, PIN_A0);
    TEST_ASSERT_BITS(PORTA_PIN_MASK, 0x0001, LATA);
}

void test_set_PinA1_HIGH(void){
    IO_setPinHigh(PORT_A, PIN_A1);
    TEST_ASSERT_BITS(PORTA_PIN_MASK, 0x0002, LATA);
}

void test_set_PinA4_HIGH(void){
    IO_setPinHigh(PORT_A, PIN_A4);
    TEST_ASSERT_BITS(PORTA_PIN_MASK, 0x0010, LATA);
}

void test_set_multiple_Pins_High(void){
    IO_setPinHigh(PORT_A, PIN_A0);
    IO_setPinHigh(PORT_A, PIN_A1);
    IO_setPinHigh(PORT_A, PIN_A4);
    TEST_ASSERT_BITS(PORTA_PIN_MASK, 0x0013, LATA);
}

//---- Test Port A LAT Low ----//
void test_set_PinA0_Low(void){
    LATA = 0xFFFF;
    IO_setPinLow(PORT_A, PIN_A0);
    TEST_ASSERT_BITS(PORTA_PIN_MASK, 0xFFFE, LATA);
}

void test_set_PinA1_Low(void){
    LATA = 0xFFFF;
    IO_setPinLow(PORT_A, PIN_A1);
    TEST_ASSERT_BITS(PORTA_PIN_MASK, 0xFFFD, LATA);
}

void test_set_PinA4_Low(void){
    LATA = 0xFFFF;
    IO_setPinLow(PORT_A, PIN_A4);
    TEST_ASSERT_BITS(PORTA_PIN_MASK, 0xFFEF, LATA);
}

void test_set_multiple_Pins_Low(void){
    LATA = 0xFFFF;
    IO_setPinLow(PORT_A, PIN_A0);
    IO_setPinLow(PORT_A, PIN_A1);
    IO_setPinLow(PORT_A, PIN_A4);
    TEST_ASSERT_BITS(PORTA_PIN_MASK, 0xFFEC, LATA);
}

//----Test Port A LAT Toggle ----//
void test_toggle_PinA0_Low_to_High(void){
    IO_togglePin(PORT_A, PIN_A0);
    TEST_ASSERT_BITS(PORTA_PIN_MASK, 0x0001, LATA);
}

void test_toggle_PinA1_Low_to_High(void){
    IO_togglePin(PORT_A, PIN_A1);
    TEST_ASSERT_BITS(PORTA_PIN_MASK, 0x0002, LATA);
}

void test_toggle_muli_pins_High(void){
    IO_togglePin(PORT_A, PIN_A0);
    IO_togglePin(PORT_A, PIN_A1);
    IO_togglePin(PORT_A, PIN_A4);
    TEST_ASSERT_BITS(PORTA_PIN_MASK, 0x0013, LATA);
}


void test_toggle_muli_pins_Low(void){
    LATA = 0xFFFF;
    IO_togglePin(PORT_A, PIN_A0);
    IO_togglePin(PORT_A, PIN_A1);
    IO_togglePin(PORT_A, PIN_A4);
    TEST_ASSERT_BITS(PORTA_PIN_MASK, ~(0x0013), LATA);
}

void test_toggle_muli_pins_mixed(void){
    IO_togglePin(PORT_A, PIN_A0);
    IO_togglePin(PORT_A, PIN_A1);
    IO_togglePin(PORT_A, PIN_A0);
    TEST_ASSERT_BITS(PORTA_PIN_MASK, 0x0002, LATA);
}

//----Test IO_Config ----//
void test_IO_Config_correctly_sets_all_pins(void){
    const PIN_CONFIG IO_CONFIG_TABLE[] =
    {
    //   -Pin-       -Direction-     -Init State-   //
        {PIN_A0,     OUTPUT,          HIGH},
        {PIN_A1,     OUTPUT,          HIGH},
        {PIN_A2,     OUTPUT,          HIGH},
        {PIN_A3,     OUTPUT,          HIGH},
        {PIN_A4,     OUTPUT,          HIGH},
        {PIN_A5,     OUTPUT,          HIGH},
        {PIN_A6,     OUTPUT,          HIGH},
        {PIN_A7,     OUTPUT,          HIGH},
        {PIN_A8,     OUTPUT,          HIGH},
        {PIN_A9,     OUTPUT,          HIGH},
        {PIN_A10,    OUTPUT,          HIGH},
        {PIN_A11,    OUTPUT,          HIGH},
        {PIN_A12,    OUTPUT,          HIGH},
        {PIN_A13,    OUTPUT,          HIGH},
        {PIN_A14,    OUTPUT,          HIGH},
        {PIN_A15,    OUTPUT,          HIGH},
        {PIN_B0,     OUTPUT,          HIGH},
        {PIN_B1,     OUTPUT,          HIGH},
        {PIN_B2,     OUTPUT,          HIGH},
        {PIN_B3,     OUTPUT,          HIGH},
        {PIN_B4,     OUTPUT,          HIGH},
        {PIN_B5,     OUTPUT,          HIGH},
        {PIN_B6,     OUTPUT,          HIGH},
        {PIN_B7,     OUTPUT,          HIGH},
        {PIN_B8,     OUTPUT,          HIGH},
        {PIN_B9,     OUTPUT,          HIGH},
        {PIN_B10,    OUTPUT,          HIGH},
        {PIN_B11,    OUTPUT,          HIGH},
        {PIN_B12,    OUTPUT,          HIGH},
        {PIN_B13,    OUTPUT,          HIGH},
        {PIN_B14,    OUTPUT,          HIGH},
        {PIN_B15,    OUTPUT,          HIGH},


    };
    IO_Config(IO_CONFIG_TABLE);
    TEST_ASSERT_BITS(PORTA_PIN_MASK, 0xFFFF, LATA);
    TEST_ASSERT_BITS(PORTA_PIN_MASK, 0x0000, TRISA);
}

void test_IO_Config_correctly_sets_all_pins_alternating(void){
    const PIN_CONFIG IO_CONFIG_TABLE[] =
    {
    //   -Pin-       -Direction-     -Init State-   //
        {PIN_A0,     INPUT,          HIGH},
        {PIN_A1,     OUTPUT,         LOW},
        {PIN_A2,     INPUT,          HIGH},
        {PIN_A3,     OUTPUT,         LOW},
        {PIN_A4,     INPUT,          HIGH},
        {PIN_A5,     OUTPUT,         LOW},
        {PIN_A6,     INPUT,          HIGH},
        {PIN_A7,     OUTPUT,         LOW},
        {PIN_A8,     INPUT,          HIGH},
        {PIN_A9,     OUTPUT,         LOW},
        {PIN_A10,    INPUT,          HIGH},
        {PIN_A11,    OUTPUT,         LOW},
        {PIN_A12,    INPUT,          HIGH},
        {PIN_A13,    OUTPUT,         LOW},
        {PIN_A14,    INPUT,          HIGH},
        {PIN_A15,    OUTPUT,         LOW},
        {PIN_B0,     INPUT,          HIGH},
        {PIN_B1,     OUTPUT,         LOW},
        {PIN_B2,     INPUT,          HIGH},
        {PIN_B3,     INPUT,          LOW},
        {PIN_B4,     OUTPUT,         HIGH},
        {PIN_B5,     OUTPUT,         LOW},
        {PIN_B6,     INPUT,          HIGH},
        {PIN_B7,     OUTPUT,         LOW},
        {PIN_B8,     INPUT,          HIGH},
        {PIN_B9,     OUTPUT,         LOW},
        {PIN_B10,    INPUT,          HIGH},
        {PIN_B11,    OUTPUT,         LOW},
        {PIN_B12,    INPUT,          HIGH},
        {PIN_B13,    OUTPUT,         LOW},
        {PIN_B14,    INPUT,          HIGH},
        {PIN_B15,    OUTPUT,         LOW},


    };
    IO_Config(IO_CONFIG_TABLE);
    TEST_ASSERT_BITS(PORTA_PIN_MASK, 0x5555, LATA);
    TEST_ASSERT_BITS(PORTA_PIN_MASK, 0x5555, TRISA);
}

//----Test Setting Open Drain----//
void test_set_ODCA0(void){
    ODCA = 0x0000;
    IO_setPinOD(PORT_A, PIN_A0);
    TEST_ASSERT_BITS(PORTA_PIN_MASK, 0x0001, ODCA);
}

void test_set_ODCA1(void){
    ODCA = 0x0000;
    IO_setPinOD(PORT_A, PIN_A1);
    TEST_ASSERT_BITS(PORTA_PIN_MASK, 0x0002, ODCA);
}

void test_set_ODCA4(void){
    ODCA = 0x0000;
    IO_setPinOD(PORT_A, PIN_A4);
    TEST_ASSERT_BITS(PORTA_PIN_MASK, 0x0010, ODCA);
}

void test_set_multiple_Pins_OD(void){
    ODCA = 0x0000;
    IO_setPinOD(PORT_A, PIN_A0);
    IO_setPinOD(PORT_A, PIN_A1);
    IO_setPinOD(PORT_A, PIN_A4);
    TEST_ASSERT_BITS(PORTA_PIN_MASK, 0x0013, ODCA);
}

//----Test Setting Pull Up----//
void test_set_CNPUA0(void){
    CNPUA = 0x0000;
    IO_setPinPU(PORT_A, PIN_A0);
    TEST_ASSERT_BITS(PORTA_PIN_MASK, 0x0001, CNPUA);
}

void test_set_CNPUA1(void){
    CNPUA = 0x0000;
    IO_setPinPU(PORT_A, PIN_A1);
    TEST_ASSERT_BITS(PORTA_PIN_MASK, 0x0002, CNPUA);
}

void test_set_CNPUA4(void){
    CNPUA = 0x0000;
    IO_setPinPU(PORT_A, PIN_A4);
    TEST_ASSERT_BITS(PORTA_PIN_MASK, 0x0010, CNPUA);
}

void test_set_multiple_Pins_PU(void){
    CNPUA = 0x0000;
    IO_setPinPU(PORT_A, PIN_A0);
    IO_setPinPU(PORT_A, PIN_A1);
    IO_setPinPU(PORT_A, PIN_A4);
    TEST_ASSERT_BITS(PORTA_PIN_MASK, 0x0013, CNPUA);
}

//----Test Setting Pull Down----//
void test_set_CNPDA0(void){
    CNPDA = 0x0000;
    IO_setPinPD(PORT_A, PIN_A0);
    TEST_ASSERT_BITS(PORTA_PIN_MASK, 0x0001, CNPDA);
}

void test_set_CNPDA1(void){
    CNPDA = 0x0000;
    IO_setPinPD(PORT_A, PIN_A1);
    TEST_ASSERT_BITS(PORTA_PIN_MASK, 0x0002, CNPDA);
}

void test_set_CNPDA4(void){
    CNPDA = 0x0000;
    IO_setPinPD(PORT_A, PIN_A4);
    TEST_ASSERT_BITS(PORTA_PIN_MASK, 0x0010, CNPDA);
}

void test_set_multiple_Pins_PD(void){
    CNPDA = 0x0000;
    IO_setPinPD(PORT_A, PIN_A0);
    IO_setPinPD(PORT_A, PIN_A1);
    IO_setPinPD(PORT_A, PIN_A4);
    TEST_ASSERT_BITS(PORTA_PIN_MASK, 0x0013, CNPDA);
}


//----Test Port B----//
void test_setPinB0_as_Output(){
    IO_setPinOut(PORT_B, PIN_B0);
    TEST_ASSERT_BITS(PORTB_PIN_MASK, 0xFFFE, TRISB);
}

void test_set_ODCB4(void){
    ODCB = 0x0000;
    IO_setPinOD(PORT_B, PIN_B4);
    TEST_ASSERT_BITS(PORTB_PIN_MASK, 0x0010, ODCB);
}