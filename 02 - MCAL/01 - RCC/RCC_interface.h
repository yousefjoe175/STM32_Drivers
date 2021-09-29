#ifndef		_RCC_INTERFACE_H_
#define		_RCC_INTERFACE_H_

void MRCC_voidInitializeSystemClock(void);	//initialize = void 

void MRCC_voidEnablePeripheralClock(u8 Copy_u8BusID, u8 Copy_PeripheralID);
void MRCC_voidDisablePeripheralClock(u8 Copy_u8BusID, u8 Copy_PeripheralID);


#define RCC_AHB 	0
#define RCC_APB1	1
#define RCC_APB2	2


//AHB RCC peripherals
#define RCC_AHB_DMA1
#define RCC_AHB_DMA2
#define RCC_AHB_SRAM
#define RCC_AHB_FLITF	//flash memory interface
#define RCC_AHB_CRC
#define RCC_AHB_FSMC
#define RCC_AHB_SDIO

//APB1 RCC peripherals
#define RCC_APB1_TIM2 
#define RCC_APB1_TIM3
#define RCC_APB1_TIM4
#define RCC_APB1_TIM5 
#define RCC_APB1_TIM6 
#define RCC_APB1_TIM7
#define RCC_APB1_TIM12 
#define RCC_APB1_TIM13
#define RCC_APB1_TIM14
#define RCC_APB1_WWDG
#define RCC_APB1_SPI2 
#define RCC_APB1_SPI2
#define RCC_APB1_USART2
#define RCC_APB1_USART3
#define RCC_APB1_USART4
#define RCC_APB1_USART5
#define RCC_APB1_I2C1
#define RCC_APB1_I2C2
#define RCC_APB1_USB
#define RCC_APB1_CAN
#define RCC_APB1_BKP
#define RCC_APB1_PWR
#define RCC_APB1_DAC

//APB2 RCC peripherals
#define RCC_APB2_AFIO
#define RCC_APB2_IOPA
#define RCC_APB2_IOPB
#define RCC_APB2_IOPC
#define RCC_APB2_IOPD
#define RCC_APB2_IOPE
#define RCC_APB2_IOPF
#define RCC_APB2_IOPG
#define RCC_APB2_ADC1
#define RCC_APB2_ADC2
#define RCC_APB2_TIM1
#define RCC_APB2_SPI1
#define RCC_APB2_TIM8
#define RCC_APB2_USART1
#define RCC_APB2_ADC3
#define RCC_APB2_TIM9
#define RCC_APB2_TIM10
#define RCC_APB2_TIM11





#endif