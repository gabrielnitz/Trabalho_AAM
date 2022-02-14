
#ifndef MAIN_PRM_H_
#define MAIN_PRM_H_

//-------------------------------------- Include Files ----------------------------------------------------------------
#include "..\Header\C_Types.h"
#include "..\Header\Appl.h"
#include "..\Header\Display.h"
#include "..\Header\Gpio.h"
#include "..\Header\Adc.h"
#include "..\Header\Timer.h"
#include "..\Header\Hal.h"
#include "..\Header\LumSensor.h"
#include "..\Header\GardenLumControl.h"
#include "..\Header\Pwm.h"
#include "..\Header\Servo.h"

//-------------------------------------- Defines ----------------------------------------------------------------

#define USE_FIXED_TIME_SLOT	ENABLED //ENABLED//

#define SLOT_TIME	 _1MS	//_1MS  // _4MS  // _10MS  

#define WATCHDOG_ENABLE  	 ENABLED// //DISABLED

#define INITIALIZE_TASKS()\
{\
	ADC__Initialize();\
	Pwm__Initialize();\
	Hal__Initialize();\
	Display__Initialize();\
	Timer__Initialize();\
	Servo__Initialize();\
	IlumSensor__Initialize();\
	Garden_Lum_Control__Initialize();\
	Appl__Initialize();\
	}

#define ALL_SLOTS_TASKS()\
{\
	ADC__Handler();\
	Timer__HMSHandler();\
	Hal__FastHandler();\
}


#define SLOT_1_TASKS()\
{\
	Servo__Background();\
	Hal__BackgroundHandler();\
}

#define SLOT_2_TASKS()\
{\
	Appl__Handler();\
	Display__Handler();\
}
	
#define SLOT_3_TASKS()\
{\
	IlumSensor__ConversionHandler();\
}
	
#define SLOT_4_TASKS()\
{\
	Garden_Lum_Control__Handler();\
}
	
#define SLOT_5_TASKS()\
{\	
}

#endif /* MAIN_PRM_H_ */
