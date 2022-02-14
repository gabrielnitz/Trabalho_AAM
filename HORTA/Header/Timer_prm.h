
#ifndef TIMER_PRM_H_
#define TIMER_PRM_H_


//-------------------------------------- Include Files ----------------------------------------------------------------


//---------------------------------------------------------------------------------------------------------------------
typedef enum
{
    //Add MsTimers here
    TIMER_MS_TEST1     = 0,
    TIMER_MS_TEST2     = 1,
    TIMER_MS_POWER_ON_SOUND,         // tempo do som de power on
    TIMER_MS_KEY_PRESS_SOUND,
    TIMER_END_CYCLE_SOUND,
    // Do NOT REMOVE the line below
    NUM_OF_MS_TIMERS			// Total timers installed -- DON´T remove it
} MS_TIMER_NAME;


//---------------------------------------------------------------------------------------------------------------------
/**
 * List of Hour-Minutes-Seconds timers
 */
typedef enum
{
   //Add HMSTimers here
    TIMER_HMS_TEST1     = 0,
    TIMER_HMS_TEST2     = 1,
	TIMER_HMS_POWER_ON_SERVO = 2,         
	TIMER_HMS_KEY_PRESS_Servo = 3,
	TIMER_HMS_END_CYCLE_SERVO = 4,
    TIMER_HMS_CYCLE_DURATION = 5,
    TIMER_HMS_LCD_MESSAGE_TIME = 6,
    // Do NOT REMOVE the line below
    NUM_OF_HMS_TIMERS = 7			// Total timers installed -- DON´T remove it
} HMS_TIMER_NAME;



/**
 * TIMERS RESOLUTION
 *
 * Recommended values in ms: 1, 5, 20, 25, 50, 100, or 1000
 */
#define MS_TIMERS_RESOLUTION      1//1

#define HMS_TIMERS_RESOLUTION     5//5


//---------------------------------------------------------------------------------------------------------------------

//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================


#endif /* TIMER_PRM_H_ */
