#include "unity.h"
#include "timer_functions.h"

#include "xc.h"


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

//defines used internally and are useful here for test
#define TIMER_ON_BIT_MASK  0x8000
#define TIMER_OFF_BIT_MASK 0x0000

#define TIMER_PRE_LOC 0x0030
#define TIMER_PRE_256_BIT_MASK 0x0030
#define TIMER_PRE_64_BIT_MASK  0x0020
#define TIMER_PRE_8_BIT_MASK   0x0010
#define TIMER_PRE_1_BIT_MASK   0x0000

#define INTERRUPT_PRIOTIY_MAX (7)

void setUp(void)
{
    T2CON = 0x0000;

}

void tearDown(void)
{


}

//---- Test Millisecond to Ticks Function ----//
void test_ms_to_tick(void)
{    
    uint16_t ticks;
    ticks = ms_to_ticks(1, 1);
    TEST_ASSERT_EQUAL(3690, ticks);

    ticks = ms_to_ticks(15, 1);
    TEST_ASSERT_EQUAL(55350, ticks);

    ticks = ms_to_ticks(50, 8);
    TEST_ASSERT_EQUAL(23063, ticks);

    ticks = ms_to_ticks(100, 8);
    TEST_ASSERT_EQUAL(46125, ticks);

    ticks = ms_to_ticks(200, 64);
    TEST_ASSERT_EQUAL(11531, ticks);

    ticks = ms_to_ticks(500, 64);
    TEST_ASSERT_EQUAL(28828, ticks);

    ticks = ms_to_ticks(1000, 64);
    TEST_ASSERT_EQUAL(57656, ticks);
}



//---- Test Turn Timers ON ----//
void test_turn_Timer2_On(void){

    TEST_ASSERT_BITS(0xFFFF, 0x0000, T2CON);

    turnTimerOn(TIMER_2);
    TEST_ASSERT_BITS(0xFFFF, 0x8000, T2CON);

}

void test_turn_Timer3_On(void){

    TEST_ASSERT_BITS(0xFFFF, 0x0000, T3CON);

    turnTimerOn(TIMER_3);
    TEST_ASSERT_BITS(0xFFFF, 0x8000, T3CON);

}

//---- Test Setting the Period Registers ----//
void test_set_Period_Register_2(void){
    setPeriodTicks(TIMER_2, 0x0000);
    TEST_ASSERT_BITS(0xFFFF, 0x0000, PR2);

    setPeriodTicks(TIMER_2, 0xFFFF);
    TEST_ASSERT_BITS(0xFFFF, 0xFFFF, PR2);

    setPeriodTicks(TIMER_2, 0xAAAA);
    TEST_ASSERT_BITS(0xFFFF, 0xAAAA, PR2);
}

void test_set_Period_Register_3(void){
    setPeriodTicks(TIMER_3, 0x0000);
    TEST_ASSERT_BITS(0xFFFF, 0x0000, PR3);

    setPeriodTicks(TIMER_2, 0xFFFF);
    TEST_ASSERT_BITS(0xFFFF, 0xFFFF, PR2);

    setPeriodTicks(TIMER_2, 0xAAAA);
    TEST_ASSERT_BITS(0xFFFF, 0xAAAA, PR2);
}

//---- Test Setting Prescaler ----//
void test_set_Prescaler2_Zeroed_Bits(void){
    T2CON = 0x0000;
    setPrescaler(TIMER_2, PRE1);
    TEST_ASSERT_BITS(TIMER_PRE_LOC, 0x0000, T2CON);

    T2CON = 0x0000;
    setPrescaler(TIMER_2, PRE8);
    TEST_ASSERT_BITS(TIMER_PRE_LOC, TIMER_PRE_8_BIT_MASK, T2CON);

    T2CON = 0x0000;
    setPrescaler(TIMER_2, PRE64);
    TEST_ASSERT_BITS(TIMER_PRE_LOC, TIMER_PRE_64_BIT_MASK, T2CON);

    T2CON = 0x0000;
    setPrescaler(TIMER_2, PRE256);
    TEST_ASSERT_BITS(TIMER_PRE_LOC, TIMER_PRE_256_BIT_MASK, T2CON);

}

void test_set_Prescaler3_Zeroed_Bits(void){
    T3CON = 0x0000;
    setPrescaler(TIMER_3, PRE1);
    TEST_ASSERT_BITS(TIMER_PRE_LOC, 0x0000, T3CON);

    T3CON = 0x0000;
    setPrescaler(TIMER_3, PRE8);
    TEST_ASSERT_BITS(TIMER_PRE_LOC, TIMER_PRE_8_BIT_MASK, T3CON);

    T3CON = 0x0000;
    setPrescaler(TIMER_3, PRE64);
    TEST_ASSERT_BITS(TIMER_PRE_LOC, TIMER_PRE_64_BIT_MASK, T3CON);

    T3CON = 0x0000;
    setPrescaler(TIMER_3, PRE256);
    TEST_ASSERT_BITS(TIMER_PRE_LOC, TIMER_PRE_256_BIT_MASK, T3CON);

}

