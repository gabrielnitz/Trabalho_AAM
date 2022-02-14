
#ifndef Servo_H_
#define Servo_H_

//-------------------------------------- Include Files ----------------------------------------------------------------
#include "..\Header\Servo_prm.h"

typedef enum {
	SERVO_POWER_ON = 0,
	SERVO_KEY_PRESS,
	SERVO_KEY_PRESS_PLANTA1,
	SERVO_KEY_PRESS_PLANTA2,
	SERVO_KEY_PRESS_PLANTA3,
	SERVO_KEY_PRESS_OFF,
	SERVO_END_CYCLE,
	PLAY_NO_MOVE, 
	NUM_OF_MOVES,
} SERVOS_TYPE;

typedef enum
{
	SERVO_DONE =0,
	SERVO_MOVING=1
}SERVO_STATUS;

//Protótipos
void Servo__Initialize(void);
void Servo__Background(void);
void Servo__MoveServo( SERVOS_TYPE servo_id);
SERVOS_TYPE Servo__GetMoves( void);  

SERVO_STATUS status_move;

#endif