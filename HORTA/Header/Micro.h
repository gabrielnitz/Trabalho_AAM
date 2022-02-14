
#ifndef MICRO_H_
#define MICRO_H_


// #include <hidef.h> 
#include <avr/io.h> 
//***********************************************************************************************************
// ************************************  MACROS *************************************************************
//***********************************************************************************************************
#define DISABLE_INTERRUPT() __asm SEI;
#define ENABLE_INTERRUPT()  __asm CLI;

//***********************************************************************************************************
// ************************************  Enums, Structs *****************************************************
//***********************************************************************************************************
//union Low Byte bit definitions Bits 0 - 7
typedef union
{
    unsigned char byte;
    struct
    {
        unsigned char bit0 :1;
        unsigned char bit1 :1;
        unsigned char bit2 :1;
        unsigned char bit3 :1;
        unsigned char bit4 :1;
        unsigned char bit5 :1;
        unsigned char bit6 :1;
        unsigned char bit7 :1;
    } bit;
} DEF_LOWBYTE;

//union High Byte bit definitions Bits 8 - 15
typedef union
{
    unsigned char byte;
    struct
    {
    	unsigned char bit8 :1;
    	unsigned char bit9 :1;
    	unsigned char bit10 :1;
    	unsigned char bit11 :1;
    	unsigned char bit12 :1;
    	unsigned char bit13 :1;
    	unsigned char bit14 :1;
    	unsigned char bit15 :1;
    } bit;
} DEF_HIBYTE;

//***********************************************************************************************************
// ***************************  GPIO Ports Registers ********************************************************
//***********************************************************************************************************

// Port Data and Direction Registers
typedef struct
{
    volatile DEF_LOWBYTE DATA_IN_REG;
    volatile DEF_LOWBYTE DIRECION_REG;
	volatile DEF_LOWBYTE DATA_OUT_PULL_REG;
} GPIO_DATA_TYPE;

// Port Data and Direction Registers Address
#define GPIOB_DATA  (*((volatile GPIO_DATA_TYPE *)0x00000023))    //Port B Data Register
#define GPIOC_DATA  (*((volatile GPIO_DATA_TYPE *)0x00000026))    //Port C Data Register
#define GPIOD_DATA  (*((volatile GPIO_DATA_TYPE *)0x00000029))    //Port D Data Register


#define PORTB_MICRO  &GPIOB_DATA
#define PORTC_MICRO  &GPIOC_DATA
#define PORTD_MICRO  &GPIOD_DATA


#define GPIO_DATA {PORTB_MICRO, PORTC_MICRO, PORTD_MICRO};

//***********************************************************************************************************
// **********************************  ADC Registers ********************************************************
//***********************************************************************************************************


// ADC Registers
typedef struct
{
    volatile DEF_LOWBYTE ADCL_REG;  /*** ADCL  - Data Result Low  Register;    0x00000078 ***/
    volatile DEF_HIBYTE  ADCH_REG;  /*** ADCH  - Data Result High Register;    0x00000079 ***/
    volatile DEF_LOWBYTE ADCSRA_REG;                /*** ADCSRA - ADC Control and Status  Register A;  0x0000007A ***/
    volatile DEF_LOWBYTE ADCSRB_REG;                  /*** ADCSRB - ADC Control and Status  Register B;    0x0000007B ***/
    volatile DEF_LOWBYTE ADMUX_REG;						/*** ADMUX - ADC Multiplexer election Register;        0x0000007C ***/
    volatile DEF_LOWBYTE LIXO;                          /*** espaço deixado pelo fabricante    ***/
	volatile DEF_LOWBYTE DIDR0_REG;						 /*** DIDR0 - Digital Input Disable Register;        0x0000007E ***/
    volatile DEF_LOWBYTE DIDR1_REG;						/*** DIDR1 - Digital Input Disable Register;        0x0000007F ***/
} ADC_REG_TYPE;

