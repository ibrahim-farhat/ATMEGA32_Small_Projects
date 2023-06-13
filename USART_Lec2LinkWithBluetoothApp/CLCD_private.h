/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: CLCD_private.h		**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

#ifndef DIO_PRIVATE_H_
#define DIO_PRIVATE_H_


static void voidSendEnablePulse(void);
static void voidSetLCDHalfDataPort(uint8 Copy_u8Nipple);

#define EIGHT_BIT_MODE	1u
#define FOUR_BIT_MODE	2u

#define	ENABLED			1u
#define	DISABLED		2u

#endif
