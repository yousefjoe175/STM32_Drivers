#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"

#include "TIMER_private.h"
#include "TIMER_config.h"
#include "TIMER_interface.h"

void (*TIMER2_voidCallBack)(void);
void (*TIMER3_voidCallBack)(void);
void (*TIMER4_voidCallBack)(void);

static u8 TIMER2_periodFlag;
static u8 TIMER3_periodFlag;
static u8 TIMER4_periodFlag;

void MTIMER_voidDelayMs(u8 Copy_u8TimerModule, u16 Copy_u16Miliseconds){
	switch(Copy_u8TimerModule){
	case 2: default:
		TIMER2->PSC = 8000 - 1;
		TIMER2->ARR = Copy_u16Miliseconds;
		TIMER2->CNT = 0;
		SET_BIT(TIMER2->CR1, 0);
		while(GET_BIT(TIMER2->SR, 0) == 0);
		CLR_BIT(TIMER2->SR, 0);
		CLR_BIT(TIMER2->CR1, 0);
		break;
	case 3:
		TIMER3->PSC = 8000 - 1;
		TIMER3->ARR = Copy_u16Miliseconds;
		TIMER3->CNT = 0;
		SET_BIT(TIMER3->CR1, 0);
		while(GET_BIT(TIMER3->SR, 0) == 0);
		CLR_BIT(TIMER3->SR, 0);
		CLR_BIT(TIMER3->CR1, 0);
		break;
	case 4:
		TIMER4->PSC = 8000 - 1;
		TIMER4->ARR = Copy_u16Miliseconds;
		TIMER4->CNT = 0;
		SET_BIT(TIMER4->CR1, 0);
		while(GET_BIT(TIMER4->SR, 0) == 0);
		CLR_BIT(TIMER4->SR, 0);
		CLR_BIT(TIMER4->CR1, 0);
		break;


	}
}


void MTIMER_voidDelayUs(u8 Copy_u8TimerModule, u16 Copy_u16Microseconds){
	switch(Copy_u8TimerModule){
		case 2: default:
			TIMER2->PSC = 8 - 1;
			TIMER2->ARR = Copy_u16Microseconds;
			TIMER2->CNT = 0;
			SET_BIT(TIMER2->CR1, 0);
			while(GET_BIT(TIMER2->SR, 0) == 0);
			CLR_BIT(TIMER2->SR, 0);
			CLR_BIT(TIMER2->CR1, 0);
			break;
		case 3:
			TIMER3->PSC = 8 - 1;
			TIMER3->ARR = Copy_u16Microseconds;
			TIMER3->CNT = 0;
			SET_BIT(TIMER3->CR1, 0);
			while(GET_BIT(TIMER3->SR, 0) == 0);
			CLR_BIT(TIMER3->SR, 0);
			CLR_BIT(TIMER3->CR1, 0);
			break;
		case 4:
			TIMER4->PSC = 8 - 1;
			TIMER4->ARR = Copy_u16Microseconds;
			TIMER4->CNT = 0;
			SET_BIT(TIMER4->CR1, 0);
			while(GET_BIT(TIMER4->SR, 0) == 0);
			CLR_BIT(TIMER4->SR, 0);
			CLR_BIT(TIMER4->CR1, 0);
			break;


		}
}

