#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H

#define UART_TX_PIN		GPIOA,PIN9
#define UART_RX_PIN		GPIOA,PIN10


void MUART_voidInitialize(void);
	

/*Transmission */
void MUART_voidTransmitSynch(u8 copy_u8Data);
//send the null character also
void MUART_voidTransmitStringSynch(u8 *ptr_u8DataBuffer);
void MUART_voidTransmitMultipleDataSynch(u8 *ptr_u8DataBuffer, u16 copy_u16NumberOfData);

#if DMA == ENABLE
	//call DMAMemoryToPeripheral and set DMA in CR2 and wait for callback if exits
	void MUART_voidTransmitAsynchDMA(u8 *ptr_u8DataBuffer, u16 copy_u16NumberOfData, void(*ptr)(void));
#endif

/* Reception */
u8 MUART_voidReceiveSynch(u8 *ptr_u8DataBuffer, u32 copy_u32TicksToWait);
void MUART_voidReceiveMultipleDataSynch(u8 *ptr_u8DataBuffer, u16 copy_u16NumberOfData);
void MUART_voidReceiveStringSynch(u8 *ptr_u8DataBuffer);

#if DMA == ENABLE
	void MUART_voidReceiveAsynchDMA(u8 *ptr_u8DataBuffer, u16 copy_u16NumberOfData, void(*ptr)(void));
#endif


#endif
