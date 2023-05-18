/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: SWITCH_program.c		**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DEFINES.h"

#include "DIO_interface.h"

#include "SWITCH_config.h"
#include "SWITCH_private.h"
#include "SWITCH_interface.h"

uint8 SWITCH_u8GetState(const SWITCH_t *Copy_pswitchtSwitchInformation, uint8 *Copy_pu8State)
{
	uint8 Local_u8ErrorState = OK;
	uint8 Local_u8SwitchState;

	/*Validate the pointer address*/
	if((Copy_pswitchtSwitchInformation != NULL) && (Copy_pu8State != NULL))
	{
		DIO_u8GetPinValue(Copy_pswitchtSwitchInformation -> Port, Copy_pswitchtSwitchInformation -> Pin, &Local_u8SwitchState);


		if(Copy_pswitchtSwitchInformation -> Type == SWITCH_u8PULL_UP)
		{
			switch(Local_u8SwitchState)
			{
				case DIO_u8PIN_HIGH: *Copy_pu8State = SWITCH_u8RELEASED;	break;
				case DIO_u8PIN_LOW: *Copy_pu8State = SWITCH_u8PRESSED;		break;
				default: Local_u8ErrorState = NOK;	break;
			}
		}
		else if(Copy_pswitchtSwitchInformation -> Type == SWITCH_u8PULL_DOWN)
		{
			switch(Local_u8SwitchState)
			{
				case DIO_u8PIN_HIGH: *Copy_pu8State = SWITCH_u8PRESSED;		break;
				case DIO_u8PIN_LOW: *Copy_pu8State = SWITCH_u8RELEASED;		break;
				default: Local_u8ErrorState = NOK;	break;
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