void MTIMER_voidGenerateSquareWave(u8 Copy_u8TimerModule,u8 Copy_u8Channel, u16 Copy_u16PeriodinMs){
	/* set GPIO pin as AFPP */

	/* set CCxS bits in CCMRx as output (00) */

	/* set OCxM bits in CCMRx to toggle (011) */

	/* set OCx pin output enable in CCER (1) */
	if (Copy_u8TimerModule == 2) {
		switch(Copy_u8Channel){
		case 1:	default:
			MGPIO_voidSetPinMode(TIMER2_LED_PIN, OUTPUT_2MHZ_AF_PP);
			SET_VAL(TIMER2->CCMR1,4,3);
			SET_BIT(TIMER2->CCER,0);
			TIMER2->CCR1 = 0;
			break;
		case 2:
			MGPIO_voidSetPinMode(TIMER2_LED_PIN_2, OUTPUT_2MHZ_AF_PP);
			SET_VAL(TIMER2->CCMR1,12,3);
			SET_BIT(TIMER2->CCER,4);
			TIMER2->CCR2 = 0;
			break;
		case 3:
			MGPIO_voidSetPinMode(TIMER2_LED_PIN_3, OUTPUT_2MHZ_AF_PP);
			SET_VAL(TIMER2->CCMR2,4,3);
			SET_BIT(TIMER2->CCER,8);
			TIMER2->CCR3 = 0;
			break;
		case 4:
			MGPIO_voidSetPinMode(TIMER2_LED_PIN_4, OUTPUT_2MHZ_AF_PP);
			SET_VAL(TIMER2->CCMR2,12,3);
			SET_BIT(TIMER2->CCER,12);
			TIMER2->CCR4 = 0;
		}
		/* set the value to be compared in CCRx and the value of overflow in ARR*/
		TIMER2->PSC = 8000 - 1;
		TIMER2->ARR = Copy_u16PeriodinMs/2;
		/* clear the counter and enable the timer */
		TIMER2->CNT = 0;
		SET_BIT(TIMER2->CR1,0);
	}
	else if (Copy_u8TimerModule == 3) {
		switch(Copy_u8Channel){
		case 1:	default:
			MGPIO_voidSetPinMode(TIMER3_LED_PIN, OUTPUT_2MHZ_AF_PP);
			SET_VAL(TIMER3->CCMR1,4,3);
			SET_BIT(TIMER3->CCER,0);
			TIMER3->CCR1 = 0;
			break;
		case 2:
			MGPIO_voidSetPinMode(TIMER3_LED_PIN_2, OUTPUT_2MHZ_AF_PP);
			SET_VAL(TIMER3->CCMR1,12,3);
			SET_BIT(TIMER3->CCER,4);
			TIMER3->CCR2 = 0;
			break;
		case 3:
			MGPIO_voidSetPinMode(TIMER3_LED_PIN_3, OUTPUT_2MHZ_AF_PP);
			SET_VAL(TIMER3->CCMR2,4,3);
			SET_BIT(TIMER3->CCER,8);
			TIMER3->CCR3 = 0;
			break;
		case 4:
			MGPIO_voidSetPinMode(TIMER3_LED_PIN_4, OUTPUT_2MHZ_AF_PP);
			SET_VAL(TIMER3->CCMR2,12,3);
			SET_BIT(TIMER3->CCER,12);
			TIMER3->CCR4 = 0;
		}
		/* set the value to be compared in CCRx and the value of overflow in ARR*/
		TIMER3->PSC = 8000 - 1;
		TIMER3->ARR = Copy_u16PeriodinMs/2;
		/* clear the counter and enable the timer */
		TIMER3->CNT = 0;
		SET_BIT(TIMER3->CR1,0);
	}
	else if (Copy_u8TimerModule == 4) {
		switch(Copy_u8Channel){
		case 1:	default:
			MGPIO_voidSetPinMode(TIMER4_LED_PIN, OUTPUT_2MHZ_AF_PP);
			SET_VAL(TIMER4->CCMR1,4,3);
			SET_BIT(TIMER4->CCER,0);
			TIMER4->CCR1 = 0;
			break;
		case 2:
			MGPIO_voidSetPinMode(TIMER4_LED_PIN_2, OUTPUT_2MHZ_AF_PP);
			SET_VAL(TIMER4->CCMR1,12,3);
			SET_BIT(TIMER4->CCER,4);
			TIMER4->CCR2 = 0;
			break;
		case 3:
			MGPIO_voidSetPinMode(TIMER4_LED_PIN_3, OUTPUT_2MHZ_AF_PP);
			SET_VAL(TIMER4->CCMR2,4,3);
			SET_BIT(TIMER4->CCER,8);
			TIMER4->CCR3 = 0;
			break;
		case 4:
			MGPIO_voidSetPinMode(TIMER4_LED_PIN_4, OUTPUT_2MHZ_AF_PP);
			SET_VAL(TIMER4->CCMR2,12,3);
			SET_BIT(TIMER4->CCER,12);
			TIMER4->CCR4 = 0;
		}
		/* set the value to be compared in CCRx and the value of overflow in ARR*/
		TIMER4->PSC = 8000 - 1;
		TIMER4->ARR = Copy_u16PeriodinMs/2;
		/* clear the counter and enable the timer */
		TIMER4->CNT = 0;
		SET_BIT(TIMER4->CR1,0);
	}
}

