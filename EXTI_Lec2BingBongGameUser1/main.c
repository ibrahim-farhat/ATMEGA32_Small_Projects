#include "STD_TYPES.h"
#include "SpecialCharacters.h"

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "EXTI_interface.h"
#include "GIE_interface.h"

#include "CLCD_interface.h"

#include <util/delay.h>

/*ISRs Functions*/
void Main_voidStateISR(void);
void Main_voidCatchButtonISR(void);
void Main_voidResultISR(void);

/*Global Variables*/
uint8 Main_u8StateFlag = 0;
uint8 Main_u8CatchAreaFlag = 0;
uint8 Main_u8AnotherCatchAreaFlag = 0;

/*It is the main*/
void main(void)
{
	/*Peripherals Initialization*/
	PORT_voidInit();
	GIE_voidEnable();
	EXTI_voidInit();
	CLCD_voidInit();

	/*ISRs Calling Back*/
	EXTI_u8SetCallBack(EXTI_u8INT0, &Main_voidStateISR);
	EXTI_u8SetCallBack(EXTI_u8INT1, &Main_voidCatchButtonISR);
	EXTI_u8SetCallBack(EXTI_u8INT2, &Main_voidResultISR);

	/*Define Variables*/
	uint8 Local_u8LaunchFlag = 1;
	uint8 Local_u8LaunchCounter = 0;
	uint8 Local_u8CatchAreaFlag = 0;

	/*Initial condition to the first microcontrolloer state*/
	DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN0, DIO_u8PIN_HIGH);
	Main_u8StateFlag = 1;
	CLCD_u8GoToXY(0, 0);
	CLCD_voidSendSpecialCharacter(Local_u8RacketCharacter, 1, 0, 0);

	/*Super Loop*/
	while(1)
	{
		if(Main_u8StateFlag == 1)
		{
			/*The ball is with us*/

			/*
			 * move the racket if you want,
			 * launch the ball,
			 * raise the state flag,
			 * set the output pin to zero.
			 * */

			/*Moving the racket will be with interrupt*/

			/*Busy wait until the user press the launch button*/
			while(Local_u8LaunchFlag == 1)
			{
				DIO_u8GetPinValue(DIO_u8PORTC, DIO_u8PIN1, &Local_u8LaunchFlag);
			}
			/*Reset the launch flag*/
			Local_u8LaunchFlag = 1;

			/*Take the current racket area*/
			Local_u8CatchAreaFlag = Main_u8CatchAreaFlag;

			/*
			 * Set the second output wire to zero or one,
			 * to inform the another microcontroller the catch area.
			 * */
			switch(Local_u8CatchAreaFlag)
			{
			case 0: DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN6, DIO_u8PIN_LOW);	break;
			case 1:	DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN6, DIO_u8PIN_HIGH);	break;
			}

			/*
			 * Launching the ball,
			 * If the Launch button is pressed, the ball will move from start to end.
			 * */
			for(Local_u8LaunchCounter = 1; Local_u8LaunchCounter < 16; Local_u8LaunchCounter++)
			{
				CLCD_u8GoToXY(Local_u8LaunchCounter, Local_u8CatchAreaFlag);
				CLCD_voidSendSpecialCharacter(Local_u8BallCharacter, 2, Local_u8LaunchCounter, Local_u8CatchAreaFlag);
				_delay_ms(100);
				CLCD_voidSendSpecialCharacter(Local_u8EraseCharacter, 0, Local_u8LaunchCounter, Local_u8CatchAreaFlag);
			}

			/*Raise the state flag*/
			Main_u8StateFlag = 0;

			/*Set the output flag to 0*/
			DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN0, DIO_u8PIN_LOW);
		}
	}
}

/*A notification to receive the ball from the another microcontroller*/
void Main_voidStateISR(void)
{
	/*Define counter*/
	uint8 Local_u8CatchCounter = 0;

	/*Get the area of the ball from the another microcontroller*/
	DIO_u8GetPinValue(DIO_u8PORTC, DIO_u8PIN7, &Main_u8AnotherCatchAreaFlag);

	/*Set the output flag to 1*/
	DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN0, DIO_u8PIN_HIGH);

	/*Receive the ball*/
	if(Main_u8StateFlag != 1)
	{
		for(Local_u8CatchCounter = 16; Local_u8CatchCounter >= 1; Local_u8CatchCounter--)
		{
			CLCD_u8GoToXY(Local_u8CatchCounter, Main_u8AnotherCatchAreaFlag);
			CLCD_voidSendSpecialCharacter(Local_u8BallCharacter, 2, Local_u8CatchCounter, Main_u8AnotherCatchAreaFlag);
			_delay_ms(100);
			CLCD_voidSendSpecialCharacter(Local_u8EraseCharacter, 0, Local_u8CatchCounter, Main_u8AnotherCatchAreaFlag);
		}
	}

	/*If I lose, inform the another microcontroller and hold up*/
	if(Main_u8AnotherCatchAreaFlag != Main_u8CatchAreaFlag)
	{
		DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN4, DIO_u8PIN_LOW);
		while(1);
	}

	/*The ball is with us*/
	Main_u8StateFlag = 1;
}

/*A button to move the ball between the two lines of the lcd*/
void Main_voidCatchButtonISR(void)
{
	if(Main_u8CatchAreaFlag == 0)
	{
		Main_u8CatchAreaFlag = 1;

		CLCD_u8GoToXY(0, 0);
		CLCD_voidSendSpecialCharacter(Local_u8EraseCharacter, 0, 0, 0);

		CLCD_u8GoToXY(0, 1);
		CLCD_voidSendSpecialCharacter(Local_u8RacketCharacter, 1, 0, 1);
	}
	else if(Main_u8CatchAreaFlag == 1)
	{
		Main_u8CatchAreaFlag = 0;

		CLCD_u8GoToXY(0, 1);
		CLCD_voidSendSpecialCharacter(Local_u8EraseCharacter, 0, 0, 1);

		CLCD_u8GoToXY(0, 0);
		CLCD_voidSendSpecialCharacter(Local_u8RacketCharacter, 1, 0, 0);
	}
}

/*The notification that tell the microcontroller that he is the winner*/
void Main_voidResultISR(void)
{
	CLCD_voidClearDisplay();
	CLCD_u8GoToXY(1, 0);
	CLCD_u8SendString("I'm the winner!");
	while(1);
}
