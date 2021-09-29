/*
 * main.c
 *
 *  Created on: Aug 30, 2021
 *      Author: Yousef_Khaled
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "NVIC_interface.h"
#include "SYSTICK_interface.h"
#include "EXTI_interface.h"


volatile u8 flag = 0;
volatile u32 dataArray[50] = {0};
volatile u32 i = 0;

void ahmed(void){
	asm("NOP");
}

void get_frame(void){
	if(flag == 0){
		MSYSTICK_voidSetIntervalSingle(1000000,ahmed);
		flag = 1;
	}else{
		dataArray[i++] = MSYSTICK_u32GetElapsedTime();
		MSYSTICK_voidSetIntervalSingle(1000000,ahmed);
	}
	//MGPIO_voidTogglePinValue(GPIOA,1);
}


void main(void){
	/* RCC */
	MRCC_voidInitializeSystemClock();
	MRCC_voidEnablePeripheralClock(RCC_APB2,2);

	/* GPIO */
	MGPIO_voidSetPinMode(GPIOA,0,INPUT_FLOATING);
	//MGPIO_voidSetPinValue(GPIOA,0,GPIO_HIGH);
	MGPIO_voidSetPinMode(GPIOA,1,OUTPUT_2MHZ_PP);

	/* SYSTICK */
	MSYSTICK_voidInitialize();

	/*EXTI*/
	MEXTI_voidEnableInterruptLine(0,FALLING_EDGE);
	MEXTI_voidSetCallBack(0,get_frame);

	/*NVIC */
	MNVIC_voidInitialize();
	MNVIC_voidEnableInterrupt(6);
	while(1);
}

