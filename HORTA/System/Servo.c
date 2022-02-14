
//-------------------------------------- Include Files ----------------------------------------------------------------
#include "..\Header\Micro.h"
#include "..\Header\Hal.h"
#include "..\Header\Servo.h"
#include "..\Header\Timer.h"
#include "..\Header\Pwm.h"
#include "..\Header\Display.h"
#include <util/delay.h> 

//--------------------defines---------------------
#define POWER_ON_SERVO   0
#define KEY_PRESS        1
#define END_CYCLE        2

typedef enum
{
	S_PLANTA1 = 0,
	S_PLANTA2,
	S_PLANTA3,
	OFF_
}SERVO_CLASS;


typedef enum
{
	POWER_ON_SERVO_STEP1 = 0,
	POWER_ON_SERVO_STEP2,
	POWER_ON_SERVO_STEP3,
	POWER_ON_SERVO_STEP4
}POWER_ON_SERVO_STEPS;

typedef enum
{
	KEY_PRESS_SERVO_STEP1_PLANTA1 = 0,
	KEY_PRESS_SERVO_STEP2_PLANTA1,
	KEY_PRESS_SERVO_STEP1_PLANTA2,
	KEY_PRESS_SERVO_STEP2_PLANTA2,
	KEY_PRESS_SERVO_STEP3_PLANTA2,
	KEY_PRESS_SERVO_STEP4_PLANTA2,
	KEY_PRESS_SERVO_STEP1_PLANTA3,
	KEY_PRESS_SERVO_STEP2_PLANTA3,
	KEY_PRESS_SERVO_STEP3_PLANTA3,
	KEY_PRESS_SERVO_STEP4_PLANTA3,
	KEY_PRESS_SERVO_STEP5_PLANTA3,
	KEY_PRESS_SERVO_STEP6_PLANTA3,
	KEY_PRESS_SERVO_STEP1_OFF,
	KEY_PRESS_SERVO_STEP2_OFF,
}KEY_PRESS_SERVO_STEPS;

typedef enum
{
	END_CYCLE_SERVO_STEP_OFF = 0,
	END_CYCLE_SERVO_STEP_ON
}END_CYCLE_SERVO_STEPS;


//-----------------------Globais -----------------

SERVOS_TYPE MoveServo;
KEY_PRESS_SERVO_STEPS Key_Press_Servo_Step_Planta1;
KEY_PRESS_SERVO_STEPS Key_Press_Servo_Step_Planta2;
KEY_PRESS_SERVO_STEPS Key_Press_Servo_Step_Planta3;
KEY_PRESS_SERVO_STEPS Key_Press_Servo_Step_Off;
POWER_ON_SERVO_STEPS  PowerON_Servo_Step;
END_CYCLE_SERVO_STEPS End_Cycle_Servo_Step;

unsigned char EndCycleServo_Counter = 0;

