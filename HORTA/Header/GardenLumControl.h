
#ifndef GARDENLUMCONTROL_H_
#define GARDENLUMCONTROL_H_

//-------------------------------------- Include Files ----------------------------------------------------------------

#include "..\Header\GardenLumControl_prm.h"

//-------------------------------------- Defines, Enumerations ----------------------------------------------------------------

typedef enum
{
	LUM_INSIDE_RANGE = 0,
	LUM_OUTSIDE_RANGE
}GARDEN_LUM_CONTROL_STATE_TYPE;


typedef enum
{
	LUM_ON = 0,
	LUM_OFF,
	NUM_OF_LUM_LEVELS
}HORTA_LUM_CONTROL_LEVELS_TYPE;

//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================

void Garden_Lum_Control__Initialize(void);
void Garden_Lum_Control__Handler(void);
void Garden_Lum_Control__SetLevel(HORTA_LUM_CONTROL_LEVELS_TYPE level);
GARDEN_LUM_CONTROL_STATE_TYPE Garden_Lum_Control__GetState(void);

#endif

