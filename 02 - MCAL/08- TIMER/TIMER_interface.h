#ifndef		TIMER_INTERFACE_H
#define		TIMER_INTERFACE_H

#define TIMER2_LED_PIN		GPIOA,PIN0
#define TIMER2_LED_PIN_2	GPIOA,PIN1
#define TIMER2_LED_PIN_3	GPIOA,PIN2
#define TIMER2_LED_PIN_4	GPIOA,PIN3

#define TIMER3_LED_PIN		GPIOA,PIN6
#define TIMER3_LED_PIN_2	GPIOA,PIN7
#define TIMER3_LED_PIN_3	GPIOB,PIN0
#define TIMER3_LED_PIN_4	GPIOB,PIN1

#define TIMER4_LED_PIN		GPIOB,PIN6
#define TIMER4_LED_PIN_2	GPIOB,PIN7
#define TIMER4_LED_PIN_3	GPIOB,PIN8
#define TIMER4_LED_PIN_4	GPIOB,PIN9


typedef struct{
	u32 freq;
	u8  dutyCyle;
}ICU_type;

void MTIMER_voidDelayMs(u8 Copy_u8TimerModule, u16 Copy_u16Miliseconds);

void MTIMER_voidDelayUs(u8 Copy_u8TimerModule, u16 Copy_u16Microseconds);

void MTIMER_voidGenerateSquareWave(u8 Copy_u8TimerModule,u8 Copy_u8Channel, u16 Copy_u16PeriodinMs);

void MTIMER_voidSetIntervalSingle(u8 Copy_u8TimerModule, u16 Copy_u16PeriodinMs,void(*ptr)(void) );

void MTIMER_voidSetIntervalPeriodic(u8 Copy_u8TimerModule, u16 Copy_u16PeriodinMs,void(*ptr)(void) );

void MTIMER_voidGetInputCapture(u8 Copy_u8TimerModule, /*u8 Copy_u8Channel,*/ u8 Copy_u8Edge, u32* ptr_u32Buffer);

void MTIMER_voidGetICFreq(u8 Copy_u8TimerModule, ICU_type *ptr_ICU_tBuffer );

void MTIMER_voidSetPWM(u8 Copy_u8TimerModule, f32 Copy_f32Frequency, u8 Copy_u8DutyCycle);

void MTIMER_voidStopTimer(u8 Copy_u8TimerModule);

u32 MTIMER_u32GetElapsedTime(u8 Copy_u8TimerModule);

u32 MTIMER_u32GetRemainingTime(u8 Copy_u8TimerModule);

#endif
