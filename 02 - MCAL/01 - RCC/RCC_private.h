#ifndef		_RCC_PRIVATE_H_
#define		_RCC_PRIVATE_H_

#define RCC_BASE_ADDRESS	0x40021000

//define RCC registers

#define RCC_CR			*((u32*)(RCC_BASE_ADDRESS + 0x00))
#define RCC_CFGR		*((u32*)(RCC_BASE_ADDRESS + 0x04))
#define RCC_CIR			*((u32*)(RCC_BASE_ADDRESS + 0x08))
#define RCC_APB2RSTR	*((u32*)(RCC_BASE_ADDRESS + 0x0C))
#define RCC_APB1RSTR	*((u32*)(RCC_BASE_ADDRESS + 0x10))
#define RCC_AHBENR		*((u32*)(RCC_BASE_ADDRESS + 0x14))
#define RCC_APB2ENR		*((u32*)(RCC_BASE_ADDRESS + 0x18))
#define RCC_APB1ENR		*((u32*)(RCC_BASE_ADDRESS + 0x1C))
#define RCC_BDCR		*((u32*)(RCC_BASE_ADDRESS + 0x20))
#define RCC_CSR			*((u32*)(RCC_BASE_ADDRESS + 0x24))

//clock types
#define RCC_HSI			0
#define RCC_HSE_CRYSTAL	1
#define RCC_HSE_RC		2
#define RCC_PLL			3

//PLL input types
#define RCC_HSE			0
#define RCC_HSE_DIV_2	1
#define RCC_HSI_DIV_2	2

//Registers pins macors
#define PLLMUL  18

		
#endif