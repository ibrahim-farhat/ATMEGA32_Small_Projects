/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: EXTI_program.c		**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file EXTI_program.c
 * @author Ibrahim Tarek
 * @brief This file implements the EXTI module functions.
 * @version 1.00
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DEFINES.h"

#include "EXTI_interface.h"
#include "EXTI_config.h"
#include "EXTI_private.h"
#include "EXTI_register.h"

/**
 * @brief Array of pointers to functions to hold ISR call backs.
 */
static void (* EXTI_pfIsrFunction[3]) (void) = {NULL};

/**
 * @brief Function to initialize external interrupt channels with prebuild configuration.
 */
void EXTI_voidInit(void)
{
	/*INT0 Channel initialization*/
#if	INT0_INITIAL_STATE == ENABLED
	SET_BIT(GICR,GICR_INT0);

#if	INT0_SENSE_CTRL == EXTI_u8LOW_LEVEL
	CLR_BIT(MCUCR,MCUCR_ISC00);
	CLR_BIT(MCUCR,MCUCR_ISC01);

#elif INT0_SENSE_CTRL == EXTI_u8ON_CHANGE
	SET_BIT(MCUCR,MCUCR_ISC00);
	CLR_BIT(MCUCR,MCUCR_ISC01);

#elif INT0_SENSE_CTRL == EXTI_u8FALLING_EDGE
	CLR_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);

#elif INT0_SENSE_CTRL == EXTI_u8RISING_EDGE
	SET_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);

#else
#error	wrong configuration for INT0 sense control

#endif

#elif INT0_INITIAL_STATE == DISABLED
	CLR_BIT(GICR,GICR_INT0);

#else
#error	wrong configuration for INT0 initial state
#endif

	/*INT1 Channel initialization*/
#if	INT1_INITIAL_STATE == ENABLED
	SET_BIT(GICR,GICR_INT1);

#if	INT1_SENSE_CTRL == EXTI_u8LOW_LEVEL
	CLR_BIT(MCUCR,MCUCR_ISC10);
	CLR_BIT(MCUCR,MCUCR_ISC11);

#elif INT1_SENSE_CTRL == EXTI_u8ON_CHANGE
	SET_BIT(MCUCR,MCUCR_ISC10);
	CLR_BIT(MCUCR,MCUCR_ISC11);

#elif INT1_SENSE_CTRL == EXTI_u8FALLING_EDGE
	CLR_BIT(MCUCR,MCUCR_ISC10);
	SET_BIT(MCUCR,MCUCR_ISC11);

#elif INT1_SENSE_CTRL == EXTI_u8RISING_EDGE
	SET_BIT(MCUCR,MCUCR_ISC10);
	SET_BIT(MCUCR,MCUCR_ISC11);

#else
#error	wrong configuration for INT1 sense control

#endif

#elif INT1_INITIAL_STATE == DISABLED
	CLR_BIT(GICR,GICR_INT1);

#else
#error	wrong configuration for INT1 initial state

#endif

	/*INT2 Channel initialization*/
#if	INT2_INITIAL_STATE == ENABLED
	SET_BIT(GICR,GICR_INT2);

#if INT2_SENSE_CTRL == EXTI_u8FALLING_EDGE
	CLR_BIT(MCUCSR,MCUCSR_ISC2);

#elif INT2_SENSE_CTRL == EXTI_u8RISING_EDGE
	SET_BIT(MCUCSR,MCUCSR_ISC2);

#else
#error	wrong configuration for INT2 sense control

#endif

#elif INT2_INITIAL_STATE == DISABLED
	CLR_BIT(GICR,GICR_INT2);

#else
#error	wrong configuration for INT2 initial state
#endif
}

/**
 * @brief Function to change the sense control of an interrupt channel during runtime.
 * @param Copy_u8IntNum	Interrupt Channel Number.
 * @param Copy_u8Sense	Interrupt Sense Control.
 * @return	Error State.
 */