//-------------------------------------- PRIVATE (Function Prototypes) ---------------------------------------------------
SERVO_STATUS PowerOnServoHandler(void);
SERVO_STATUS KeyPressServoHandler(SERVO_CLASS servo_class);
SERVO_STATUS EndCycleServoHandler(void);

 void Servo__Initialize(void)
{
MoveServo = PLAY_NO_MOVE;   // variável global => sem som no início
PowerON_Servo_Step = POWER_ON_SERVO_STEP1;
Key_Press_Servo_Step_Planta1 = KEY_PRESS_SERVO_STEP1_PLANTA1;
Key_Press_Servo_Step_Planta2 = KEY_PRESS_SERVO_STEP1_PLANTA2;
Key_Press_Servo_Step_Planta3 = KEY_PRESS_SERVO_STEP1_PLANTA3;
Key_Press_Servo_Step_Off = KEY_PRESS_SERVO_STEP1_OFF;
End_Cycle_Servo_Step = END_CYCLE_SERVO_STEP_ON;
}

 
void Servo__Background(void)
{
switch (MoveServo)
	{
	case SERVO_POWER_ON:
	if(PowerOnServoHandler() == SERVO_DONE)
	{
		MoveServo = PLAY_NO_MOVE;
	}
	break;

	case SERVO_KEY_PRESS_PLANTA1:
	if(KeyPressServoHandler((SERVO_CLASS)S_PLANTA1) == SERVO_DONE)
	{
		MoveServo = PLAY_NO_MOVE;
	}
	break;

	case SERVO_KEY_PRESS_PLANTA2:
	if(KeyPressServoHandler((SERVO_CLASS)S_PLANTA2) == SERVO_DONE)
	{
		MoveServo = PLAY_NO_MOVE;
	}
	break;
	
	case SERVO_KEY_PRESS_PLANTA3:
	if(KeyPressServoHandler((SERVO_CLASS)S_PLANTA3) == SERVO_DONE)
	{
		MoveServo = PLAY_NO_MOVE;
	}
	break;
	
	case SERVO_KEY_PRESS_OFF:
	if(KeyPressServoHandler((SERVO_CLASS)OFF_) == SERVO_DONE)
	{
		MoveServo = PLAY_NO_MOVE;
	}
	break;

	case SERVO_END_CYCLE:
	if(EndCycleServoHandler() == SERVO_DONE)
	{
		MoveServo = PLAY_NO_MOVE;
	}
	break;
	
	case PLAY_NO_MOVE:
	Hal__SetServo(OFF);
	break;
	default:
	
	break;
	}
}
 

void Servo__MoveServo( SERVOS_TYPE sound_id)
{
MoveServo = PLAY_NO_MOVE;

if(sound_id < NUM_OF_MOVES)
   	MoveServo = sound_id;
}

 SERVOS_TYPE Servo__GetMoves( void)
{
	return (MoveServo);
}

SERVO_STATUS PowerOnServoHandler(void)
{
SERVO_STATUS status;
status = SERVO_MOVING;
Hal__SetServoFreq(30);

switch (PowerON_Servo_Step)
{
case POWER_ON_SERVO_STEP1:
	Hal__SetServo(ON); 
    Timer__HMSSet(TIMER_HMS_POWER_ON_SERVO, 0,0,2);
	PowerON_Servo_Step = POWER_ON_SERVO_STEP2;
	break;

case POWER_ON_SERVO_STEP2:
	if(Timer__HMSGetStatus(TIMER_HMS_POWER_ON_SERVO) == TIMER_EXPIRED)
		{
		Timer__HMSSet(TIMER_HMS_POWER_ON_SERVO, 0,0,1);	
		PowerON_Servo_Step = POWER_ON_SERVO_STEP3;
		Hal__SetServo(OFF);
		}
	break;  

case POWER_ON_SERVO_STEP3:
	if(Timer__HMSGetStatus(TIMER_HMS_POWER_ON_SERVO) == TIMER_EXPIRED)
		{
	    Timer__HMSSet(TIMER_HMS_POWER_ON_SERVO, 0,0,1);
		PowerON_Servo_Step = POWER_ON_SERVO_STEP4;
		Hal__SetServo(ON);
	    }
	break;
	
case POWER_ON_SERVO_STEP4:
	if(Timer__HMSGetStatus(TIMER_HMS_POWER_ON_SERVO) == TIMER_EXPIRED)
		{
		PowerON_Servo_Step = POWER_ON_SERVO_STEP1;
		Hal__SetServo(OFF);
		status = SERVO_DONE;
		}
	break;

default:
	PowerON_Servo_Step = POWER_ON_SERVO_STEP1;
	status = SERVO_DONE;
	break;
}
return status;
}

