
//-------------------------------------- Include Files ----------------------------------------------------------------
#include "..\Header\C_Types.h"
#include "..\Header\Display.h"
#include "..\Header\Hal.h"
//-------------------------------------- PUBLIC (Variables) -----------------------------------------------------------


//-------------------------------------- Defines, Enumerations ----------------------------------------------------------------

#define NUM_EVENTS     	   50
#define LIGA_SAIDA          0
#define DESLIGA_SAIDA           1

#define NUM_OF_SEG      4      // número de segmentos do Display 7 segmentos

#define TRUE               1

//-------------------------------------- Global Variables ----------------------------------------------------------------

GARD_DISPLAY_STATE_TYPE Garden_Display_State;      // variável global  de display

KEY_EVENT_TYPE Display_Keys_Map;                  // variável global  de keys

char ZERADO_DIGITO[NUM_OF_SEG] = {0xC0,0xC0,0xC0,0xC0};   //# 0000
char MINIMO_DIGITO[NUM_OF_SEG] = {0xC0,0xC0,0xC0,0xF9};   //# 0001
char MEDIO_DIGITO[NUM_OF_SEG] =  {0xC0,0xC0,0xC0,0xA4};   //# 0002
char MAXIMO_DIGITO[NUM_OF_SEG] = {0xC0,0xC0,0xC0,0xB0};   //# 0003 

//-------------------------------------- PRIVATE (Function Prototypes) ---------------------------------------------------

void UpdateDisplaySaidas(void);
void UpdateDisplaySevenSeg(void);
void ReadDisplayKeys(void);


//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================
//---------------------------------------------------------------------------------------------------------------------
/**
 *  
 */
void Display__Initialize(void)
{
	Garden_Display_State = GARD_IN;
	Display_Keys_Map = KEY_INIT_EVENT;
	luminosidade_planta_ON = LUMIN_PLANTA_ON_1;
	luminosidade_planta_OFF = LUMIN_PLANTA_OFF_1;
}

//---------------------------------------------------------------------------------------------------------------------
/**
 *  
 */
void Display__Handler(void)
{
ReadDisplayKeys();
	
#if (SAIDA_DISPLAY == ENABLED)	
	UpdateDisplaySaidas();
#endif	

#if (SEVEN_SEG_DISPLAY == ENABLED)
     UpdateDisplaySevenSeg();
#endif	
}

//---------------------------------------------------------------------------------------------------------------------
/**
 *  
 */
void Display__SetState(GARD_DISPLAY_STATE_TYPE state)
{
	if(state < NUM_OF_GARD_STATES)
	{
		Garden_Display_State = state;
	}
	
}
//---------------------------------------------------------------------------------------------------------------------


KEY_EVENT_TYPE Display__GetEvent(void)
{
	KEY_EVENT_TYPE event;
	ReadDisplayKeys();   
	event = Display_Keys_Map;
	return (event);	
}

//=====================================================================================================================
//-------------------------------------- PRIVATE Functions -------------------------------------------------------------
//=====================================================================================================================