uint8 EXTI_u8SetSenseCtrl(uint8 Copy_u8IntNum, uint8 Copy_u8Sense)
{
	/*Define Variables*/
	uint8 Local_u8ErrorState = OK;

	/*Switch the interrupt channel*/
	switch(Copy_u8IntNum)
	{
	case EXTI_u8INT0:
		/*Switch the sense control for INT0*/
		switch(Copy_u8Sense)
		{
		case EXTI_u8LOW_LEVEL	:	CLR_BIT(MCUCR,MCUCR_ISC00);	CLR_BIT(MCUCR,MCUCR_ISC01);	break;
		case EXTI_u8ON_CHANGE	: 	SET_BIT(MCUCR,MCUCR_ISC00);	CLR_BIT(MCUCR,MCUCR_ISC01);	break;
		case EXTI_u8FALLING_EDGE: 	CLR_BIT(MCUCR,MCUCR_ISC00);	SET_BIT(MCUCR,MCUCR_ISC01);	break;
		case EXTI_u8RISING_EDGE	: 	SET_BIT(MCUCR,MCUCR_ISC00);	SET_BIT(MCUCR,MCUCR_ISC01);	break;
		default: Local_u8ErrorState = NOK;
		}
		break;

	case EXTI_u8INT1:
		/*Switch the sense control for INT1*/
		switch(Copy_u8Sense)
		{
		case EXTI_u8LOW_LEVEL	:	CLR_BIT(MCUCR,MCUCR_ISC10);	CLR_BIT(MCUCR,MCUCR_ISC11);	break;
		case EXTI_u8ON_CHANGE	: 	SET_BIT(MCUCR,MCUCR_ISC10);	CLR_BIT(MCUCR,MCUCR_ISC11);	break;
		case EXTI_u8FALLING_EDGE: 	CLR_BIT(MCUCR,MCUCR_ISC10);	SET_BIT(MCUCR,MCUCR_ISC11);	break;
		case EXTI_u8RISING_EDGE	: 	SET_BIT(MCUCR,MCUCR_ISC10);	SET_BIT(MCUCR,MCUCR_ISC11);	break;
		default: Local_u8ErrorState = NOK;
		}
		break;

	case EXTI_u8INT2:
		/*Switch the sense control for INT2*/
		switch(Copy_u8Sense)
		{
		case EXTI_u8FALLING_EDGE: 	CLR_BIT(MCUCSR,MCUCSR_ISC2);	SET_BIT(MCUCSR,MCUCSR_ISC2);	break;
		case EXTI_u8RISING_EDGE	: 	SET_BIT(MCUCSR,MCUCSR_ISC2);	SET_BIT(MCUCSR,MCUCSR_ISC2);	break;
		default: Local_u8ErrorState = NOK;
		}
		break;

	default: Local_u8ErrorState = NOK;	break;
	}

	/*Return Error State*/
	return Local_u8ErrorState;
}

/**
 * @brief Function to enable an interrupt channel.
 * @param Copy_u8IntNum	Interrupt Channel Number.
 * @return	Error State.
 */
uint8 EXTI_u8IntEnable(uint8 Copy_u8IntNum)
{
	/*Define Variables*/
	uint8 Local_u8ErrorState = OK;

	/*Switch the interrupt channel*/
	switch(Copy_u8IntNum)
	{
	case EXTI_u8INT0: SET_BIT(GICR,GICR_INT0);	break;
	case EXTI_u8INT1: SET_BIT(GICR,GICR_INT1);	break;
	case EXTI_u8INT2: SET_BIT(GICR,GICR_INT2);	break;
	default: Local_u8ErrorState = NOK;	break;
	}

	/*Return Error State*/
	return Local_u8ErrorState;
}

/**
 * @brief Function to disable an interrupt channel.
 * @param Copy_u8IntNum	Interrupt Channel Number.
 * @return	Error State.
 */
uint8 EXTI_u8IntDisable(uint8 Copy_u8IntNum)
{
	/*Define Variables*/
	uint8 Local_u8ErrorState = OK;

	/*Switch the interrupt channel*/
	switch(Copy_u8IntNum)
	{
	case EXTI_u8INT0: CLR_BIT(GICR,GICR_INT0);	break;
	case EXTI_u8INT1: CLR_BIT(GICR,GICR_INT1);	break;
	case EXTI_u8INT2: CLR_BIT(GICR,GICR_INT2);	break;
	default: Local_u8ErrorState = NOK;	break;
	}

	/*Return Error State*/
	return Local_u8ErrorState;
}

/**
 * @brief Function to call back the ISR functions for any interrupt.
 * @param Copy_u8IntNum	Interrupt Channel Number.
 * @param Copy_pfFunctionPtr Pointer to the ISR function that is needed to set.
 * @return Error State.
 */
uint8 EXTI_u8SetCallBack(uint8 Copy_u8IntNum, void (* Copy_pfFunctionPtr)(void))
{
	/*Define Variables*/
	uint8 Local_u8ErrorState = OK;

	/*Check the pointer to function*/
	if(Copy_pfFunctionPtr != NULL)
	{
		/*Switch the interrupt channel*/
		switch(Copy_u8IntNum)
		{
		case EXTI_u8INT0: EXTI_pfIsrFunction[0] = Copy_pfFunctionPtr;	break;
		case EXTI_u8INT1: EXTI_pfIsrFunction[1] = Copy_pfFunctionPtr;	break;
		case EXTI_u8INT2: EXTI_pfIsrFunction[2] = Copy_pfFunctionPtr;	break;
		default: Local_u8ErrorState = NOK;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	/*Return Error State*/
	return Local_u8ErrorState;
}

/**
 * @brief Int0 ISR.
 */
void __vector_1 (void) __attribute((signal));
void __vector_1 (void)
{
	if(EXTI_pfIsrFunction[0] != NULL)
	{
		EXTI_pfIsrFunction[0]();
	}
}

/**
 * @brief Int1 ISR.
 */
void __vector_2 (void) __attribute((signal));
void __vector_2 (void)
{
	if(EXTI_pfIsrFunction[1] != NULL)
	{
		EXTI_pfIsrFunction[1]();
	}
}

/**
 * @brief Int2 ISR.
 */
void __vector_3 (void) __attribute((signal));
void __vector_3 (void)
{
	if(EXTI_pfIsrFunction[2] != NULL)
	{
		EXTI_pfIsrFunction[2]();
	}
}
