#ifndef 	LCD_CONFIG_H
#define 	LCD_CONFIG_H

#define LCD_DATA_PORT	GPIOA
#define LCD_RS			GPIOA,PIN11
#define LCD_RW			GPIOA,PIN12
#define LCD_EN			GPIOA,PIN15

/* 0: 4-bit Length
 * 1: 8-bit Length
 */
#define LCD_DATA_LENGTH		1

#define LCD_START_BIT	0
#endif