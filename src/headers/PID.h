#ifndef _PID_H
#define _PID_H



typedef struct{

    //Paramaters
    float Kp;
    float Ki;
    float Kd;

    float setpoint;

    float deltaT;
    
    float totalError;
    float prevError;

    float out_max;
    float out_min;
} PID;

//---- Init Function ----//
void PID_Init(PID* pid);

//---- Getter Functions ----//
float getKp(PID* pid);
float getKi(PID* pid);
float getKd(PID* pid);

float getSetpoint(PID* pid);

//---- Setter Functions ----//
void setCoeff(PID* pid, float P, float I, float D);
void setSetpoint(PID* pid, float setpoint);
void setDeltaT(PID* pid, float deltaT);
void setOutputLimits(PID* pid, float min, float max);


float Compute(PID* pid, float Input);
#endif // _PID_H


