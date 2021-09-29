#ifndef  NVIC_INTERFACE_H
#define  NVIC_INTERFACE_H


void MNVIC_voidInitialize (void);

void MNVIC_voidSetPriority (u8 copy_u8Peripheral, u8 copy_u8Priority);

void MNVIC_voidEnableInterrupt (u8 copy_u8InterruptNumber);

void MNVIC_voidDisableInterrupt (u8 copy_u8InterruptNumber);

void MNVIC_voidSetPendingFlag(u8 copy_u8InterruptNumber);

void MNVIC_voidClearPendingFlag (u8 copy_u8InterruptNumber);

u8 MNVIC_u8GetActiveFlag (u8 copy_u8InterruptNumber);

#endif
