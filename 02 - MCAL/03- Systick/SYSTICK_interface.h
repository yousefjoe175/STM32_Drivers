#ifndef SYSTICK_INTERFACE_H
#define SYSTICK_INTERFACE_H

void(*Callback)(void);

//init function
void MSYSTICK_voidInitialize(void);
//delay polling (Synch.)
void MSYSTICK_voidSetBusyWait(u32 copy_u32ticks);
//delay interrupt (Asynch.)
void MSYSTICK_voidSetIntervalSingle(u32 copy_u32ticks,void(*ptr)(void) );
//set tick count register without interrupt
void MSYSTICK_voidSetTickCount(u32 copy_u32ticks );
//periodic timer
void MSYSTICK_voidSetIntervalPeriodic(u32 copy_u32ticks,void(*ptr)(void) );
//stop periodic timer
void MSYSTICK_voidStopInterval(void);
//get elapsed time
u32 MSYSTICK_u32GetElapsedTime(void);
//get remaining time
u32 MSYSTICK_u32GetRemainingTime(void);


#endif
