/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: CLCD_program.c		**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DEFINES.h"

#include "DIO_interface.h"

#include <util/delay.h>

#include "CLCD_config.h"
#include "CLCD_interface.h"
#include "CLCD_private.h"

static void voidSendEnablePulse(void)
{
	/*Send enable pulse*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8PIN_HIGH);

	/*Delay for 2 millisecond, it is enough time for lcd to implement any command*/
	_delay_ms(2);

	/*Clear enable*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8PIN_LOW);
}

static void voidSetLCDHalfDataPort(uint8 Copy_u8Nipple)
{
	DIO_u8SetPinValue(CLCD_DATA_PORT, CLCD_D4_PIN, GET_BIT(Copy_u8Nipple, 0));
	DIO_u8SetPinValue(CLCD_DATA_PORT, CLCD_D5_PIN, GET_BIT(Copy_u8Nipple, 1));
	DIO_u8SetPinValue(CLCD_DATA_PORT, CLCD_D6_PIN, GET_BIT(Copy_u8Nipple, 2));
	DIO_u8SetPinValue(CLCD_DATA_PORT, CLCD_D7_PIN, GET_BIT(Copy_u8Nipple, 3));
}

void CLCD_voidSendCmd(uint8 Copy_u8Cmd)
{
	/*Set RS pin to low for command*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_RS_PIN, DIO_u8PIN_LOW);

	/*Set RW pin to low for write operation*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_RW_PIN, DIO_u8PIN_LOW);

#if CLCD_OP_MODE == EIGHT_BIT_MODE
	/*Set the command on data pins*/
	DIO_u8SetPortValue(CLCD_DATA_PORT, Copy_u8Cmd);
	/*Send Enable Pulse to lcd*/
	voidSendEnablePulse();

#elif CLCD_OP_MODE == FOUR_BIT_MODE
	/*Set the most 4 bits on data pins*/
	voidSetLCDHalfDataPort(Copy_u8Cmd >> 4);
	/*Send Enable Pulse to lcd*/
	voidSendEnablePulse();
	/*Set the least 4 bits on data pins*/
	voidSetLCDHalfDataPort(Copy_u8Cmd);
	/*Send Enable Pulse to lcd*/
	voidSendEnablePulse();

#endif

}

void CLCD_voidSendData(char Copy_c8Data)
{

	/*Set RS pin to high for data*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_RS_PIN, DIO_u8PIN_HIGH);

	/*Set RW pin to low for write operation*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_RW_PIN, DIO_u8PIN_LOW);

#if CLCD_OP_MODE == EIGHT_BIT_MODE
	/*Set the data on data pins*/
	DIO_u8SetPortValue(CLCD_DATA_PORT, Copy_c8Data);
	/*Send Enable Pulse to lcd*/
	voidSendEnablePulse();

#elif CLCD_OP_MODE == FOUR_BIT_MODE
	/*Set the most 4 bits on data pins*/
	voidSetLCDHalfDataPort(Copy_c8Data >> 4);
	/*Send Enable Pulse to lcd*/
	voidSendEnablePulse();
	/*Set the least 4 bits on data pins*/
	voidSetLCDHalfDataPort(Copy_c8Data);
	/*Send Enable Pulse to lcd*/
	voidSendEnablePulse();

#endif

}

void CLCD_voidInit(void)
{
	/*Wait for more than 30ms after power on*/
	_delay_ms(40);

#if	CLCD_OP_MODE == EIGHT_BIT_MODE
	/*Function set command: 2 lines, 5*7 font size*/
	CLCD_voidSendCmd(0b00111000);

#elif CLCD_OP_MODE == FOUR_BIT_MODE
	/*Set RS pin to low for command*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_RS_PIN, DIO_u8PIN_LOW);

	/*Set RW pin to low for write operation*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_RW_PIN, DIO_u8PIN_LOW);

	/*Set Commands to lcd*/
	voidSetLCDHalfDataPort(0b0010);
	voidSendEnablePulse();
	voidSetLCDHalfDataPort(0b0010);
	voidSendEnablePulse();
	voidSetLCDHalfDataPort(0b1000);
	voidSendEnablePulse();
#endif

	/*Display on/off control: display enable, cursor and blink disable*/
	CLCD_voidSendCmd(0b00001100);

	/*Display Clear cmd*/
	CLCD_voidSendCmd(0b00000001);
}

