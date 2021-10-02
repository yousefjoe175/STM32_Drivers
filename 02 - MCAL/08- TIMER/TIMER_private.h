#ifndef		TIMER_PRIVATE_H
#define		TIMER_PRIVATE_H

typedef struct{
	volatile u32 CR1	;
	volatile u32 CR2	;
	volatile u32 SMCR	;
	volatile u32 DIER	;
	volatile u32 SR		;
	volatile u32 EGR	;
	volatile u32 CCMR1	;
	volatile u32 CCMR2	;
	volatile u32 CCER	;
	volatile u32 CNT	;
	volatile u32 PSC	;
	volatile u32 ARR	;
	volatile u32 RCR	;
	volatile u32 CCR1	;
	volatile u32 CCR2	;
	volatile u32 CCR3	;
	volatile u32 CCR4	;
	volatile u32 BDTR	;
	volatile u32 DCR	;
	volatile u32 DMAR	;
}Timer_t;

/* Advanced Timer */
#define TIMER1  ((Timer_t*)(0x40012C00))

/*General Purpose Timer */
#define TIMER2  ((Timer_t*)(0x40000000))
#define TIMER3  ((Timer_t*)(0x40000400))
#define TIMER4  ((Timer_t*)(0x40000800))


#endif
