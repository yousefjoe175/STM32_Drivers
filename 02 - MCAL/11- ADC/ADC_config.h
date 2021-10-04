#ifndef 	ADC_CONFIG_H
#define 	ADC_CONFIG_H

/*
 * ENABLE
 * DISABLE
 */
#define ADC_MUL_CHANNELS
/*
 * 0: single conversion
 * 1: continuous conversion 
 */
#define ADC_CONT	0


/*
 * choose from 0 to 15
 *	0: 1 conversion ..etc
 */
#define ADC_SEQ_LEN	0

/*
 *	choose for each from 0 to 17 to be the sequence
 *	NOTE: only the number of SEQ_LEN will be taken in sequence 
 */
#define ADC_SQ1	    0
#define ADC_SQ2	    0
#define ADC_SQ3	    0
#define ADC_SQ4	    0
#define ADC_SQ5	    0
#define ADC_SQ6	    0
#define ADC_SQ7	    0
#define ADC_SQ8	    0
#define ADC_SQ9	    0
#define ADC_SQ10	0
#define ADC_SQ11	0
#define ADC_SQ12	0
#define ADC_SQ13	0
#define ADC_SQ14	0
#define ADC_SQ15	0
#define ADC_SQ16	0


/*
 * ENABLE
 * DISABLE
 */
#define DMA


#endif