#ifndef		LCD_INTERFACE_H
#define		LCD_INTERFACE_H


u8 LCD_CG_ADDR_Counter;		//to hold the address of each row to be used
u8 LCD_CG_addresses[8];		//to hold the value to be sent to send data function
u8 counter;					//used to store the value of ADDR_Counter in addresses[counter];

void HLCD_GPIOInitialize(void);
void HLCD_voidInitialize(void);

void HLCD_voidSendCommand(u8 Copy_u8Command);
void HLCD_voidSendData(u8 Copy_u8Data);

void HLCD_voidSetPosition(u8 Copy_u8Column, u8 Copy_u8Row);
void HLCD_voidClearDisplay(void);

void HLCD_voidSetCustomChar(u8 Buffer[]);

void HLCD_voidSend4BitNibble(u8 Copy_u8Data, u8 Copy_u8Command);

void HLCD_voidSendNumber(u32 Copy_u32Number);
void LCD_voidPrintString(u8 *Ptr_u8String);
#endif

