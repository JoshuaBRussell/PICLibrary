#include "unity.h"
#include "PID.h"

void setUp(void)
{
}

void tearDown(void)
{
}

//---- Test Init Function ----//
void test_PID_Init(void){
    PID myPID;
    PID_Init(&myPID);
}
//---- Test Getter Functions ----//
void test_getKp_Default(void){
    PID myPID;
    PID_Init(&myPID);
    TEST_ASSERT_EQUAL(0.0, getKp(&myPID));

}

void test_getKi_Default(void){
    PID myPID;
    PID_Init(&myPID);
    TEST_ASSERT_EQUAL(0.0, getKi(&myPID));

}

void test_getKd_Default(void){
    PID myPID;
    PID_Init(&myPID);
    TEST_ASSERT_EQUAL(0.0, getKd(&myPID));

}

void test_getSetpoint_Default(void){
    PID myPID;
    PID_Init(&myPID);
    TEST_ASSERT_EQUAL(0.0, getSetpoint(&myPID));

}

//---- Test Setters ----//
void test_setCoeff(void){
    PID myPID;
    PID_Init(&myPID);
    float P = 2.5; 
    float I = 3.5;
    float D = 6.4;

    setCoeff(&myPID, P, I, D);

    TEST_ASSERT_EQUAL(P, getKp(&myPID));
    TEST_ASSERT_EQUAL(I, getKi(&myPID));
    TEST_ASSERT_EQUAL(D, getKd(&myPID));

}

void test_setSetpoint(void){
    PID myPID;
    PID_Init(&myPID);

    TEST_ASSERT_EQUAL_FLOAT(0.0, getSetpoint(&myPID));

    setSetpoint(&myPID, 1.0);
    TEST_ASSERT_EQUAL_FLOAT(1.0, getSetpoint(&myPID));
}

//---- Test Various Configs ----//
void test_Compute_P_Only(void){
    float proc_val = 0.5;

    PID myPID;
    PID_Init(&myPID);
    setCoeff(&myPID, 1.0, 0.0, 0.0);
    
    TEST_ASSERT_EQUAL_FLOAT(-0.5, Compute(&myPID, proc_val));

    setSetpoint(&myPID, 1.0);
    TEST_ASSERT_EQUAL_FLOAT(0.5, Compute(&myPID, proc_val));

}

void test_Compute_I_Only(void){
    float proc_val = 0.5;
    
    PID myPID;
    PID_Init(&myPID);
    setCoeff(&myPID, 0.0, 1.0, 0.0);
    setDeltaT(&myPID, 1.0);
    
    TEST_ASSERT_EQUAL_FLOAT(-0.5, Compute(&myPID, proc_val));
    TEST_ASSERT_EQUAL_FLOAT(-1.0, Compute(&myPID, proc_val));
    TEST_ASSERT_EQUAL_FLOAT(-1.5, Compute(&myPID, proc_val));

    PID aPID;
    PID_Init(&aPID);
    setCoeff(&aPID, 0.0, 1.0, 0.0);
    setDeltaT(&aPID, 1.0);
    setSetpoint(&aPID, 1.0);
    
    TEST_ASSERT_EQUAL_FLOAT(0.5, Compute(&aPID, proc_val));
    TEST_ASSERT_EQUAL_FLOAT(1.0, Compute(&aPID, proc_val));
    TEST_ASSERT_EQUAL_FLOAT(1.5, Compute(&aPID, proc_val));


}

void test_Compute_D_Only(void){
    float proc_val = 0.5;
    
    PID myPID;
    PID_Init(&myPID);
    setCoeff(&myPID, 0.0, 0.0, 1.0);
    setDeltaT(&myPID, 1.0);
    setSetpoint(&myPID, 1.0);

    TEST_ASSERT_EQUAL_FLOAT(0.5, Compute(&myPID, proc_val));

    proc_val = 0.75;
    TEST_ASSERT_EQUAL_FLOAT(-0.25, Compute(&myPID, proc_val));

}

void test_Max_Integral_Limit(void){
    float proc_val = 0.5;

    //----Test Max Output Limit
    PID aPID;
    PID_Init(&aPID);
    setCoeff(&aPID, 0.0, 1.0, 0.0);
    setDeltaT(&aPID, 1.0);
    setSetpoint(&aPID, 1.0);

    setOutputLimits(&aPID, 0.0, 1.5);
    
    //Integral Winds Up
    TEST_ASSERT_EQUAL_FLOAT(0.5, Compute(&aPID, proc_val));
    TEST_ASSERT_EQUAL_FLOAT(1.0, Compute(&aPID, proc_val));
    TEST_ASSERT_EQUAL_FLOAT(1.5, Compute(&aPID, proc_val));

    //Integral is Limited
    TEST_ASSERT_EQUAL_FLOAT(1.5, Compute(&aPID, proc_val));
    TEST_ASSERT_EQUAL_FLOAT(1.5, Compute(&aPID, proc_val));
    TEST_ASSERT_EQUAL_FLOAT(1.5, Compute(&aPID, proc_val));
 
}

void test_Min_Integral_Limit(){
    float proc_val = 0.5;

    PID myPID;
    PID_Init(&myPID);
    setCoeff(&myPID, 0.0, 1.0, 0.0);
    setDeltaT(&myPID, 1.0);
    
    setOutputLimits(&myPID, -1.5, 0.0);
    
    TEST_ASSERT_EQUAL_FLOAT(-0.5, Compute(&myPID, proc_val));
    TEST_ASSERT_EQUAL_FLOAT(-1.0, Compute(&myPID, proc_val));
    TEST_ASSERT_EQUAL_FLOAT(-1.5, Compute(&myPID, proc_val));

    TEST_ASSERT_EQUAL_FLOAT(-1.5, Compute(&myPID, proc_val));
    TEST_ASSERT_EQUAL_FLOAT(-1.5, Compute(&myPID, proc_val));
    TEST_ASSERT_EQUAL_FLOAT(-1.5, Compute(&myPID, proc_val));
}


