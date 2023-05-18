#include "STD_TYPES.h"

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "TIMER_interface.h"
#include "GIE_interface.h"

#include "SSD_interface.h"

#include <util/delay.h>

/*Function to send to Timer Compare Match ISR*/
void MAIN_voidSSD(void);


/*It is the main*/
void main(void)
{
	/*
	 * Connections of two seven segments are explained starting from line 47.
	 * This application of two seven segments connected on the same port,
	 * one count up and one count down.
	 * */

	/*Peripherals Initialization*/
	PORT_voidInit();
	GIE_voidEnable();

	TIMER_voidInit();
	TIMER_u8SetCallBackCompareMatch(MAIN_voidSSD);


	/*Super Loop*/
	while(1);
}


void MAIN_voidSSD(void)
{
	/*Define Counters*/
	static uint8 Local_u8DisplayingIterator = 0;
	static uint16 Local_u16CountingIterator = 0;
	static uint8 Local_u8SSDUpCounter = 0;
	static uint8 Local_u8SSDDownCounter = 9;

	/*Define a Flag*/
	static uint8 Local_u8InitialFlag = 0;

	/*Define two SSDs*/
	static SSD_t Local_ssdtCountUp;
	Local_ssdtCountUp.Port = DIO_u8PORTA;
	Local_ssdtCountUp.Type = SSD_u8CATHODE;
	Local_ssdtCountUp.LedPin = DIO_u8PIN0;
	Local_ssdtCountUp.EnablePort = DIO_u8PORTC;
	Local_ssdtCountUp.EnablePin = DIO_u8PIN0;

	static SSD_t Local_ssdtCountDown;
	Local_ssdtCountDown.Port = DIO_u8PORTA;
	Local_ssdtCountDown.Type = SSD_u8CATHODE;
	Local_ssdtCountDown.LedPin = DIO_u8PIN0;
	Local_ssdtCountDown.EnablePort = DIO_u8PORTC;
	Local_ssdtCountDown.EnablePin = DIO_u8PIN1;

	/*For the first time you turn the code on turn on SSD up*/
	if(Local_u8InitialFlag == 0)
	{
		Local_u8InitialFlag = 1;
		SSD_u8SetNumber(&Local_ssdtCountUp, Local_u8SSDUpCounter);
	}

	/*Increase Iterators*/
	Local_u8DisplayingIterator++;
	Local_u16CountingIterator++;


	/*After 10 milli seconds*/
	if(Local_u8DisplayingIterator == 40)
	{
		/*Turn off SSD up and turn on SSD down*/
		SSD_u8Disable(&Local_ssdtCountUp);
		SSD_u8SetNumber(&Local_ssdtCountDown, Local_u8SSDDownCounter);
	}
	/*After 20 milli seconds*/
	else if(Local_u8DisplayingIterator == 80)
	{
		/*Turn on SSD up and turn off SSD down*/
		SSD_u8SetNumber(&Local_ssdtCountUp, Local_u8SSDUpCounter);
		SSD_u8Disable(&Local_ssdtCountDown);

		/*Clear the counter to zero*/
		Local_u8DisplayingIterator = 0;
	}

	/*Every 1 sec increase SSD up and decrease SSD down*/
	if(Local_u16CountingIterator == 4000)
	{
		/*Make the range of SSD up between 0 - 9*/
		Local_u8SSDUpCounter++;
		if(Local_u8SSDUpCounter > 9)
		{
			Local_u8SSDUpCounter = 0;
		}

		/*Make the range of SSD down between 9 - 0*/
		Local_u8SSDDownCounter--;
		if(Local_u8SSDDownCounter == 255)
		{
			Local_u8SSDDownCounter = 9;
		}
		Local_u16CountingIterator = 0;
	}
}
