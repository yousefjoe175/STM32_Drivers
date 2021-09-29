#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "FPEC_interface.h"
#include "FPEC_config.h"
#include "FPEC_private.h"

void FPEC_voidEraseAppArea(void){
	for(u8 i = 4; i<64; i++){
		FPEC_voidFlashPageErase(i);		
	}
}


void FPEC_voidFlashPageErase(u8 Copy_u8PageNumber){
	//wait for Busy flag
	while(GET_BIT(FPEC->SR, BSY) == 1);
	
	//check on the lock
	if(GET_BIT(FPEC->CR, LOCK) == 1){
		//perform the unlock sequence
		FPEC->KEYR = FPEC_KEY1;
		FPEC->KEYR = FPEC_KEY2;
	}
	
	//set the mode to page erase
	SET_BIT(FPEC->CR, PER);
	//set the address of the page to be erased
	FPEC->AR = (u32)(Copy_u8PageNumber * 1024) + FLASH_MEMORY_ADDRESS;
	//set the start bit
	SET_BIT(FPEC->CR, STRT);
	//wait for the busy flag
	while(GET_BIT(FPEC->SR, BSY) == 1);
	
}


void FPEC_voidFlashWrite(u32 Copy_u32Address, u16* Copy_u16Data, u8 Copy_u8Length){
	u8 counter = 0;
	
	//wait for Busy flag
	while(GET_BIT(FPEC->SR, BSY) == 1);
	
	//check on the lock
	if(GET_BIT(FPEC->CR, LOCK) == 1){
		//perform the unlock sequence
		FPEC->KEYR = FPEC_KEY1;
		FPEC->KEYR = FPEC_KEY2;
	}
	
	//set PG bit in CR
	SET_BIT(FPEC->CR, PG);
	
	while(counter < Copy_u8Length){
		//in flash we write 16 bit data
		*((u16*)(Copy_u32Address)) = Copy_u16Data[counter];
		//increase the address passed by copy by 2 bytes
		Copy_u32Address+=2;
		counter++;
		//wait for the operation to end
		while(GET_BIT(FPEC->SR, BSY) == 1);
		//reset the EOP flag
		SET_BIT(FPEC->SR, EOP);
	}
	
	
}


u32 FPEC_u32FlashRead(u32 Copy_u32Address){
	return *((u32*)(Copy_u32Address));
}