// Port Data and Direction Registers Address
#define ADC_ADCL  (*((volatile ADC_REG_TYPE *)0x00000078))	/*** ADCL  - Data Result Low  Register;    0x00000078 ***/
#define ADC_ADCH  (*((volatile ADC_REG_TYPE *)0x00000079))   /*** ADCH  - Data Result High Register;    0x00000079 ***/
#define ADC_ADCSRA   (*((volatile ADC_REG_TYPE *)0x0000007A))    /*** ADCRH  - Data Result High Register;     0x00000012 ***/
#define ADC_ADCSRB   (*((volatile ADC_REG_TYPE *)0x0000007B))    /*** ADCRL  - Data Result Low Register;      0x00000013 ***/
#define ADC_ADMUX  (*((volatile ADC_REG_TYPE *)0x0000007C))    /*** ADCCVH - Compare Value High Register;   0x00000014 ***/
#define ADC_DIDR0  (*((volatile ADC_REG_TYPE *)0x0000007E))    /*** ADCCVL - Compare Value Low Register;    0x00000015 ***/
#define ADC_DIDR1  (*((volatile ADC_REG_TYPE *)0x0000007F))    /*** ADCCFG - Configuration Register;        0x00000016 ***/

#define ADC_REGISTERS  &ADC_ADCL	

// PWM registers

typedef struct
{
	volatile DEF_LOWBYTE  TCCR0A_REG;  //*** TCCR0A  - Timer/Counter Control 0 Register A;    0x00000044 ***/
	volatile DEF_LOWBYTE  TCCR0B_REG;  //*** TCCR0B  - Timer/Counter Control 0 Register B;    0x00000045 ***/
	volatile DEF_LOWBYTE  TCNT0_REG;   //*** TCNT0   - Timer/Counter 0 Register;              0x00000046 ***/
	volatile DEF_LOWBYTE  OCR0A_REG;   //*** OCR0A   - Output Compare 0 Register A;           0x00000047 ***/
	volatile DEF_LOWBYTE  OCR0B_REG;   //*** OCR0B   - Output Compare 0 Register B;           0x00000048 ***/
} TC0_REG_TYPE;

// TC0 Registers Address
#define TC0_TCCR0A  (*((volatile TC0_REG_TYPE *)0x00000044))	/*** TCCR0A  - Timer/Counter Control 0 Register A;    0x00000044 ***/
#define TC0_TCCR0B  (*((volatile TC0_REG_TYPE *)0x00000045))    /*** TCCR0B  - Timer/Counter Control 0 Register B;    0x00000045 ***/
#define TC0_TCNT0   (*((volatile TC0_REG_TYPE *)0x00000046))    /*** TCNT0   - Timer/Counter 0 Register;              0x00000046 ***/
#define TC0_OCR0A   (*((volatile TC0_REG_TYPE *)0x00000047))    /*** OCR0A   - Output Compare 0 Register A;           0x00000047 ***/
#define TC0_OCR0B  (*((volatile TC0_REG_TYPE *)0x00000048))     /*** OCR0B   - Output Compare 0 Register B;           0x00000048 ***/

#define TC0_REGISTERS  &TC0_TCCR0A

typedef struct
{
	volatile DEF_LOWBYTE  TCCR1A_REG;  /*** TCCR1A  - Timer/Counter Control 1 Register A;    0x00000080 ***/
	volatile DEF_LOWBYTE  TCCR1B_REG;  /*** TCCR1B  - Timer/Counter Control 1 Register B;    0x00000081 ***/
	volatile DEF_LOWBYTE  TCCR1C_REG;  /*** TCCR1C  - Timer/Counter Control 1 Register c;    0x00000082 ***/
	volatile DEF_LOWBYTE  LIXO;    /*** espaço deixado pelo fabricante    ***/
	volatile DEF_LOWBYTE  TCNT1L_REG;  /*** TCNT1L   - Timer/Counter 1 Low Register;        0x00000084 ***/
	volatile DEF_HIBYTE   TCNT1H_REG;  /*** TCNT1H   - Timer/Counter 1 High Register;       0x00000085 ***/
	volatile DEF_LOWBYTE  ICR1L_REG;   /*** ICR1L   - Input capture Low Register 1;          0x00000086 ***/
	volatile DEF_HIBYTE   ICR1H_REG;   /*** ICR1H   - Input capture High Register 1;         0x00000087 ***/
	volatile DEF_LOWBYTE  OCR1AL_REG;  /*** OCR1AL   - Output Compare 1 Low Register A;     0x00000088 ***/
	volatile DEF_HIBYTE   OCR1AH_REG;  /*** OCR1AH   - Output Compare 1 High Register A;    0x00000089 ***/
	volatile DEF_LOWBYTE  OCR1BL_REG;  /*** OCR1BL   - Output Compare 1 Low Register B;     0x0000008A ***/
	volatile DEF_HIBYTE   OCR1BH_REG;  /*** OCR1BH   - Output Compare 1 High Register B;    0x0000008B ***/
} TC1_REG_TYPE;

