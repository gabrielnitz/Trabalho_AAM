
#ifndef GARDENLUMCONTROL_PRM_H_
#define GARDENLUMCONTROL_PRM_H_

//-------------------------------------- Include Files ----------------------------------------------------------------
#include "..\Header\Hal.h"

//-------------------------------------- Defines, Enumerations ----------------------------------------------------------------

#define GARDEN_RELATED_SENSOR		LUM_SENSOR_2      

#define TURN_LAMP_ON()  Hal__SetDigitalOutput(LAMPADA, SAIDA_ON);
#define TURN_LAMP_OFF() Hal__SetDigitalOutput(LAMPADA, SAIDA_OFF);

#endif


