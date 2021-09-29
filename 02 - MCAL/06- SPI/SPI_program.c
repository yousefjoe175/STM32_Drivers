#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "DMA_interface.h"

#include "SPI_interface.h"
#include "SPI_config.h"
#include "SPI_private.h"


void (*SPI1_CallBack)(void);

void SPI1_DMACallBack(void){
	MSPI_voidDisablePeripheral();
	SPI1_CallBack();
}

u8 SPI_SendCounter = 0;
u8 SPI_ReceiveCounter = 0;
u8 SPI_BufferSize;


#if DATA_FRAME == EIGHT_BIT
u8 *SPI_TransmitBuffer, *SPI_ReceiveBuffer;
#elif DATA_FRAME == SIXTEEN_BIT
u16 *SPI_TransmitBuffer, *SPI_ReceiveBuffer;
#endif

static void SPI_SendReceiveCallBack(void){
	if(SPI_SendCounter < SPI_BufferSize){	//Transmit and Receive
		if((GET_BIT(SPI->SR, 1)) == 1){
			SPI->DR = SPI_TransmitBuffer[SPI_SendCounter++];
		}
		if((GET_BIT(SPI->SR, 0)) == 1){
			SPI_ReceiveBuffer[SPI_ReceiveCounter++] = SPI->DR;
		}
	}else{
		if((GET_BIT(SPI->SR, 0)) == 1){	//Receive the last byte
			SPI_ReceiveBuffer[SPI_ReceiveCounter++] = SPI->DR;
		}
		CLR_BIT(SPI->CR2,6);
		CLR_BIT(SPI->CR2,7);
	}
}



void MSPI_voidModeInitialize(void){
	u32 Local_temp = 0;
#if MODE == FULL_DUPLEX
	CLR_BIT(Local_temp, 15);
	CLR_BIT(Local_temp, 14);
#elif MODE == BIDIRECTIONAL	//half duplex		
	SET_BIT(Local_temp,15);	//set or reset bit-14 when transmitting or receiving 
#elif MODE == UNI_RECEIVE
	CLR_BIT(Local_temp, 15);
	CLR_BIT(Local_temp, 14);
	SET_BIT(Local_temp, 10);
#elif MODE == UNI_TRANSMIT
	CLR_BIT(Local_temp, 15);
	CLR_BIT(Local_temp, 14);
	CLR_BIT(Local_temp, 10);
#endif

#if DATA_FRAME == EIGHT_BIT
	CLR_BIT(Local_temp, 11);
#elif DATA_FRAME == SIXTEEN_BIT
	SET_BIT(Local_temp, 11);
#endif

#if LSBFIRST == TRUE
	SET_BIT(Local_temp, 7);
#elif LSBFIRST == FALSE
	CLR_BIT(Local_temp, 7);
#endif

#if SLAVE_SELECT == SOFTWARE
	SET_BIT(Local_temp,9);
#elif SLAVE_SELECT == HARDWARE
	CLR_BIT(Local_temp,9);
#endif

	SET_VAL(Local_temp,3,BAUD_RATE);
	
#if CLOCK_POL_PHASE == LOW_IDLE_LEADING
	CLR_BIT(Local_temp, 0);
	CLR_BIT(Local_temp, 1);
#elif CLOCK_POL_PHASE == LOW_IDLE_TRAILING
	SET_BIT(Local_temp, 1);
	CLR_BIT(Local_temp, 1);
#elif CLOCK_POL_PHASE == HIGH_IDLE_LEADING
	CLR_BIT(Local_temp,0);
	SET_BIT(Local_temp,1);

#elif CLOCK_POL_PHASE == HIGH_IDLE_TRAILING
	SET_BIT(Local_temp, 1);
	SET_BIT(Local_temp,1);
#endif

#if OPERATION == MASTER
	SET_BIT(Local_temp,2);
#elif OPERATION == SLAVE
	CLR_BIT(Local_temp,2);
#endif
	SPI->CR1 = Local_temp;
}


