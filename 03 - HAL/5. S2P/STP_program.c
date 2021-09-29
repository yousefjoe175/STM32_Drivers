#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "SYSTICK_interface.h"
#include "GPIO_interface.h"

#include "STP_interface.h"
#include "STP_config.h"
#include "STP_private.h"

void HSTP_voidInitialize(void){
	MGPIO_voidSetPinMode(SERIAL_DATA,	OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinMode(SHIFT_CLOCK,	OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinMode(STORAGE_CLOCK, OUTPUT_2MHZ_PP);	
	
}



void HSTP_voidSendData(u32 copy_u32DataSent, u8 copy_numberOfBytes){
	s8 counter;
	u8 bit;
	for(counter = 7*copy_numberOfBytes; counter >=0; counter--)
	{
		bit = GET_BIT(copy_u32DataSent, counter);
		MGPIO_voidSetPinValue(SERIAL_DATA, bit);
		
		/* edge on shift clock pin */
		MGPIO_voidSetPinValue(SHIFT_CLOCK, GPIO_HIGH);
		MSYSTICK_voidSetBusyWait(1);
		MGPIO_voidSetPinValue(SHIFT_CLOCK, GPIO_LOW);
		MSYSTICK_voidSetBusyWait(1);
	}
	/*edge on storage clock pin */
	MGPIO_voidSetPinValue(STORAGE_CLOCK, GPIO_HIGH);
	MSYSTICK_voidSetBusyWait(1);
	MGPIO_voidSetPinValue(STORAGE_CLOCK, GPIO_LOW);
	MSYSTICK_voidSetBusyWait(1);
}