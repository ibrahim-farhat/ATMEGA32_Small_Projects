#include "STD_TYPES.h"

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "TIMER_interface.h"
#include "GIE_interface.h"

#include <util/delay.h>

void MAIN_voidLedAss(void);

/*It is the main*/
void main(void)
{
	/*
	 * Connections:
	 * Led 0 on Port B pin 0,
	 * Led 1 on port B pin 1,
	 * Led 2 on port B pin 2.
	 * */

	/*Peripherals Initialization*/
	PORT_voidInit();
	GIE_voidEnable();

	TIMER_voidInit();
	TIMER_u8SetCallBackCompareMatch(MAIN_voidLedAss);

	/*Super Loop*/
	while(1)
	{

	}
}

/*
 * Description:
 * LED 0: On for 5 milli seconds, Off for 15 milli seconds.
 * LED 1: On for 10 milli seconds, Off for 10 milli seconds.
 * LED 2: On for 15 milli seconds, Off for 5 milli seconds.
 */
void MAIN_voidLedAss(void)
{
	/*Define the Counter*/
	static uint8 Local_u8Counter = 0;

	Local_u8Counter++;

	/*After 5 milli seconds*/
	if(Local_u8Counter == 20)
	{
		/*LED 0*/
		DIO_u8SetPinValue(DIO_u8PORTB, DIO_u8PIN0, DIO_u8PIN_LOW);

	}
	/*After 10 milli seconds*/
	else if(Local_u8Counter == 40)
	{
		/*LED 1*/
		DIO_u8SetPinValue(DIO_u8PORTB, DIO_u8PIN1, DIO_u8PIN_LOW);
	}
	/*After 15 milli seconds*/
	else if(Local_u8Counter == 60)
	{
		/*LED 2*/
		DIO_u8SetPinValue(DIO_u8PORTB, DIO_u8PIN2, DIO_u8PIN_LOW);
	}
	/*After 20 milli seconds*/
	else if(Local_u8Counter == 80)
	{
		/*LED 0*/
		DIO_u8SetPinValue(DIO_u8PORTB, DIO_u8PIN0, DIO_u8PIN_HIGH);
		/*LED 1*/
		DIO_u8SetPinValue(DIO_u8PORTB, DIO_u8PIN1, DIO_u8PIN_HIGH);
		/*LED 2*/
		DIO_u8SetPinValue(DIO_u8PORTB, DIO_u8PIN2, DIO_u8PIN_HIGH);

		/*Clear the counter to zero*/
		Local_u8Counter = 0;
	}
}
