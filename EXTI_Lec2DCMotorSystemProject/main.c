#include "STD_TYPES.h"
#include "SpecialCharacters.h"

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "EXTI_interface.h"
#include "GIE_interface.h"

#include "CLCD_interface.h"
#include "SSD_interface.h"
#include "KEYPAD_interface.h"
#include "MOTOR_interface.h"

#include <util/delay.h>

void Main_voidInt0ISR(void);

MOTOR_t Local_motortSystemMotor;

/*It is the main*/
void main(void)
{
	/*
	 * LCD connections are defined on CLCD_config.h.
	 * KEYPAD connections are defined on KEYPAD_config.h.
	 * SEVEN SEGMENT connections are defined on line number 49 on main file.
	 * MOTOR connections are defined on line 57 on main file.
	 * Connect DIO_u8PIN3 with a button to the ground for INTERRUPT 1.
	 * */

	/*Peripherals Initialization*/
	PORT_voidInit();
	GIE_voidEnable();
	EXTI_voidInit();
	CLCD_voidInit();

	EXTI_u8SetCallBack(EXTI_u8INT1, &Main_voidInt0ISR);

	/*Define variables*/
	uint8 Local_u8Iterator = 0;
	uint8 Local_u8PressedKey = KEYPAD_u8NO_PRESSED_KEY;
	uint8 Local_u8IDIterator = 0;
	uint8 Local_u8SevenSegmentIterator = 3;
	uint8 Local_u8LoginFlag = 0;

	uint16 Local_u16ID = 0;
	uint16 Local_u16Password = 0;
	uint16 Local_u16ReversedID = 0;


	SSD_t Local_ssdtLoginCounter;
	Local_ssdtLoginCounter.Port = DIO_u8PORTC;
	Local_ssdtLoginCounter.EnablePort = DIO_u8PORTD;
	Local_ssdtLoginCounter.EnablePin = DIO_u8PIN0;
	Local_ssdtLoginCounter.LedPin = DIO_u8PIN0;
	Local_ssdtLoginCounter.Type = SSD_u8CATHODE;


	Local_motortSystemMotor.Port = DIO_u8PORTD;
	Local_motortSystemMotor.Pin1 = DIO_u8PIN4;
	Local_motortSystemMotor.Pin2 = DIO_u8PIN5;
	MOTOR_u8Stop(&Local_motortSystemMotor);

	/*Hamoksha welcome the user*/
	for(Local_u8Iterator = 0; Local_u8Iterator < 16; Local_u8Iterator++)
	{
		CLCD_voidClearDisplay();
		CLCD_voidSendSpecialCharacter(Local_u8Hamoksha1, 0, Local_u8Iterator, 0);
		CLCD_voidSendSpecialCharacter(Local_u8Hamoksha2, 1, Local_u8Iterator, 1);
		_delay_ms(100);
	}
	CLCD_u8GoToXY(1, 0);
	CLCD_u8SendString("Welcome Mido!");
	_delay_ms(1000);

	/*Super Loop*/
	while(1)
	{

		while(Local_u8SevenSegmentIterator != 0)
		{
			for(Local_u8Iterator = 0; Local_u8Iterator < 14; Local_u8Iterator++)
			{
				CLCD_voidSendSpecialCharacter(Local_u8EraseCharacter, 2, Local_u8Iterator, 0);
				CLCD_voidSendSpecialCharacter(Local_u8EraseCharacter, 2, Local_u8Iterator, 1);
			}

			CLCD_u8GoToXY(0, 0);
			CLCD_u8SendString("ID: ");
			CLCD_u8GoToXY(0, 1);
			CLCD_u8SendString("Password: ");

			/*Print Login times remained to seven segment*/
			SSD_u8SetNumber(&Local_ssdtLoginCounter, Local_u8SevenSegmentIterator);

			/*Scan ID from the user*/
			Local_u8IDIterator = 0;
			CLCD_u8GoToXY(4, 0);

			while(Local_u8IDIterator != 4)
			{
				while(Local_u8PressedKey == KEYPAD_u8NO_PRESSED_KEY)
				{
					Local_u8PressedKey = KEYPAD_u8GetPressedKey();
				}

				switch(Local_u8PressedKey)
				{
				default:
					CLCD_voidSendDecimalNumber(Local_u8PressedKey);
					Local_u16ID = Local_u8PressedKey + Local_u16ID * 10;
					Local_u8PressedKey = KEYPAD_u8NO_PRESSED_KEY;
					Local_u8IDIterator++;
					break;
				case 11:
					Local_u8PressedKey = KEYPAD_u8NO_PRESSED_KEY;
					break;
				}
			}

			/*Scan Password from the user*/
			Local_u8IDIterator = 0;
			CLCD_u8GoToXY(10, 1);

			while(Local_u8IDIterator != 4)
			{
				while(Local_u8PressedKey == KEYPAD_u8NO_PRESSED_KEY)
				{
					Local_u8PressedKey = KEYPAD_u8GetPressedKey();
				}
				switch(Local_u8PressedKey)
				{
				default:
					CLCD_voidSendDecimalNumber(Local_u8PressedKey);
					Local_u16Password = Local_u8PressedKey + Local_u16Password * 10;
					CLCD_u8GoToXY(10 + Local_u8IDIterator, 1);
					_delay_ms(250);
					CLCD_voidSendData('*');
					Local_u8PressedKey = KEYPAD_u8NO_PRESSED_KEY;
					Local_u8IDIterator++;
					break;
				case 11:
					Local_u8PressedKey = KEYPAD_u8NO_PRESSED_KEY;
					break;
				}
			}

			/*Reverse the ID*/
			Local_u8IDIterator = 0;
			while(Local_u8IDIterator != 4)
			{
				Local_u8IDIterator++;
				Local_u16ReversedID = (Local_u16ID % 10) + Local_u16ReversedID * 10;
				Local_u16ID = Local_u16ID / 10;
			}

			CLCD_u8GoToXY(0, 0);

			/*Erase the CLCD*/
			for(Local_u8Iterator = 0; Local_u8Iterator < 14; Local_u8Iterator++)
			{
				CLCD_voidSendSpecialCharacter(Local_u8EraseCharacter, 2, Local_u8Iterator, 0);
			}
			for(Local_u8Iterator = 0; Local_u8Iterator < 14; Local_u8Iterator++)
			{
				CLCD_voidSendSpecialCharacter(Local_u8EraseCharacter, 2, Local_u8Iterator, 1);
			}

			/*Check ID and Password*/
			if(Local_u16Password == Local_u16ReversedID)
			{
				CLCD_u8GoToXY(4, 0);
				CLCD_u8SendString("Welcome");
				SSD_u8Disable(&Local_ssdtLoginCounter);
				Local_u8LoginFlag = 1;
				_delay_ms(1000);
				break;
			}
			else
			{
				Local_u16ID = 0;
				Local_u16Password = 0;
				Local_u16ReversedID = 0;
				Local_u8SevenSegmentIterator--;
				CLCD_u8GoToXY(1, 0);
				CLCD_u8SendString("Wrong Input!");
				if(Local_u8SevenSegmentIterator > 0)
				{
					CLCD_u8GoToXY(2, 1);
					CLCD_u8SendString("Try again!");
				}
				_delay_ms(500);
				continue;
			}
		}

		if(Local_u8SevenSegmentIterator == 0)
		{
			SSD_u8SetNumber(&Local_ssdtLoginCounter, Local_u8SevenSegmentIterator);
			CLCD_u8GoToXY(0, 1);
			CLCD_u8SendString("Call Emergency!");
		}

		if(Local_u8LoginFlag == 1)
		{
			while(1)
			{
				MOTOR_u8RotateCW(&Local_motortSystemMotor);
				_delay_ms(3000);
				MOTOR_u8Stop(&Local_motortSystemMotor);
				_delay_ms(250);
				MOTOR_u8RotateCCW(&Local_motortSystemMotor);
				_delay_ms(3000);
				MOTOR_u8Stop(&Local_motortSystemMotor);
				_delay_ms(250);
			}
		}

	}
}

void Main_voidInt0ISR(void)
{
	MOTOR_u8Stop(&Local_motortSystemMotor);
	CLCD_voidClearDisplay();
	CLCD_u8GoToXY(3, 0);
	CLCD_u8SendString("Force Stop!");
	_delay_ms(1000);
	CLCD_voidClearDisplay();
	while(1);
}
