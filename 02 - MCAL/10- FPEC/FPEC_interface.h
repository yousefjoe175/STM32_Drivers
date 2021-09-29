#ifndef		FPEC_INTERFACE_H
#define		FPEC_INTERFACE_H


void FPEC_voidEraseAppArea(void);
	
void FPEC_voidFlashPageErase(u8 Copy_u8PageNumber);

void FPEC_voidFlashWrite(u32 Copy_u32Address, u16* Copy_u16Data, u8 Copy_u8Length);

u32 FPEC_u32FlashRead(u32 Copy_u32Address);

#endif