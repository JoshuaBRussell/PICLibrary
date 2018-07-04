#ifndef _PID_H_
#define _PID_H_

/*----------------------------------------------------------------------------//
// PID Interface: Interface for the PID module. 
//----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------//
// PID Struct: Holds all the needed info for a specific PID instance. 
//----------------------------------------------------------------------------*/

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


/*----------------------------------------------------------------------------//
// Functions for manipulating the PID instance
//----------------------------------------------------------------------------*/

//Initializes PID to a known state.
void PID_Init(PID* pid);

//---- Getter Functions ----//
//Gets the various PID coefficients
float getKp(PID* pid);
float getKi(PID* pid);
float getKd(PID* pid);

//Gets the currently established setpoint
float getSetpoint(PID* pid);

//---- Setter Functions ----//
//Sets the various values needed for the PID controller
void setCoeff(PID* pid, float P, float I, float D);
void setSetpoint(PID* pid, float setpoint);
void setDeltaT(PID* pid, float deltaT);
void setOutputLimits(PID* pid, float min, float max);

//Computes the output of the PID controller
float Compute(PID* pid, float Input);
#endif // _PID_H_


