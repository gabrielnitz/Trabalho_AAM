
#include <avr/io.h>
#include "..\Header\Gpio.h"
#include "..\Header\Hal.h"
#include "..\Header\Pwm.h"
#include "..\Header\Micro.h"

 
void Pwm__Initialize(void){
volatile TC2_REG_TYPE *pwm_pt2;
volatile TC0_REG_TYPE *pwm_pt0;

pwm_pt2 = TC2_REGISTERS;
pwm_pt0 = TC0_REGISTERS;

bitWrite(DDRD, 5, OUTPUT_DIGITAL);

pwm_pt0->TCCR0A_REG.byte =  0b00110011;

Pwm__SetTCFrequency(PWM_TC0, SERVO_DEFAULT_FREQ);
Pwm__SetDutyCycle(PWM1, SERVO_OFF_DUTY);

}

 
void Pwm__SetTCFrequency( PWM_TC_TYPE tc, unsigned short int frequency){
volatile TC0_REG_TYPE *pwm_pt0;
volatile TC1_REG_TYPE *pwm_pt1;
volatile TC2_REG_TYPE *pwm_pt2;

pwm_pt0 = TC0_REGISTERS;
pwm_pt1 = TC1_REGISTERS;
pwm_pt2 = TC2_REGISTERS;



if((frequency > 20) && (frequency  < 40) ){
switch(tc){
case PWM_TC0:
   pwm_pt0->TCCR0B_REG.byte = 0x05; //prescaler = 1024 dando frequencia de 30Hz
   break;   
case PWM_TC1:
	pwm_pt1->TCCR1B_REG.byte = 0x02; //prescaler = 8 dando frequencia de 4000Hz
	break;
case PWM_TC2:
	pwm_pt2->TCCR2B_REG.byte = 0x05; //prescaler = 8 dando frequencia de 4000Hz   	
	break;

default:
	break;
}
}
}  // fim da função


void Pwm__SetDutyCycle( PWM_ID_TYPE pwm, unsigned char duty){
volatile TC0_REG_TYPE *pwm_pt0;
volatile TC1_REG_TYPE *pwm_pt1;
volatile TC2_REG_TYPE *pwm_pt2;

pwm_pt0 = TC0_REGISTERS;
pwm_pt1 = TC1_REGISTERS;
pwm_pt2 = TC2_REGISTERS;
if (duty >100)
   duty = 100;
switch (pwm){
case PWM0:
	pwm_pt0->OCR0A_REG.byte = (unsigned char)(255*duty/100); //considerando TOP = 255
	break;
case PWM1:
	pwm_pt0->OCR0B_REG.byte = (unsigned char)(255*duty/100); //considerando TOP = 255
	break;
case PWM2:
	pwm_pt1->OCR1AH_REG.byte = (unsigned char)(255*duty/100); //considerando TOP = 255
 	break;    // tem que checar para 16 bits
case PWM3:
	 pwm_pt1->OCR1BH_REG.byte = (unsigned char)(255*duty/100); //considerando TOP = 255
	 break;    // tem que checar para 16 bits
case PWM4:
	 pwm_pt2->OCR2A_REG.byte = (unsigned char)(255*duty/100); //considerando TOP = 255
	 break;    // tem que checar para 16 bits
case PWM5:
	pwm_pt2->OCR2B_REG.byte = (unsigned char)(255*duty/100); //considerando TOP = 255
	break;    // tem que checar para 16 bits
default:
	break;	
}
}

