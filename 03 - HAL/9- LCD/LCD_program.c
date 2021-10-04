#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "SYSTICK_interface.h"
#include "GPIO_interface.h"

#include "LCD_private.h"
#include "LCD_config.h"
#include "LCD_interface.h"


void HLCD_GPIOInitialize(void){
	/* RCC */
	MRCC_voidEnablePeripheralClock(RCC_APB2, 2 );
	/* GPIO */
	/*Initialize data pins */
	MGPIO_voidSetPinMode(LCD_DATA_PORT, LCD_START_BIT, OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinMode(LCD_DATA_PORT, LCD_START_BIT+1, OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinMode(LCD_DATA_PORT, LCD_START_BIT+2, OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinMode(LCD_DATA_PORT, LCD_START_BIT+3, OUTPUT_2MHZ_PP);
	#if LCD_DATA_LENGTH == 1	//initialize the 8-bit
		MGPIO_voidSetPinMode(LCD_DATA_PORT,LCD_START_BIT+4 , OUTPUT_2MHZ_PP);
		MGPIO_voidSetPinMode(LCD_DATA_PORT,LCD_START_BIT+5 , OUTPUT_2MHZ_PP);
		MGPIO_voidSetPinMode(LCD_DATA_PORT,LCD_START_BIT+6 , OUTPUT_2MHZ_PP);
		MGPIO_voidSetPinMode(LCD_DATA_PORT,LCD_START_BIT+7 , OUTPUT_2MHZ_PP);
	#endif
	/*initialize the command pins */
	MGPIO_voidSetPinMode(LCD_RS, OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinMode(LCD_RW, OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinMode(LCD_EN, OUTPUT_2MHZ_PP);
}

void HLCD_voidInitialize(void){
	/* wait for 40 ms */
	MSYSTICK_voidSetBusyWait(40000);
	/*function set  2 line with 5*7 dot matrix*/
	HLCD_voidSendCommand(0x38);
	MSYSTICK_voidSetBusyWait(40);
	/*display on */
	HLCD_voidSendCommand(0x0E);
	MSYSTICK_voidSetBusyWait(40);
	/*display clear */
	HLCD_voidSendCommand(0x01);
	MSYSTICK_voidSetBusyWait(2000);
	/* entry mode */
	HLCD_voidSendCommand(0x06);
}

#if LCD_DATA_LENGTH == 1	//initialize the 8-bit
void HLCD_voidSendCommand(u8 Copy_u8Command){
	MGPIO_voidSetMultiplePinValue(LCD_DATA_PORT,0, Copy_u8Command);
	/* clear RS pin */
	MGPIO_voidSetPinValue(LCD_RS,GPIO_LOW);
	/* clear RW pin */
	MGPIO_voidSetPinValue(LCD_RW,GPIO_LOW);
	/*pulse on the enable pin */
	MGPIO_voidSetPinValue(LCD_EN,GPIO_HIGH);
	MSYSTICK_voidSetBusyWait(2);
	MGPIO_voidSetPinValue(LCD_EN,GPIO_LOW);
	/*delay for 2 ms */
	MSYSTICK_voidSetBusyWait(2000);

}
#elif LCD_DATA_LENGTH == 0	//initialize the 4-bit
void HLCD_voidSendCommand(u8 Copy_u8Command){
	/*send the high nibble first */
	HLCD_voidSend4BitNibble(Copy_u8Command>>4, 1);
	/*send the low nibble */
	HLCD_voidSend4BitNibble(Copy_u8Command&0x0F, 1);
	MSYSTICK_voidSetBusyWait(2000);
}
#endif

#if LCD_DATA_LENGTH == 1	//initialize the 8-bit
void HLCD_voidSendData(u8 Copy_u8Data){
	MGPIO_voidSetMultiplePinValue(LCD_DATA_PORT,0, Copy_u8Data);
	/* set RS pin */
	MGPIO_voidSetPinValue(LCD_RS,GPIO_HIGH);
	/* clear RW pin */
	MGPIO_voidSetPinValue(LCD_RW,GPIO_LOW);
	/*pulse on the enable pin */
	MGPIO_voidSetPinValue(LCD_EN,GPIO_HIGH);
	MSYSTICK_voidSetBusyWait(2);
	MGPIO_voidSetPinValue(LCD_EN,GPIO_LOW);
	/*delay for 2 ms */
	MSYSTICK_voidSetBusyWait(2000);
}
#elif LCD_DATA_LENGTH == 0	//initialize the 4-bit
void HLCD_voidSendData(u8 Copy_u8Data){
	/*send the high nibble first */
	HLCD_voidSend4BitNibble(Copy_u8Data>>4, 0);
	/*send the low nibble */
	HLCD_voidSend4BitNibble(Copy_u8Data&0x0F, 0);
	MSYSTICK_voidSetBusyWait(2000);
}
#endif

void HLCD_voidSetPosition(u8 Copy_u8Column, u8 Copy_u8Row){
	u8 firstChar[] = {0x80,0xC0};
	HLCD_voidSendCommand(firstChar[Copy_u8Column] + (Copy_u8Row));
}

void HLCD_voidClearDisplay(void){
	HLCD_voidSendCommand(0x01);
}

void HLCD_voidSetCustomChar(u8 Buffer[]){
	LCD_CG_addresses[counter++] =  LCD_CG_ADDR_Counter;
	u8 address = 1<<6 |LCD_CG_ADDR_Counter;
	/*go to the CG address */
	HLCD_voidSendCommand(address);
	for(u8 i = 0; i<7; i++){
		HLCD_voidSendData(Buffer[i]);
		LCD_CG_ADDR_Counter++;
	}
}

void HLCD_voidSend4BitNibble(u8 Copy_u8Data, u8 Copy_u8Control){
	//send the data whether command or data on the 4 bits
	MGPIO_voidSetMultiplePinValue(LCD_DATA_PORT,LCD_START_BIT,Copy_u8Data);
	//if Control == 1 -> RS = 0
	if(Copy_u8Control == 1){
		/* clear RS pin */
		MGPIO_voidSetPinValue(LCD_RS,GPIO_LOW);
		/* clear RW pin */
		MGPIO_voidSetPinValue(LCD_RW,GPIO_LOW);
	}
	else 
	{
		/* set RS pin */
		MGPIO_voidSetPinValue(LCD_RS,GPIO_HIGH);
		/* clear RW pin */
		MGPIO_voidSetPinValue(LCD_RW,GPIO_LOW);
	}
	/*pulse on the enable pin */
	MGPIO_voidSetPinValue(LCD_EN,GPIO_HIGH);
	MSYSTICK_voidSetBusyWait(2);
	MGPIO_voidSetPinValue(LCD_EN,GPIO_LOW);
	
}

void HLCD_voidSendNumber(u32 Copy_u32Number){
	u8 Local_u8SentChar;
	u32 y = 1;
	while(Copy_u32Number/(10*y) !=0){
		y*=10;
	}
	while(Copy_u32Number !=0){
		Local_u8SentChar = (Copy_u32Number/y)+'0';
		HLCD_voidSendData(Local_u8SentChar);
		Copy_u32Number %=y;
		y/=10;
	}
}


void LCD_voidPrintString(u8 *Ptr_u8String){
	u8 i = 0;	//counter for the array of chars
	while(*(Ptr_u8String+i) != '\0'){	
		HLCD_voidSendData(*(Ptr_u8String+i));	
		i++;
	}
}