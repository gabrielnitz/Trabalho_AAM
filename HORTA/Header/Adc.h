
#ifndef ADC_H_
#define ADC_H_

//-------------------------------------- Include Files ----------------------------------------------------------------
#include "..\Header\Micro.h"
#include "..\Header\Adc_prm.h"


//-------------------------------------- Defines, Enumerations ----------------------------------------------------------------


typedef enum
{
	AD_CH0 = 0,
	AD_CH1,
	AD_CH2,
	AD_CH3,
	AD_CH4,
	AD_CH5,
	NUM_OF_AD_CHANNELS,
}AD_CHANNEL_TYPE;

typedef enum
{
	MODE_8BITS = 0, 	//8  bits mode is 0b00
	MODE_10BITS,	    //10 bits mode is 0b01
	NUM_OF_MODES
}AD_MODE_TYPE;

typedef enum
{
	AD_SINGLE_CONVERSION = 0,
	AD_CONTINUOUS_CONVERSION,
	NUM_OF_CONVERSION_TYPES
}AD_CONVERSION_TYPE;


//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================
void ADC__Initialize(void);
void ADC__ConfigModes(AD_MODE_TYPE  mode, AD_CONVERSION_TYPE conv_type);
unsigned short int ADC__GetValue(AD_CHANNEL_TYPE channel);
void ADC__Handler(void);

#endif /* ADC_H_ */