void CLCD_voidClearDisplay(void)
{
	CLCD_voidSendCmd(0x01);
}

uint8 CLCD_u8SendString(const char *Copy_ch8String)
{
	uint8 Local_u8ErrorState = OK;

	uint8 Local_u8Counter = 0;

	if(Copy_ch8String != NULL)
	{
		while(Copy_ch8String[Local_u8Counter] != '\0')
		{
			CLCD_voidSendData(Copy_ch8String[Local_u8Counter]);
			Local_u8Counter++;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}


void CLCD_voidSendDecimalNumber(sint32 Copy_s32Number)
{
	char Local_ch8Digit[10] = {0};

	uint8 Local_u8ReverseCounter = 0u;
	uint8 Local_u8PrintCounter;

	if(Copy_s32Number == 0)
	{
		CLCD_voidSendData('0');
	}
	else
	{
		/*Check for the negative sign*/
		if(Copy_s32Number < 0)
		{
			/*Print the negative sign to the lcd*/
			CLCD_voidSendData('-');

			/*Change the sign of the number*/
			Copy_s32Number = Copy_s32Number * -1;
		}

		/*Extracting the number digits into array of characters*/
		while(Copy_s32Number > 0)
		{
			/*
			 * Extract every digit number to the array of characters,
			 * then translate it into ascii value through adding '0'
			 */
			Local_ch8Digit[Local_u8ReverseCounter] = (char) (Copy_s32Number % 10);
			Local_ch8Digit[Local_u8ReverseCounter] = Local_ch8Digit[Local_u8ReverseCounter] + '0';

			Copy_s32Number = Copy_s32Number / 10;
			Local_u8ReverseCounter++;
		}

		/*Printing every character in the array until the end of the number*/
		Local_u8PrintCounter = Local_u8ReverseCounter;
		do
		{
			CLCD_voidSendData(Local_ch8Digit[Local_u8PrintCounter - 1u]);
			Local_u8PrintCounter--;
		}
		while(Local_u8PrintCounter > 0u);
	}
}


void CLCD_voidSendBinaryNumber(sint16 Copy_s16Number)
{
	uint8 Local_u8BinaryDigits[32] = {0u};

	uint8 Local_u8ReverseCounter = 0u;
	uint8 Local_u8PrintCounter;

	/*Print 0b before the binary representation*/
	CLCD_u8SendString("0b");

	/*Loading zoros and ones into array of characters*/
	for(Local_u8ReverseCounter = 0; Local_u8ReverseCounter < 16; Local_u8ReverseCounter++)
	{
		if((Copy_s16Number & 1) == 1)
		{
			Local_u8BinaryDigits[Local_u8ReverseCounter] = 1u;
		}
		else
		{
			Local_u8BinaryDigits[Local_u8ReverseCounter] = 0u;
		}
		Copy_s16Number = Copy_s16Number >> 1;
	}

	/*Go to the next line in the lcd*/
	CLCD_u8GoToXY(0,1);

	/*Printing every character in the array until the end of the number*/
	Local_u8PrintCounter = 16;
	do
	{
		if(Local_u8BinaryDigits[Local_u8PrintCounter - 1] == 0)
		{
			CLCD_voidSendData('0');
		}
		else
		{
			CLCD_voidSendData('1');
		}

		Local_u8PrintCounter--;
	}
	while(Local_u8PrintCounter > 0);
}

//int u8GetMaxSeqZerosBetweenTwoOnesInBinaryRep(int Num)
//{
//	/*Defining variables*/
//	int i, MaxZeros = 0, Zeros = 0, Ones = 0;
//
//	/*Passing over all bits of 32 bit integer*/
//	for(i = 0; i < 32; i++)
//	{
//		/*Getting the value of the bit*/
//		if((((Num >> i) & 1) == 0) && (Ones > 0))
//		{
//			/*If the value is Zero, update Zeros counter*/
//			Zeros++;
//		}
//		else if(((Num >> i) & 1) == 1)
//		{
//			/*If Zeros counter exceed MaxZeros counter update MaxZeros counter*/
//			if((Zeros > MaxZeros))
//			{
//				MaxZeros = Zeros;
//			}
//
//			/*Else if the value is one, reset Zeros counter*/
//			Zeros = 0;
//			Ones++;
//		}
//	}
//
//	/*Returnning the MaxZeros counter*/
//	return MaxZeros;
//}

void CLCD_voidSendHexaNumber(sint32 Copy_s32Number)
{
	/*Define Variables*/
	char Local_ch8HexaTable[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
									'A', 'B', 'C', 'D', 'E', 'F'};
	uint8 Local_u8HexaDigits[8];
	sint8 Local_s8PrintCounter;
	uint8 Local_u8ReverseCounter;
	uint8 Local_u8LeastFourBits;
	uint8 Local_u8PrintTemp;

	/*Load the Hexadecimal digits into array of characters*/
	for(Local_u8ReverseCounter = 0u; Local_u8ReverseCounter < 8u; Local_u8ReverseCounter++)
	{
		/*Get the least for bits of the number*/
		Local_u8LeastFourBits = Copy_s32Number & 0x0f;
		Copy_s32Number = Copy_s32Number >> 4;

		Local_u8HexaDigits[Local_u8ReverseCounter] = Local_u8LeastFourBits;
	}

	/*Print 0x before Hexadecimal representation*/
	CLCD_u8SendString("0x");

	/*Print the hexadecimal number from array of hexadecimal table*/
	for(Local_s8PrintCounter = 7; Local_s8PrintCounter >= 0; Local_s8PrintCounter--)
	{
		Local_u8PrintTemp = Local_u8HexaDigits[Local_s8PrintCounter];
		CLCD_voidSendData(Local_ch8HexaTable[Local_u8PrintTemp]);
	}
}

void CLCD_voidSendSpecialCharacter(uint8 *Copy_pu8Pattern, uint8 Copy_u8PatternNum, uint8 Copy_u8XPos, uint8 Copy_u8YPos)
{
	/*Define Variables*/
	uint8 Local_u8CGRAMAdd = Copy_u8PatternNum * 8u;
	uint8 Local_u8Counter;

	/*Set bit 6 in CGRAMAdd for CGRAM Address command standard*/
	SET_BIT(Local_u8CGRAMAdd, 6);

	/*Send the address command to lcd*/
	CLCD_voidSendCmd(Local_u8CGRAMAdd);

	/*Send the pattern to the lcd*/
	for(Local_u8Counter = 0u; Local_u8Counter < 8u; Local_u8Counter++)
	{
		CLCD_voidSendData(Copy_pu8Pattern[Local_u8Counter]);
	}

	/*Go to DDRAM Address to display the pattern*/
	CLCD_u8GoToXY(Copy_u8XPos, Copy_u8YPos);

	/*Display the pattern from CGRAM to DDRAM*/
	CLCD_voidSendData(Copy_u8PatternNum);
}

uint8 CLCD_u8GoToXY(uint8 Copy_u8XPos, uint8 Copy_u8YPos)
{
	uint8 Local_u8ErrorState = OK;

	uint8 Local_u8DDRamAdd;

	/*Configure the address of DDRam*/
	if(Copy_u8YPos == 0u)
	{
		Local_u8DDRamAdd = Copy_u8XPos;
	}
	else if(Copy_u8YPos == 1u)
	{
		Local_u8DDRamAdd = 0x40 + Copy_u8XPos;
	}
	else
	{
		Local_u8ErrorState = NOK;
	}

	/*Send DDRam Set Address command to lcd*/
	SET_BIT(Local_u8DDRamAdd,7);
	CLCD_voidSendCmd(Local_u8DDRamAdd);

	return Local_u8ErrorState;
}

