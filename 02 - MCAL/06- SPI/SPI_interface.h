#ifndef SPI_INTERFACE_H
#define SPI_INTERFACE_H

void MSPI_voidModeInitialize(void);

void MSPI_voidSendReceiveMasterSynchronous(u16 copy_u16Sentdata, u16* ptr_u16Received);
void MSPI_voidSendReceiveBurstMasterAsynchronous(u16* ptr_u16TransmitBuffer, u16* ptr_u16ReceiveBuffer, u8 copy_u8BufferSize, void (*ptr)(void));

void MSPI_voidSetSlaveNSSPinMode(u8 copy_u8PortID, u8 copy_u8PinID);
void MSPI_voidSlaveSelect(u8 copy_u8PortID, u8 copy_u8PinID, u8 state);

void MSPI_voidReceiveSlaveSynchronous(u16* ptr_u16TransmitBuffer, u16* ptr_u16ReceiveBuffer);
void MSPI_voidReceiveSlaveAsynchronous(u16* ptr_u16TransmitBuffer, u16* ptr_u8ReceiveBuffer, u8 copy_u8BufferSize, void (*ptr)(void));

void MSPI_voidDMATransmitterReceiver(u16* ptr_u16TransmitBuffer, u16* ptr_u16ReceiveBuffer, u16  copy_u16NumberOfData, void (*ptr)(void));

void MSPI_voidDisablePeripheral(void);


#endif