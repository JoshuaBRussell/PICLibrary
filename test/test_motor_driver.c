#include "unity.h"

#include "xc.h"
#include "motor_driver.h"
#include "mock_IO_Functions.h"
#include "mock_pwm_module.h"
#include "timer_functions.h"

float DIR_PIN_1 = 0;
float DIR_PIN_2 = 1;
float MOTOR_VOLTAGE = 12.0;
float PWM_PERIOD_US = 2000;

void setUp(void)
{

}

void tearDown(void)
{
}

uint16_t getPWM_High_Time_from_Float(float input, float max_input, uint16_t us_max_period){
    return ((uint16_t)((input/max_input) * (float)us_max_period) + 0.5);
}

void test_MOTOR_Init(void)
{
    float DIR_PIN_1 = 0;
    float DIR_PIN_2 = 1;
    
    MOTOR_Handle motor1 = MOTOR_Init(1.0, PORT_A, PIN_A0, PORT_A, DIR_PIN_1, PORT_A, DIR_PIN_2, PWM_0);
}


void test_get_motor_direction_default(){

    
    MOTOR_Handle motor1 = MOTOR_Init(1.0, PORT_A, PIN_A0, PORT_A, DIR_PIN_1, PORT_A, DIR_PIN_2, PWM_0);


    TEST_ASSERT_EQUAL(DIR_1, MOTOR_getDirection(motor1));
}

void test_set_motor_direction(){

    MOTOR_Handle motor1 = MOTOR_Init(1.0, PORT_A, PIN_A0, PORT_A, DIR_PIN_1, PORT_B, DIR_PIN_2, PWM_0);
    
    IO_setPinLow_Expect(PORT_A, DIR_PIN_1);
    IO_setPinHigh_Expect(PORT_B, DIR_PIN_2);
    MOTOR_setDirection(motor1, DIR_2);
    TEST_ASSERT_EQUAL(DIR_2, MOTOR_getDirection(motor1));

    IO_setPinHigh_Expect(PORT_A, DIR_PIN_1);
    IO_setPinLow_Expect(PORT_B, DIR_PIN_2);
    MOTOR_setDirection(motor1, DIR_1);
    TEST_ASSERT_EQUAL(DIR_1, MOTOR_getDirection(motor1));
}

void test_set_motor_output(){

    MOTOR_Handle motor1 = MOTOR_Init(12.0, PORT_A, PIN_A0, PORT_A, DIR_PIN_1, PORT_B, DIR_PIN_2, PWM_0);
    
    float motor_input = 6.0;
    
    //Sets Dir
    IO_setPinHigh_Expect(PORT_A, DIR_PIN_1);
    IO_setPinLow_Expect(PORT_B, DIR_PIN_2);

    //Sets Output
    PWM_setScaledOutput_Expect(PWM_0, (fabs(motor_input)/12.0));
    
    MOTOR_setOutput(motor1, motor_input);

    TEST_ASSERT_EQUAL(DIR_1, MOTOR_getDirection(motor1));

    motor_input = -6.0;
    IO_setPinLow_Expect(PORT_A, DIR_PIN_1);
    IO_setPinHigh_Expect(PORT_B, DIR_PIN_2);

    PWM_setScaledOutput_Expect(PWM_0, (fabs(motor_input)/12.0));

    MOTOR_setOutput(motor1, motor_input);

    TEST_ASSERT_EQUAL(DIR_2, MOTOR_getDirection(motor1));
}
