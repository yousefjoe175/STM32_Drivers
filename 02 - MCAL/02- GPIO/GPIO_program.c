#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "GPIO_private.h"
#include "GPIO_config.h"


void MGPIO_voidSetPinMode(u8 copy_u8PortID, u8 copy_u8PinID, u8 copy_u8PinMode){
	if(copy_u8PinID <= 15)
	{
		switch(copy_u8PortID)
		{
			case GPIOA:	if(copy_u8PinID <=7)
						{
							GPIOA_CRL &= ~((0b1111)<<(copy_u8PinID*4));
							GPIOA_CRL |= ((copy_u8PinMode)<<(copy_u8PinID*4));
						}
						else if(copy_u8PinID <=15)
						{
							copy_u8PinID -= 8;
							GPIOA_CRH &= ~((0b1111)<<(copy_u8PinID*4));
							GPIOA_CRH |= ((copy_u8PinMode)<<(copy_u8PinID*4));
						}
						else
						{
							//error
						}
						break;
			case GPIOB: if(copy_u8PinID <=7)
						{
							GPIOB_CRL &= ~((0b1111)<<(copy_u8PinID*4));
							GPIOB_CRL |= ((copy_u8PinMode)<<(copy_u8PinID*4));
						}
						else if(copy_u8PinID <=15)
						{
							copy_u8PinID -= 8;
							GPIOB_CRH &= ~((0b1111)<<(copy_u8PinID*4));
							GPIOB_CRH |= ((copy_u8PinMode)<<(copy_u8PinID*4));
						}
						else
						{
							//error
						}
						break;
			case GPIOC: if(copy_u8PinID <=7)
						{
							GPIOC_CRL &= ~((0b1111)<<(copy_u8PinID*4));
							GPIOC_CRL |= ((copy_u8PinMode)<<(copy_u8PinID*4));
						}
						else if(copy_u8PinID <=15)
						{
							copy_u8PinID -= 8;
							GPIOC_CRH &= ~((0b1111)<<(copy_u8PinID*4));
							GPIOC_CRH |= ((copy_u8PinMode)<<(copy_u8PinID*4));
						}
						else
						{
							//error
						}
						break;
			default:	/*invalid error*/ break;
		}
		
		
	}
	else
	{
		//invalid input
	}
}

void MGPIO_voidSetPinValue(u8 copy_u8PortID, u8 copy_u8PinID, u8 copy_u8PinValue){
	if(copy_u8PinID <= 15)
	{
		switch(copy_u8PortID)
		{
			case GPIOA:	if(copy_u8PinValue == GPIO_HIGH)
						{
							SET_BIT(GPIOA_ODR, copy_u8PinID);
						}
						else if (copy_u8PinValue == GPIO_LOW)
						{
							CLR_BIT(GPIOA_ODR, copy_u8PinID);
						}
						else{
							//error
						}
						break;
			case GPIOB: if(copy_u8PinValue == GPIO_HIGH)
						{
							SET_BIT(GPIOB_ODR, copy_u8PinID);
						}
						else if (copy_u8PinValue == GPIO_LOW)
						{
							CLR_BIT(GPIOB_ODR, copy_u8PinID);
						}
						else{
							//error
						}
						break;
			case GPIOC: if(copy_u8PinValue == GPIO_HIGH)
						{
							SET_BIT(GPIOC_ODR, copy_u8PinID);
						}
						else if (copy_u8PinValue == GPIO_LOW)
						{
							CLR_BIT(GPIOC_ODR, copy_u8PinID);
						}
						else{
							//error
						}
						break;			
			default: /*invalid */ break;
			
		}
	}
	else
	{
		//invalid input
	}
}

void MGPIO_voidTogglePinValue(u8 copy_u8PortID, u8 copy_u8PinID){
	if(copy_u8PinID <= 15)
		{
			switch(copy_u8PortID)
			{
				case GPIOA:	TOG_BIT(GPIOA_ODR, copy_u8PinID);
							break;
				case GPIOB: TOG_BIT(GPIOB_ODR, copy_u8PinID);
							break;
				case GPIOC: TOG_BIT(GPIOC_ODR, copy_u8PinID);
							break;
				default: /*invalid */ break;
			}
		}
		else
		{
			//invalid input
		}
}

u8	 MGPIO_u8GetPinValue(u8 copy_u8PortID, u8 copy_u8PinID)
{
	u8 Local_u8PinState = 0;
	if(copy_u8PinID <= 15)
	{
		switch(copy_u8PortID)
		{
			case GPIOA: Local_u8PinState = GET_BIT(GPIOA_IDR, copy_u8PinID); break;
			case GPIOB: Local_u8PinState = GET_BIT(GPIOB_IDR, copy_u8PinID); break;
			case GPIOC: Local_u8PinState = GET_BIT(GPIOC_IDR, copy_u8PinID); break;
			default: /*error */ break;
		}
	}
	else
	{
		// invalid input
	}
	return Local_u8PinState;
		
}




