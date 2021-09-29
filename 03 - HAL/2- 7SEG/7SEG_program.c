#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"

#include "7SEG_config.h"
#include "7SEG_private.h"
#include "7SEG_interface.h"

static display_arr[10] = {
	0b00111111,
	0b00000110,
	0b01011011,
	0b01001111,
	0b01100110,
	0b01101101,
	0b01111101,
	0b00000111,
	0b01111111,
	0b01101111
};


void HSEG_voidInitialize(void){
	MGPIO_voidSetPinMode(SEG_PORT_1_PIN_A, OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinMode(SEG_PORT_1_PIN_B, OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinMode(SEG_PORT_1_PIN_C, OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinMode(SEG_PORT_1_PIN_D, OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinMode(SEG_PORT_1_PIN_E, OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinMode(SEG_PORT_1_PIN_F, OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinMode(SEG_PORT_1_PIN_G, OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinMode(SEG_PORT_1_PIN_DOT, OUTPUT_2MHZ_PP);
	
	MGPIO_voidSetPinMode(SEG_PORT_2_PIN_A, OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinMode(SEG_PORT_2_PIN_B, OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinMode(SEG_PORT_2_PIN_C, OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinMode(SEG_PORT_2_PIN_D, OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinMode(SEG_PORT_2_PIN_E, OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinMode(SEG_PORT_2_PIN_F, OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinMode(SEG_PORT_2_PIN_G, OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinMode(SEG_PORT_2_PIN_DOT, OUTPUT_2MHZ_PP);

}



void HSEG_voidDisplayNumber(u8 copy_u8DisplayedNumber){
		if(copy_u8DisplayedNumber < 100){
			HSEG_voidDisplayDigit1(copy_u8DisplayedNumber % 10);
			HSEG_voidDisplayDigit2(copy_u8DisplayedNumber / 10);
		}else{
			//error
		}
}

static void HSEG_voidDisplayDigit1(u8 copy_u8DisplayedDigit){
	u8 Local_u8displayedpattern = display_arr[copy_u8DisplayedDigit];
	
	u8 Local_u8displayedpattern = display_arr[copy_u8DisplayedDigit];
	MGPIO_voidSetPinValue(SEG_PORT_1_PIN_A, GET_BIT(Local_u8displayedpattern, 0));
	MGPIO_voidSetPinValue(SEG_PORT_1_PIN_B, GET_BIT(Local_u8displayedpattern, 1));
	MGPIO_voidSetPinValue(SEG_PORT_1_PIN_C, GET_BIT(Local_u8displayedpattern, 2));
	MGPIO_voidSetPinValue(SEG_PORT_1_PIN_D, GET_BIT(Local_u8displayedpattern, 3));
	MGPIO_voidSetPinValue(SEG_PORT_1_PIN_E, GET_BIT(Local_u8displayedpattern, 4));
	MGPIO_voidSetPinValue(SEG_PORT_1_PIN_F, GET_BIT(Local_u8displayedpattern, 5));
	MGPIO_voidSetPinValue(SEG_PORT_1_PIN_G, GET_BIT(Local_u8displayedpattern, 6));
	MGPIO_voidSetPinValue(SEG_PORT_1_PIN_DOT, GET_BIT(Local_u8displayedpattern, 7));
	
} 

static void HSEG_voidDisplayDigit2(u8 copy_u8DisplayedDigit){
	u8 Local_u8displayedpattern = display_arr[copy_u8DisplayedDigit];
	MGPIO_voidSetPinValue(SEG_PORT_2_PIN_A, GET_BIT(Local_u8displayedpattern, 0));
	MGPIO_voidSetPinValue(SEG_PORT_2_PIN_B, GET_BIT(Local_u8displayedpattern, 1));
	MGPIO_voidSetPinValue(SEG_PORT_2_PIN_C, GET_BIT(Local_u8displayedpattern, 2));
	MGPIO_voidSetPinValue(SEG_PORT_2_PIN_D, GET_BIT(Local_u8displayedpattern, 3));
	MGPIO_voidSetPinValue(SEG_PORT_2_PIN_E, GET_BIT(Local_u8displayedpattern, 4));
	MGPIO_voidSetPinValue(SEG_PORT_2_PIN_F, GET_BIT(Local_u8displayedpattern, 5));
	MGPIO_voidSetPinValue(SEG_PORT_2_PIN_G, GET_BIT(Local_u8displayedpattern, 6));
	MGPIO_voidSetPinValue(SEG_PORT_2_PIN_DOT, GET_BIT(Local_u8displayedpattern, 7));

}



