
//-------------------------------------- Include Files ----------------------------------------------------------------
#include "..\Header\C_Types.h"
#include "..\Header\LumSensor.h"
#include "..\Header\Hal.h"
//-------------------------------------- PUBLIC (Variables) -----------------------------------------------------------

unsigned short int Luminosidade[NUM_OF_LUM_SENSOR];
const unsigned char LumSensorTable[NUM_OF_LUM_SENSOR] = LUM_SENSOR_CONFIG;
const unsigned char LumSensor_Enable_Table[NUM_OF_LUM_SENSOR]= {USE_LUM_SENSOR_1, USE_LUM_SENSOR_2};
//-------------------------------------- Defines, Enumerations ----------------------------------------------------------------


//-------------------------------------- Global Variables ----------------------------------------------------------------


//-------------------------------------- PRIVATE (Function Prototypes) ---------------------------------------------------



//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================

void IlumSensor__Initialize(void)
{
	LUM_SENSOR_TYPE sensor_id;

	for (sensor_id = 0; sensor_id < NUM_OF_LUM_SENSOR; sensor_id++) 
	{
		Luminosidade[sensor_id] = 0;
	}
}
 
//---------------------------------------------------------------------------------------------------------------------
void IlumSensor__ConversionHandler(void)
{
	unsigned short int ad_value;
	LUM_SENSOR_TYPE sensor_id; 
	
	for (sensor_id = 0; sensor_id < NUM_OF_LUM_SENSOR; sensor_id++) 
	{
		if(LumSensor_Enable_Table[sensor_id] == ENABLED)
		{
			ad_value = Hal__GetAnalogInput(LumSensorTable[sensor_id]);
			ad_value = (ad_value + 400);
			ad_value = (ad_value/4) + 50;
			Luminosidade[sensor_id] = ad_value;
		}
	}
}
//---------------------------------------------------------------------------------------------------------------------
unsigned short int LumSensor__Interface(LUM_SENSOR_TYPE sensor_id)
{
	if (sensor_id < NUM_OF_LUM_SENSOR)
	{
		return Luminosidade[sensor_id];
	}
	else
	{
		return 0;
	}
	
}
//---------------------------------------------------------------------------------------------------------------------
