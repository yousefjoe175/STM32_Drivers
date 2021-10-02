#ifndef UART_PRIVATE_H
#define UART_PRIVATE_H

typedef struct
{
	
	volatile u32 SR		;
	volatile u32 DR		;
	volatile u32 BBR	;
	volatile u32 CR1	;
	volatile u32 CR2	;
	volatile u32 CR3	;
	volatile u32 GTPR	;
	
}UART_type;
#define UART ((UART_type*)(0x40013800))

/* USART_CR1 */
#define UART_UE		13
#define UART_M		12
#define UART_WAKE	11
#define UART_PCE	10
#define UART_PS		9
#define UART_PEIE	8
#define UART_TXEIE	7
#define UART_TCIE	6
#define UART_RXNEIE	5
#define UART_IDLEIE	4
#define UART_TE		3
#define UART_RE		2	
#define UART_RWU	1
#define UART_SBK	0

/* USART_SR */
#define UART_CTS	9
#define UART_LBD	8
#define UART_TXE	7
#define UART_TC		6
#define UART_RXNE	5
#define UART_IDLE	4
#define UART_ORE	3
#define UART_NE		2
#define UART_FE		1
#define UART_PE		0

/* USART_CR3 */
#define UART_DMAT	7
#define UART_DMAR	6

#define ENABLE	1
#define DISABLE	0



#endif
