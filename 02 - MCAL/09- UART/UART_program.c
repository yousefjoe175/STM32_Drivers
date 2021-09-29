#include "STD_TYPES.h"
#include "BIT_MATH.h"


#include "SYSTICK_interface.h"

#include "UART_interface.h"
#include "UART_config.h"
#include "UART_private.h"
#if DMA == ENABLE
	#include "DMA_interface.h"
#endif

void emptyfunc(void){

}

void (*UART_UserTransmissionCallBack)(void);

void UART_TransmissionCallback(void){
	/*Wait for TC flag*/
	while(GET_BIT(UART->SR, UART_TC) == 0);
	/* clear the TC flag */
	CLR_BIT(UART->SR,UART_TC);
	/* disable the transmission */
	CLR_BIT(UART->CR1,UART_TE);
	/* call the user callback */
	UART_UserTransmissionCallBack();
}

void (*UART_UserReceptionionCallBack)(void);

void UART_ReceptionCallBack(void){
	/* disable the receiver */
	CLR_BIT(UART->CR1,UART_RE);
	/* call the user callback */
	UART_UserReceptionionCallBack();
}

void MUART_voidInitialize(void)
{
	/* set UART enable */
	SET_BIT(UART->CR1,UART_UE);
	/* set the baud rate */
#if 	UART_BAUD_RATE == 4800
	UART->BBR = 0x683;
#elif	UART_BAUD_RATE == 9600
	UART->BBR = 0x341;
#elif	UART_BAUD_RATE == 38400
	UART->BBR = 0xD0;
#elif	UART_BAUD_RATE == 115200
	UART->BBR = 0x45;
#endif

}
	

/*Transmission */
void MUART_voidTransmitSynch(u8 copy_u8Data){
	/* enable the transmitter */
	SET_BIT(UART->CR1,UART_TE);
	/* put the data in DR */
	UART->DR = copy_u8Data;
	/* wait for the transmission is completed */
	while(GET_BIT(UART->SR,UART_TC) == 0);
	/* clear the TC flag */
	CLR_BIT(UART->SR,UART_TC);
	/* disable the transmission */
	CLR_BIT(UART->CR1,UART_TE);
}

//send the null character also
void MUART_voidTransmitStringSynch(u8 *ptr_u8DataBuffer){
	u8 Local_counter = 0;
	/* enable the transmitter */
	SET_BIT(UART->CR1,UART_TE);
	while(ptr_u8DataBuffer[Local_counter] != '\0'){
		/* check if the DR is empty */
		while(GET_BIT(UART->SR, UART_TXE) == 0);
		UART->DR = ptr_u8DataBuffer[Local_counter++];
	}
	/*putting the last data */
//	UART->DR = ptr_u8DataBuffer[Local_counter];
	/*wait for TC flag*/
	while(GET_BIT(UART->SR, UART_TC) == 0);
	/* clear the TC flag */
	CLR_BIT(UART->SR,UART_TC);
	/* disable the transmission */
	CLR_BIT(UART->CR1,UART_TE);
}

void MUART_voidTransmitMultipleDataSynch(u8 *ptr_u8DataBuffer, u16 copy_u16NumberOfData){
	/* enable the transmitter */
	SET_BIT(UART->CR1,UART_TE);
	for(u16 i=0;i < copy_u16NumberOfData; i++ ){
		/* check if the DR is empty */
		while(GET_BIT(UART->SR,UART_TXE) == 0);
		UART->DR = ptr_u8DataBuffer[i];
	}
	/*wait for TC flag*/
	while(GET_BIT(UART->SR, UART_TC) == 0);
	/* clear the TC flag */
	CLR_BIT(UART->SR,UART_TC);
	/* disable the transmission */
	CLR_BIT(UART->CR1,UART_TE);
}

