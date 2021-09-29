#ifndef   SPI_PRIVATE_H
#define   SPI_PRIVATE_H

typedef struct{
	volatile u32 CR1		;
	volatile u32 CR2        ;
	volatile u32 SR         ;
	volatile u32 DR         ;
	volatile u32 CRCPR      ;
	volatile u32 RXCRCR     ;
	volatile u32 TXCRCR     ;
	volatile u32 I2SCFGR    ;
	volatile u32 I2SPR      ;
}SPI_type;

#define	SPI	((SPI_type*) 0x40013000)	//pointer to struct 
/* used as: SPI->CR1 */

#define MASTER	0
#define SLAVE	1

#define FULL_DUPLEX		0
#define BIDIRECTIONAL	1
#define UNI_RECEIVE		2
#define UNI_TRANSMIT	3

#define SOFTWARE	0
#define HARDWARE	1


#define EIGHT_BIT		0
#define SIXTEEN_BIT		1

#define FALSE		0
#define TRUE		1

#define	FPCLK_2		0
#define FPCLK_4		1
#define FPCLK_8		2
#define FPCLK_16	3
#define FPCLK_32	4
#define FPCLK_64	5
#define FPCLK_128	6
#define FPCLK_256	7

#define LOW_IDLE_LEADING		0
#define LOW_IDLE_TRAILING		1
#define HIGH_IDLE_LEADING		2
#define HIGH_IDLE_TRAILING		3

static void SPI_MasterSendReceiveCallBack(void);

#endif

