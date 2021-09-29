#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "EXTI_private.h"
#include "EXTI_config.h"
#include "EXTI_interface.h"
#include "RCC_interface.h"

void (*EXTI0_CallBack)(void);
void (*EXTI1_CallBack)(void);
void (*EXTI2_CallBack)(void);
void (*EXTI3_CallBack)(void);
void (*EXTI4_CallBack)(void);



void MEXTI_voidEnableInterruptLine(u8 copy_u8LineID, u8 copy_u8SenseMode){
	
	switch(copy_u8SenseMode){
		case RISING_EDGE : SET_BIT(EXTI->RTSR, copy_u8LineID); break;
		
		case FALLING_EDGE: SET_BIT(EXTI->FTSR, copy_u8LineID); break;
		
		case ON_CHANGE	 : SET_BIT(EXTI->RTSR, copy_u8LineID);
	                       SET_BIT(EXTI->FTSR, copy_u8LineID);
						   break;
		default:    break;
			//error
	}        
	SET_BIT(EXTI->IMR, copy_u8LineID);
	
}

void MEXTI_voidSwtichPort(u8 copy_u8LineID, u8 copy_u8PortID){
	#define AFIO_EXTICR1	*((u32*)(0x40010008))
	#define AFIO_EXTICR2	*((u32*)(0x4001000C))
	MRCC_voidEnablePeripheralClock(RCC_APB2, 0);
	if(copy_u8LineID < 4){
		switch(copy_u8LineID){
			case 0: SET_VAL(AFIO_EXTICR1, 0, copy_u8PortID); break;
			case 1: SET_VAL(AFIO_EXTICR1, 4, copy_u8PortID); break;
			case 2: SET_VAL(AFIO_EXTICR1, 8, copy_u8PortID); break;
			case 3: SET_VAL(AFIO_EXTICR1, 12, copy_u8PortID); break;
			default:    break;
				//error
		}
	}else if(copy_u8LineID == 4){
		SET_VAL(AFIO_EXTICR2, 0 , copy_u8PortID);
	}
}


void MEXTI_voidDisableInterruptLine(u8 copy_u8LineID){
	CLR_BIT(EXTI->IMR, copy_u8LineID);
}


void MEXTI_voidSetPendingInterrupt(u8 copy_u8LineID){
	SET_BIT(EXTI->SWIER, copy_u8LineID);
	SET_BIT(EXTI->PR, copy_u8LineID);
}

void MEXTI_voidSetCallBack(u8 copy_u8LineID, void(*ptr)(void)){
	switch(copy_u8LineID){
		case EXTI_LINE0:	EXTI0_CallBack = ptr; break;
		case EXTI_LINE1:	EXTI1_CallBack = ptr; break;
		case EXTI_LINE2:	EXTI2_CallBack = ptr; break;
		case EXTI_LINE3:	EXTI3_CallBack = ptr; break;
		case EXTI_LINE4:	EXTI4_CallBack = ptr; break;
		default:    break;
			//error
	}
}


void EXTI0_IRQHandler(void){
	EXTI0_CallBack();
	SET_BIT(EXTI->PR, 0);
}


void EXTI1_IRQHandler(void){
	EXTI1_CallBack();
	SET_BIT(EXTI->PR, 1);
}


void EXTI2_IRQHandler(void){
	EXTI2_CallBack();
	SET_BIT(EXTI->PR, 2);
}


void EXTI3_IRQHandler(void){
	EXTI3_CallBack();
	SET_BIT(EXTI->PR, 3);
}


void EXTI4_IRQHandler(void){
	EXTI4_CallBack();
	SET_BIT(EXTI->PR, 4);
}

