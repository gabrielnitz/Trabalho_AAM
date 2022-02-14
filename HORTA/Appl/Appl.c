
// 	Nomes:	Gabriel Lezan Nitz
// 			Guilherme Tsubahara Horstmann
//
// 	TRABALHO FINAL DE AAM

//-------------------------------------- Include Files ----------------------------------------------------------------

#include "..\Header\C_Types.h"
#include "..\Header\Appl.h"
#include "..\Header\Display.h"
#include "..\Header\Gpio.h"
#include "..\Header\Adc.h"
#include "..\Header\Timer.h"
#include "..\Header\Hal.h"
#include "..\Header\GardenLumControl.h"
#include "..\Header\Pwm.h"
#include "..\Header\Servo.h"

//-------------------------------------- PUBLIC (Variables) -----------------------------------------------------------
KEY_EVENT_TYPE User_Action;
SERVOS_TYPE status_botao;

//-------------------------------------- Defines, Enumerations ----------------------------------------------------------------
#define EXP_ADC                ENABLED
#define EXP_GARDEN               ENABLED
#define EXP_TIMER              DISABLED       // TEMPO em ms
#define EXP_TIMER1             DISABLED       // TEMPO em HMS
#define TIME_IN_50MS_BASE	20 // 1s in 50ms time base (20*50ms = 1s)

#define LIGA_SAIDA               0
#define DESLIGA_SAIDA                1

//-------------------------------------- Global Variables ----------------------------------------------------------------
unsigned char Trigger;            // Indica quando o processo de cada planta acaba

//-------------------------------------- PRIVATE (Function Prototypes) ---------------------------------------------------

//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================


void Appl__Initialize(void)
{
	User_Action = EVENTS_NO_EVENT;
	status_botao = SERVO_KEY_PRESS_PLANTA1; // Por padrão inicia com a Planta 01 selecionada
	Trigger = FALSE;
}


void Appl__Handler(void)
{
	
#if (EXP_GARDEN == ENABLED)
          User_Action = Display__GetEvent();
		   if (User_Action != EVENTS_NO_EVENT)
		    {
			switch(User_Action)
			    {
			    case KEY_INIT_EVENT: 
				   Display__SetState(GARD_INIT);
				   Garden_Lum_Control__SetLevel(LUM_ON); 
				   Servo__MoveServo(status_botao); 
				   Timer__HMSSet(TIMER_HMS_CYCLE_DURATION, 0,0,tempo_planta_x);
					
					Trigger = TRUE;
	
				   break;
				
			    case KEY_PLANT1_EVENT: // PLANTA 1
			          Display__SetState(GARD_P1);
					  status_botao = SERVO_KEY_PRESS_PLANTA1;
				      break;
							
				 case KEY_PLANT2_EVENT: // PLANTA 2
					  Display__SetState(GARD_P2);
					  status_botao = SERVO_KEY_PRESS_PLANTA2;
					  break;
				
			     case KEY_PLANT3_EVENT: // PLANTA 3
				      Display__SetState(GARD_P3);
					  status_botao = SERVO_KEY_PRESS_PLANTA3;
				      break;
			     default:
				    break;
			} 
		} 
		

if( (Trigger == TRUE ) && (Timer__HMSGetStatus(TIMER_HMS_CYCLE_DURATION) == TIMER_EXPIRED) )
	{
	 	Display__SetState(GARD_TIMEOUT);
	 	Garden_Lum_Control__SetLevel(LUM_OFF);
	 	Trigger = FALSE;
	

	}
	
#endif


}   // fim do Appl_Handler()

//---------------------------------------------------------------------------------------------------------------------



