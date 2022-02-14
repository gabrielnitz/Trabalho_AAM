
#ifndef HAL_PRM_H_
#define HAL_PRM_H_

//-------------------------------------- Include Files ----------------------------------------------------------------
#include "..\Header\C_Types.h"

//-------------------------------------- Defines, Enumerations ----------------------------------------------------------------

#define USE_LED_0		ENABLED
#define USE_LED_1		ENABLED
#define USE_LED_2		ENABLED
#define USE_LED_3		ENABLED
#define USE_LAMPADA		ENABLED


//-------------------------------------------------------------------------------------------
// ---------------------------------  KEYS CONFIGURATION ----------------------------------
//-------------------------------------------------------------------------------------------
//On board Keys configuration
// Select ENABLED for Keys that will be used otherwise DISABLED
#define USE_KEY_0		ENABLED	
#define USE_KEY_1		ENABLED	
#define USE_KEY_2		ENABLED	
#define USE_KEY_3		ENABLED

//-------------------------------------------------------------------------------------------
// ---------------------------------  AD CONFIGURATION ------------------------------------
//-------------------------------------------------------------------------------------------
#define USE_POT_IN		DISABLED
#define USE_POT_OUT     ENABLED

#define HAL_ANALOG_MODE	    	MODE_10BITS//MODE_8BITS //MODE_10BITS //MODE_12BITS
#define HAL_CONVERSION_METHOD	AD_CONTINUOUS_CONVERSION//AD_SINGLE_CONVERSION //AD_CONTINUOUS_CONVERSION

#define HAL_ANALOG_CHANNEL_CONFIG\
	{\
	AD_CH0,\
	AD_CH1,\
	AD_CH2,\
	AD_CH3,\
	AD_CH4,\
	AD_CH5\
	}	

//-------------------------------------------------------------------------------------------
// --------------------------------- BUZZER CONFIGURATION ------------------------------------
//-------------------------------------------------------------------------------------------

#define USE_SERVO				ENABLED  //	DISABLED		 
#define SERVO_DEFAULT_ON_DUTY	99 //100%
#define SERVO_OFF_DUTY			0 //0%	
#define SERVO_DEFAULT_FREQ		30 //Hz
//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================

#endif /* HAL_PRM_H_ */
