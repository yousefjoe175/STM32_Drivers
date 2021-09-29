#ifndef EXTI_PRIVATE_H
#define EXTI_PRIVATE_H


typedef struct{
	volatile u32 IMR	 ;
	volatile u32 EMR     ;
	volatile u32 RTSR    ;
	volatile u32 FTSR    ;
	volatile u32 SWIER   ;
	volatile u32 PR      ;
}EXTI_TYPE;
#define EXTI 	((EXTI_TYPE*)(0x40010400))
/*EXTI->IMR = value;*/

#define EXTI_LINE0	0
#define EXTI_LINE1	1
#define EXTI_LINE2	2
#define EXTI_LINE3	3
#define EXTI_LINE4	4



#endif