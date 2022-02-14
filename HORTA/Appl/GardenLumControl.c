
// 	Nomes:	Gabriel Lezan Nitz
// 			Guilherme Tsubahara Horstmann
//
// 	TRABALHO FINAL DE AAM

//-------------------------------------- Include Files ----------------------------------------------------------------
#include "..\Header\C_Types.h"
#include "..\Header\LumSensor.h"
#include "..\Header\GardenLumControl.h"
#include "..\Header\Display.h"
//-------------------------------------- PUBLIC (Variables) -----------------------------------------------------------


//-------------------------------------- Defines, Enumerations ----------------------------------------------------------------


typedef struct // não vamos mais usar essas paradas
{
	unsigned short int Temp_On;
	unsigned short int Temp_Off;
}OVEN_TEMP_RANGE_TYPE;


HORTA_LUM_CONTROL_LEVELS_TYPE Current_Level;			

//-------------------------------------- Global Variables ----------------------------------------------------------------

GARDEN_LUM_CONTROL_STATE_TYPE Garden_LumControl_State; 
//-------------------------------------- PRIVATE (Function Prototypes) ---------------------------------------------------



//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================


//---------------------------------------------------------------------------------------------------------------------
void Garden_Lum_Control__Initialize(void)
{
	Garden_LumControl_State = LUM_INSIDE_RANGE;   
	Current_Level = LUM_OFF;
}

void Garden_Lum_Control__Handler(void)
{
	unsigned short int temp_on;
	unsigned short int temp_off;
	unsigned short int current_ilum;

	current_ilum = LumSensor__Interface(GARDEN_RELATED_SENSOR);

	if(Current_Level == LUM_OFF)
	{
		TURN_LAMP_OFF();
	}
	else
	{
		switch(Garden_LumControl_State)
		{
		case LUM_INSIDE_RANGE:
			TURN_LAMP_OFF(); // desliga o rele
			if(current_ilum <= luminosidade_planta_ON)
			{
				Garden_LumControl_State = LUM_OUTSIDE_RANGE;
			}
			break;

		case LUM_OUTSIDE_RANGE:
			TURN_LAMP_ON(); // liga o rele
			if(current_ilum >= luminosidade_planta_OFF)
			{
				Garden_LumControl_State = LUM_INSIDE_RANGE;
			}

			break;
		}
	}
}


void Garden_Lum_Control__SetLevel(HORTA_LUM_CONTROL_LEVELS_TYPE level)
{
	Current_Level = level;
}


GARDEN_LUM_CONTROL_STATE_TYPE Garden_Lum_Control__GetState(void)
{
	return Garden_LumControl_State; 
}



