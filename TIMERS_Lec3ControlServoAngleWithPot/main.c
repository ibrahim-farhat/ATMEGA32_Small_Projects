#include "STD_TYPES.h"
#include "LIBRARY_interface.h"

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "TIMERS_interface.h"
#include "ADC_interface.h"

#include <util/delay.h>

/*It is the main*/
void main(void)
{
	/*
	 * Brief: This is an application which control the angle of a servo motor with a potentiometer.
	 *
	 * Connections: 1- Connect Output of Potentiometer on Port A Pin 0.
	 * 				2- Connect Pin D5 the servo control pin.
	 */

	/*Peripherals Initialization*/
	PORT_voidInit();
	ADC_voidInit();
	TIMER1_voidInit();


	/*Define Variables*/
	uint16 Local_u16PotentionmeterVoltage = 0;
	uint16 Local_u16ServoAngleTicks = 0;

	/*Super Loop*/
	while(1)
	{
		/*Measure the potentiometer voltage*/
		ADC_u8StartConversionSynch(ADC_u8SINGLE_ENDED_CH0, &Local_u16PotentionmeterVoltage);

		/*Map the ADC ouput to the ticks we need to control the servo*/
		Local_u16ServoAngleTicks = LIBRARY_s32Mapping(0, 1023, 500, 2500, Local_u16PotentionmeterVoltage);

		/*Send ticks number to the timer 1*/
		TIMER1_voidSetCompValue(Local_u16ServoAngleTicks);
	}
}

