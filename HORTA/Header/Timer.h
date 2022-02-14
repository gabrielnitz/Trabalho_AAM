
#ifndef TIMER_H_
#define TIMER_H_

//-------------------------------------- Include Files ----------------------------------------------------------------
#include "..\Header\Timer_prm.h"

//-------------------------------Defines-----------------------
typedef enum                                            
{
	TIMER_EXPIRED = 0,
	TIMER_IS_RUNNING = 1,
}TIMER_STATUS;



//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================

void Timer__Initialize(void);

void Timer__MsHandler(void);
void Timer__MsSet(MS_TIMER_NAME, unsigned short int);
void Timer__MsExpire(MS_TIMER_NAME);
TIMER_STATUS Timer__MsGetStatus(MS_TIMER_NAME);

void Timer__HMSHandler(void);
void Timer__HMSSet(HMS_TIMER_NAME, unsigned char, unsigned char, unsigned char);
void Timer__HMSExpire(HMS_TIMER_NAME);
TIMER_STATUS Timer__HMSGetStatus(HMS_TIMER_NAME);
unsigned char Timer__HMSGetTime (HMS_TIMER_NAME id);

// Protótipo da função de interrupção
ISR(TIMER1_OVF_vect); // Protótipo da Interrupção TIMER1.  Tabela de vetores pag. 158

#endif /* TIMER_H_ */
