/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: KEYPAD_program.c		**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/


#include "STD_TYPES.h"

#include "DIO_interface.h"

#include "KEYPAD_config.h"
#include "KEYPAD_private.h"
#include "KEYPAD_interface.h"


uint8 KEYPAD_u8GetPressedKey(void)
{
	uint8 Local_u8ColumnCounter;
	uint8 Local_u8RowCounter;
	uint8 Local_u8KeyState;
	uint8 Local_u8PressedKey = KEYPAD_u8NO_PRESSED_KEY;

	static uint8 Local_u8ColumnArr[KEYPAD_u8COLUMN_NUM] = {KEYPAD_u8COLUMN1_PIN, KEYPAD_u8COLUMN2_PIN, KEYPAD_u8COLUMN3_PIN, KEYPAD_u8COLUMN4_PIN};
	static uint8 Local_u8RowArr[KEYPAD_u8ROW_NUM] = {KEYPAD_u8ROW1_PIN, KEYPAD_u8ROW2_PIN, KEYPAD_u8ROW3_PIN, KEYPAD_u8ROW4_PIN};
	static uint8 Local_u8KeypadArr[KEYPAD_u8ROW_NUM][KEYPAD_u8COLUMN_NUM] = KEYPAD_u8BUTTON_ARR;

	/*Activate column pins and read the rows*/
	for(Local_u8ColumnCounter = 0; Local_u8ColumnCounter < KEYPAD_u8COLUMN_NUM; Local_u8ColumnCounter++)
	{
		/*Activate the current column*/
		DIO_u8SetPinValue(KEYPAD_u8COLUMN_PORT, Local_u8ColumnArr[Local_u8ColumnCounter], DIO_u8PIN_LOW);

		/*Get values of rows and check for signals from them*/
		for(Local_u8RowCounter = 0; Local_u8RowCounter < KEYPAD_u8ROW_NUM; Local_u8RowCounter++)
		{
			/*Get the value of the current row*/
			DIO_u8GetPinValue(KEYPAD_u8ROW_PORT, Local_u8RowArr[Local_u8RowCounter], &Local_u8KeyState);

			/*If the current row is low, then button is pressed*/
			if(Local_u8KeyState == DIO_u8PIN_LOW)
			{
				/*Wait until the key is released*/
				while(Local_u8KeyState == DIO_u8PIN_LOW)
				{
					DIO_u8GetPinValue(KEYPAD_u8ROW_PORT, Local_u8RowArr[Local_u8RowCounter], &Local_u8KeyState);
				}

				/*Return the corresponding value of the key from the buttons array*/
				Local_u8PressedKey = Local_u8KeypadArr[Local_u8RowCounter][Local_u8ColumnCounter];

				/*Deactivate the current column*/
				DIO_u8SetPinValue(KEYPAD_u8COLUMN_PORT, Local_u8ColumnArr[Local_u8ColumnCounter], DIO_u8PIN_HIGH);

				/*Return the pressed key*/
				return Local_u8PressedKey;
			}
		}

		/*Deactivate the current column*/
		DIO_u8SetPinValue(KEYPAD_u8COLUMN_PORT, Local_u8ColumnArr[Local_u8ColumnCounter], DIO_u8PIN_HIGH);
	}

	/*Return that is no pressed key*/
	return Local_u8PressedKey;
}
