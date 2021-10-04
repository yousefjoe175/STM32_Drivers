#ifndef 	ADC_INTERFACE_H
#define 	ADC_INTERFACE_H

void MADC_voidInitialize(void);

void MADC_voidStartConversion(void);

void MADC_voidReadData(u16 *ptr_u16Buffer);

#endif