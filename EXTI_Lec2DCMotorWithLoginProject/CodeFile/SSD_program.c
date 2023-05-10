/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: SSD_program.c			**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DEFINES.h"

#include "DIO_interface.h"

#include "SSD_config.h"
#include "SSD_private.h"
#include "SSD_interface.h"

//	uint8 Type;
//	uint8 Port;
//	uint8 LedPin;
//	uint8 EnablePort;
//	uint8 EnablePin;

uint8 SSD_u8SetNumber(const SSD_t *Copy_pssdtSSDInformation, uint8 Copy_u8Number)
{
	uint8 Local_u8ErrorState = OK;

	/*Validate the pointer address*/
	if(Copy_pssdtSSDInformation != NULL)
	{

		/*Set the number to the SSD according to the type of it*/
		if(Copy_pssdtSSDInformation -> Type == SSD_u8CATHODE)
		{
			/*Set enable pin to LOW*/
			DIO_u8SetPinValue(Copy_pssdtSSDInformation -> EnablePort, Copy_pssdtSSDInformation -> EnablePin, DIO_u8PIN_LOW);

			/*Set the first of the pins*/
			if(Copy_pssdtSSDInformation -> LedPin == 0)
			{
				DIO_u8SetPortValue(Copy_pssdtSSDInformation -> Port, SSD_u8NumbersArray[Copy_u8Number]);
			}
			else if(Copy_pssdtSSDInformation -> LedPin == 1)
			{
				DIO_u8SetPortValue(Copy_pssdtSSDInformation -> Port, (SSD_u8NumbersArray[Copy_u8Number] << 1));
			}
			else
			{
				Local_u8ErrorState = NOK;
			}
		}
		else if(Copy_pssdtSSDInformation -> Type == SSD_u8ANODE)
		{
			/*Set enable pin to HIGH*/
			DIO_u8SetPinValue(Copy_pssdtSSDInformation -> EnablePort, Copy_pssdtSSDInformation -> EnablePin, DIO_u8PIN_HIGH);

			/*Set the first of the pins*/
			if(Copy_pssdtSSDInformation -> LedPin == 0)
			{
				DIO_u8SetPortValue(Copy_pssdtSSDInformation -> Port, ~SSD_u8NumbersArray[Copy_u8Number]);
			}
			else if(Copy_pssdtSSDInformation -> LedPin == 1)
			{
				DIO_u8SetPortValue(Copy_pssdtSSDInformation -> Port, ~(SSD_u8NumbersArray[Copy_u8Number] << 1));
			}
			else
			{
				Local_u8ErrorState = NOK;
			}
		}
		else
		{
			Local_u8ErrorState = NOK;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}


uint8 SSD_u8Disable(const SSD_t *Copy_pssdtSSDInformation)
{
	uint8 Local_u8ErrorState = OK;

	/*Validate the pointer address*/
	if(Copy_pssdtSSDInformation != NULL)
	{
		if(Copy_pssdtSSDInformation -> Type == SSD_u8CATHODE)
		{
			DIO_u8SetPinValue(Copy_pssdtSSDInformation -> EnablePort, Copy_pssdtSSDInformation -> EnablePin, DIO_u8PIN_HIGH);
		}
		else if(Copy_pssdtSSDInformation -> Type == SSD_u8ANODE)
		{
			DIO_u8SetPinValue(Copy_pssdtSSDInformation -> EnablePort, Copy_pssdtSSDInformation -> EnablePin, DIO_u8PIN_LOW);
		}
		else
		{
			Local_u8ErrorState = NOK;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}
