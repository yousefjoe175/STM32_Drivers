#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "SYSTICK_interface.h"
#include "GPIO_interface.h"
#include "UART_interface.h"


u8 ParseData(u8* copy_u8DataBuffer);

u8 DataBuffer[100];	//takes only data line by line
u8 counter;
u8 BLerase;
u8 flash_state = 1;
typedef void (*Function_t)(void);
Function_t addr_to_call = 0;

void func(void)
{
#define SCB_VTOR   *((volatile u32*)0xE000ED08)

	SCB_VTOR = 0x08001000;

	addr_to_call = *(Function_t*)(0x08001004);
	addr_to_call();
}


void main(void){
	/* RCC */
	MRCC_voidInitializeSystemClock();
	/* UART enable */
	MRCC_voidEnablePeripheralClock(RCC_APB2, 14);
	/* GPIO enable Port A*/
	MRCC_voidEnablePeripheralClock(RCC_APB2, 2);
	
	/* SYSTICK */
	MSYSTICK_voidInitialize();
	
	/* GPIO */
	//set TX and RX as output and input AFIO
	MGPIO_voidSetPinMode(UART_TX_PIN, OUTPUT_2MHZ_AF_PP);
	MGPIO_voidSetPinMode(UART_RX_PIN, INPUT_FLOATING);
	
	/* UART */
	MUART_voidInitialize();
	
	while(MUART_voidReceiveSynch(&DataBuffer[counter],15000000) == 1){
		if(BLerase == 0){
			FPEC_voidEraseAppArea();
			BLerase = 1;
		}
		if(DataBuffer[counter] == '\n'){
			//perform the parsing
			flash_state = ParseData(DataBuffer);
			MUART_voidTransmitStringSynch("OK");
			if(flash_state == 0){ //we reached the end of file so no more flashing
				func();
				return;
			}
			else if(flash_state == 1){	//there're more data to be received
				//reset the counter
				counter = 0;
			}
			else if (flash_state == -1){ //didn't receive the line properly (didn't find ':')
				counter = 0;
			}
		}else{
			counter++;
		}
		
	}	
	
}