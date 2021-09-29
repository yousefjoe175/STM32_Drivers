#ifndef		EXTI_INTERFAC_H
#define		EXTI_INTERFAC_H

void MEXTI_voidEnableInterruptLine(u8 copy_u8LineID, u8 copy_u8SenseMode);

void MEXTI_voidSwtichPort(u8 copy_u8LineID, u8 copy_u8PortID);

void MEXTI_voidDisableInterruptLine(u8 copy_u8LineID);

void MEXTI_voidSetPendingInterrupt(u8 copy_u8LineID);

void MEXTI_voidSetCallBack(u8 copy_u8LineID, void(*ptr)(void));



#define RISING_EDGE		0
#define FALLING_EDGE	1
#define ON_CHANGE		2


#endif