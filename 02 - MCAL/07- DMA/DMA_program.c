#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "DMA_interface.h"
#include "DMA_config.h"
#include "DMA_private.h"


void (*MDMA_handler1)(void);
void (*MDMA_handler2)(void);
void (*MDMA_handler3)(void);
void (*MDMA_handler4)(void);
void (*MDMA_handler5)(void);
void (*MDMA_handler6)(void);
void (*MDMA_handler7)(void);

/* try to change the parameters into struct bit field */ 
void MDMA_voidInitialize(u8 copy_u8ChannelID, 		//0->6
						 u8 copy_u8Mem2Mem,			//1-> memory to memory
						 u8 copy_u8SIZE,			//0-> 8bit, 1->16bit,2->32bit
						 u8 copy_u8MemoryIncrement,	//1 -> memory, 0 -> peripheral
						 u8 copy_u8PeripheralIncrement,		//1 -> memory, 0 -> peripheral
						 u8 copy_u8PeriorityLevel,	
						 u8 copy_u8Circular		
						 )							
{
	if(copy_u8ChannelID>7){
		//error
		return;
	}
	switch(copy_u8Mem2Mem){
		case 0:	
		case 1: 
			SET_VAL(DMA->channel[copy_u8ChannelID].CCR,DMA_MEM2MEM, copy_u8Mem2Mem); break;
		default: /*error */ break;
	}
	switch(copy_u8SIZE){
		case 0:	
		case 1:
		case 2:
			SET_VAL(DMA->channel[copy_u8ChannelID].CCR,DMA_MSIZE, copy_u8SIZE); break;
			SET_VAL(DMA->channel[copy_u8ChannelID].CCR,DMA_PSIZE, copy_u8SIZE); break;
		default: /*error */ break;
	}
	switch(copy_u8MemoryIncrement){
		case 0:	
		case 1: 
			SET_VAL(DMA->channel[copy_u8ChannelID].CCR,DMA_MINC, copy_u8MemoryIncrement); break;
		default: /*error */ break;
	}
	switch(copy_u8PeripheralIncrement){
		case 0:	
		case 1: 
			SET_VAL(DMA->channel[copy_u8ChannelID].CCR,DMA_PINC, copy_u8PeripheralIncrement); break;
		default: /*error */ break;
	}
	switch(copy_u8PeriorityLevel){
		case 0:	
		case 1:
		case 2:
		case 3:
			SET_VAL(DMA->channel[copy_u8ChannelID].CCR,DMA_PL, copy_u8PeriorityLevel); break;
		default: /*error */ break;
	}
	switch(copy_u8Circular){
		case 0:	
		case 1: 
			SET_VAL(DMA->channel[copy_u8ChannelID].CCR,DMA_CIRC, copy_u8Circular); break;
		default: /*error */ break;
	}
	/* always set direction to 1 source is memory, destination is peripheral */
	SET_BIT(DMA->channel[copy_u8ChannelID].CCR,DMA_DIR);
	/* always set transmission complete interrupt */
	SET_BIT(DMA->channel[copy_u8ChannelID].CCR,DMA_TCIE);
}

void MDMA_voidSendDataMemoryToMemory(u8 copy_u8ChannelID, 
									 u32* ptr_u32SourceAddress,
									 u32* ptr_u32DestinationAddress,
									 u16 copy_u16NumberofData)
{
	DMA->channel[copy_u8ChannelID].CMAR = ptr_u32SourceAddress;							 
	DMA->channel[copy_u8ChannelID].CPAR = ptr_u32DestinationAddress;
	DMA->channel[copy_u8ChannelID].CNDTR = copy_u16NumberofData;
}

/* calling before configuring the DMA request in the peripheral driver */
/* choosing a peripheral from the peripheral macros */
void MDMA_voidSendDataMemoryToPeripheral(u8 copy_u8ChannelID,
										 u32* ptr_u32SourceAddress,
										 u32* ptr_u32DestinationAddress,
										 u16 copy_u16NumberofData)
{
	DMA->channel[copy_u8ChannelID].CMAR = ptr_u32SourceAddress;
	DMA->channel[copy_u8ChannelID].CPAR = ptr_u32DestinationAddress;
	DMA->channel[copy_u8ChannelID].CNDTR = copy_u16NumberofData;
}

/* calling before configuring the DMA request in the peripheral driver */
/* choosing a peripheral from the peripheral macros */
void MDMA_voidReceiveDataPeripheralToMemory(u8 copy_u8ChannelID,
											u32* ptr_u32SourceAddress,
											u32* ptr_u32DestinationAddress,
											u16 copy_u16NumberofData)
{
	DMA->channel[copy_u8ChannelID].CMAR = ptr_u32SourceAddress;
	DMA->channel[copy_u8ChannelID].CPAR = ptr_u32DestinationAddress;
	DMA->channel[copy_u8ChannelID].CNDTR = copy_u16NumberofData;
}

void MDMA_voidEnableDMA(u8 copy_u8ChannelID)
{
	SET_BIT(DMA->channel[copy_u8ChannelID].CCR,DMA_EN); 
}

void MDMA_voidDisableDMA(u8 copy_u8ChannelID){
	CLR_BIT(DMA->channel[copy_u8ChannelID].CCR,DMA_EN); 
}

void MDMA_voidSetInterruptHandler(u8 copy_u8ChannelID,void (*ptr)(void)){
	switch (copy_u8ChannelID){
		case 0:
			MDMA_handler1 = ptr;	break;
		case 1:
			MDMA_handler2 = ptr;	break;
		case 2:
			MDMA_handler3 = ptr;	break;
		case 3:
			MDMA_handler4 = ptr;	break;
		case 4:
			MDMA_handler5 = ptr;	break;
		case 5:
			MDMA_handler6 = ptr;	break;
		case 6:
			MDMA_handler7 = ptr;	break;
		default:	/*error*/
			break;
	}
}


void DMA1_Channel1_IRQHandler(void){
	MDMA_handler1();
	SET_BIT(DMA->IFCR, DMA_CGIF);
}
void DMA1_Channel2_IRQHandler(void){
	MDMA_handler2();
	SET_BIT(DMA->IFCR,4 + DMA_CGIF);
}
void DMA1_Channel3_IRQHandler(void){
	MDMA_handler3();
	SET_BIT(DMA->IFCR,8+ DMA_CGIF);
}
void DMA1_Channel4_IRQHandler(void){
	MDMA_handler4();
	SET_BIT(DMA->IFCR,12+ DMA_CGIF);
}
void DMA1_Channel5_IRQHandler(void){
	MDMA_handler5();
	SET_BIT(DMA->IFCR,16+ DMA_CGIF);
}
void DMA1_Channel6_IRQHandler(void){
	MDMA_handler6();
	SET_BIT(DMA->IFCR,20+ DMA_CGIF);
}
void DMA1_Channel7_IRQHandler(void){
	MDMA_handler7();
	SET_BIT(DMA->IFCR,24+ DMA_CGIF);
}
