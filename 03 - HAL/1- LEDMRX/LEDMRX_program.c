#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "SYSTICK_interface.h"

#include "LEDMRX_interface.h"
#include "LEDMRX_config.h"
#include "LEDMRX_private.h"

void HLEDMRX_voidInitialize (void){
	
	MGPIO_voidSetPinMode(LEDMRX_ROW0_PIN, OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinMode(LEDMRX_ROW1_PIN, OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinMode(LEDMRX_ROW2_PIN, OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinMode(LEDMRX_ROW3_PIN, OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinMode(LEDMRX_ROW4_PIN, OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinMode(LEDMRX_ROW5_PIN, OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinMode(LEDMRX_ROW6_PIN, OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinMode(LEDMRX_ROW7_PIN, OUTPUT_2MHZ_PP);
	
	MGPIO_voidSetPinMode(LEDMRX_COL0_PIN, OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinMode(LEDMRX_COL1_PIN, OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinMode(LEDMRX_COL2_PIN, OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinMode(LEDMRX_COL3_PIN, OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinMode(LEDMRX_COL4_PIN, OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinMode(LEDMRX_COL5_PIN, OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinMode(LEDMRX_COL6_PIN, OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinMode(LEDMRX_COL7_PIN, OUTPUT_2MHZ_PP);
	
}



void HLEDMRX_voidDisplay(u8 *ptr_u8Data, u8 copy_u8periodinSec){
	
	for(u32 i = 0; i<(50*copy_u8periodinSec);i++){
		//disable all the columns
		MGPIO_voidSetMultiplePinValue(LEDMRX_COL_PORT, 0, 2019); 	//0b11111100011
		// set Row Values
		MGPIO_voidSetPortValue(LEDMRX_ROW_PORT, ptr_u8Data[0]);
		//set the specific column to the ground
		MGPIO_voidSetPinValue(LEDMRX_COL0_PIN,GPIO_LOW);
		//delay 2.5 ms 
		MSYSTICK_voidSetBusyWait(2500);
		
		
		//disable all the columns
		MGPIO_voidSetMultiplePinValue(LEDMRX_COL_PORT, 0, 2019); 	//0b11111100011
		// set Row Values
		MGPIO_voidSetPortValue(LEDMRX_ROW_PORT, ptr_u8Data[1]);
		//set the specific column to the ground
		MGPIO_voidSetPinValue(LEDMRX_COL1_PIN,GPIO_LOW);
		//delay 2.5 ms 
		MSYSTICK_voidSetBusyWait(2500);
		
		//disable all the columns
		MGPIO_voidSetMultiplePinValue(LEDMRX_COL_PORT, 0, 2019); 	//0b11111100011
		// set Row Values
		MGPIO_voidSetPortValue(LEDMRX_ROW_PORT, ptr_u8Data[2]);
		//set the specific column to the ground
		MGPIO_voidSetPinValue(LEDMRX_COL2_PIN,GPIO_LOW);
		//delay 2.5 ms 
		MSYSTICK_voidSetBusyWait(2500);
		
		//disable all the columns
		MGPIO_voidSetMultiplePinValue(LEDMRX_COL_PORT, 0, 2019); 	//0b11111100011
		// set Row Values
		MGPIO_voidSetPortValue(LEDMRX_ROW_PORT, ptr_u8Data[3]);
		//set the specific column to the ground
		MGPIO_voidSetPinValue(LEDMRX_COL3_PIN,GPIO_LOW);
		//delay 2.5 ms 
		MSYSTICK_voidSetBusyWait(2500);
		
		//disable all the columns
		MGPIO_voidSetMultiplePinValue(LEDMRX_COL_PORT, 0, 2019); 	//0b11111100011
		// set Row Values
		MGPIO_voidSetPortValue(LEDMRX_ROW_PORT, ptr_u8Data[4]);
		//set the specific column to the ground
		MGPIO_voidSetPinValue(LEDMRX_COL4_PIN,GPIO_LOW);
		//delay 2.5 ms 
		MSYSTICK_voidSetBusyWait(2500);
		
		//disable all the columns
		MGPIO_voidSetMultiplePinValue(LEDMRX_COL_PORT, 0, 2019); 	//0b11111100011
		// set Row Values
		MGPIO_voidSetPortValue(LEDMRX_ROW_PORT, ptr_u8Data[5]);
		//set the specific column to the ground
		MGPIO_voidSetPinValue(LEDMRX_COL5_PIN,GPIO_LOW);
		//delay 2.5 ms 
		MSYSTICK_voidSetBusyWait(2500);
		
		//disable all the columns
		MGPIO_voidSetMultiplePinValue(LEDMRX_COL_PORT, 0, 2019); 	//0b11111100011
		// set Row Values
		MGPIO_voidSetPortValue(LEDMRX_ROW_PORT, ptr_u8Data[6]);
		//set the specific column to the ground
		MGPIO_voidSetPinValue(LEDMRX_COL6_PIN,GPIO_LOW);
		//delay 2.5 ms 
		MSYSTICK_voidSetBusyWait(2500);
		
		//disable all the columns
		MGPIO_voidSetMultiplePinValue(LEDMRX_COL_PORT, 0, 2019); 	//0b11111100011
		// set Row Values
		MGPIO_voidSetPortValue(LEDMRX_ROW_PORT, ptr_u8Data[7]);
		//set the specific column to the ground
		MGPIO_voidSetPinValue(LEDMRX_COL7_PIN,GPIO_LOW);
		//delay 2.5 ms 
		MSYSTICK_voidSetBusyWait(2500);
		
		
	}


}




