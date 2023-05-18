#include "STD_TYPES.h"

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "TIMER_interface.h"
#include "GIE_interface.h"

#include "CLCD_interface.h"

#include <util/delay.h>

void MAIN_voidExternalTriggerHandler(void);

/*It is the main*/
void main(void)
{
	/*
	 * Connections:
	 * LCD connections are explained at CLCD_config.h file.
	 * Connect a switch to the ground to the pin B0 to do a falling edge on it.
	 *
	 * This application count the external triggers on pin B0 and display this counter on the lcd.
	 * */

	/*Peripherals Initialization*/
	PORT_voidInit();
	GIE_voidEnable();
	TIMER_voidInit();
	TIMER_u8SetCallBackCompareMatch(MAIN_voidExternalTriggerHandler);

	/*Initialize LCD*/
	CLCD_voidInit();
	CLCD_u8SendString("Counts: ");

	/*Super Loop*/
	while(1)
	{
	}
}

void MAIN_voidExternalTriggerHandler(void)
{
	/*Define Counter*/
	static uint8 Local_u8Counter = 0;
	Local_u8Counter++;

	/*Print the counter to the lcd*/
	CLCD_u8GoToXY(8, 0);
	CLCD_u8SendString("    ");
	CLCD_u8GoToXY(8, 0);
	CLCD_voidSendDecimalNumber(Local_u8Counter);
}
