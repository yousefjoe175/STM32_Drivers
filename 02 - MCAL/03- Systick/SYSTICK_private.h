#ifndef	SYSTICK_PRIVATE_H
#define SYSTICK_PRIVATE_H

#define SYSTICK_BASE_ADDRESS 0xE000E010

//Systick Registers
#define STK_CTRL  *((u32*)(SYSTICK_BASE_ADDRESS + 0x00))
#define STK_LOAD  *((u32*)(SYSTICK_BASE_ADDRESS + 0x04))
#define STK_VAL   *((u32*)(SYSTICK_BASE_ADDRESS + 0x08))
#define STK_CALIB *((u32*)(SYSTICK_BASE_ADDRESS + 0x0C))

//clock options
#define AHB 0
#define AHB_DIV_8 1




#endif