void test_set_Prescaler2_NonZeroed_Bits(void){
    T2CON = 0x0000;
    setPrescaler(TIMER_2, PRE256);
    TEST_ASSERT_BITS(TIMER_PRE_LOC, TIMER_PRE_256_BIT_MASK, T2CON);

    setPrescaler(TIMER_2, PRE64);
    TEST_ASSERT_BITS(TIMER_PRE_LOC, TIMER_PRE_64_BIT_MASK, T2CON);

    setPrescaler(TIMER_2, PRE8);
    TEST_ASSERT_BITS(TIMER_PRE_LOC, TIMER_PRE_8_BIT_MASK, T2CON);

    setPrescaler(TIMER_2, PRE1);
    TEST_ASSERT_BITS(TIMER_PRE_LOC, 0x0000, T2CON);

}

void test_set_Prescaler3_NonZeroed_Bits(void){
    T3CON = 0x0000;
    setPrescaler(TIMER_3, PRE256);
    TEST_ASSERT_BITS(TIMER_PRE_LOC, TIMER_PRE_256_BIT_MASK, T3CON);

    setPrescaler(TIMER_3, PRE64);
    TEST_ASSERT_BITS(TIMER_PRE_LOC, TIMER_PRE_64_BIT_MASK, T3CON);

    setPrescaler(TIMER_3, PRE8);
    TEST_ASSERT_BITS(TIMER_PRE_LOC, TIMER_PRE_8_BIT_MASK, T3CON);

    setPrescaler(TIMER_3, PRE1);
    TEST_ASSERT_BITS(TIMER_PRE_LOC, 0x0000, T3CON);

}

//---- Test Reading/Clearing T2 Interrupt Flag ----//
void test_Timer2_Expired(void){
    _T2IF = 1;
    TEST_ASSERT_TRUE(isTimer2Expired());
    _T2IF = 0;
    TEST_ASSERT_FALSE(isTimer2Expired());
}

void test_clear_Timer2_Interrupt_Flag(void){
    _T2IF = 1;
    clearTimer2IntFlag();
    TEST_ASSERT_FALSE(isTimer2Expired());

}

//---- Test Reading/Clearing T3 Interrupt Flag ----//
void test_Timer3_Expired(void){
    _T3IF = 1;
    TEST_ASSERT_TRUE(isTimer3Expired());
    _T3IF = 0;
    TEST_ASSERT_FALSE(isTimer3Expired());
}

void test_clear_Timer3_Interrupt_Flag(void){
    _T3IF = 1;
    clearTimer3IntFlag();
    TEST_ASSERT_FALSE(isTimer3Expired());

}

//---- Test Turning On the Timer2 Interrupt ----//
void test_enable_Timer2_Interrupt_Low_to_High(void){
    _T2IE = 0;
    setTimer2IntEn(true);
    TEST_ASSERT_BIT_HIGH(0, _T2IE);
        
}

void test_enable_Timer2_Interrupt_High_to_Low(void){

    _T2IE = 1;
    setTimer2IntEn(false);
    TEST_ASSERT_BIT_LOW(0, _T2IE);

}

//---- Test Turning On the Timer3 Interrupt ----//
void test_enable_Timer3_Interrupt_Low_to_High(void){
    _T3IE = 0;
    setTimer3IntEn(true);
    TEST_ASSERT_BIT_HIGH(0, _T3IE);
        
}

void test_enable_Timer3_Interrupt_High_to_Low(void){

    _T3IE = 1;
    setTimer3IntEn(false);
    TEST_ASSERT_BIT_LOW(0, _T3IE);

}

//---- Test Setting Timer2 Interupt Priority ----//
void test_set_Timer2_Priority(void){
    _T2IP = 0;
    setTimer2IntPriority(1);
    TEST_ASSERT_EQUAL(1, _T2IP);

    setTimer2IntPriority(3);
    TEST_ASSERT_EQUAL(3, _T2IP);

    setTimer2IntPriority(7);
    TEST_ASSERT_EQUAL(7, _T2IP);
    
}

void test_set_Timer2_Priority_Upper_Bound(void){
    
    _T2IP = 4;
    setTimer2IntPriority(10);
    TEST_ASSERT_EQUAL(4, _T2IP);
}

//---- Test Setting Timer3 Interupt Priority ----//
void test_set_Timer3_Priority(void){
    _T3IP = 0;
    setTimer3IntPriority(1);
    TEST_ASSERT_EQUAL(1, _T2IP);

    setTimer2IntPriority(3);
    TEST_ASSERT_EQUAL(3, _T2IP);

    setTimer2IntPriority(7);
    TEST_ASSERT_EQUAL(7, _T2IP);
    
}

void test_set_Timer3_Priority_Upper_Bound(void){
    
    _T3IP = 4;
    setTimer3IntPriority(10);
    TEST_ASSERT_EQUAL(4, _T3IP);
}






