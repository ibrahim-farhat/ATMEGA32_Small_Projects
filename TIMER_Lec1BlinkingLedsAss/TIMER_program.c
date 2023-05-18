/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: TIMER Tarek			**********************/
/**********************			File: TIMER_program.c		**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file TIMER_program.c
 * @author Ibrahim Tarek
 * @brief This file implements the TIMER module functions.
 * @version 1.00
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DEFINES.h"

#include "TIMER_interface.h"
#include "TIMER_config.h"
#include "TIMER_private.h"
#include "TIMER_register.h"


static void (* TIMER_pvCTCNotificationFunc)(void) = NULL;
static void (* TIMER_pvOverflowNotificationFunc)(void) = NULL;

void TIMER_voidInit(void)
{
	/*Select Wave Generation Mode*/
	CLR_BIT(TCCR0,TCCR0_WGM00);
	SET_BIT(TCCR0,TCCR0_WGM01);

	/*Select Compare Match Output Mode*/
	CLR_BIT(TCCR0,TCCR0_COM00);
	CLR_BIT(TCCR0,TCCR0_COM01);

	/*Select Prescaler*/
	CLR_BIT(TCCR0,TCCR0_CS00);
	SET_BIT(TCCR0,TCCR0_CS01);
	CLR_BIT(TCCR0,TCCR0_CS02);

	/*Enable The Timer Interrupt*/
	SET_BIT(TIMSK,TIMSK_OCIE0);

	/*Set the Compare Match Value*/
	OCR0 = 250;
}

uint8 TIMER_u8SetCallBackCompareMatch(void (* Copy_pvNotificationFunc)(void))
{
	/*Define Variables*/
	uint8 Local_u8ErrorState = OK;

	/*Validating the pointer to the function*/
	if(Copy_pvNotificationFunc != NULL)
	{
		/*Convert the local pointer to global to be sent to ISR*/
		TIMER_pvCTCNotificationFunc = Copy_pvNotificationFunc;
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	/*Return Error State*/
	return Local_u8ErrorState;
}


uint8 TIMER_u8SetCallBackOverflow(void (* Copy_pvNotificationFunc)(void))
{
	/*Define Variables*/
	uint8 Local_u8ErrorState = OK;

	/*Validating the pointer to the function*/
	if(Copy_pvNotificationFunc != NULL)
	{
		/*Convert the local pointer to global to be sent to ISR*/
		TIMER_pvOverflowNotificationFunc = Copy_pvNotificationFunc;
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	/*Return Error State*/
	return Local_u8ErrorState;
}


/*OverFlow Event ISR*/
void __vector_11 (void) __attribute((signal));
void __vector_11 (void)
{
	/*Validate the pointer*/
	if(TIMER_pvOverflowNotificationFunc != NULL)
	{
		/*Calling the ISR function*/
		TIMER_pvOverflowNotificationFunc();
	}
	else
	{
		/*Do nothing*/
	}
}


/*Compare Match Event ISR*/
void __vector_10 (void) __attribute((signal));
void __vector_10 (void)
{
	/*Validate the pointer*/
	if(TIMER_pvCTCNotificationFunc != NULL)
	{
		/*Calling the ISR function*/
		TIMER_pvCTCNotificationFunc();
	}
	else
	{
		/*Do nothing*/
	}
}
