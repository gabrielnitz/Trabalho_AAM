
#ifndef HAL_H_
#define HAL_H_

//-------------------------------------- Include Files ----------------------------------------------------------------
 #include "..\Header\Hal_prm.h"

//-------------------------------------- Defines, Enumerations ----------------------------------------------------------------
#define SAIDA_ON 		FALSE 
#define SAIDA_OFF 		TRUE  
#define KEY_PRESSED 	FALSE 

#define  ON             1
#define  OFF            0

#define  TRUE           1
#define  FALSE          0
#define  ENABLED        1

#define LIGA_SAIDA      0

typedef enum
{
	LED_0 = 0,
	LED_1,
	LED_2,
	LED_3,
	LAMPADA,
	NUM_OF_OUTPUTS
}OUTPUT_TYPE;

typedef enum
{
	KEY_0 = 0,
	KEY_1,
	KEY_2,
	KEY_3,
	NUM_OF_KEYS
}KEY_INPUT_TYPE;

// define as entradas analógicas existentes POT_INT no canal 0 e POT_EXT no canal 5
typedef enum
{
	POT_INT = 0,
	ANALOG_INPUT_1,
	ANALOG_INPUT_2,
	ANALOG_INPUT_3,
	ANALOG_INPUT_4,
	POT_EXT,
	NUM_OF_ANALOG_INPUT,
	}ANALOG_INPUT_TYPE;

//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================
void Hal__Initialize(void);
void Hal__BackgroundHandler(void);          // chamado pelo SLOT1 => ADC
void Hal__FastHandler(void);

void Hal__SetDigitalOutput(OUTPUT_TYPE output,unsigned char value);
void Hal__SetAllDigitalOutputs(unsigned char value);
unsigned char Hal__ReadKey(KEY_INPUT_TYPE key);

void Hal__WriteValtoSegment(char Segment, char *Value);

// Analog input read
unsigned short int Hal__GetAnalogInput(ANALOG_INPUT_TYPE input);

// Servo
void Hal__SetServo(unsigned char state);
void Hal__SetServoFreq(unsigned short int frequency);

#endif /* HAL_H_ */