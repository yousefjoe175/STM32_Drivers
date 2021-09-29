#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "SYSTICK_interface.h"
#include "SPI_interface.h"

#include "TFT_interface.h"
#include "TFT_private.h"
#include "TFT_config.h"

void HTFT_voidInitialize (void)
{
	/* PINS directions */
	MGPIO_voidSetPinMode(RESET_PIN, OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinMode(A0_PIN   , OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinMode(GPIOA, PIN5, OUTPUT_2MHZ_AF_PP);
	MGPIO_voidSetPinMode(GPIOA, PIN7, OUTPUT_2MHZ_AF_PP);

	
	/* Reset pulse */
	MGPIO_voidSetPinValue(RESET_PIN, GPIO_HIGH);
	MSYSTICK_voidSetBusyWait(100);
	
	MGPIO_voidSetPinValue(RESET_PIN, GPIO_LOW);
	MSYSTICK_voidSetBusyWait(1);
	
	MGPIO_voidSetPinValue(RESET_PIN, GPIO_HIGH);
	MSYSTICK_voidSetBusyWait(100);
	
	MGPIO_voidSetPinValue(RESET_PIN, GPIO_LOW);
	MSYSTICK_voidSetBusyWait(100);
	
	MGPIO_voidSetPinValue(RESET_PIN, GPIO_HIGH);
	MSYSTICK_voidSetBusyWait(120000);
	
	/* sleep out mode */
	u16 temp;
	MGPIO_voidSetPinValue(A0_PIN, GPIO_LOW);
	MSPI_voidSendReceiveMasterSynchronous(0x11, &temp);
	
	/* wait 150 msec */
	MSYSTICK_voidSetBusyWait(150000);
	
	/* Color mode */
	MGPIO_voidSetPinValue(A0_PIN, GPIO_LOW);  // COMMAND
	MSPI_voidSendReceiveMasterSynchronous(0x3A, &temp);
	
	MGPIO_voidSetPinValue(A0_PIN, GPIO_HIGH); // DATA
	MSPI_voidSendReceiveMasterSynchronous(0x05, &temp);
	
	/* display on */
	MGPIO_voidSetPinValue(A0_PIN, GPIO_LOW);  // COMMAND
	MSPI_voidSendReceiveMasterSynchronous(0x29, &temp);
}

void HTFT_voidDisplayImage (const u16 *Ptr_u16Image)
{
	/* set x address */
	u16 temp;
	MGPIO_voidSetPinValue(A0_PIN, GPIO_LOW);  // COMMAND
	MSPI_voidSendReceiveMasterSynchronous(0x2A, &temp);
	
	MGPIO_voidSetPinValue(A0_PIN, GPIO_HIGH); // DATA
	MSPI_voidSendReceiveMasterSynchronous(0, &temp);
	
	MGPIO_voidSetPinValue(A0_PIN, GPIO_HIGH); // DATA
	MSPI_voidSendReceiveMasterSynchronous(0, &temp);
	
	MGPIO_voidSetPinValue(A0_PIN, GPIO_HIGH); // DATA
	MSPI_voidSendReceiveMasterSynchronous(0, &temp);
	
	MGPIO_voidSetPinValue(A0_PIN, GPIO_HIGH); // DATA
	MSPI_voidSendReceiveMasterSynchronous(127, &temp);
	
	
	/* set y address */
	MGPIO_voidSetPinValue(A0_PIN, GPIO_LOW);  // COMMAND
	MSPI_voidSendReceiveMasterSynchronous(0x2B, &temp);
	
	MGPIO_voidSetPinValue(A0_PIN, GPIO_HIGH); // DATA
	MSPI_voidSendReceiveMasterSynchronous(0, &temp);
	
	MGPIO_voidSetPinValue(A0_PIN, GPIO_HIGH); // DATA
	MSPI_voidSendReceiveMasterSynchronous(0, &temp);
	
	MGPIO_voidSetPinValue(A0_PIN, GPIO_HIGH); // DATA
	MSPI_voidSendReceiveMasterSynchronous(0, &temp);
	
	MGPIO_voidSetPinValue(A0_PIN, GPIO_HIGH); // DATA
	MSPI_voidSendReceiveMasterSynchronous(159, &temp);
	
	
	/* RAM write */
	MGPIO_voidSetPinValue(A0_PIN, GPIO_LOW);  // COMMAND
	MSPI_voidSendReceiveMasterSynchronous(0x2C, &temp);
	
	u8 data;
	for(u16 counter=0; counter<20480; counter++)
	{
		data = Ptr_u16Image[counter] >> 8;
		MGPIO_voidSetPinValue(A0_PIN, GPIO_HIGH); // DATA
	    MSPI_voidSendReceiveMasterSynchronous(data, &temp);
	    
		data = Ptr_u16Image[counter];
	    MGPIO_voidSetPinValue(A0_PIN, GPIO_HIGH); // DATA
	    MSPI_voidSendReceiveMasterSynchronous(data, &temp);
	}

}


void HTFT_voidFillColor(u16 copy_u16Color)
{
	/* set x address */
	u16 temp;
	MGPIO_voidSetPinValue(A0_PIN, GPIO_LOW);  // COMMAND
	MSPI_voidSendReceiveMasterSynchronous(0x2A, &temp);

	MGPIO_voidSetPinValue(A0_PIN, GPIO_HIGH); // DATA
	MSPI_voidSendReceiveMasterSynchronous(0, &temp);

	MGPIO_voidSetPinValue(A0_PIN, GPIO_HIGH); // DATA
	MSPI_voidSendReceiveMasterSynchronous(0, &temp);

	MGPIO_voidSetPinValue(A0_PIN, GPIO_HIGH); // DATA
	MSPI_voidSendReceiveMasterSynchronous(0, &temp);

	MGPIO_voidSetPinValue(A0_PIN, GPIO_HIGH); // DATA
	MSPI_voidSendReceiveMasterSynchronous(127, &temp);


	/* set y address */
	MGPIO_voidSetPinValue(A0_PIN, GPIO_LOW);  // COMMAND
	MSPI_voidSendReceiveMasterSynchronous(0x2B, &temp);

	MGPIO_voidSetPinValue(A0_PIN, GPIO_HIGH); // DATA
	MSPI_voidSendReceiveMasterSynchronous(0, &temp);

	MGPIO_voidSetPinValue(A0_PIN, GPIO_HIGH); // DATA
	MSPI_voidSendReceiveMasterSynchronous(0, &temp);

	MGPIO_voidSetPinValue(A0_PIN, GPIO_HIGH); // DATA
	MSPI_voidSendReceiveMasterSynchronous(0, &temp);

	MGPIO_voidSetPinValue(A0_PIN, GPIO_HIGH); // DATA
	MSPI_voidSendReceiveMasterSynchronous(159, &temp);


	/* RAM write */
	MGPIO_voidSetPinValue(A0_PIN, GPIO_LOW);  // COMMAND
	MSPI_voidSendReceiveMasterSynchronous(0x2C, &temp);

	u8 data;
	for(u16 counter=0; counter<20480; counter++)
	{
		data = copy_u16Color>> 8;
		MGPIO_voidSetPinValue(A0_PIN, GPIO_HIGH); // DATA
	    MSPI_voidSendReceiveMasterSynchronous(data, &temp);

		data = copy_u16Color;
	    MGPIO_voidSetPinValue(A0_PIN, GPIO_HIGH); // DATA
	    MSPI_voidSendReceiveMasterSynchronous(data, &temp);
	}
}


void HTFT_voidDrawRectangle (u8 x1, u8 x2, u8 y1, u8 y2, u16 color)
{
	u16 size = (x2 - x1)*(y2 - y1);
	/* set x address */
	u16 temp;
	MGPIO_voidSetPinValue(A0_PIN, GPIO_LOW);  // COMMAND
	MSPI_voidSendReceiveMasterSynchronous(0x2A, &temp);

	MGPIO_voidSetPinValue(A0_PIN, GPIO_HIGH); // DATA
	MSPI_voidSendReceiveMasterSynchronous(0, &temp);

	MGPIO_voidSetPinValue(A0_PIN, GPIO_HIGH); // DATA
	MSPI_voidSendReceiveMasterSynchronous(x1, &temp);

	MGPIO_voidSetPinValue(A0_PIN, GPIO_HIGH); // DATA
	MSPI_voidSendReceiveMasterSynchronous(0, &temp);

	MGPIO_voidSetPinValue(A0_PIN, GPIO_HIGH); // DATA
	MSPI_voidSendReceiveMasterSynchronous(x2, &temp);


	/* set y address */
	MGPIO_voidSetPinValue(A0_PIN, GPIO_LOW);  // COMMAND
	MSPI_voidSendReceiveMasterSynchronous(0x2B, &temp);

	MGPIO_voidSetPinValue(A0_PIN, GPIO_HIGH); // DATA
	MSPI_voidSendReceiveMasterSynchronous(0, &temp);

	MGPIO_voidSetPinValue(A0_PIN, GPIO_HIGH); // DATA
	MSPI_voidSendReceiveMasterSynchronous(y1, &temp);

	MGPIO_voidSetPinValue(A0_PIN, GPIO_HIGH); // DATA
	MSPI_voidSendReceiveMasterSynchronous(0, &temp);

	MGPIO_voidSetPinValue(A0_PIN, GPIO_HIGH); // DATA
	MSPI_voidSendReceiveMasterSynchronous(y2, &temp);


	/* RAM write */
	MGPIO_voidSetPinValue(A0_PIN, GPIO_LOW);  // COMMAND
	MSPI_voidSendReceiveMasterSynchronous(0x2C, &temp);

	u8 data;
	for(u16 counter=0; counter<size-20; counter++)
	{
		data = color >> 8;
		MGPIO_voidSetPinValue(A0_PIN, GPIO_HIGH); // DATA
	    MSPI_voidSendReceiveMasterSynchronous(data, &temp);

		data = color;
	    MGPIO_voidSetPinValue(A0_PIN, GPIO_HIGH); // DATA
	    MSPI_voidSendReceiveMasterSynchronous(data, &temp);
	}
}



/*
static void sendCommand(u8 command)
{
	u8 temp;
	MGPIO_voidSetPinValue(A0_PIN, GPIO_LOW);  // COMMAND
	MSPI_voidSendReceiveMasterSynchronous(command, &temp);
}

static void sendData(u8 data)
{
	u8 temp;
	MGPIO_voidSetPinValue(A0_PIN, GPIO_HIGH);  // DATA
	MSPI_voidSendReceiveMasterSynchronous(data, &temp);
}
*/



