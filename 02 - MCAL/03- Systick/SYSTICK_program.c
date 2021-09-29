#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "SYSTICK_private.h"
#include "SYSTICK_config.h"
#include "SYSTICK_interface.h"


void(*Callback)(void);
u8 Global_u8IsPeriodic;

//init function
void MSYSTICK_voidInitialize(void){
	STK_CTRL = 0;
	//sets the clock source
#if CLOCK_SOURCE == AHB
	SET_BIT(STK_CTRL,2);	//sets to AHB
#elif CLOCK_SOURCE == AHB_DIV_8
	CLR_BIT(STK_CTRL,2);
#else
	//error
#endif
}

//delay polling (Synch.)
void MSYSTICK_voidSetBusyWait(u32 copy_u32ticks){
	STK_LOAD = copy_u32ticks;
	SET_BIT(STK_CTRL, 0);
	asm("NOP");
	while(GET_BIT(STK_CTRL,16) == 0);
	CLR_BIT(STK_CTRL, 16);
}

//delay interrupt (Asynch.)
void MSYSTICK_voidSetIntervalSingle(u32 copy_u32ticks,void(*ptr)(void) ){
	Global_u8IsPeriodic = 0;
	STK_LOAD = copy_u32ticks;
	Callback = ptr;
	SET_BIT(STK_CTRL, 1);
	
	SET_BIT(STK_CTRL, 0);
}

void MSYSTICK_voidSetTickCount(u32 copy_u32ticks ){
	STK_LOAD = copy_u32ticks;
	SET_BIT(STK_CTRL, 0);
}

//periodic timer
void MSYSTICK_voidSetIntervalPeriodic(u32 copy_u32ticks,void(*ptr)(void) ){
	STK_VAL = 0;
	Global_u8IsPeriodic = 1;
	STK_LOAD = copy_u32ticks;
	Callback = ptr;
	SET_BIT(STK_CTRL, 1);
	
	SET_BIT(STK_CTRL, 0);
}

//stop periodic timer
void MSYSTICK_voidStopInterval(void){
	CLR_BIT(STK_CTRL,0);
	CLR_BIT(STK_CTRL,1);
	STK_LOAD = 0;
	STK_VAL = 0;
}
//get elapsed time
u32 MSYSTICK_u32GetElapsedTime(void){
	return STK_LOAD - STK_VAL;
}
//get remaining time
u32 MSYSTICK_u32GetRemainingTime(void){
	return STK_VAL;
}


void SysTick_Handler(void){
	Callback();
	if(Global_u8IsPeriodic == 0){
		STK_LOAD = 0;
	}
}