#if DMA == ENABLE
//call DMAMemoryToPeripheral and set DMA in CR2 and wait for callback if exits
void MUART_voidTransmitAsynchDMA(u8 *ptr_u8DataBuffer, u16 copy_u16NumberOfData, void(*ptr)(void)){
	UART_UserTransmissionCallBack = ptr;
	/* enable the DMAT */
	SET_BIT(UART->CR3,UART_DMAT);
	/* set the DMA channel*/
	MDMA_voidSendDataMemoryToPeripheral(DMA_CHANNEL4,	//DMA channel 4 for UART1_TX 
										(u32*)ptr_u8DataBuffer,
										(u32*)&(UART->DR),
										copy_u16NumberOfData);
	MDMA_voidSetInterruptHandler(DMA_CHANNEL4,UART_TransmissionCallback);
	MDMA_voidEnableDMA(DMA_CHANNEL4);
	/*enable the transmitter */
	SET_BIT(UART->CR1,UART_TE);
}
#endif
/* Reception */
u8 MUART_voidReceiveSynch(u8 *ptr_u8DataBuffer, u32 copy_u32TicksToWait){
	u8 Local_u8State = 0;
	/* enable the receiver */
	SET_BIT(UART->CR1,UART_RE);
	/* wait for the received */
	if(copy_u32TicksToWait == -1) //wait forever
	{
		while(GET_BIT(UART->SR,UART_RXNE) == 0);
		*ptr_u8DataBuffer = UART->DR;
		CLR_BIT(UART->SR,UART_RXNE);
		Local_u8State = 1;
	}
	else
	{
		MSYSTICK_voidSetTickCount(copy_u32TicksToWait);
		while(MSYSTICK_u32GetRemainingTime() != 0 ){
			if(GET_BIT(UART->SR,UART_RXNE) == 1){
				*ptr_u8DataBuffer = UART->DR;
				CLR_BIT(UART->SR,UART_RXNE);
				Local_u8State = 1;
				break;
			}
		}
	}
	//disable the timer
	MSYSTICK_voidStopInterval();
	// disable the receiver
	CLR_BIT(UART->CR1,UART_RE);
	return Local_u8State;
}


void MUART_voidReceiveStringSynch(u8 *ptr_u8DataBuffer){
	u16 i = 0;
	u8 Local_u8Data = -1;
	/* enable the receiver */
	SET_BIT(UART->CR1,UART_RE);
	while(Local_u8Data != '\0'){
		//wait for data to be received
		while(GET_BIT(UART->SR,UART_RXNE) == 0);
		//get the received data
		Local_u8Data = UART->DR;
		ptr_u8DataBuffer[i++] = Local_u8Data;
		// clear the flag
		CLR_BIT(UART->SR,UART_RXNE);
	}
	// disable the receiver
	CLR_BIT(UART->CR1,UART_RE);
}


void MUART_voidReceiveMultipleDataSynch(u8 *ptr_u8DataBuffer, u16 copy_u16NumberOfData){
	/* enable the receiver */
	SET_BIT(UART->CR1,UART_RE);
	for(u16 i=0; i<copy_u16NumberOfData;i++){
		while(GET_BIT(UART->SR,UART_RXNE) == 0);
		ptr_u8DataBuffer[i] = UART->DR;
		CLR_BIT(UART->SR,UART_RXNE);
	}
	// disable the receiver
	CLR_BIT(UART->CR1,UART_RE);
}

#if DMA == ENABLE
void MUART_voidReceiveAsynchDMA(u8 *ptr_u8DataBuffer, u16 copy_u16NumberOfData, void(*ptr)(void)){
	UART_UserReceptionionCallBack = ptr;
	/* enable the DMAT */
	SET_BIT(UART->CR3,UART_DMAR);
	/* set the DMA channel*/
	MDMA_voidReceiveDataPeripheralToMemory(DMA_CHANNEL5,	//DMA channel 4 for UART1_TX
										   (u32*)&(UART->DR),
										   (u32*)ptr_u8DataBuffer,
										   copy_u16NumberOfData);
	MDMA_voidSetInterruptHandler(DMA_CHANNEL5,UART_ReceptionCallBack);
	MDMA_voidEnableDMA(DMA_CHANNEL5);
	/*enable the receiver */
	SET_BIT(UART->CR1,UART_RE);
}
#endif
