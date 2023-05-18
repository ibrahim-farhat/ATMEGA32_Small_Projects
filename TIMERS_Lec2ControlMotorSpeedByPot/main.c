#include "STD_TYPES.h"
#include "LIBRARY_interface.h"

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "TIMERS_interface.h"
#include "ADC_interface.h"

/*It is the main*/
void main(void)
{
	/*
	 * Brief: This is an application which control the speed of a DC motor with a potentiometer.
	 *
	 * Connections: 1- Connect Output of Potentiometer on Port A Pin 0.
	 * 				2- Connect Pin B3 to one of the motor pins.
	 */

	/*Peripherals Initialization*/
	PORT_voidInit();
	ADC_voidInit();
	TIMER0_voidInit();

	/*Define Variables*/
	uint16 Local_u16ADCReadingHighRes = 0;
	uint8 Local_u8ADCReadingLowRes = 0;

	/*Super Loop*/
	while(1)
	{
		ADC_u8StartConversionSynch(ADC_u8SINGLE_ENDED_CH0, &Local_u16ADCReadingHighRes);
		Local_u8ADCReadingLowRes = LIBRARY_s32Mapping(0, 1023, 0, 255, Local_u16ADCReadingHighRes);
		TIMER0_voidSetCompValue(Local_u8ADCReadingLowRes);
	}
}