void UpdateDisplaySaidas(void)
{
	unsigned short int ad_value;
	
	switch(Garden_Display_State)
	{
	case GARD_IN:
	      Hal__SetAllDigitalOutputs(SAIDA_OFF);
	      break;
	case GARD_INIT:
		  Hal__SetDigitalOutput(LED_0, DESLIGA_SAIDA);
		  Hal__SetDigitalOutput(LED_1, DESLIGA_SAIDA);
		  Hal__SetDigitalOutput(LED_2, DESLIGA_SAIDA);
		  Hal__SetDigitalOutput(LED_3, LIGA_SAIDA);
	      break;
	case GARD_TIMEOUT:
		Hal__SetDigitalOutput(LED_3, DESLIGA_SAIDA);
	      break;
	case GARD_P1: // PLANTA 1
	    {
		Hal__SetDigitalOutput(LED_0, LIGA_SAIDA);
		Hal__SetDigitalOutput(LED_1, DESLIGA_SAIDA);
		Hal__SetDigitalOutput(LED_2, DESLIGA_SAIDA);
		
		luminosidade_planta_ON = LUMIN_PLANTA_ON_1;
		luminosidade_planta_OFF = LUMIN_PLANTA_OFF_1;

		break;
	    }
	case GARD_P2: // PLANTA 2
	{
		Hal__SetDigitalOutput(LED_0, DESLIGA_SAIDA);
		Hal__SetDigitalOutput(LED_1, LIGA_SAIDA);
		Hal__SetDigitalOutput(LED_2, DESLIGA_SAIDA);
		
		luminosidade_planta_ON = LUMIN_PLANTA_ON_2;
		luminosidade_planta_OFF = LUMIN_PLANTA_OFF_2;
		
		break;
	}
	case GARD_P3: // PLANTA 3
	{
		Hal__SetDigitalOutput(LED_0, DESLIGA_SAIDA);
		Hal__SetDigitalOutput(LED_1, DESLIGA_SAIDA);
		Hal__SetDigitalOutput(LED_2, LIGA_SAIDA);
		
		luminosidade_planta_ON = LUMIN_PLANTA_ON_3;
		luminosidade_planta_OFF = LUMIN_PLANTA_OFF_3;
		
		break;
	}
		
	default:
		{
		break;
		}
 }
}

//---------------------------------------------------------------------------------------------------------------------
/**
 *  
 */
void ReadDisplayKeys(void)
{
        unsigned char leitura;
		
		Display_Keys_Map = KEY_NONE;
       		   	
		leitura = Hal__ReadKey(KEY_0);
		if(leitura  == TRUE)
		     {
			Display_Keys_Map = KEY_PLANT1_EVENT;
			 }
		leitura = Hal__ReadKey(KEY_1);
		if(leitura == TRUE)
		    {
			Display_Keys_Map = KEY_PLANT2_EVENT;
			}
		leitura = Hal__ReadKey(KEY_2);
		if(leitura == TRUE)
		    {
			Display_Keys_Map =  KEY_PLANT3_EVENT;
			}
		leitura = Hal__ReadKey(KEY_3);
		if(leitura == TRUE)
			{
			Display_Keys_Map =  KEY_INIT_EVENT; 
			}
}

void UpdateDisplaySevenSeg(void)
{
char i;
char *p_digito;
switch(Garden_Display_State)
	{
	case GARD_INIT:
		{
		p_digito = &ZERADO_DIGITO[0];
		for (i = 0; i< NUM_OF_SEG; i++, p_digito++)
		Hal__WriteValtoSegment(i, p_digito);
		break;
		}
	case GARD_IN:
		{
		p_digito = &ZERADO_DIGITO[0];
		for (i = 0; i< NUM_OF_SEG; i++, p_digito++)
		Hal__WriteValtoSegment(i, p_digito);
		break;
		}
	case GARD_TIMEOUT:
		break;
	case GARD_P1:
		{
		p_digito = &MINIMO_DIGITO[0];
		for (i = 0; i< NUM_OF_SEG; i++, p_digito++)
		Hal__WriteValtoSegment(i, p_digito);
		break;
		}
	case GARD_P2:
		{
		p_digito = &MEDIO_DIGITO[0];
		for (i = 0; i< NUM_OF_SEG; i++, p_digito++)
		Hal__WriteValtoSegment(i, p_digito);
		break;
		}
	case GARD_P3:
		{
		p_digito = &MAXIMO_DIGITO;   // ou p_digito = &MAXIMO_DIGITO[0];
		for (i = 0; i< NUM_OF_SEG; i++, p_digito++)
		Hal__WriteValtoSegment(i, p_digito);
		break;
		}
	
	default:
		{
		break;
		}
   }
}
