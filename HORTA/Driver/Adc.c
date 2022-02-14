
//-------------------------------------- Include Files ----------------------------------------------------------------
#include <avr/io.h> //definições do componente especificado 
#include "..\Header\C_Types.h"
#include "..\Header\Adc.h"
#include "..\Header\Gpio.h"
#include "..\Header\Hal.h"
 
//-------------------------------------- PUBLIC (Variables) -----------------------------------------------------------


//-------------------------------------- Defines, Enumerations ----------------------------------------------------------------
#define HI_BYTE_MASK          0xFF00
#define LO_BYTE_MASK          0x00FF

const unsigned char Adc_Enable_Table[NUM_OF_AD_CHANNELS]= 
{	CONFIG_AD_CH0, 
	CONFIG_AD_CH1, 
	CONFIG_AD_CH2, 
	CONFIG_AD_CH3, 
	CONFIG_AD_CH4, 
	CONFIG_AD_CH5,
	};

const unsigned char ADC_BIT_SET_MASK[] = {0x1,0x2,0x4,0x8,0x10,0x20};
const unsigned char ADC_BIT_CLR_MASK[] = {0xFE,0xFD,0xFB,0xF7,0xEF,0xDF};

typedef enum
{
	ADC_STEP_INIT = 0,
	ADC_STEP_SAMPLING,
	ADC_STEP_CONFIG_CHANNEL,
	ADC_STEP_WAIT_CONVERSION,
	ADC_STEP_READ_RESULT
}ADC_CONV_STEPS_TYPE;
//-------------------------------------- Global Variables ----------------------------------------------------------------

// Variáveis do ADC
unsigned short int ADC_Buffer[NUM_OF_AD_CHANNELS];
ADC_CONV_STEPS_TYPE Adc_Step;
AD_CHANNEL_TYPE Adc_Channel;
unsigned char Sampling_Time;
//-------------------------------------- PRIVATE (Function Prototypes) ---------------------------------------------------





//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================
 
void ADC__Initialize(void)
{
	unsigned char channel;
	volatile ADC_REG_TYPE *adc_pt;   // tipo definido no micro.h
	adc_pt = ADC_REGISTERS;          // adc_pt aponta par ao inicio dos regs do ADC ($000078)
	
	

	Adc_Step = ADC_STEP_INIT;   // inicializa o Adc_Step em INIT
	Sampling_Time = 0;
	adc_pt->DIDR0_REG.byte =0x00;  //  nenhuma entrada analógica habilitada
	
	for(channel = 0; channel <NUM_OF_AD_CHANNELS ; channel++)
	 {
		ADC_Buffer[channel] = 0;

		if(Adc_Enable_Table[channel] == ENABLED)      // se o canal é habilitado, então deixa analógico
		{
			// Configures relative input as analog input
			if(channel < NUM_OF_AD_CHANNELS) 
			   {							// CH0 to CH5 are configured in DIDR0
			   adc_pt->DIDR0_REG.byte |= ADC_BIT_SET_MASK[channel];	// configura como analógico conforme o canal enabled
			   }
		}
	 }  
}

//---------------------------------------------------------------------------------------------------------------------