void MSPI_voidSendReceiveMasterSynchronous(u16 copy_u16Sentdata, u16* ptr_u16Received){
	SET_BIT(SPI->CR1,6);	//enable the SPI
#if MODE == FULL_DUPLEX
	SPI->DR = copy_u16Sentdata;
	while(!GET_BIT(SPI->SR,1)); //wait for the transmit to be finished
	while(!GET_BIT(SPI->SR,0));	//wait for the data to be received
	*ptr_u16Received = SPI->DR;
#elif MODE == BIDIRECTIONAL
	SPI->DR = copy_u16Sentdata;
	while(!GET_BIT(SPI->SR,1)); //wait for the transmit to be finished
#elif MODE == UNI_TRANSMIT
	SPI->DR = copy_u16Sentdata;
	while(!GET_BIT(SPI->SR,1)); //wait for the transmit to be finished
#elif MODE == UNI_RECEIVE
	while(!GET_BIT(SPI->SR,0));	
	*ptr_u16Received = SPI->DR;
#endif
}


void MSPI_voidSendReceiveBurstMasterAsynchronous(u16* ptr_u16TransmitBuffer, u16* ptr_u16ReceiveBuffer, u8 copy_u8BufferSize, void (*ptr)(void)){
	SET_BIT(SPI->CR1,6);	//enable the SPI
	SPI_BufferSize = copy_u8BufferSize;
	SPI1_CallBack = ptr;
#if DATA_FRAME == EIGHT_BIT
	SPI_TransmitBuffer = (u8*) ptr_u16TransmitBuffer;
	SPI_ReceiveBuffer  = (u8*) ptr_u16ReceiveBuffer;
#elif DATA_FRAME == SIXTEEN_BIT
	SPI_TransmitBuffer =  ptr_u16TransmitBuffer;
	SPI_ReceiveBuffer  =  ptr_u16ReceiveBuffer;
#endif
	SET_BIT(SPI->CR2,6);	//RXNEIE
	SET_BIT(SPI->CR2,7);	//TXEIE
	SPI->DR = SPI_TransmitBuffer[SPI_SendCounter++];
}


void MSPI_voidSetSlaveNSSPinMode(u8 copy_u8PortID, u8 copy_u8PinID){
	MGPIO_voidSetPinMode(copy_u8PortID, copy_u8PinID, OUTPUT_2MHZ_PP);
#if SLAVE_SELECT == HARDWARE
	MGPIO_voidSetPinValue( copy_u8PortID, copy_u8PinID, GPIO_HIGH); 
#endif
}


void MSPI_voidSlaveSelect(u8 copy_u8PortID, u8 copy_u8PinID, u8 state){
#if SLAVE_SELECT == HARDWARE
	if(state == 1){
		MGPIO_voidSetPinValue( copy_u8PortID, copy_u8PinID, GPIO_LOW); 
	}else{
		MGPIO_voidSetPinValue( copy_u8PortID, copy_u8PinID, GPIO_HIGH); 
	}
#endif
}


void MSPI_voidDisablePeripheral(void){
	while(!GET_BIT(SPI->SR,7)){
		CLR_BIT(SPI->CR1,6);
	}
}


void MSPI_voidReceiveSlaveSynchronous(u16* ptr_u16TransmitBuffer, u16* ptr_u16ReceiveBuffer){
	SET_BIT(SPI->CR1,6);	//enable the SPI
	SPI->DR = *ptr_u16TransmitBuffer;
	while(!GET_BIT(SPI->SR, 0));
	*ptr_u16ReceiveBuffer = SPI->DR;
}


