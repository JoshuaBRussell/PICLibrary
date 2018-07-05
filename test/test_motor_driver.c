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

void SETUP_MOCK_MOTOR_INIT(void){

    MOTOR motor1;

    setPinOut_Expect(0, DIR_PIN_1);
    setPinOut_Expect(0, DIR_PIN_2);

    setPinHigh_Expect(0, DIR_PIN_1);
    setPinLow_Expect(0,  DIR_PIN_2);
}

void test_MOTOR_Init(void)
{
    float DIR_PIN_1 = 0;
    float DIR_PIN_2 = 1;
    MOTOR motor1;

    setPinOut_Expect(0, DIR_PIN_1);
    setPinOut_Expect(0, DIR_PIN_2);

    setPinHigh_Expect(0, DIR_PIN_1);
    setPinLow_Expect(0,  DIR_PIN_2);
    MOTOR_Init(&motor1, 1.0, 0, DIR_PIN_1, DIR_PIN_2);
}


void test_get_motor_direction_default(){
    SETUP_MOCK_MOTOR_INIT();
    MOTOR motor1;
    MOTOR_Init(&motor1, 1.0, 0, 0, 1);


    TEST_ASSERT_EQUAL(DIR_1, MOTOR_getDirection(&motor1));
}

void test_set_motor_direction(){
    SETUP_MOCK_MOTOR_INIT();
    MOTOR motor1;
    MOTOR_Init(&motor1, 1.0, 0, DIR_PIN_1, DIR_PIN_2);
    
    setPinLow_Expect(0, DIR_PIN_1);
    setPinHigh_Expect(0, DIR_PIN_2);
    MOTOR_setDirection(&motor1, DIR_2);
    TEST_ASSERT_EQUAL(DIR_2, MOTOR_getDirection(&motor1));

    setPinHigh_Expect(0, DIR_PIN_1);
    setPinLow_Expect(0, DIR_PIN_2);
    MOTOR_setDirection(&motor1, DIR_1);
    TEST_ASSERT_EQUAL(DIR_1, MOTOR_getDirection(&motor1));
}

void test_set_motor_output(){
    SETUP_MOCK_MOTOR_INIT();
    MOTOR motor1;
    MOTOR_Init(&motor1, 12.0, 0, DIR_PIN_1, DIR_PIN_2);
    
    float motor_input = 6.0;
    setPinHigh_Expect(0, DIR_PIN_1);
    setPinLow_Expect(0, DIR_PIN_2);
    PWM_getPeriod_ExpectAndReturn(PWM_PERIOD_US);
    setHighTime_Expect(PWM_PERIOD_US/2);
    MOTOR_setOutput(&motor1, motor_input);

    TEST_ASSERT_EQUAL(DIR_1, MOTOR_getDirection(&motor1));

    motor_input = -6.0;
    setPinLow_Expect(0, DIR_PIN_1);
    setPinHigh_Expect(0, DIR_PIN_2);
    PWM_getPeriod_ExpectAndReturn(PWM_PERIOD_US);
    setHighTime_Expect(PWM_PERIOD_US/2);
    MOTOR_setOutput(&motor1, motor_input);

    TEST_ASSERT_EQUAL(DIR_2, MOTOR_getDirection(&motor1));
}
