#ifndef FPEC_PRIVATE_H
#define FPEC_PRIVATE_H

#define FLASH_MEMORY_ADDRESS	0x08000000

typedef struct{
	volatile u32 ACR;
	volatile u32 KEYR;
	volatile u32 OPTKEYR;
	volatile u32 SR;
	volatile u32 CR;
	volatile u32 AR;
	volatile u32 RESERVED;
	volatile u32 OBR;
	volatile u32 WRPR;
}FPEC_type;

#define FPEC	((FPEC_type*)(0x40022000))

/* FLASH_CR*/
#define PG		0
#define PER		1
#define MER		2
#define OPTPG	4
#define OPTER	5
#define STRT	6
#define LOCK	7
#define OPTWRE	9
#define ERRIE	10
#define EOPIE	12

/* FLASH_SR */
#define	BSY		0
#define	PGERR	2
#define WRPRT	4
#define EOP		5

#define FPEC_RDPRT_KEY	0x00A5
#define FPEC_KEY1		0x45670123
#define FPEC_KEY2		0xCDEF89AB


#endif