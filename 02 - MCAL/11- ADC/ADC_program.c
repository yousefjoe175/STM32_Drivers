#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ADC_private.h"
#include "ADC_config.h"
#include "ADC_interface.h"

#if DMA == ENABLE
	#include "DMA_interface.h"
#endif

void MADC_voidInitialize(void){
	#if	ADC_CONT == 0
		SET_BIT(ADC1->CR2,1);
	#elif ADC_CONT == 1
		CLR_BIT(ADC1->CR2,1);
	#endif
	
	#if ADC_MUL_CHANNELS == ENABLE
		/*enable the scan mode */
		SET_BIT(ADC1->CR1,8);
		/* set the sequence length of conversion */
		SET_VAL(ADC1->SQR1,20,ADC_SEQ_LEN);
		/*set the channels in sequence */
		//seq1
		SET_VAL(ADC1->SQR3,0,ADC_SQ1);
		//seq2
		SET_VAL(ADC1->SQR3,5,ADC_SQ2);
		//seq3
		SET_VAL(ADC1->SQR3,10,ADC_SQ3);
		//seq4
		SET_VAL(ADC1->SQR3,10,ADC_SQ4);
		//seq5
		SET_VAL(ADC1->SQR3,10,ADC_SQ5);
		//seq6
		SET_VAL(ADC1->SQR3,10,ADC_SQ6);
		//seq7
		SET_VAL(ADC1->SQR3,10,ADC_SQ7);
		//seq8
		SET_VAL(ADC1->SQR3,10,ADC_SQ8);
		//seq9
		SET_VAL(ADC1->SQR3,10,ADC_SQ9);
		//seq10
		SET_VAL(ADC1->SQR3,10,ADC_SQ10);
		//seq11
		SET_VAL(ADC1->SQR3,10,ADC_SQ11);
		//seq12
		SET_VAL(ADC1->SQR3,10,ADC_SQ12);
		//seq13
		SET_VAL(ADC1->SQR3,10,ADC_SQ13);
		//seq14
		SET_VAL(ADC1->SQR3,10,ADC_SQ14);
		//seq15
		SET_VAL(ADC1->SQR3,10,ADC_SQ15);
		//seq16
		SET_VAL(ADC1->SQR3,10,ADC_SQ16);
	#elif ADC_MUL_CHANNELS == DISABLE
		CLR_VAL(ADC1->SQR1,20,0b1111);
		//seq1
		SET_VAL(ADC1->SQR3,0,ADC_SQ1);
	#endif
	/* set ADON */
	SET_BIT(ADC1->CR2,0);
}

void MADC_voidStartConversion(void){
	/*set ADON again*/
	SET_BIT(ADC1->CR2,0);
}

void MADC_voidReadData(u16 *ptr_u16Buffer){
	while(GET_BIT(ADC1->SR,1) ==0 );
	*ptr_u16Buffer = ADC1->DR;
}

void MADC_voidSetAnalogWatchDog(u16 HighThreshold, u16 LowThreshold, void (*ptr)(void));


//For the use of multiple channels we need to enable scan bit beside the DMA channel 1
#if DMA == ENABLE
	void MADC_voidReadDataScanDMA(u16 *ptr_u16Buffer);
#endif
