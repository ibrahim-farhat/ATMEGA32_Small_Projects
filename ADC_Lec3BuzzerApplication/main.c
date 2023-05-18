#include "STD_TYPES.h"

#include "DIO_interface.h"
#include "PORT_interface.h"

#include "KEYPAD_interface.h"

#include <util/delay.h>

/**
 * @brief A function to send a tone to the buzzer.
 * @param Copy_u8PressedKey	the pressed key on the keypad.
 */
static void Local_voidSendTone(uint8 Copy_u8PressedKey);

/*It is the main*/
void main(void)
{
	/*Peripherals Initialization*/
	PORT_voidInit();


	/*Define variables*/
	uint8 Local_u8PressedKey = KEYPAD_u8NO_PRESSED_KEY;

	/*Super Loop*/
	while(1)
	{
		Local_u8PressedKey = KEYPAD_u8GetPressedKey();

		if(Local_u8PressedKey != KEYPAD_u8NO_PRESSED_KEY)
		{
			Local_voidSendTone(Local_u8PressedKey);
		}
	}
}

static void Local_voidSendTone(uint8 Copy_u8PressedKey)
{
	/*Define Variables*/
	uint8 Local_u8Iterator = 0;

	/*Sending tone*/
	for(Local_u8Iterator = 0; Local_u8Iterator < 20; Local_u8Iterator++)
	{
		DIO_u8SetPinValue(DIO_u8PORTB, DIO_u8PIN0, DIO_u8PIN_HIGH);
		_delay_ms(Copy_u8PressedKey);
		DIO_u8SetPinValue(DIO_u8PORTB, DIO_u8PIN0, DIO_u8PIN_LOW);
		_delay_ms(Copy_u8PressedKey);
	}

	for(Local_u8Iterator = 0; Local_u8Iterator < 20; Local_u8Iterator++)
	{
		DIO_u8SetPinValue(DIO_u8PORTB, DIO_u8PIN0, DIO_u8PIN_HIGH);
		_delay_ms(2 * Copy_u8PressedKey);
		DIO_u8SetPinValue(DIO_u8PORTB, DIO_u8PIN0, DIO_u8PIN_LOW);
		_delay_ms(2 * Copy_u8PressedKey);
	}

	for(Local_u8Iterator = 0; Local_u8Iterator < 20; Local_u8Iterator++)
	{
		DIO_u8SetPinValue(DIO_u8PORTB, DIO_u8PIN0, DIO_u8PIN_HIGH);
		_delay_ms(Copy_u8PressedKey / 2);
		DIO_u8SetPinValue(DIO_u8PORTB, DIO_u8PIN0, DIO_u8PIN_LOW);
		_delay_ms(Copy_u8PressedKey / 2);
	}
}

