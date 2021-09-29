#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "NVIC_config.h"
#include "NVIC_private.h"
#include "NVIC_interface.h"


/*To Be Deleted after setting SCB driver */
void MNVIC_voidInitialize (void){
	#define SCB_AIRCR	*((u32*)(0xE000ED0C))
	SCB_AIRCR = GROUP_SUB_DISTRIBUTION;
}

void MNVIC_voidSetPriority (u8 copy_u8Peripheral, u8 copy_u8Priority){
	NVIC_IPR[copy_u8Peripheral] = copy_u8Priority;
}

/* check register description data sheet pg.204 for peripheral interrupt number (position number)*/
void MNVIC_voidEnableInterrupt (u8 copy_u8InterruptNumber){
	if(copy_u8InterruptNumber <= 31){
		/*we WON'T use this in NVIC as writing 0 won't affect so we don't have to consume time for ORing*/
		/*SET_BIT(NVIC_ISER0,copy_u8InterruptNumber);*/
	
		NVIC_ISER0 = (1<<copy_u8InterruptNumber);
		
	}else if(copy_u8InterruptNumber <=59){
		copy_u8InterruptNumber-=32;
		NVIC_ISER1 = (1<<copy_u8InterruptNumber);
		
	}else{
		//error
	}
}


void MNVIC_voidDisableInterrupt (u8 copy_u8InterruptNumber){
	if(copy_u8InterruptNumber <= 31){
		/*we WON'T use this in NVIC as writing 0 won't affect so we don't have to consume time for ORing*/
		/*SET_BIT(NVIC_ISER0,copy_u8InterruptNumber);*/
	
		NVIC_ICER0 = (1<<copy_u8InterruptNumber);
	
	}else if(copy_u8InterruptNumber <=59){
		copy_u8InterruptNumber-=32;
		NVIC_ICER1 = (1<<copy_u8InterruptNumber);
	
	}else{
		//error
	}
}

void MNVIC_voidSetPendingFlag(u8 copy_u8InterruptNumber){
	if(copy_u8InterruptNumber <= 31){
		/*we WON'T use this in NVIC as writing 0 won't affect so we don't have to consume time for ORing*/
		/*SET_BIT(NVIC_ISER0,copy_u8InterruptNumber);*/
	
		NVIC_ISPR0 = (1<<copy_u8InterruptNumber);
	
	}else if(copy_u8InterruptNumber <=59){
		copy_u8InterruptNumber-=32;
		NVIC_ISPR1 = (1<<copy_u8InterruptNumber);
	
	}else{
		//error
	}
}

void MNVIC_voidClearPendingFlag (u8 copy_u8InterruptNumber){
	if(copy_u8InterruptNumber <= 31){
		/*we WON'T use this in NVIC as writing 0 won't affect so we don't have to consume time for ORing*/
		/*SET_BIT(NVIC_ISER0,copy_u8InterruptNumber);*/
	
		NVIC_ICPR0 = (1<<copy_u8InterruptNumber);
	
	}else if(copy_u8InterruptNumber <=59){
		copy_u8InterruptNumber-=32;
		NVIC_ICPR1 = (1<<copy_u8InterruptNumber);
	
	}else{
		//error
	}
}


u8 MNVIC_u8GetActiveFlag (u8 copy_u8InterruptNumber){
	u8 Local_u8ActiveFlag;
	if(copy_u8InterruptNumber <= 31){
		/*we WON'T use this in NVIC as writing 0 won't affect so we don't have to consume time for ORing*/
		/*SET_BIT(NVIC_ISER0,copy_u8InterruptNumber);*/
	
		copy_u8InterruptNumber = GET_BIT(NVIC_IABR0, copy_u8InterruptNumber);

	}else if(copy_u8InterruptNumber <=59){
		copy_u8InterruptNumber-=32;
		copy_u8InterruptNumber = GET_BIT(NVIC_IABR1, copy_u8InterruptNumber);
	}else{
		//error
	}
	return Local_u8ActiveFlag;
}