//---------------------------------------------------------------------------------------------------------------------
SERVO_STATUS KeyPressServoHandler(SERVO_CLASS servo_class)
{
status_move = SERVO_MOVING;
Hal__SetServoFreq(30);

switch (servo_class){
	case (S_PLANTA1):
	tempo_planta_x = 5;
	switch(Key_Press_Servo_Step_Planta1)
	{
		case KEY_PRESS_SERVO_STEP1_PLANTA1:
			Timer__HMSSet(TIMER_HMS_KEY_PRESS_Servo, 0,0,5);
			Hal__SetServo(ON);
			Key_Press_Servo_Step_Planta1 = KEY_PRESS_SERVO_STEP2_PLANTA1;
		break;

		case KEY_PRESS_SERVO_STEP2_PLANTA1:
			if(Timer__HMSGetStatus(TIMER_HMS_KEY_PRESS_Servo) == TIMER_EXPIRED)
			{
				Hal__SetServo(OFF);
				Key_Press_Servo_Step_Planta1 = KEY_PRESS_SERVO_STEP1_PLANTA1;
				status_move = SERVO_DONE;
			}
		break;
		
		default:
			Key_Press_Servo_Step_Planta1 = KEY_PRESS_SERVO_STEP1_PLANTA1;
			status_move = SERVO_DONE;
		break;
	}
	break;
	
	case (S_PLANTA2):
	tempo_planta_x = 18;
	switch(Key_Press_Servo_Step_Planta2)
	{
		case KEY_PRESS_SERVO_STEP1_PLANTA2:
			Timer__HMSSet(TIMER_HMS_KEY_PRESS_Servo, 0,0,5);
			Hal__SetServo(ON);
			Key_Press_Servo_Step_Planta2 = KEY_PRESS_SERVO_STEP2_PLANTA2;
		break;
		
		case KEY_PRESS_SERVO_STEP2_PLANTA2:
			if(Timer__HMSGetStatus(TIMER_HMS_KEY_PRESS_Servo) == TIMER_EXPIRED)
			{
				Timer__HMSSet(TIMER_HMS_KEY_PRESS_Servo, 0,0,8);
				Hal__SetServo(OFF);
				Key_Press_Servo_Step_Planta2 = KEY_PRESS_SERVO_STEP3_PLANTA2;
			}
		break;
		
		case KEY_PRESS_SERVO_STEP3_PLANTA2:
			if(Timer__HMSGetStatus(TIMER_HMS_KEY_PRESS_Servo) == TIMER_EXPIRED)
			{
				Timer__HMSSet(TIMER_HMS_KEY_PRESS_Servo, 0,0,5);
				Hal__SetServo(ON);
				Key_Press_Servo_Step_Planta2 = KEY_PRESS_SERVO_STEP4_PLANTA2;
			}
		break;
		
		case KEY_PRESS_SERVO_STEP4_PLANTA2:
			if(Timer__HMSGetStatus(TIMER_HMS_KEY_PRESS_Servo) == TIMER_EXPIRED)
			{
				Hal__SetServo(OFF);
				Key_Press_Servo_Step_Planta2 = KEY_PRESS_SERVO_STEP1_PLANTA2;
				status_move = SERVO_DONE;
			}
		break;
		
		default:
			Key_Press_Servo_Step_Planta2 = KEY_PRESS_SERVO_STEP1_PLANTA2;
			status_move = SERVO_DONE;
		break;
	}
	break;
	
	case (S_PLANTA3):
	tempo_planta_x = 31;
	switch(Key_Press_Servo_Step_Planta3)
	{
		case KEY_PRESS_SERVO_STEP1_PLANTA3:
			Timer__HMSSet(TIMER_HMS_KEY_PRESS_Servo, 0,0,5);
			Hal__SetServo(ON);
			Key_Press_Servo_Step_Planta3= KEY_PRESS_SERVO_STEP2_PLANTA3;
		break;
	
		case KEY_PRESS_SERVO_STEP2_PLANTA3:
			if(Timer__HMSGetStatus(TIMER_HMS_KEY_PRESS_Servo) == TIMER_EXPIRED)
			{
				Timer__HMSSet(TIMER_HMS_KEY_PRESS_Servo, 0,0,8);
				Hal__SetServo(OFF);
				Key_Press_Servo_Step_Planta3 = KEY_PRESS_SERVO_STEP3_PLANTA3;
			}
		break;
	
		case KEY_PRESS_SERVO_STEP3_PLANTA3:
			if(Timer__HMSGetStatus(TIMER_HMS_KEY_PRESS_Servo) == TIMER_EXPIRED)
			{
				Timer__HMSSet(TIMER_HMS_KEY_PRESS_Servo, 0,0,5);
				Hal__SetServo(ON);
				Key_Press_Servo_Step_Planta3 = KEY_PRESS_SERVO_STEP4_PLANTA3;
			}
		break;
		
		case KEY_PRESS_SERVO_STEP4_PLANTA3:
			if(Timer__HMSGetStatus(TIMER_HMS_KEY_PRESS_Servo) == TIMER_EXPIRED)
			{
				Timer__HMSSet(TIMER_HMS_KEY_PRESS_Servo, 0,0,8);
				Hal__SetServo(OFF);
				Key_Press_Servo_Step_Planta3 = KEY_PRESS_SERVO_STEP5_PLANTA3;
			}
		break;
		
		case KEY_PRESS_SERVO_STEP5_PLANTA3:
			if(Timer__HMSGetStatus(TIMER_HMS_KEY_PRESS_Servo) == TIMER_EXPIRED)
			{
				Timer__HMSSet(TIMER_HMS_KEY_PRESS_Servo, 0,0,5);
				Hal__SetServo(ON);
				Key_Press_Servo_Step_Planta3 = KEY_PRESS_SERVO_STEP6_PLANTA3;
			}
		break;
	
		case KEY_PRESS_SERVO_STEP6_PLANTA3:
			if(Timer__HMSGetStatus(TIMER_HMS_KEY_PRESS_Servo) == TIMER_EXPIRED)
			{
				Hal__SetServo(OFF);
				Key_Press_Servo_Step_Planta3 = KEY_PRESS_SERVO_STEP1_PLANTA3;
				status_move = SERVO_DONE;
			}
		break;
	
		default:
			Key_Press_Servo_Step_Planta3 = KEY_PRESS_SERVO_STEP1_PLANTA3;
			status_move = SERVO_DONE;
		break;
	}
	break;
	
	case (OFF_):
	switch(Key_Press_Servo_Step_Off)
	{
		case KEY_PRESS_SERVO_STEP1_OFF:
			Timer__HMSSet(TIMER_HMS_KEY_PRESS_Servo, 0,0,1);
			Hal__SetServo(ON);
			Key_Press_Servo_Step_Off = KEY_PRESS_SERVO_STEP2_OFF;
		break;

		case KEY_PRESS_SERVO_STEP2_OFF:
			if(Timer__HMSGetStatus(TIMER_HMS_KEY_PRESS_Servo) == TIMER_EXPIRED)
			{
				Hal__SetServo(OFF);
				Key_Press_Servo_Step_Off = KEY_PRESS_SERVO_STEP1_OFF;
				status_move = SERVO_DONE;
			}
		break;
		
		default:
			Key_Press_Servo_Step_Off = KEY_PRESS_SERVO_STEP1_OFF;
			status_move = SERVO_DONE;
		break;
	}
	break;

}
return status_move;
}


SERVO_STATUS EndCycleServoHandler(void)
{
SERVO_STATUS status;
status = SERVO_MOVING;
Hal__SetServoFreq(30);
	
switch(End_Cycle_Servo_Step)
	{
	case END_CYCLE_SERVO_STEP_ON:
		Timer__HMSSet(TIMER_HMS_END_CYCLE_SERVO, 0,0,5);
		Hal__SetServo(ON);
		End_Cycle_Servo_Step = END_CYCLE_SERVO_STEP_OFF;
		Display__SetState(GARD_INIT);
		break;

	case END_CYCLE_SERVO_STEP_OFF:
		if(Timer__HMSGetStatus(TIMER_HMS_END_CYCLE_SERVO) == TIMER_EXPIRED)
			{
			Hal__SetServo(OFF);
			End_Cycle_Servo_Step = END_CYCLE_SERVO_STEP_ON;
			status = SERVO_DONE;
			}
		break;
	default:
		End_Cycle_Servo_Step = END_CYCLE_SERVO_STEP_ON;
		status = SERVO_DONE;
		break;
	}
	
return status;
}