void MSPI_voidReceiveSlaveAsynchronous(u16* ptr_u16TransmitBuffer, u16* ptr_u16ReceiveBuffer, u8 copy_u8BufferSize, void (*ptr)(void)){
	SPI_BufferSize = copy_u8BufferSize;
	SPI1_CallBack = ptr;
#if DATA_FRAME == EIGHT_BIT
	SPI_TransmitBuffer = (u8*) ptr_u16TransmitBuffer;
	SPI_ReceiveBuffer  = (u8*) ptr_u16ReceiveBuffer;
#elif DATA_FRAME == SIXTEEN_BIT
	SPI_TransmitBuffer =  ptr_u16TransmitBuffer;
	SPI_ReceiveBuffer  =  ptr_u16ReceiveBuffer;
#endif
	SET_BIT(SPI->CR1,6);	//enable the SPI
	SET_BIT(SPI->CR2,6);	//RXNEIE
	SET_BIT(SPI->CR2,7);	//TXEIE
	SPI->DR = SPI_TransmitBuffer[SPI_SendCounter++];
}


void MSPI_voidDMATransmitterReceiver(u16* ptr_u16TransmitBuffer, u16* ptr_u16ReceiveBuffer, u16  copy_u16NumberOfData, void (*ptr)(void)){
	SPI1_CallBack = ptr;
	#if MODE == FULL_DUPLEX	||	MODE == BIDIRECTIONAL
		SET_BIT(SPI->CR2, 1);	//TX DMA
		SET_BIT(SPI->CR2, 0);	//RX DMA
		MDMA_voidSendDataMemoryToPeripheral(DMA_CHANNEL3,	//DMA channel 3 for SPI1_TX 
											(u32*)ptr_u16TransmitBuffer,
											(u32*)&(SPI->DR),
											 copy_u16NumberOfData);
		MDMA_voidSendDataMemoryToPeripheral(DMA_CHANNEL2,	//DMA channel 2 for SPI1_RX 
											(u32*)&(SPI->DR),
											(u32*)ptr_u16ReceiveBuffer,
											 copy_u16NumberOfData); 
		MDMA_voidSetInterruptHandler(DMA_CHANNEL2,SPI1_DMACallBack);	//enable the interrupt for RX only 
		MDMA_voidEnableDMA(DMA_CHANNEL2);
		MDMA_voidEnableDMA(DMA_CHANNEL3);
		SET_BIT(SPI->CR1,6);	//enable the SPI
	#elif MODE == UNI_RECEIVE
		SET_BIT(SPI->CR2, 0);	//RX DMA
		MDMA_voidSendDataMemoryToPeripheral(DMA_CHANNEL2,	//DMA channel 2 for SPI1_RX 
											(u32*)&(SPI->DR),
											(u32*)ptr_u16ReceiveBuffer,
											 copy_u16NumberOfData); 
		MDMA_voidSetInterruptHandler(DMA_CHANNEL2,SPI1_DMACallBack);	//enable the interrupt for RX only 
		MDMA_voidEnableDMA(DMA_CHANNEL2);
		SET_BIT(SPI->CR1,6);	//enable the SPI
	#elif MODE == UNI_TRANSMIT
		SET_BIT(SPI->CR2, 1);	//TX DMA
		MDMA_voidSendDataMemoryToPeripheral(DMA_CHANNEL3,	//DMA channel 3 for SPI1_TX 
											(u32*)ptr_u16TransmitBuffer,
											(u32*)&(SPI->DR),
											 copy_u16NumberOfData); 
		MDMA_voidSetInterruptHandler(DMA_CHANNEL3,SPI1_DMACallBack);	//enable the interrupt for TX only 
		MDMA_voidEnableDMA(DMA_CHANNEL3);
		SET_BIT(SPI->CR1,6);	//enable the SPI
	#endif
}


void SPI1_IRQHandler(void){
#if OPERATION == MASTER
	SPI_SendReceiveCallBack();
#elif OPERATION == SLAVE
	SPI_SendReceiveCallBack();
#endif
	SPI1_CallBack();
}
