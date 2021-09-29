#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "RCC_private.h"
#include "RCC_config.h"
#include "RCC_interface.h"
/*
 *RCC_HSI
 * RCC_HSE_CRYSTAL
 * RCC_HSE_RC
 * RCC_PLL
**/
void MRCC_voidInitializeSystemClock(void){
	#if RCC_CLOCK_TYPE  == RCC_HSI
	RCC_CR	  = 0x00000081;
	RCC_CFGR  = 0x00000000;
	
	#elif RCC_CLOCK_TYPE == RCC_HSE_CRYSTAL
	RCC_CR	  = 0x00010000;
	RCC_CFGR  = 0x00000001;
	
	#elif RCC_CLOCK_TYPE == RCC_HSE_RC
	RCC_CR	  = 0x00050000;
	RCC_CFGR  = 0x00000001;
	
	#elif RCC_CLOCK_TYPE == RCC_PLL
			#if RCC_PLL_INPUT   == RCC_HSE
			RCC_CR	 =  0x01000000;
			RCC_CFGR =  0x00010002;
			SET_VAL(RCC_CFGR,PLLMUL,(RCC_PLL_MUL_FACTOR - 2) );
				//clear the 4 bits of the multiplier factor 
				//then add the value you wanted after you subtract 2
				
			#elif RCC_PLL_INPUT == RCC_HSE_DIV_2
			RCC_CR	 =  0x01000000;
			RCC_CFGR =  0x00030002;
			SET_VAL(RCC_CFGR,PLLMUL,(RCC_PLL_MUL_FACTOR - 2) );
			
			#elif RCC_PLL_INPUT == RCC_HSI_DIV_2
			RCC_CR	 =  0x01000000;
			RCC_CFGR =  0x00000002;
			SET_VAL(RCC_CFGR,PLLMUL,(RCC_PLL_MUL_FACTOR - 2) );
			#else
				//error
			#endif
			
	#else
		//error
	#endif
}


void MRCC_voidEnablePeripheralClock(u8 Copy_u8BusID, u8 Copy_PeripheralID){
    if(Copy_PeripheralID < 32)
    {
        switch(Copy_u8BusID)
        {
            case RCC_AHB :   SET_BIT(RCC_AHBENR, Copy_PeripheralID);  break;
            case RCC_APB1:  SET_BIT(RCC_APB1ENR, Copy_PeripheralID); break;
            case RCC_APB2:  SET_BIT(RCC_APB2ENR, Copy_PeripheralID); break;
            default: /* error */ break;
        }
    }
    else
    {
        //error
    }
}

void MRCC_voidDisablePeripheralClock(u8 Copy_u8BusID, u8 Copy_PeripheralID){
    if(Copy_PeripheralID < 32)
    {
        switch(Copy_u8BusID)
        {
            case RCC_AHB :  CLR_BIT(RCC_AHBENR, Copy_PeripheralID);  break;
            case RCC_APB1:  CLR_BIT(RCC_APB1ENR, Copy_PeripheralID); break;
            case RCC_APB2:  CLR_BIT(RCC_APB2ENR, Copy_PeripheralID); break;
            default: /* error */ break;
        }
    }
    else
    {
        //error
    }
}