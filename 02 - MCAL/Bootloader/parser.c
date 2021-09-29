#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "FPEC_interface.h"

u16 data[100];
u8 CC;	//character counter
u32 address = 0x08000000;	//the offset address coming from the file will be ored with the low 2 bytes
u8 RT;	//record type
u8 counter;



static u8 AsciToHex(u8 Copy_u8Asci)
{
	u8 Result;
	if ( (Copy_u8Asci >= '0') && (Copy_u8Asci <= '9') )
	{
		Result = Copy_u8Asci - '0';
	}
	else
	{
		Result = Copy_u8Asci - 'A' + 10;
	}

	return Result;
}


u8 ParseData(u8* copy_u8DataBuffer){
	counter = 0;

	u8 DigitalCharHigh = 0;
	u8 DigitalCharLow  = 0;

	u8 DigitalAddress3 = 0;
	u8 DigitalAddress2 = 0;
	u8 DigitalAddress1 = 0;
	u8 DigitalAddress0 = 0;

	u8 DigitalData3 = 0;
	u8 DigitalData2 = 0;
	u8 DigitalData1 = 0;
	u8 DigitalData0 = 0;

	//check for ':'
	if(AsciToHex(copy_u8DataBuffer[counter++]) == ':'){
		//continue parsing
		//get the CC
		DigitalCharHigh = AsciToHex(copy_u8DataBuffer[counter++]);
		DigitalCharLow  = AsciToHex(copy_u8DataBuffer[counter++]);
		CC = (DigitalCharHigh<<4) | DigitalCharLow;
		//get the address
		DigitalAddress3 = AsciToHex(copy_u8DataBuffer[counter++]);
		DigitalAddress2 = AsciToHex(copy_u8DataBuffer[counter++]);
		DigitalAddress1 = AsciToHex(copy_u8DataBuffer[counter++]);
		DigitalAddress0 = AsciToHex(copy_u8DataBuffer[counter++]);
		//clear the previous offset
		address = address & 0xffff0000;
		//save the address
		address = address | (DigitalAddress3<<12) | (DigitalAddress2<<8) | (DigitalAddress1<<4) | (DigitalAddress0);
		//get the RT
		DigitalCharHigh = AsciToHex(copy_u8DataBuffer[counter++]);
		DigitalCharLow  = AsciToHex(copy_u8DataBuffer[counter++]);
		RT = (DigitalCharHigh<<4) | DigitalCharLow;
		if(RT == 1){	//if RT is end of file return the state that ends the bootloader program
			return 0;
		}
		else if( RT == 4){	//if RT is the upper 2 bytes of address
			//get the next 4 digits (2 bytes)
			//get the address
			DigitalAddress3 = AsciToHex(copy_u8DataBuffer[counter++]);
			DigitalAddress2 = AsciToHex(copy_u8DataBuffer[counter++]);
			DigitalAddress1 = AsciToHex(copy_u8DataBuffer[counter++]);
			DigitalAddress0 = AsciToHex(copy_u8DataBuffer[counter++]);
			
			address = address & 0x0000ffff;
			address = address | (DigitalAddress3<<28) | (DigitalAddress2<<24) | (DigitalAddress1<<20) | (DigitalAddress0<<16);
		}
		else if(RT == 0){ //if RT is data record
			for(u16 i=0; i<CC/2; i++){	// CC/2 because we get two bytes at once
				DigitalData3 = AsciToHex(copy_u8DataBuffer[counter++]);
				DigitalData2 = AsciToHex(copy_u8DataBuffer[counter++]);
				DigitalData1 = AsciToHex(copy_u8DataBuffer[counter++]);
				DigitalData0 = AsciToHex(copy_u8DataBuffer[counter++]);
				data[i] = (DigitalData3<<12) | (DigitalData2<<8) | (DigitalData1<<4) | (DigitalData0);
			}
			FPEC_voidFlashWrite(address, data, CC/2);
		}
		else{
			
		}
		return 1;	//return the continue state (there're more data to send)
		
	}
	else
	{
		return -1; //return error
	}
}

