/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: TIMER Tarek			**********************/
/**********************			File: TIMERS_program.c		**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file TIMERS_program.c
 * @author Ibrahim Tarek
 * @brief This file implements the TIMERS module functions.
 * @version 1.00
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DEFINES.h"

#include "TIMERS_interface.h"
#include "TIMERS_config.h"
#include "TIMERS_private.h"
#include "TIMERS_register.h"

static void (* TIMERS_pvCallBackFuncArr[8])(void);

void TIMER0_voidInit(void)
{
	/*Select Wave Generation Mode*/
	SET_BIT(TCCR0,TCCR0_WGM00);
	SET_BIT(TCCR0,TCCR0_WGM01);

	/*Select Compare Match Output Mode*/
	CLR_BIT(TCCR0,TCCR0_COM00);
	SET_BIT(TCCR0,TCCR0_COM01);

	/*Select Prescaler*/
	TCCR0 &= PRESCALER_MASK;
	TCCR0 |= DIVISION_BY_8;
}

void TIMER1_voidInit(void)
{
	/*Select Wave Generation Mode*/
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1B,TCCR1B_WGM12);
	SET_BIT(TCCR1B,TCCR1B_WGM13);

	/*Select Compare Match Output Mode*/
	CLR_BIT(TCCR1A,TCCR1A_COM1A0);
	SET_BIT(TCCR1A,TCCR1A_COM1A1);

	/*Select Prescaler*/
	CLR_BIT(TCCR1B,TCCR1B_CS10);
	SET_BIT(TCCR1B,TCCR1B_CS11);
	CLR_BIT(TCCR1B,TCCR1B_CS12);

	/*Set the top value*/
	ICR1 = 20000;
}

void TIMER0_voidSetCompValue(uint8 Copy_u8Value)
{
	/*Set the Compare Match Value*/
	OCR0 = Copy_u8Value;
}

void TIMER1_voidSetCompValue(uint16 Copy_u16Value)
{
	/*Set the Compare Match Value*/
	OCR1A = Copy_u16Value;

}

uint8 TIMERS_u8SetCallBack(TIMERS_Int_Src_t Copy_u8TimerIntSource, void (* Copy_pvCallBackFunc)(void))
{
	/*Define Variables*/
	uint8 Local_u8ErrorState = OK;

	/*Validate the pointer of function*/
	if(Copy_pvCallBackFunc != NULL)
	{
		TIMERS_pvCallBackFuncArr[Copy_u8TimerIntSource] = Copy_pvCallBackFunc;
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
	if(TIMERS_pvCallBackFuncArr[TIMER0_OVF] != NULL)
	{
		/*Calling the ISR function*/
		TIMERS_pvCallBackFuncArr[TIMER0_OVF]();
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
	if(TIMERS_pvCallBackFuncArr[TIMER0_COMP] != NULL)
	{
		/*Calling the ISR function*/
		TIMERS_pvCallBackFuncArr[TIMER0_COMP]();
	}
	else
	{
		/*Do nothing*/
	}
}
