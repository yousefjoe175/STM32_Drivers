#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "IR_interface.h"
#include "IR_private.h"
#include "IR_config.h"


#define LED_PORT	GPIOA
#define LED_RED		LED_PORT,1
#define LED_GREEN	LED_PORT,2
#define LED_BLUE	LED_PORT,3

static volatile u8 flag = 0;
static volatile u32 dataArray[50] = {0};
static volatile u32 i = 0;
static volatile u8 data;


void HIR_voidGetFrameCallBack(void){
	if(flag == 0){
		MSYSTICK_voidSetIntervalSingle(1000000,ahmed);
		flag = 1;
	}else{
		dataArray[i++] = MSYSTICK_u32GetElapsedTime();
		MSYSTICK_voidSetIntervalSingle(1000000,ahmed);
	}
}

void HIR_voidApplication(void){
	asm("NOP");
}


