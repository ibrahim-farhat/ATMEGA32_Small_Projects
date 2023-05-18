/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: ADC_program.c			**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file ADC_program.c
 * @author Ibrahim Tarek
 * @brief This file implements the ADC module functions.
 * @version 1.00
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DEFINES.h"

#include "ADC_interface.h"
#include "ADC_config.h"
#include "ADC_private.h"
#include "ADC_register.h"

static void (* ADC_pvNotificationFunc)(void) = NULL;

static uint16 *ADC_pu16ConversionResult = NULL;

static uint8 ADC_u8BusyFlag = IDLE;

/**
 * @brief Function to initialize ADC with prebuild configuration.
 */
void ADC_voidInit(void)
{
	/*Reference Selection*/
#if	ADC_u8REF_VOLT == AREF_REF
	CLR_BIT(ADMUX,ADMUX_REFS0);
	CLR_BIT(ADMUX,ADMUX_REFS1);

#elif ADC_u8REF_VOLT == AVCC_REF
	SET_BIT(ADMUX,ADMUX_REFS0);
	CLR_BIT(ADMUX,ADMUX_REFS1);

#elif ADC_u8REF_VOLT == INTERNAL_2560mV_REF
	SET_BIT(ADMUX,ADMUX_REFS0);
	SET_BIT(ADMUX,ADMUX_REFS1);

#else
#error Wrong ADC_u8REF_VOLT configuration option

#endif

	/*Left Adjust Result Selection*/
#if	ADC_u8RESOLUTION == EIGHT_BITS
	SET_BIT(ADMUX,ADMUX_ADLAR);

#elif ADC_u8RESOLUTION == TEN_BITS
	CLR_BIT(ADMUX,ADMUX_ADLAR);

#else
#error Wrong ADC_u8RESOLUTION configuration option

#endif

	/*ADC Interrupt Enable/Disable*/
#if ADC_u8INT_ENABLE == ENABLED
	SET_BIT(ADCSRA,ADCSRA_ADIE);

#elif ADC_u8INT_ENABLE == DISABLED
	CLR_BIT(ADCSRA,ADCSRA_ADIE);

#else
#error Wrong ADC_u8INT_ENABLE configuration option

#endif

	/*Prescaler Selection*/
	ADCSRA = ADCSRA & PRESCALER_MASK;
	ADCSRA = ADCSRA | ADC_u8PRESCALER_VALUE;

	/*Enable the ADC*/
	SET_BIT(ADCSRA,ADCSRA_ADEN);
}


/**
 * @brief Function to get the reading of an ADC channel.
 * @param Copy_u8Channel The number of channel you want to read.
 * @param Copy_pu16Result This pointer return the reading of the channel selected.
 * @return Error State of the function.
 */
uint8 ADC_u8StartConversionSynch(uint8 Copy_u8Channel, uint16 *Copy_pu16Result)
{
	/*Define variables*/
	uint8 Local_u8ErrorState = OK;
	uint8 Local_u32TimeoutCounter = 0u;

	/*Validate Copy_pu16Rsult*/
	if(Copy_pu16Result != NULL)
	{
		if(ADC_u8BusyFlag == IDLE)
		{
			/*Inform others that adc is busy*/
			ADC_u8BusyFlag = BUSY;

			/*Set the required channel*/
			ADMUX = ADMUX & CHANNEL_MASK;
			ADMUX = ADMUX | Copy_u8Channel;

			/*Start Conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);

			/*Polling until the interrupt flag rise*/
			while((GET_BIT(ADCSRA,ADCSRA_ADIF) == 0) && (Local_u32TimeoutCounter < ADC_u32TIMEOUT))
			{
				Local_u32TimeoutCounter++;
			}

			/*Check why the loop has been broken*/
			if(Local_u32TimeoutCounter == ADC_u32TIMEOUT)
			{
				/*Loop is broken because the conversion exceed timeout counter*/
				Local_u8ErrorState = TIMEOUT_ERR;
			}
			else
			{
				/*Loop is broken because the conversion has been done*/

				/*Clear the conversion complete flag flag*/
				SET_BIT(ADCSRA,ADCSRA_ADIF);

				/*Return the data*/
#if ADC_u8RESOLUTION == EIGHT_BITS
				*Copy_pu16Result = ADCH;

#elif ADC_u8RESOLUTION == TEN_BITS
				*Copy_pu16Result = ADC;
#endif
			}

			/*Inform others that ADC is idle now*/
			ADC_u8BusyFlag = IDLE;
		}
		else
		{
			/*ADC is busy now*/
			Local_u8ErrorState = BUSY_STATE_ERR;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	/*Return the error state*/
	return Local_u8ErrorState;
}


/**
 * @brief Function to get the reading of an ADC channel.
 * @note You should enable GIE before using this function.
 * @param Copy_u8Channel The number of channel you want to read.
 * @param Copy_pu16Result This pointer return the reading of the channel selected.
 * @param Copy_pvNotificationFunc This pointer set call back the notification function from the application layer.
 * @return Error State of the function.
 */
uint8 ADC_u8StartConversionAsynch(uint8 Copy_u8Channel, uint16 *Copy_pu16Result, void (* Copy_pvNotificationFunc)(void))
{
	/*Define variables*/
	uint8 Local_u8ErrorState = OK;

	/*Validate Copy_pu16Rsult*/
	if((Copy_pu16Result != NULL) && (Copy_pvNotificationFunc != NULL))
	{
		/*Check if ADC is busy or idle*/
		if(ADC_u8BusyFlag == IDLE)
		{
			/*Inform others that ADC is busy now*/
			ADC_u8BusyFlag = BUSY;

			/*Initialize the result pointer globally*/
			ADC_pu16ConversionResult = Copy_pu16Result;

			/*Initialize the notification function globally*/
			ADC_pvNotificationFunc = Copy_pvNotificationFunc;

			/*Set the required channel*/
			ADMUX = ADMUX & CHANNEL_MASK;
			ADMUX = ADMUX | Copy_u8Channel;

			/*Start Conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);

			/*Enable ADC Conversion Complete Interrupt*/
			SET_BIT(ADCSRA,ADCSRA_ADIE);
		}
		else
		{
			/*ADC is busy now*/
			Local_u8ErrorState = BUSY_STATE_ERR;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	/*Return the error state*/
	return Local_u8ErrorState;
}


/**
 * @brief ADC Conversion Complete ISR.
 */
void __vector_16 (void) __attribute((signal));
void __vector_16 (void)
{
	if(ADC_pu16ConversionResult != NULL)
	{
		/*Return the data*/
#if ADC_u8RESOLUTION == EIGHT_BITS
		*ADC_pu16ConversionResult = ADCH;

#elif ADC_u8RESOLUTION == TEN_BITS
		*ADC_pu16ConversionResult = ADC;
#endif

		/*Disable ADC Conversion Complete Interrupt*/
		CLR_BIT(ADCSRA,ADCSRA_ADIE);

		/*Inform others that ADC is idle now*/
		ADC_u8BusyFlag = IDLE;

		/*Invoke the application notification function*/
		if(ADC_pvNotificationFunc != NULL)
		{
			ADC_pvNotificationFunc();
		}
		else
		{
			/*Notification pointer is assigned to NULL*/
		}
	}
	else
	{
		/*Result pointer is assigned to NULL*/
	}
}