void MTIMER_voidSetIntervalSingle(u8 Copy_u8TimerModule, u16 Copy_u16PeriodinMs,void(*ptr)(void) ){
	
	if(Copy_u8TimerModule == 2){
		TIMER2_periodFlag = 0;
		TIMER2_voidCallBack = ptr;
		/* set URS in CR1 */
		SET_BIT(TIMER2->CR1,2);
		/*set UIE in DIER */
		SET_BIT(TIMER2->DIER,0);

		/* set the prescaler to 8000 */
		TIMER2->PSC = 8000 - 1;
		TIMER2->ARR = Copy_u16PeriodinMs;
		TIMER2->CNT = 0;
		SET_BIT(TIMER2->CR1, 0);
		/*set OPM in CR1 */
		SET_BIT(TIMER2->CR1,3);
	}
	else if(Copy_u8TimerModule == 3){
		TIMER3_periodFlag = 0;
		TIMER3_voidCallBack = ptr;
		/* set URS in CR1 */
		SET_BIT(TIMER3->CR1,2);
		/*set UIE in DIER */
		SET_BIT(TIMER3->DIER,0);

		/* set the prescaler to 8000 */
		TIMER3->PSC = 8000 - 1;
		TIMER3->ARR = Copy_u16PeriodinMs;
		TIMER3->CNT = 0;
		SET_BIT(TIMER3->CR1, 0);
		/*set OPM in CR1 */
		SET_BIT(TIMER3->CR1,3);
	} 
	else if(Copy_u8TimerModule == 4){
		TIMER4_periodFlag = 0;
		TIMER4_voidCallBack = ptr;
		/* set URS in CR1 */
		SET_BIT(TIMER4->CR1,2);
		/*set UIE in DIER */
		SET_BIT(TIMER4->DIER,0);

		/* set the prescaler to 8000 */
		TIMER4->PSC = 8000 - 1;
		TIMER4->ARR = Copy_u16PeriodinMs;
		TIMER4->CNT = 0;
		SET_BIT(TIMER4->CR1, 0);
		/*set OPM in CR1 */
		SET_BIT(TIMER4->CR1,3);
	} 
}

