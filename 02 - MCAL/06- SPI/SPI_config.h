#ifndef SPI_CONFIG_H
#define SPI_CONFIG_H


/*
 *	MASTER
 *	SLAVE
 */
#define OPERATION 


/*	Modes of Operation
 *
 *	FULL_DUPLEX
 *	BIDIRECTIONAL
 *	UNI_RECEIVE
 *	UNI_TRANSMIT
 *
 */
#define MODE




/*
 *	SOFTWARE
 *	HARDWARE
 */
#define SLAVE_SELECT



/*	data frame
 *	EIGHT_BIT
 *	SIXTEEN_BIT
 */
#define DATA_FRAME 




/*	
 *	FALSE
 *	TRUE
 */
#define LSBFIRST


/*	Baud Rate
 *	FPCLK_2
 *	FPCLK_4
 *	FPCLK_8
 *	FPCLK_16
 *	FPCLK_32
 *	FPCLK_64
 *	FPCLK_128
 *	FPCLK_256
 */
#define BAUD_RATE


/* clock polarity and phase
 *	LOW_IDLE_LEADING
 *	LOW_IDLE_TRAILING
 *	HIGH_IDLE_LEADING
 *	HIGH_IDLE_TRAILING
 */
#define CLOCK_POL_PHASE


/*	Slave selection
 *	GPIOA,0
 *	GPIOA,1
 *	.
 *	.
 */
#define SLAVE0
#define SLAVE1
#define SLAVE2

#endif