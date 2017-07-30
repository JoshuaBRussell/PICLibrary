#ifndef _TIMER_FUNCTIONS_H_
#define _TIMER_FUNCTIONS_H_


#include "timer_defines.h"
#include <stdint.h>
#include <stdbool.h>



//----------------------------------------------------------------------------//
//    Timer Utility Functions:                                                //
//                                                                            //
//    These functions are useful for generic timing issues, such as           //
//    converting milliseconds to a register tick count.                       //
//                                                                            //
//----------------------------------------------------------------------------//
uint16_t ms_to_ticks(uint16_t ms, uint16_t pre);

uint16_t us_to_ticks(uint16_t ms, uint16_t pre);


//----------------------------------------------------------------------------//
//    Timer Config Functions:                                                 //
//                                                                            //
//    Functions for configuring the HW timer such as                          //
//    the period length, prescaler, and the associated interrupt flags.       //
//----------------------------------------------------------------------------//

// Starts a timer. Which timer is chosen by TimerChannel 
void turnTimerOn(Timer_Channel timer);

// Sets the number of ticks for a timer to count before the Timer Expires.   
// Useful in conjuction with ms_to_timer()                                   
void setPeriodTicks(Timer_Channel timer, uint16_t ticks);

// Sets the Prescaler for the Timer. Timer is chosen by TimerChannel. Prescaler 
// is chosen by PRE_SEL.                                                        
void setPrescaler(Timer_Channel timer, PRE_SEL PRE);


//---- Timer 2 Interrupt Functions----//

// Checks if Timer2 has incremented to the value in the PeriodTicks Register.  
bool isTimer2Expired(void);

//Clears the Timer 2 Interrupt Expiration Flag. This must be cleared for the 
//interrupt to stop running.
void clearTimer2IntFlag(void);

//Enables the Timer 2 Interrupt. The Interrupt can never happen if this is not set High.
void setTimer2IntEn(bool bit);

//Sets the priority for the Timer 2 Interrupt. The value must be greater than 0
//for the interrupt to run at all. Provides bounds checking. Priority can not be set
//to a value greater than INTERRUPT_PRIOTIY_MAX(values greater than INTERRUPT_PRIOTIY_MAX
//are reserved for traps). If attempted the value is set to INTERRUPT_PRIOTIY_MAX
void setTimer2IntPriority(uint8_t priority);

#endif // _TIMER_FUNCTIONS_H_
