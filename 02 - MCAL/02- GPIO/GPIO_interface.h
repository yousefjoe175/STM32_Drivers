#ifndef GPIO_INTERFACE_H
#define  GPIO_INTERFACE_H

void MGPIO_voidSetPinMode(u8 copy_u8PortID, u8 copy_u8PinID, u8 copy_u8PinMode);

void MGPIO_voidSetPinValue(u8 copy_u8PortID, u8 copy_u8PinID, u8 copy_u8PinValue);

void MGPIO_voidTogglePinValue(u8 copy_u8PortID, u8 copy_u8PinID);

u8	 MGPIO_u8GetPinValue(u8 copy_u8PortID, u8 copy_u8PinID);

void MGPIO_voidSetMultiplePinValue(u8 copy_u8PortID, u8 copy_u8FirstPinID, u16 copy_u16Value);

void MGPIO_voidClearMultiplePinValue(u8 copy_u8PortID, u8 copy_u8FirstPinID, u16 copy_u16Value);

void MGPIO_voidSetPortValue(u8 copy_u8PortID, u16 copy_u16Value);

void MGPIO_voidAtomicSetPinValue(u8 copy_u8PortID, u8 copy_u8PinID, u8 copy_u8PinValue);

void MGPIO_voidAtomicResetPinValue(u8 copy_u8PortID, u8 copy_u8PinID);

void MGPIO_voidUnlockSequence(u8 copy_u8PortID);

/* macros */
#define GPIO_HIGH 1
#define GPIO_LOW  0 

/*ports macros */
#define  GPIOA	0
#define  GPIOB	1
#define  GPIOC	2

/* pin macros */
#define PIN0   0
#define PIN1   1
#define PIN2   2
#define PIN3   3
#define PIN4   4
#define PIN5   5
#define PIN6   6
#define PIN7   7
#define PIN8   8
#define PIN9   9
#define PIN10 10
#define PIN11 11
#define PIN12 12
#define PIN13 13
#define PIN14 14
#define PIN15 15





/* PIN modes */
#define  OUTPUT_10MHZ_PP	0b0001
#define  OUTPUT_10MHZ_OD    0b0101
#define  OUTPUT_10MHZ_AF_PP 0b1001
#define  OUTPUT_10MHZ_AF_OD 0b1101

#define  OUTPUT_2MHZ_PP		0b0010
#define  OUTPUT_2MHZ_OD     0b0110
#define  OUTPUT_2MHZ_AF_PP  0b1010
#define  OUTPUT_2MHZ_AF_OD  0b1110

#define  OUTPUT_50MHZ_PP	0b0011
#define  OUTPUT_50MHZ_OD    0b0111
#define  OUTPUT_50MHZ_AF_PP 0b1011
#define  OUTPUT_50MHZ_AF_OD 0b1111

#define  INPUT_ANALOG       0b0000
#define  INPUT_FLOATING     0b0100
#define  INPUT_PULL_UP_DOWN 0b1000		//for setting Pull up set 1 on GPIO_ODR and 0 for pull down

/* lock unlock */
#define GPIO_LOCK   1
#define GPIO_UNLOCK 0

#endif