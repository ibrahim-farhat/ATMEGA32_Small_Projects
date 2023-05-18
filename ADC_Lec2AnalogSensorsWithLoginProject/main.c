#include "STD_TYPES.h"
#include "SpecialCharacters.h"

#include "LIBRARY_interface.h"

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "ADC_interface.h"

#include "CLCD_interface.h"
#include "LM35_interface.h"
#include "LDR_interface.h"
#include "MOTOR_interface.h"
#include "SSD_interface.h"
#include "KEYPAD_interface.h"

#include <util/delay.h>


/*It is the main*/
void main(void)
{
	/*
	 * LCD connections are defined on CLCD_config.h.
	 * KEYPAD connections are defined on KEYPAD_config.h.
	 * SEVEN SEGMENT connections are defined on line 54 on main file.
	 * LEDs are connected with SEVEN SEGMENT on the port D, those connections are defined on line
	 * MOTOR connections are defined on line 57 on main file.
	 * Connect DIO_u8PIN3 with a button to the ground for INTERRUPT 1.
	 * */

	/*Peripherals Initialization*/
	PORT_voidInit();
	CLCD_voidInit();
	ADC_voidInit();

	/*Define variables*/
	uint8 Local_u8Temperature = 0;
	uint16 Local_u16LDRVoltage = 0;
	uint8 Local_u8PrintIterator = 0;
	uint8 Local_u8HamokshaIterator = 0;
	uint8 Local_u8LedsMap = 0;

	uint8 Local_u8Iterator = 0;
	uint8 Local_u8PressedKey = KEYPAD_u8NO_PRESSED_KEY;
	uint8 Local_u8IDIterator = 0;
	uint8 Local_u8SevenSegmentIterator = 3;
	uint8 Local_u8LoginFlag = 0;

	uint16 Local_u16ID = 0;
	uint16 Local_u16Password = 0;
	uint16 Local_u16ReversedID = 0;


	/*Define the seven segment*/
	SSD_t Local_ssdtLoginCounter;
	Local_ssdtLoginCounter.Port = DIO_u8PORTD;
	Local_ssdtLoginCounter.EnablePort = DIO_u8PORTA;
	Local_ssdtLoginCounter.EnablePin = DIO_u8PIN1;
	Local_ssdtLoginCounter.LedPin = DIO_u8PIN0;
	Local_ssdtLoginCounter.Type = SSD_u8CATHODE;


	/*Define the motor*/
	MOTOR_t Local_motortSystemMotor;
	Local_motortSystemMotor.Port = DIO_u8PORTA;
	Local_motortSystemMotor.Pin1 = DIO_u8PIN3;
	Local_motortSystemMotor.Pin2 = DIO_u8PIN4;
	MOTOR_u8Stop(&Local_motortSystemMotor);


	/*Hamoksha welcome the user*/
	for(Local_u8HamokshaIterator = 0; Local_u8HamokshaIterator < 16; Local_u8HamokshaIterator++)
	{
		CLCD_voidClearDisplay();
		CLCD_voidSendSpecialCharacter(Local_u8Hamoksha1, 0, Local_u8HamokshaIterator, 0);
		CLCD_voidSendSpecialCharacter(Local_u8Hamoksha2, 1, Local_u8HamokshaIterator, 1);
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
				for(Local_u8PrintIterator = 4; Local_u8PrintIterator < 11; Local_u8PrintIterator++)
				{
					CLCD_voidSendSpecialCharacter(Local_u8EraseCharacter, 2, Local_u8PrintIterator, 0);
					CLCD_voidSendSpecialCharacter(Local_u8EraseCharacter, 2, Local_u8PrintIterator, 1);
				}
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

		CLCD_u8GoToXY(0, 0);
		CLCD_u8SendString("Temp.: ");

		CLCD_u8GoToXY(0, 1);
		CLCD_u8SendString("LEDs: 0 - ");

		CLCD_u8GoToXY(11, 0);
		CLCD_voidSendData('(');
		CLCD_u8GoToXY(13, 0);
		CLCD_voidSendData(')');
		DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN2, DIO_u8PIN_LOW);

		while(1)
		{
			for(Local_u8PrintIterator = 7; Local_u8PrintIterator < 10; Local_u8PrintIterator++)
			{
				CLCD_voidSendSpecialCharacter(Local_u8EraseCharacter, 2, Local_u8PrintIterator, 0);
			}
			CLCD_voidSendSpecialCharacter(Local_u8EraseCharacter, 2, 10, 1);

			/*Get temp and voltage*/
			LM35_u8GetTemp(LM35_u8ADC_CH0, &Local_u8Temperature);
			LDR_u8GetAnalogVolt(LDR_u8ADC_CH7, &Local_u16LDRVoltage);
			CLCD_u8GoToXY(7, 0);
			CLCD_voidSendDecimalNumber(Local_u8Temperature);

			if(Local_u8Temperature > 40)
			{
				MOTOR_u8RotateCW(&Local_motortSystemMotor);
				CLCD_u8GoToXY(12, 0);
				CLCD_voidSendData('M');
			}
			else if(Local_u8Temperature < 35)
			{
				MOTOR_u8Stop(&Local_motortSystemMotor);
				CLCD_u8GoToXY(12, 0);
				CLCD_voidSendSpecialCharacter(Local_u8EraseCharacter, 2, 12, 0);
			}

			/*Set the pins*/
			Local_u8LedsMap = LIBRARY_s32Mapping(0, 4980, 0, 8, Local_u16LDRVoltage);
			CLCD_u8GoToXY(10, 1);
			CLCD_voidSendDecimalNumber(Local_u8LedsMap);
			DIO_u8SetPortValue(DIO_u8PORTD, 0);
			switch(Local_u8LedsMap)
			{
			case 0:	DIO_u8SetPortValue(DIO_u8PORTD, 0x00);	break;
			case 1:	DIO_u8SetPortValue(DIO_u8PORTD, 0x01);	break;
			case 2:	DIO_u8SetPortValue(DIO_u8PORTD, 0x03);	break;
			case 3:	DIO_u8SetPortValue(DIO_u8PORTD, 0x07);	break;
			case 4:	DIO_u8SetPortValue(DIO_u8PORTD, 0x0f);	break;
			case 5:	DIO_u8SetPortValue(DIO_u8PORTD, 0x1f);	break;
			case 6:	DIO_u8SetPortValue(DIO_u8PORTD, 0x3f);	break;
			case 7:	DIO_u8SetPortValue(DIO_u8PORTD, 0x7f);	break;
			case 8:	DIO_u8SetPortValue(DIO_u8PORTD, 0xff);	break;
			}
			_delay_ms(2000);
		}

//
//		CLCD_u8GoToXY(7, 1);
//		CLCD_voidSendDecimalNumber(0);
//		CLCD_voidSendData('-');
//		CLCD_voidSendDecimalNumber(0);
//		_delay_ms(1000);
	}
}
