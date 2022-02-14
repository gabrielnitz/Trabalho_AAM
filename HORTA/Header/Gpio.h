
#ifndef GPIO1_H_
#define GPIO1_H_


// ********************arduino ****************************
#define set_bit(Y,bit_x) (Y|=(1<<bit_x)) /*ativa o bit x da
variável Y (coloca em 1)*/
#define clr_bit(Y,bit_x) (Y&=~(1<<bit_x)) /*limpa o bit x da variável Y
(coloca em 0)*/
#define tst_bit(Y,bit_x) (Y&(1<<bit_x)) /*testa o bit x da variável Y
(retorna 0 ou 1)*/
#define cpl_bit(Y,bit_x) (Y^=(1<<bit_x)) /*troca o estado do bit x da
variável Y (complementa)*/

#define SW_OFF 1     
#define SW_ON  0


// ********************arduino ****************************
// LEDS
#define LED1 PB5 //LED1 é o substituto de PB5 na programação
#define LED2 PB4 //LED2 é o substituto de PB4 na programação
#define LED3 PB3 //LED3 é o substituto de PB3 na programação
#define LED4 PB2 //LED4 é o substituto de PB2 na programação 
#define LAMPADA_A PD6
// CHAVES
#define SW1  PC1 //SW1  é o substituto de PC1 na programação   
#define SW2  PC2 //SW2  é o substituto de PC2 na programação
#define SW3  PC3 //SW3  é o substituto de PC3 na programação
#define SW4  PB1 //SW4  COLOCADO EXTERNAMENTE
// 7 segmentos
#define LATCH_PIN     PD4   // pino 11 (shiftclk do 74HC595)
#define CLK_PIN       PD7   // pino 12 (latchclk do 74HC595)
#define DATA_PIN      PB8   // pino 14 (serial data input do 74HC595)



#define  bitSet(valor,bit) ((valor) |= ( 1UL << (bit)))
#define  bitClear(valor,bit) ((valor) &= ~( 1UL << (bit)))
#define  bitWrite(valor,bit,bitvalue)  (bitvalue? bitSet (valor, bit): bitClear (valor, bit))

// *****************arduino ***************************


//-------------------------------------- Defines, Enumerations ----------------------------------------------------------------

typedef enum
{ 
	INPUT_DIGITAL_PULLUP = 0,
	OUTPUT_DIGITAL
} GPIO_PIN_TYPE;

#define PORT_DATA_TYPE  unsigned char       //This define is mandatory, it defines the register's type

typedef enum
{
	PORT_B = 0,
	PORT_C,
	PORT_D,
	NUM_OF_PORTS 
}GPIO_PORT;

#define MAX_NUM_OF_PORT_PINS 8
#define MAX_NUM_OF_PORTS 	 3


//=====================================================================================================================
//-------------------------------------- PUBLIC (Function Prototypes) -------------------------------------------------
//=====================================================================================================================

void Gpio__PinConfig(GPIO_PORT port,unsigned char pin,GPIO_PIN_TYPE type);
void Gpio__PinWrite(GPIO_PORT port,unsigned char pin,unsigned char value);
unsigned char Gpio__PinRead(GPIO_PORT port,unsigned char pin);

#endif /* GPIO_H_ */