void MTIMER_voidSetIntervalPeriodic(u8 Copy_u8TimerModule, u16 Copy_u16PeriodinMs,void(*ptr)(void) ){
	if(Copy_u8TimerModule == 2){
		TIMER2_periodFlag = 1;
		TIMER2_voidCallBack = ptr;
		/* set URS in CR1 */
		SET_BIT(TIMER2->CR1,2);
		/*set UIE in DIER */
		SET_BIT(TIMER2->DIER,0);

		/* set the prescaler to 8000 */
		TIMER2->PSC = 8000 - 1;
		TIMER2->ARR = Copy_u16PeriodinMs;
		TIMER2->CNT = 0;
		SET_BIT(TIMER2->CR1, 0);
		
	}
	else if(Copy_u8TimerModule == 3){
		TIMER3_periodFlag = 1;
		TIMER3_voidCallBack = ptr;
		/* set URS in CR1 */
		SET_BIT(TIMER3->CR1,2);
		/*set UIE in DIER */
		SET_BIT(TIMER3->DIER,0);

		/* set the prescaler to 8000 */
		TIMER3->PSC = 8000 - 1;
		TIMER3->ARR = Copy_u16PeriodinMs;
		TIMER3->CNT = 0;
		SET_BIT(TIMER3->CR1, 0);
		
	} 
	else if(Copy_u8TimerModule == 4){
		TIMER4_periodFlag = 1;
		TIMER4_voidCallBack = ptr;
		/* set URS in CR1 */
		SET_BIT(TIMER4->CR1,2);
		/*set UIE in DIER */
		SET_BIT(TIMER4->DIER,0);

		/* set the prescaler to 8000 */
		TIMER4->PSC = 8000 - 1;
		TIMER4->ARR = Copy_u16PeriodinMs;
		TIMER4->CNT = 0;
		SET_BIT(TIMER4->CR1, 0);
		
	} 
}

void MTIMER_voidGetInputCapture(u8 Copy_u8TimerModule, /*u8 Copy_u8Channel,*/ u8 Copy_u8Edge, u32* ptr_u32Buffer){
	u32 Data;
	if(Copy_u8TimerModule == 2){
		/*set LED_PIN as AFPP */
		MGPIO_voidSetPinMode(TIMER2_LED_PIN, OUTPUT_2MHZ_AF_PP);
		/* set the channel as input with 8 samples per input */
		SET_VAL(TIMER2->CCMR1,0,1);
		SET_VAL(TIMER2->CCMR1,4,3);
		/* set the edge of the input capture */
		if(Copy_u8Edge == 1){
			CLR_BIT(TIMER2->CCER,1);
		}else if(Copy_u8Edge == 0){
			SET_BIT(TIMER2->CCER,1);
		}
		/*enable the capture */
		SET_BIT(TIMER2->CCER,0);
		/*enable the timer*/
		TIMER2->PSC = 8000;
		TIMER2->CNT = 0;
		SET_BIT(TIMER2->CR1,0);
		while(GET_BIT(TIMER2->SR,1) == 0);
		CLR_BIT(TIMER2->SR,1);
		Data = TIMER2->CCR1;
		*ptr_u32Buffer = Data;
	}
	else if (Copy_u8TimerModule == 3){
		/*set LED_PIN as AFPP */
		MGPIO_voidSetPinMode(TIMER3_LED_PIN, OUTPUT_2MHZ_AF_PP);
		/* set the channel as input with 8 samples per input */
		SET_VAL(TIMER3->CCMR1,0,1);
		SET_VAL(TIMER3->CCMR1,4,3);
		/* set the edge of the input capture */
		if(Copy_u8Edge == 1){
			CLR_BIT(TIMER3->CCER,1);
		}else if(Copy_u8Edge == 0){
			SET_BIT(TIMER3->CCER,1);
		}
		/*enable the capture */
		SET_BIT(TIMER3->CCER,0);
		/*enable the timer*/
		TIMER3->PSC = 8000;
		TIMER3->CNT = 0;
		SET_BIT(TIMER3->CR1,0);
		while(GET_BIT(TIMER3->SR,1) == 0);
		CLR_BIT(TIMER3->SR,1);
		Data = TIMER3->CCR1;
		*ptr_u32Buffer = Data;
		
	}
	else if (Copy_u8TimerModule == 4){
		/*set LED_PIN as AFPP */
		MGPIO_voidSetPinMode(TIMER4_LED_PIN, OUTPUT_2MHZ_AF_PP);
		/* set the channel as input with 8 samples per input */
		SET_VAL(TIMER4->CCMR1,0,1);
		SET_VAL(TIMER4->CCMR1,4,3);
		/* set the edge of the input capture */
		if(Copy_u8Edge == 1){
			CLR_BIT(TIMER4->CCER,1);
		}else if(Copy_u8Edge == 0){
			SET_BIT(TIMER4->CCER,1);
		}
		/*enable the capture */
		SET_BIT(TIMER4->CCER,0);
		/*enable the timer*/
		TIMER4->PSC = 8000;
		TIMER4->CNT = 0;
		SET_BIT(TIMER4->CR1,0);
		while(GET_BIT(TIMER4->SR,1) == 0);
		CLR_BIT(TIMER4->SR,1);
		Data = TIMER4->CCR1;
		*ptr_u32Buffer = Data;
	}
	
	
}