void ADC__Handler(void)
{
	unsigned short int value, value_high;
	volatile ADC_REG_TYPE *adc_pt;
	adc_pt = ADC_REGISTERS;
	

	switch(Adc_Step)
	{
	case ADC_STEP_INIT:
		Adc_Channel++;											// Selects next channel
		if(Adc_Channel >= NUM_OF_AD_CHANNELS)
		{
			Adc_Channel = AD_CH0;  // varre constantemente todas os canais
		}

		if(Adc_Enable_Table[Adc_Channel] == ENABLED)			// Checks if current channel is enabled
		{
			Adc_Step = ADC_STEP_SAMPLING;
			Sampling_Time = ADC_SAMPLING_TIME;
		}
		break;

	case ADC_STEP_SAMPLING:
		if(Sampling_Time)
		{
			Sampling_Time--;
		}
		else
		{
			Adc_Step = ADC_STEP_CONFIG_CHANNEL;	
		}
		break;

	case ADC_STEP_CONFIG_CHANNEL:
	    adc_pt->ADMUX_REG.byte |= (unsigned char)Adc_Channel;
		adc_pt->ADCSRA_REG.byte =  0x87; 
		adc_pt->ADCSRA_REG.bit.bit6  = 1;    //seta bit 6 (ADSC)
		Adc_Step = ADC_STEP_WAIT_CONVERSION;					// Set next step
		break;
		
	case ADC_STEP_WAIT_CONVERSION:
		if(adc_pt->ADCSRA_REG.bit.bit6 == 0)	// Wait until conversion be completed
		   	Adc_Step = ADC_STEP_READ_RESULT;
		break;

	case ADC_STEP_READ_RESULT:  // AQUI é feita a leitura do ADC físico!!!
	    if(adc_pt->ADMUX_REG.bit.bit5 == 1)   //8 bits
		   {
			value = (unsigned short int)((adc_pt->ADCH_REG.byte)& LO_BYTE_MASK); // 8 bits   
		   }
		if(adc_pt->ADMUX_REG.bit.bit5 == 0)    // 10 bits
		   {
			value = (unsigned short int)((adc_pt->ADCL_REG.byte)& LO_BYTE_MASK);
			value_high = (unsigned short int)(adc_pt->ADCH_REG.byte <<8); 
			value |= value_high;	// Reads the conversion result bytes  
		   }

		ADC_Buffer[Adc_Channel] = value;  // A leitura do ADC é colocado no buffer ADC_Buffer do respectivo canal.
		Adc_Step = ADC_STEP_INIT;

	 	 break;

	default:
		Adc_Step = ADC_STEP_INIT;
		break;
	}
	
}  

//---------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------

 void ADC__ConfigModes(AD_MODE_TYPE  mode, AD_CONVERSION_TYPE conv_type)  //tipos dos parametros definidos no adc.h
{
	volatile ADC_REG_TYPE *adc_pt;
	adc_pt = ADC_REGISTERS;
	
	 	// seleção da tensão de referencia:
	adc_pt->ADMUX_REG.bit.bit7 = 0;   //tensão de referencia 5V
	adc_pt->ADMUX_REG.bit.bit6 = 1;   //tensão de referencia 5V
	
	if(mode < NUM_OF_MODES)
	{
		if (mode == MODE_8BITS)
		   adc_pt->ADMUX_REG.bit.bit5 = 1;  //Micro.h => ADLAR = 1, alinhado a esquerda e a leitura é no ADCH (8 bits)
		if (mode == MODE_10BITS)
		   adc_pt->ADMUX_REG.bit.bit5 = 0;  //ADLAR = 0, alinhado a direita e a leitura é primeiro no ADCL e depois ADCH (10 bits)
	}
		
	if(conv_type < NUM_OF_CONVERSION_TYPES)
	{
		if (conv_type == AD_SINGLE_CONVERSION)
		   adc_pt->ADCSRA_REG.bit.bit5 = 0;      //Micro.h => ADATE = 0, uma leitura
		if (conv_type == AD_CONTINUOUS_CONVERSION)
		   adc_pt->ADCSRA_REG.bit.bit5 = 1;      //ADATE = 1, a fonte de disparo pode ser conversão continua, comparador analogico, etc 
	}	                                     // no ATDS2:0
	
	
}

//---------------------------------------------------------------------------------------------------------------------
/*
 * Returns the current ADC value saved in the ADC_Buffer for a specific channel
 * channel: ADC Channel 
 */


unsigned short int ADC__GetValue(AD_CHANNEL_TYPE channel)
{
	if(channel < NUM_OF_AD_CHANNELS)
	{
		return ADC_Buffer[channel];  // retorna valor do ADC lido no ADC_Buffer do canal solcitado!
	}
	return 0;
}