void MGPIO_voidAtomicSetPinValue(u8 copy_u8PortID, u8 copy_u8PinID, u8 copy_u8PinValue){
	if(copy_u8PinID <= 15){
		switch(copy_u8PortID){
			case GPIOA:	
					if(copy_u8PinValue == GPIO_HIGH)
					{
						GPIOA_BSRR = (1<< copy_u8PinID);
					}
					else
					{
						GPIOA_BSRR = (1<< (copy_u8PinID + 16));
					}
					break;
			case GPIOB:
					if(copy_u8PinValue == GPIO_HIGH)
					{
						GPIOB_BSRR = (1<< copy_u8PinID);
					}
					else
					{
						GPIOB_BSRR = (1<< (copy_u8PinID + 16));
					}
					break;
			case GPIOC:
					if(copy_u8PinValue == GPIO_HIGH)
					{
						GPIOC_BSRR = (1<< copy_u8PinID);
					}
					else
					{
						GPIOC_BSRR = (1<< (copy_u8PinID + 16));
					}
					break;
			default:
				//error
				break;
		}
	}
	else{
		//error
	}
}


void MGPIO_voidAtomicResetPinValue(u8 copy_u8PortID, u8 copy_u8PinID)
{
	if(copy_u8PinID <= 15){
		switch(copy_u8PortID){
			case GPIOA:	
				GPIOA_BRR = (1<<copy_u8PinID);
				break;
			case GPIOB:
				GPIOB_BRR = (1<<copy_u8PinID);
				break;
			case GPIOC:	
				GPIOC_BRR = (1<<copy_u8PinID);
				break;
			default:
			//error
			break;
		}
	}
	else
	{
		//error
	}
}


void MGPIO_voidUnlockSequence(u8 copy_u8PortID){
	switch(copy_u8PortID){
		case GPIOA:
			SET_BIT(GPIOA_LCKR, 16);
			CLR_BIT(GPIOA_LCKR, 16);
			SET_BIT(GPIOA_LCKR, 16);
			while(GET_BIT(GPIOA_LCKR, 16));
			break;
		case GPIOB:
			SET_BIT(GPIOB_LCKR, 16);
			CLR_BIT(GPIOB_LCKR, 16);
			SET_BIT(GPIOB_LCKR, 16);
			while(GET_BIT(GPIOB_LCKR, 16));
			break;
		case GPIOC:
			SET_BIT(GPIOC_LCKR, 16);
			CLR_BIT(GPIOC_LCKR, 16);
			SET_BIT(GPIOC_LCKR, 16);
			while(GET_BIT(GPIOC_LCKR, 16));
			break;
		default:
			//error
			break;
	}
}

void MGPIO_voidLockUnlock(u8 copy_u8PortID, u8 copy_u8PinID, u8 copy_u8PinLockUnlock){
	if(copy_u8PinID <= 15){
		switch(copy_u8PortID){
			case GPIOA:	
				if(copy_u8PinLockUnlock == GPIO_LOCK){
					GPIOA_LCKR = (1<<copy_u8PinID);
				}else{
					GPIOA_LCKR = (1<<copy_u8PinID);
				}
				break;
			case GPIOB:
				if(copy_u8PinLockUnlock == GPIO_LOCK){
					GPIOB_LCKR = (1<<copy_u8PinID);
				}else{
					GPIOB_LCKR = (1<<copy_u8PinID);
				}
				break;
			case GPIOC:	
				if(copy_u8PinLockUnlock == GPIO_LOCK){
					GPIOC_LCKR = (1<<copy_u8PinID);
				}else{
					GPIOC_LCKR = (1<<copy_u8PinID);
				}
				break;
			default:
			//error
			break;
		}
	}
	else
	{
		//error
	}
}

void MGPIO_voidSetMultiplePinValue(u8 copy_u8PortID, u8 copy_u8FirstPinID, u16 copy_u16Value){
	if(copy_u8FirstPinID <= 15)
	{
		switch(copy_u8PortID)
		{
			case GPIOA:	SET_VAL(GPIOA_ODR,copy_u8FirstPinID,copy_u16Value);
						break;
			case GPIOB: SET_VAL(GPIOB_ODR,copy_u8FirstPinID,copy_u16Value);
						break;
			case GPIOC: SET_VAL(GPIOC_ODR,copy_u8FirstPinID,copy_u16Value);
						break;			
			default: /*invalid */ break;
			
		}
	}
	else
	{
		//invalid input
	}	
	
}

void MGPIO_voidClearMultiplePinValue(u8 copy_u8PortID, u8 copy_u8FirstPinID, u16 copy_u16Value){
	if(copy_u8FirstPinID <= 15)
	{
		switch(copy_u8PortID)
		{
			case GPIOA:	CLR_VAL(GPIOA_ODR,copy_u8FirstPinID,copy_u16Value);
						break;                                    
			case GPIOB: CLR_VAL(GPIOB_ODR,copy_u8FirstPinID,copy_u16Value);
						break;                                    
			case GPIOC: CLR_VAL(GPIOC_ODR,copy_u8FirstPinID,copy_u16Value);
						break;			
			default: /*invalid */ break;
			
		}
	}
	else
	{
		//invalid input
	}	
}


void MGPIO_voidSetPortValue(u8 copy_u8PortID, u16 copy_u16Value){
	
	switch(copy_u8PortID)
	{
		case GPIOA:	GPIOA_ODR = copy_u16Value;
					break;
		case GPIOB: GPIOB_ODR = copy_u16Value;
					break;
		case GPIOC: GPIOC_ODR = copy_u16Value;
					break;			
		default: /*invalid */ break;
		
	}
	
}