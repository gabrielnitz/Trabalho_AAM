
#ifndef DISPLAY_H_
#define DISPLAY_H_

//-------------------------------------- Include Files ----------------------------------------------------------------
#include "..\Header\Display_prm.h"

//-------------------------------------- Defines, Enumerations ----------------------------------------------------------------

unsigned int luminosidade_planta_ON;
unsigned int luminosidade_planta_OFF;

#define LUMIN_PLANTA_ON_1 180
#define LUMIN_PLANTA_OFF_1 220
#define LUMIN_PLANTA_ON_2 250
#define LUMIN_PLANTA_OFF_2 300
#define LUMIN_PLANTA_ON_3 320
#define LUMIN_PLANTA_OFF_3 380


typedef enum
{
	GARD_INIT = 0,
	GARD_P1,
	GARD_P2,
	GARD_P3,
	GARD_IN,
	GARD_TIMEOUT,
	NUM_OF_GARD_STATES
}GARD_DISPLAY_STATE_TYPE;

typedef enum
{
	KEY_INIT_EVENT = 0,
	KEY_PLANT1_EVENT,
	KEY_PLANT2_EVENT,
	KEY_PLANT3_EVENT,
	NUM_OF_KEYS_EVENTS
}KEY_EVENT_TYPE;

#define KEY_NONE		0xAA
#define EVENTS_NO_EVENT 0xFF

//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================
void Display__Initialize(void);
void Display__Handler(void);
void Display__SetState(GARD_DISPLAY_STATE_TYPE state);
KEY_EVENT_TYPE Display__GetEvent(void);

#endif /* DISPLAY_H_ */
