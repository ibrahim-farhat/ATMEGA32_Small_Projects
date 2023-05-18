#include "STD_TYPES.h"
#include "SpecialCharacters.h"

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "EXTI_interface.h"
#include "GIE_interface.h"
#include "TIMERS_interface.h"
#include "ADC_interface.h"

#include "CLCD_interface.h"
#include "SSD_interface.h"
#include "KEYPAD_interface.h"
#include "MOTOR_interface.h"
#include "STEPPER_interface.h"

#include "LIBRARY_interface.h"

#include <util/delay.h>

void Main_voidInt0ISR(void);

uint8 Main_u8SystemIndicator;

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
	ADC_voidInit();

	EXTI_u8SetCallBack(EXTI_u8INT1, &Main_voidInt0ISR);

	/*Define variables*/
	uint8 Local_u8Iterator = 0;
	uint8 Local_u8PressedKey = KEYPAD_u8NO_PRESSED_KEY;
	uint8 Local_u8IDIterator = 0;
	uint8 Local_u8SevenSegmentIterator = 3;
	uint8 Local_u8LoginFlag = 0;

	uint8 Local_u8DCMotorManage = 0;
	uint8 Local_u8StepperMotorManage = 0;
	uint8 Local_u8ServoMotorManage = 0;

	uint8 Local_u8DCMotorDir = 0;
	uint8 Local_u8StepperDir = 0;

	uint16 Local_u16StepperAngle = 0;
	uint16 Local_u16ServoAngle = 0;
	uint16 Local_u16ServoAngleTicks = 0;


	uint16 Local_u16ID = 0;
	uint16 Local_u16Password = 0;
	uint16 Local_u16ReversedID = 0;

	uint16 Local_u16PotentiometerVoltage = 0;
	uint16 Local_u16TimerTicks = 0;

	SSD_t Local_ssdtLoginCounter;
	Local_ssdtLoginCounter.Port = DIO_u8PORTC;
	Local_ssdtLoginCounter.EnablePort = DIO_u8PORTD;
	Local_ssdtLoginCounter.EnablePin = DIO_u8PIN6;
	Local_ssdtLoginCounter.LedPin = DIO_u8PIN0;
	Local_ssdtLoginCounter.Type = SSD_u8CATHODE;

	MOTOR_t Local_motortSystemMotor;
	Local_motortSystemMotor.Port = DIO_u8PORTD;
	Local_motortSystemMotor.Pin1 = DIO_u8PIN6;
	Local_motortSystemMotor.Pin2 = DIO_u8PIN7;
	MOTOR_u8Stop(&Local_motortSystemMotor);

	STEPPER_t Local_steppertMain;
	Local_steppertMain.Port = DIO_u8PORTD;
	Local_steppertMain.PinkPin = DIO_u8PIN4;
	Local_steppertMain.BluePin = DIO_u8PIN2;
	Local_steppertMain.YellowPin = DIO_u8PIN1;
	Local_steppertMain.OrangePin = DIO_u8PIN0;

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
				SSD_u8SetNumber(&Local_ssdtLoginCounter, 8);
				Local_u8LoginFlag = 1;
				_delay_ms(2000);
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
				_delay_ms(1000);
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
				/*The Main Menu of our program*/
				if(Main_u8SystemIndicator == 0)
				{
					/*Clear the display*/
					CLCD_voidClearDisplay();

					/*print the menu*/
					CLCD_u8GoToXY(0, 0);
					CLCD_u8SendString("Choose: 1-DCM,");
					CLCD_u8GoToXY(0, 1);
					CLCD_u8SendString("2-Step, 3-Servo");

					/*Scan the choice from the keypad*/
					Local_u8PressedKey = KEYPAD_u8NO_PRESSED_KEY;
					while(Local_u8PressedKey == KEYPAD_u8NO_PRESSED_KEY)
					{
						Local_u8PressedKey = KEYPAD_u8GetPressedKey();
					}

					/*Which is the pressed key*/
					switch(Local_u8PressedKey)
					{
					case 1: Main_u8SystemIndicator = 1;	break;
					case 2:	Main_u8SystemIndicator = 2;	break;
					case 3:	Main_u8SystemIndicator = 3;	break;
					default:
						CLCD_voidClearDisplay();
						CLCD_u8GoToXY(2, 0);
						CLCD_u8SendString("Wrong Input!");
						_delay_ms(2000);
						Main_u8SystemIndicator = 0;
						break;
					}
				}
				else if(Main_u8SystemIndicator == 1)
				{
					/*Print DC Motor Menu*/
					CLCD_voidClearDisplay();
					CLCD_u8GoToXY(0, 0);
					CLCD_u8SendString("1- Max Speed");
					CLCD_u8GoToXY(0, 1);
					CLCD_u8SendString("2- Map with Pot");

					/*Scan the choice from the keypad*/
					Local_u8PressedKey = KEYPAD_u8NO_PRESSED_KEY;
					while(Local_u8PressedKey == KEYPAD_u8NO_PRESSED_KEY)
					{
						Local_u8PressedKey = KEYPAD_u8GetPressedKey();
					}

					/*Which is the pressed key*/
					switch(Local_u8PressedKey)
					{
					case 1: Local_u8DCMotorManage = 1;	break;
					case 2:	Local_u8DCMotorManage = 2;	break;
					default:
						CLCD_voidClearDisplay();
						CLCD_u8GoToXY(2, 0);
						CLCD_u8SendString("Wrong Input!");
						_delay_ms(2000);
						Main_u8SystemIndicator = 0;
						break;
					}

					if(Main_u8SystemIndicator == 1)
					{
						/*Scan the direction from the user*/
						CLCD_voidClearDisplay();
						CLCD_u8GoToXY(0, 1);
						CLCD_u8SendString("1- CW, 2- CCW");
						CLCD_u8GoToXY(0, 0);
						CLCD_u8SendString("Enter the Dir: ");

						/*Scan the choice from the keypad*/
						Local_u8PressedKey = KEYPAD_u8NO_PRESSED_KEY;
						while(Local_u8PressedKey == KEYPAD_u8NO_PRESSED_KEY)
						{
							Local_u8PressedKey = KEYPAD_u8GetPressedKey();
						}

						switch(Local_u8PressedKey)
						{
						case 1:
						case 2:
							Local_u8DCMotorDir = Local_u8PressedKey;
							break;
						default:
							CLCD_voidClearDisplay();
							CLCD_u8GoToXY(2, 0);
							CLCD_u8SendString("Wrong Input!");
							_delay_ms(2000);
							Main_u8SystemIndicator = 0;
							break;
						}


						/*Open DC Motor with Max Speed*/
						if(Local_u8DCMotorManage == 1)
						{
							/*Print State to the LCD*/
							CLCD_voidClearDisplay();
							CLCD_u8GoToXY(3, 0);
							CLCD_u8SendString("Max Speed");
							CLCD_u8GoToXY(5, 1);

							if(Local_u8DCMotorDir == 1)
							{
								CLCD_u8SendString("in CW");

								MOTOR_u8RotateCW(&Local_motortSystemMotor);

								while(Main_u8SystemIndicator != 0);
							}
							else if(Local_u8DCMotorDir == 2)
							{
								CLCD_u8SendString("in CCW");

								MOTOR_u8RotateCCW(&Local_motortSystemMotor);

								while(Main_u8SystemIndicator != 0);
							}

							/*Close the motor*/
							MOTOR_u8Stop(&Local_motortSystemMotor);
						}
						else if(Local_u8DCMotorManage == 2)
						{
							/*Print State to the LCD*/
							CLCD_voidClearDisplay();
							CLCD_u8GoToXY(2, 0);
							CLCD_u8SendString("Map with Pot");
							CLCD_u8GoToXY(5, 1);

							if(Local_u8DCMotorDir == 1)
							{
								CLCD_u8SendString("in CW");
								MOTOR_u8RotateCW(&Local_motortSystemMotor);

								while(Main_u8SystemIndicator != 0)
								{
									/*Measure the potentiometer voltage*/
									ADC_u8StartConversionSynch(ADC_u8SINGLE_ENDED_CH7, &Local_u16PotentiometerVoltage);

									/*Map the ADC ouput to the ticks we need to control the speed of the DC motor*/
									Local_u16TimerTicks = LIBRARY_s32Mapping(0, 1023, 0, 20000, Local_u16PotentiometerVoltage);

									/*Moving Motor with delay to manage its speed*/
									_delay_us(Local_u16TimerTicks);
									MOTOR_u8Stop(&Local_motortSystemMotor);
									_delay_us(20000 - Local_u16TimerTicks);
									MOTOR_u8RotateCW(&Local_motortSystemMotor);
								}

								/*Close the motor*/
								MOTOR_u8Stop(&Local_motortSystemMotor);
							}
							else if(Local_u8DCMotorDir == 2)
							{
								CLCD_u8SendString("in CCW");

								MOTOR_u8RotateCCW(&Local_motortSystemMotor);

								while(Main_u8SystemIndicator != 0)
								{
									/*Measure the potentiometer voltage*/
									ADC_u8StartConversionSynch(ADC_u8SINGLE_ENDED_CH7, &Local_u16PotentiometerVoltage);

									/*Map the ADC ouput to the ticks we need to control the speed of the DC motor*/
									Local_u16TimerTicks = LIBRARY_s32Mapping(0, 1023, 0, 20000, Local_u16PotentiometerVoltage);

									/*Moving Motor with delay to manage its speed*/
									_delay_us(Local_u16TimerTicks);
									MOTOR_u8Stop(&Local_motortSystemMotor);
									_delay_us(20000 - Local_u16TimerTicks);
									MOTOR_u8RotateCCW(&Local_motortSystemMotor);
								}

								/*Close the motor*/
								MOTOR_u8Stop(&Local_motortSystemMotor);
							}
						}
					}
				}
				else if(Main_u8SystemIndicator == 2)
				{
					/*Scan the angle from the user*/
					CLCD_voidClearDisplay();
					CLCD_u8GoToXY(0, 0);
					CLCD_u8SendString("Enter Angle: ");

					Local_u8IDIterator = 0;
					Local_u16StepperAngle = 0;
					while(Local_u8IDIterator < 3)
					{
						Local_u8IDIterator++;
						Local_u8PressedKey = KEYPAD_u8NO_PRESSED_KEY;
						while(Local_u8PressedKey == KEYPAD_u8NO_PRESSED_KEY)
						{
							Local_u8PressedKey = KEYPAD_u8GetPressedKey();
						}

						switch(Local_u8PressedKey)
						{
						case 11:
							Local_u8IDIterator = 3;
							break;
						default:
							/*Print the number to the lcd*/
							CLCD_voidSendDecimalNumber(Local_u8PressedKey);
							/*Calculate the angle*/
							Local_u16StepperAngle = Local_u16StepperAngle * 10u + (uint16) Local_u8PressedKey;
							break;
						}
					}

					/*Scan the direction from the user*/
					_delay_ms(1000);
					CLCD_voidClearDisplay();
					CLCD_u8GoToXY(0, 0);

					/*Scan the direction from the user*/
					CLCD_voidClearDisplay();
					CLCD_u8GoToXY(0, 1);
					CLCD_u8SendString("1- CW, 2- CCW");
					CLCD_u8GoToXY(0, 0);
					CLCD_u8SendString("Enter the Dir: ");

					/*Scan the choice from the keypad*/
					Local_u8PressedKey = KEYPAD_u8NO_PRESSED_KEY;
					while(Local_u8PressedKey == KEYPAD_u8NO_PRESSED_KEY)
					{
						Local_u8PressedKey = KEYPAD_u8GetPressedKey();
					}

					switch(Local_u8PressedKey)
					{
					case 1:
					case 2:
						Local_u8StepperDir = Local_u8PressedKey;
						break;
					default:
						CLCD_voidClearDisplay();
						CLCD_u8GoToXY(2, 0);
						CLCD_u8SendString("Wrong Input!");
						_delay_ms(2000);
						Main_u8SystemIndicator = 0;
						break;
					}

					/*Move the stepper*/
					CLCD_voidClearDisplay();
					CLCD_u8GoToXY(0, 0);
					CLCD_u8SendString("Angle: ");
					CLCD_voidSendDecimalNumber(Local_u16StepperAngle);

					if(Main_u8SystemIndicator == 2)
					{
						switch(Local_u8StepperDir)
						{
						case 1:
							STEPPER_u8RotateWithFixedSpeed(&Local_steppertMain, Local_u16StepperAngle, STEPPER_u8ROTATE_CW);
							break;
						case 2:
							STEPPER_u8RotateWithFixedSpeed(&Local_steppertMain, Local_u16StepperAngle, STEPPER_u8ROTATE_CCW);
							break;
						}

						Main_u8SystemIndicator = 0;
					}
				}
				else if(Main_u8SystemIndicator == 3)
				{
					/*Print DC Motor Menu*/
					CLCD_voidClearDisplay();
					CLCD_u8GoToXY(0, 0);
					CLCD_u8SendString("1- Enter Angle");
					CLCD_u8GoToXY(0, 1);
					CLCD_u8SendString("2- Map with Pot");

					/*Scan the choice from the keypad*/
					Local_u8PressedKey = KEYPAD_u8NO_PRESSED_KEY;
					while(Local_u8PressedKey == KEYPAD_u8NO_PRESSED_KEY)
					{
						Local_u8PressedKey = KEYPAD_u8GetPressedKey();
					}

					/*Which is the pressed key*/
					switch(Local_u8PressedKey)
					{
					case 1: Local_u8ServoMotorManage = 1;	break;
					case 2:	Local_u8ServoMotorManage = 2;	break;
					default:
						CLCD_voidClearDisplay();
						CLCD_u8GoToXY(2, 0);
						CLCD_u8SendString("Wrong Input!");
						_delay_ms(2000);
						Main_u8SystemIndicator = 0;
						break;
					}

					if(Main_u8SystemIndicator == 3)
					{
						if(Local_u8ServoMotorManage == 1)
						{
							/*Scan the angle from the user*/
							CLCD_voidClearDisplay();
							CLCD_u8GoToXY(0, 0);
							CLCD_u8SendString("Enter Angle: ");

							Local_u8IDIterator = 0;
							Local_u16ServoAngle = 0;
							while(Local_u8IDIterator < 3)
							{
								Local_u8IDIterator++;
								Local_u8PressedKey = KEYPAD_u8NO_PRESSED_KEY;
								while(Local_u8PressedKey == KEYPAD_u8NO_PRESSED_KEY)
								{
									Local_u8PressedKey = KEYPAD_u8GetPressedKey();
								}

								switch(Local_u8PressedKey)
								{
								case 11:
									Local_u8IDIterator = 3;
									break;
								default:
									/*Print the number to the lcd*/
									CLCD_voidSendDecimalNumber(Local_u8PressedKey);
									/*Calculate the angle*/
									Local_u16ServoAngle = Local_u16ServoAngle * 10u + (uint16) Local_u8PressedKey;
									break;
								}
							}

							_delay_ms(1000);
							if(Local_u16ServoAngle > 180)
							{
								CLCD_voidClearDisplay();
								CLCD_u8GoToXY(1, 0);
								CLCD_u8SendString("This Angle is ");
								CLCD_u8GoToXY(2, 1);
								CLCD_u8SendString("out of range");
								_delay_ms(2000);

								Main_u8SystemIndicator = 0;
							}
							else
							{
								/*Move the servo*/
								CLCD_voidClearDisplay();
								CLCD_u8GoToXY(0, 0);
								CLCD_u8SendString("Angle: ");
								CLCD_voidSendDecimalNumber(Local_u16ServoAngle);

								Local_u16ServoAngleTicks = LIBRARY_s32Mapping(0, 180, 750, 2250, Local_u16ServoAngle);
								TIMER1_voidInit();
								TIMER1_voidSetCompValue(Local_u16ServoAngleTicks);
								_delay_ms(2000);
								Main_u8SystemIndicator = 0;
							}
						}
						else if(Local_u8ServoMotorManage == 2)
						{
							/*Initialize the timer*/
							TIMER1_voidInit();

							CLCD_voidClearDisplay();
							CLCD_u8GoToXY(2, 0);
							CLCD_u8SendString("Map with Pot");
							while(Main_u8SystemIndicator == 3)
							{

								/*Measure the potentiometer voltage*/
								ADC_u8StartConversionSynch(ADC_u8SINGLE_ENDED_CH7, &Local_u16PotentiometerVoltage);

								/*Map the ADC output to the ticks we need to control the servo*/
								Local_u16ServoAngleTicks = LIBRARY_s32Mapping(0, 1023, 500, 2500, Local_u16PotentiometerVoltage);

								/*Send ticks number to the timer 1*/
								TIMER1_voidSetCompValue(Local_u16ServoAngleTicks);
							}
						}
					}
				}
			}
		}
	}
}

void Main_voidInt0ISR(void)
{
	Main_u8SystemIndicator = 0;
}


///*Define Variables*/
//uint16 Local_u16PotentionmeterVoltage = 0;
//uint16 Local_u16ServoAngleTicks = 0;
//
///*Super Loop*/
//while(1)
//{
//	/*Measure the potentiometer voltage*/
//	ADC_u8StartConversionSynch(ADC_u8SINGLE_ENDED_CH0, &Local_u16PotentionmeterVoltage);
//
//	/*Map the ADC ouput to the ticks we need to control the servo*/
//	Local_u16ServoAngleTicks = LIBRARY_s32Mapping(0, 1023, 500, 2500, Local_u16PotentionmeterVoltage);
//
//	/*Send ticks number to the timer 1*/
//	TIMER1_voidSetCompValue(Local_u16ServoAngleTicks);
//}
