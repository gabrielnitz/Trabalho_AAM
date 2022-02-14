
#ifndef LUMSENSOR_H_
#define LUMSENSOR_H_

//-------------------------------------- Include Files ----------------------------------------------------------------
#include "..\Header\LumSensor_prm.h"

//-------------------------------------- Defines, Enumerations ----------------------------------------------------------------

typedef enum
{
	LUM_SENSOR_1 = 0,
	LUM_SENSOR_2,
	NUM_OF_LUM_SENSOR
}LUM_SENSOR_TYPE;

//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================
void IlumSensor__Initialize(void);
unsigned short int LumSensor__Interface(LUM_SENSOR_TYPE sensor_id);
void IlumSensor__ConversionHandler(void);

#endif