// TC1 Registers Address
#define TC1_TCCR1A  (*((volatile TC1_REG_TYPE *)0x00000080))	/*** TCCR1A  - Timer/Counter Control 1 Register A;    0x00000080 ***/
#define TC1_TCCR1B  (*((volatile TC1_REG_TYPE *)0x00000081))    /*** TCCR1B  - Timer/Counter Control 1 Register B;    0x00000081 ***/
#define TC1_TCCR1C  (*((volatile TC1_REG_TYPE *)0x00000082))    /*** TCCR1B  - Timer/Counter Control 1 Register C;    0x00000082 ***/
#define TC1_TCNT1L   (*((volatile TC1_REG_TYPE *)0x00000084))    /*** TCNT1L   - Timer/Counter 1 Low Register;        0x00000084 ***/
#define TC1_TCNT1H   (*((volatile TC1_REG_TYPE *)0x00000085))    /*** TCNT1H   - Timer/Counter 1 High Register;       0x00000085 ***/
#define TC1_ICR1L   (*((volatile TC1_REG_TYPE *)0x00000086))    /*** ICR1L   - Input capture Low Register 1;          0x00000086 ***/
#define TC1_ICR1H   (*((volatile TC1_REG_TYPE *)0x00000087))    /*** ICR1H   - Input capture High Register 1;         0x00000087 ***/
#define TC1_OCR1AL   (*((volatile TC1_REG_TYPE *)0x00000088))    /*** OCR1AL   - Output Compare 0 Low Register A;     0x00000088 ***/
#define TC1_OCR1AH   (*((volatile TC1_REG_TYPE *)0x00000089))    /*** OCR1AH   - Output Compare 0 High Register A;    0x00000089 ***/
#define TC1_OCR1BL  (*((volatile TC1_REG_TYPE *)0x0000008A))     /*** OCR1BL   - Output Compare 0 Low Register B;     0x0000008A ***/
#define TC1_OCR1BH  (*((volatile TC1_REG_TYPE *)0x0000008B))     /*** OCR1BH   - Output Compare 0 High Register B;     0x0000008B ***/

#define TC1_REGISTERS  &TC1_TCCR1A

typedef struct
{
	volatile DEF_LOWBYTE  TCCR2A_REG;  /*** TCCR2A  - Timer/Counter Control 2 Register A;    0x000000B0 ***/
	volatile DEF_LOWBYTE  TCCR2B_REG;  /*** TCCR2B  - Timer/Counter Control 2 Register B;    0x000000B1 ***/
	volatile DEF_LOWBYTE  TCNT2_REG;   /*** TCNT2   - Timer/Counter 2 Register;              0x000000B2 ***/
	volatile DEF_LOWBYTE  OCR2A_REG;   /*** OCR2A   - Output Compare 2 Register A;           0x000000B3 ***/
	volatile DEF_LOWBYTE  OCR2B_REG;   /*** OCR2B   - Output Compare 2 Register B;           0x000000B4 ***/
} TC2_REG_TYPE;

// TC2 Registers Address
#define TC2_TCCR2A  (*((volatile TC2_REG_TYPE *)0x000000B0))	/*** TCCR2A  - Timer/Counter Control 0 Register A;    0x000000B0 ***/
#define TC2_TCCR2B  (*((volatile TC2_REG_TYPE *)0x000000B1))    /*** TCCR2B  - Timer/Counter Control 0 Register B;    0x000000B1 ***/
#define TC2_TCNT2   (*((volatile TC2_REG_TYPE *)0x000000B2))    /*** TCNT2   - Timer/Counter 0 Register;              0x000000B2 ***/
#define TC2_OCR2A   (*((volatile TC2_REG_TYPE *)0x000000B3))    /*** OCR2A   - Output Compare 0 Register A;           0x000000B3 ***/
#define TC2_OCR2B  (*((volatile TC2_REG_TYPE  *)0x000000B4))     /*** OCR2B   - Output Compare 0 Register B;           0x000000B4 ***/

#define TC2_REGISTERS  &TC2_TCCR2A


#endif /* MICRO_H_ */