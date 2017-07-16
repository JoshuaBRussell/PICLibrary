#include "unity.h"
#include "encoders.h"



extern uint16_t PORTA;
void setUp(void)
{
}

void tearDown(void)
{
}

//----Test Specific Functions----//
void test_Default_getEncoderCount(void){
    int val = getEncoderCount();
    TEST_ASSERT_EQUAL(0, val);
}

void test_getTransitionTable(void)
{
    //A loop would look preferable, but I would prefer to have this check the values individually w/o creating yet another table   
    TEST_ASSERT_EQUAL(getTransistionTable(0),  0);
    TEST_ASSERT_EQUAL(getTransistionTable(1), -1);
    TEST_ASSERT_EQUAL(getTransistionTable(2),  1);
    TEST_ASSERT_EQUAL(getTransistionTable(3),  0);
    TEST_ASSERT_EQUAL(getTransistionTable(4),  1);
    TEST_ASSERT_EQUAL(getTransistionTable(5),  0);
    TEST_ASSERT_EQUAL(getTransistionTable(6),  0);
    TEST_ASSERT_EQUAL(getTransistionTable(7), -1);
    TEST_ASSERT_EQUAL(getTransistionTable(8), -1);
    TEST_ASSERT_EQUAL(getTransistionTable(9),  0);
    TEST_ASSERT_EQUAL(getTransistionTable(10), 0);
    TEST_ASSERT_EQUAL(getTransistionTable(11), 1);
    TEST_ASSERT_EQUAL(getTransistionTable(12), 0);
    TEST_ASSERT_EQUAL(getTransistionTable(13), 1);
    TEST_ASSERT_EQUAL(getTransistionTable(14),-1);
    TEST_ASSERT_EQUAL(getTransistionTable(15), 0);
    
}