void MTIMER_voidGetICFreq(u8 Copy_u8TimerModule, ICU_type *ptr_ICU_tBuffer ){
	volatile u16 T1;
	volatile u16 period;
	if(Copy_u8TimerModule == 2){
		/*set LED_PIN as AFPP */
		MGPIO_voidSetPinMode(TIMER2_LED_PIN, OUTPUT_2MHZ_AF_PP);
		/*set channel1 to T1 and channel2 to T1 as well*/
		SET_VAL(TIMER2->CCMR1,0,1);
		SET_VAL(TIMER2->CCMR1,8,2);
		/* set the input filter to 8 samples */
		SET_VAL(TIMER2->CCMR1,4,3);
		SET_VAL(TIMER2->CCMR1,12,3);
		/* the polarity of channel1 is rising edge and channel2 is falling edge */
		CLR_BIT(TIMER2->CCER,1);
		SET_BIT(TIMER2->CCER,5);
		/*enable the capture*/
		SET_BIT(TIMER2->CCER,0);
		SET_BIT(TIMER2->CCER,4);
		/*enable the timer */
		TIMER2->PSC = 8000;
		SET_BIT(TIMER2->CR1,0);
		while(GET_BIT(TIMER2->SR, 1) == 0);
		TIMER2->CNT = 0;
		CLR_BIT(TIMER2->SR,1);
		CLR_BIT(TIMER2->SR,2);
		while(GET_BIT(TIMER2->SR, 2) == 0);
		T1 = TIMER2->CCR2;
		while(GET_BIT(TIMER2->SR,1) == 0);
		period = TIMER2->CCR1;
		ptr_ICU_tBuffer->dutyCyle = T1*100/period;
		ptr_ICU_tBuffer->freq = 1000.0f/period;
	}
	else if (Copy_u8TimerModule == 3){
		/*set LED_PIN as AFPP */
		MGPIO_voidSetPinMode(TIMER3_LED_PIN, OUTPUT_2MHZ_AF_PP);
		/*set channel1 to T1 and channel2 to T1 as well*/
		SET_VAL(TIMER3->CCMR1,0,1);
		SET_VAL(TIMER3->CCMR1,8,2);
		/* set the input filter to 8 samples */
		SET_VAL(TIMER3->CCMR1,4,3);
		SET_VAL(TIMER3->CCMR1,12,3);
		/* the polarity of channel1 is rising edge and channel2 is falling edge */
		CLR_BIT(TIMER3->CCER,1);
		SET_BIT(TIMER3->CCER,5);
		/*enable the capture*/
		SET_BIT(TIMER3->CCER,0);
		SET_BIT(TIMER3->CCER,4);
		/*enable the timer */
		TIMER3->PSC = 8000;
		SET_BIT(TIMER3->CR1,0);
		while(GET_BIT(TIMER3->SR, 1) == 0);
		TIMER3->CNT = 0;
		CLR_BIT(TIMER3->SR,1);
		CLR_BIT(TIMER3->SR,2);
		while(GET_BIT(TIMER3->SR, 2) == 0);
		T1 = TIMER3->CCR2;
		while(GET_BIT(TIMER3->SR,1) == 0);
		period = TIMER3->CCR1;
		ptr_ICU_tBuffer->dutyCyle = T1*100/period;
		ptr_ICU_tBuffer->freq = 1000.0f/period;
	}
	else if (Copy_u8TimerModule == 4){
		/*set LED_PIN as AFPP */
		MGPIO_voidSetPinMode(TIMER4_LED_PIN, OUTPUT_2MHZ_AF_PP);
		/*set channel1 to T1 and channel2 to T1 as well*/
		SET_VAL(TIMER4->CCMR1,0,1);
		SET_VAL(TIMER4->CCMR1,8,2);
		/* set the input filter to 8 samples */
		SET_VAL(TIMER4->CCMR1,4,3);
		SET_VAL(TIMER4->CCMR1,12,3);
		/* the polarity of channel1 is rising edge and channel2 is falling edge */
		CLR_BIT(TIMER4->CCER,1);
		SET_BIT(TIMER4->CCER,5);
		/*enable the capture*/
		SET_BIT(TIMER4->CCER,0);
		SET_BIT(TIMER4->CCER,4);
		/*enable the timer */
		TIMER4->PSC = 8000;
		SET_BIT(TIMER4->CR1,0);
		while(GET_BIT(TIMER4->SR, 1) == 0);
		TIMER4->CNT = 0;
		CLR_BIT(TIMER4->SR,1);
		CLR_BIT(TIMER4->SR,2);
		while(GET_BIT(TIMER4->SR, 2) == 0);
		T1 = TIMER4->CCR2;
		while(GET_BIT(TIMER4->SR,1) == 0);
		period = TIMER4->CCR1;
		ptr_ICU_tBuffer->dutyCyle = T1*100/period;
		ptr_ICU_tBuffer->freq = 1000.0f/period;
	}
	
	
}

