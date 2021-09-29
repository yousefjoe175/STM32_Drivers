#ifndef DMA_INTERFACE_H
#define DMA_INTERFACE_H

/* always set direction to 1 source is memory, destination is peripheral */
/*to get the DMA request of a certian peripheral check the data sheet to know what channel to activate*/
void MDMA_voidInitialize(u8 copy_u8ChannelID, 
						 u8 copy_u8Mem2Mem,			//1-> memory to memory
						 u8 copy_u8SIZE,			//0-> 8bit, 1->16bit,2->32bit
						 u8 copy_u8MemoryIncrement,	//1 -> memory, 0 -> peripheral
						 u8 copy_u8PeripheralIncrement,		//1 -> memory, 0 -> peripheral
						 u8 copy_u8PeriorityLevel,			//0,1,2,3 from Low to High
						 u8 copy_u8Circular		
						 );


void MDMA_voidSendDataMemoryToMemory(u8 copy_u8ChannelID, 
									 u32* ptr_u32SourceAddress,
									 u32* ptr_u32DestinationAddress,
									 u16 copy_u16NumberofData);
							 
void MDMA_voidSendDataMemoryToPeripheral(u8 copy_u8ChannelID,
										 u32* ptr_u32SourceAddress,
										 u32* ptr_u32DestinationAddress,
										 u16 copy_u16NumberofData);
										 
void MDMA_voidReceiveDataPeripheralToMemory(u8 copy_u8ChannelID,
											u32* ptr_u32SourceAddress,
											u32* ptr_u32DestinationAddress,
											u16 copy_u16NumberofData);
									
void MDMA_voidSetInterruptHandler(u8 copy_u8ChannelID,void (*ptr)(void));
									
void MDMA_voidEnableDMA(u8 copy_u8ChannelID);

void MDMA_voidDisableDMA(u8 copy_u8ChannelID);


/* relate the addresses macros with user interface macros */
#define DMA_SPI		DMA_SPI_DR_AD

#define DMA_CHANNEL1	0
#define DMA_CHANNEL2	1
#define DMA_CHANNEL3	2
#define DMA_CHANNEL4	3
#define DMA_CHANNEL5	4
#define DMA_CHANNEL6	5
#define DMA_CHANNEL7	6


#endif