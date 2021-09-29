#ifndef DMA_PRIVATE_H
#define DMA_PRIVATE_H

typedef struct{
	volatile u32 CCR     ;
	volatile u32 CNDTR   ;
	volatile u32 CPAR	 ;
	volatile u32 CMAR	 ;
	volatile u32 RESERVED;
}CHANNEL_type;

typedef struct{
	volatile u32 ISR 	   ;
	volatile u32 IFCR	   ;
	CHANNEL_type channel[7];
}DMA_type;
#define DMA ((DMA_type*)(0x40020000))

/* put all the data registers adresses in DMA private driver */
#define DMA_SPI_DR_AD		((u32*)(0x4001300C))


#define DMA_EN			0
#define DMA_TCIE        1
#define DMA_HTIE        2
#define DMA_TEIE        3
#define DMA_DIR         4
#define DMA_CIRC        5
#define DMA_PINC        6
#define DMA_MINC        7
#define DMA_PSIZE       8
#define DMA_MSIZE       10
#define DMA_PL          12
#define DMA_MEM2MEM     14

/*DMA_ISR */
#define DMA_GIF			0
#define DMA_TCIF		1
#define DMA_HTIF		2
#define DMA_TEIF		3

/*DMA_IFCR */
#define DMA_CGIF		0
#define DMA_CTCIF		1
#define DMA_CHTIF		2
#define DMA_CTEIF		3



#endif