void MTIMER_voidSetPWM(u8 Copy_u8TimerModule, f32 Copy_f32Frequency, u8 Copy_u8DutyCycle){
	if(Copy_u8TimerModule == 2){
		MGPIO_voidSetPinMode(TIMER2_LED_PIN,OUTPUT_2MHZ_AF_PP);
		/*set Capture compare mode as PWM 1 */
		SET_VAL(TIMER2->CCMR1,4,6);
		/* set the compare preload*/
		SET_BIT(TIMER2->CCMR1,3);
		/* set the auto reload preload */
		SET_BIT(TIMER2->CR1,7);
		/*set the direction as upcounter */
		CLR_BIT(TIMER2->CR1,4);
		/* set the compare output as active high */
		CLR_BIT(TIMER2->CCER,1);
		/* set the timer compare and auto reload */
		TIMER2->PSC = 800;
		TIMER2->ARR = 10000/Copy_f32Frequency;
		TIMER2->CCR1 = Copy_u8DutyCycle * TIMER2->ARR / 100;
		TIMER2->CNT = 0;
		/* set the counter and set the update generator */
		SET_BIT(TIMER2->CCER,0);
		SET_BIT(TIMER2->CR1,0);
		SET_BIT(TIMER2->EGR,0);
	}
	else if (Copy_u8TimerModule == 3){
		MGPIO_voidSetPinMode(TIMER3_LED_PIN,OUTPUT_2MHZ_AF_PP);
		/*set Capture compare mode as PWM 1 */
		SET_VAL(TIMER3->CCMR1,4,6);
		/* set the compare preload*/
		SET_BIT(TIMER3->CCMR1,3);
		/* set the auto reload preload */
		SET_BIT(TIMER3->CR1,7);
		/*set the direction as upcounter */
		CLR_BIT(TIMER3->CR1,4);
		/* set the compare output as active high */
		CLR_BIT(TIMER3->CCER,1);
		/* set the timer compare and auto reload */
		TIMER3->PSC = 800;
		TIMER3->ARR = 10000/Copy_f32Frequency;
		TIMER3->CCR1 = Copy_u8DutyCycle * TIMER3->ARR / 100;
		TIMER3->CNT = 0;
		/* set the counter and set the update generator */
		SET_BIT(TIMER3->CCER,0);
		SET_BIT(TIMER3->CR1,0);
		SET_BIT(TIMER3->EGR,0);

	}
	else if (Copy_u8TimerModule == 4){
		MGPIO_voidSetPinMode(TIMER4_LED_PIN,OUTPUT_2MHZ_AF_PP);
		/*set Capture compare mode as PWM 1 */
		SET_VAL(TIMER4->CCMR1,4,6);
		/* set the compare preload*/
		SET_BIT(TIMER4->CCMR1,3);
		/* set the auto reload preload */
		SET_BIT(TIMER4->CR1,7);
		/*set the direction as upcounter */
		CLR_BIT(TIMER4->CR1,4);
		/* set the compare output as active high */
		CLR_BIT(TIMER4->CCER,1);
		/* set the timer compare and auto reload */
		TIMER4->PSC = 800;
		TIMER4->ARR = 10000/Copy_f32Frequency;
		TIMER4->CCR1 = Copy_u8DutyCycle * TIMER4->ARR / 100;
		TIMER4->CNT = 0;
		/* set the counter and set the update generator */
		SET_BIT(TIMER4->CCER,0);
		SET_BIT(TIMER4->CR1,0);
		SET_BIT(TIMER4->EGR,0);
	}
	
}


