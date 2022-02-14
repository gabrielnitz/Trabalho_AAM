
#ifndef C_TYPES_H_
#define C_TYPES_H_

//#include <hidef.h> 
//-------------------------------------- Defines, Enumerations -------------------------------------------------------------

enum
{
	OFF = 0,
	NOT_COMPLETED = 0,
	INACTIVE = 0,
	LOW = 0,
	DESLIGADO = 0,
	DOWN = 0,
	LIGADO =1,
	ON = 1,
	COMPLETED = 1,
	ACTIVE = 1,
	HIGH = 1,
	UP = 1
};

#define ENABLED		1
#define DISABLED 	0

#define BIT_TEST(mem,bit)   ((mem)&(1UL<<(bit))) //This macro is used to perform test on bit of the data
#define BIT_SET(mem,bit)    ((mem)|=(1UL<<(bit))) //This macro is used to set the bit of the data
#define BIT_CLR(mem,bit)    ((mem)&=~(1UL<<(bit))) //This macro is used to clear the bit of the data
#define BIT_TOGGLE(mem,bit) ((mem)^=(1UL<<(bit))) //This macro is used to toggle the bit of the data

#endif /* C_TYPES_H_ */
