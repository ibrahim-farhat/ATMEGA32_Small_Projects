#include "STD_TYPES.h"
#include "DEFINES.h"

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "TIMERS_interface.h"
#include "GIE_interface.h"

#include "ULTSONIC_interface.h"
#include "CLCD_interface.h"

#include <util/delay.h>

/*It is the main*/
void main(void)
{
	/*
	 * Connections: 1- connect the buzzer pin with C2.
	 * 				2- connect Echo of ultrasonic sensor with D6.
	 * 				3- connect Trig of ultrasonic sensor with C0.
	 */

	/*Peripherals Initialization*/
	PORT_voidInit();
	GIE_voidEnable();

	uint16 Local_u16Distance = 0;
	ULTSONIC_t Local_stUltsonic;
	Local_stUltsonic.TrigPort = DIO_u8PORTC;
	Local_stUltsonic.TrigPin = DIO_u8PIN0;


	/*Super Loop*/
	while(1)
	{
		ULTSONIC_u8MeasureDistance(&Local_stUltsonic, &Local_u16Distance);
		DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN2, DIO_u8PIN_LOW);

		if(Local_u16Distance > 30)
		{
			/*Do nothing*/
		}
		else if(Local_u16Distance > 20)
		{
			DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN2, DIO_u8PIN_HIGH);
			_delay_ms(120);
			DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN2, DIO_u8PIN_LOW);
			_delay_ms(119);

		}
		else if(Local_u16Distance > 10)
		{
			DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN2, DIO_u8PIN_HIGH);
			_delay_ms(90);
			DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN2, DIO_u8PIN_LOW);
			_delay_ms(89);
		}
		else if(Local_u16Distance > 5)
		{
			DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN2, DIO_u8PIN_HIGH);
			_delay_ms(50);
			DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN2, DIO_u8PIN_LOW);
			_delay_ms(49);
		}
		else
		{
			DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN2, DIO_u8PIN_HIGH);
			_delay_ms(30);
		}
	}
}