void MTIMER_voidStopTimer(u8 Copy_u8TimerModule){
	if(Copy_u8TimerModule == 2){
		CLR_BIT(TIMER2->CR1,0);
	}
	else if (Copy_u8TimerModule == 3){
		CLR_BIT(TIMER3->CR1,0);
	}
	else if (Copy_u8TimerModule == 4){
		CLR_BIT(TIMER4->CR1,0);
	}
	else
	{
		CLR_BIT(TIMER2->CR1,0);
	}
}

u32 MTIMER_u32GetElapsedTime(u8 Copy_u8TimerModule){

	if(Copy_u8TimerModule == 2){
		return TIMER2->CNT * TIMER2->PSC;
	}
	else if (Copy_u8TimerModule == 3){
		return TIMER3->CNT * TIMER3->PSC;
	}
	else if (Copy_u8TimerModule == 4){
		return TIMER4->CNT * TIMER4->PSC;	
	}
	else {
		return TIMER2->CNT * TIMER2->PSC;
	}
}

u32 MTIMER_u32GetRemainingTime(u8 Copy_u8TimerModule){
	if(Copy_u8TimerModule == 2){
		return (TIMER2->ARR - TIMER2->CNT) * TIMER2->PSC; 	
	}
	else if (Copy_u8TimerModule == 3){
		return (TIMER3->ARR - TIMER3->CNT) * TIMER3->PSC; 
	
	}
	else if (Copy_u8TimerModule == 4){
		return (TIMER4->ARR - TIMER4->CNT) * TIMER4->PSC; 
	}
	else {
		return (TIMER2->ARR - TIMER2->CNT) * TIMER2->PSC;
	}
}


void TIM2_IRQHandler(void){
	if(TIMER2_periodFlag == 0){
		CLR_BIT(TIMER2->CR1, 0);
	};
	CLR_BIT(TIMER2->SR, 0);
	TIMER2_voidCallBack();
}

void TIM3_IRQHandler(void){
	if(TIMER3_periodFlag == 0){
		CLR_BIT(TIMER3->CR1, 0);
	}
	CLR_BIT(TIMER3->SR, 0);
	TIMER3_voidCallBack();
}

void TIM4_IRQHandler(void){
	if(TIMER4_periodFlag == 0){
		CLR_BIT(TIMER4->CR1, 0);
	}
	CLR_BIT(TIMER4->SR, 0);
	TIMER4_voidCallBack();
}

