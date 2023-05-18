/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: MOTOR_program.c		**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DEFINES.h"

#include "DIO_interface.h"

#include "MOTOR_config.h"
#include "MOTOR_private.h"
#include "MOTOR_interface.h"


uint8 MOTOR_u8RotateCW(const MOTOR_t *Copy_pmotortMotorInfo)
{
	/*Define Variables*/
	uint8 Local_u8ErrorState = OK;

	/*Validate the pointer address*/
	if(Copy_pmotortMotorInfo != NULL)
	{
		/*Set pin 1 as low, pin 2 as high*/
		DIO_u8SetPinValue(Copy_pmotortMotorInfo -> Port, Copy_pmotortMotorInfo -> Pin1, DIO_u8PIN_LOW);
		DIO_u8SetPinValue(Copy_pmotortMotorInfo -> Port, Copy_pmotortMotorInfo -> Pin2, DIO_u8PIN_HIGH);
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	/*Return the error state*/
	return Local_u8ErrorState;
}

uint8 MOTOR_u8RotateCCW(const MOTOR_t *Copy_pmotortMotorInfo)
{
	/*Define Variables*/
	uint8 Local_u8ErrorState = OK;

	/*Validate the pointer address*/
	if(Copy_pmotortMotorInfo != NULL)
	{
		/*Set pin 2 as low, pin 1 as high*/
		DIO_u8SetPinValue(Copy_pmotortMotorInfo -> Port, Copy_pmotortMotorInfo -> Pin2, DIO_u8PIN_LOW);
		DIO_u8SetPinValue(Copy_pmotortMotorInfo -> Port, Copy_pmotortMotorInfo -> Pin1, DIO_u8PIN_HIGH);
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	/*Return the error state*/
	return Local_u8ErrorState;
}

uint8 MOTOR_u8Stop(const MOTOR_t *Copy_pmotortMotorInfo)
{
	/*Define Variables*/
	uint8 Local_u8ErrorState = OK;

	/*Validate the pointer address*/
	if(Copy_pmotortMotorInfo != NULL)
	{
		/*Set pin 1 and 2 as low*/
		DIO_u8SetPinValue(Copy_pmotortMotorInfo -> Port, Copy_pmotortMotorInfo -> Pin2, DIO_u8PIN_LOW);
		DIO_u8SetPinValue(Copy_pmotortMotorInfo -> Port, Copy_pmotortMotorInfo -> Pin1, DIO_u8PIN_LOW);
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	/*Return the error state*/
	return Local_u8ErrorState;
}
