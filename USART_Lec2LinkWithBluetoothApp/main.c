#include "STD_TYPES.h"
#include "DEFINES.h"
#include "LIBRARY_interface.h"

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "GIE_interface.h"
#include "UART_interface.h"
#include "ADC_interface.h"
#include "TIMERS_interface.h"

#include "ULTSONIC_interface.h"
#include "LDR_interface.h"
#include "CLCD_interface.h"

#include <util/delay.h>


/*Set UART Messages Macros*/
#define TURN_ON_LIGHT				'1'
#define CONTROL_LIGHT_INTENSITY		'2'
#define TURN_OFF_LIGHT				'3'
#define OPEN_THE_DOOR				'4'
#define CLOSE_THE_DOOR				'5'
#define OPEN_THE_FAN				'6'
#define CONTROL_THE_FAN_SPEED		'7'
#define CLOSE_THE_FAN				'8'
#define SEND_ALARM					'9'


/*Define Some Macros*/
#define PASSED					0u
#define IGNORED					1u

#define OPENED					0u
#define CLOSED					1u


/*Set Hardware Connections*/
#define MAIN_u8LDR_CH			LDR_u8ADC_CH0

#define MAIN_u8LIGHT_PORT		DIO_u8PORTC
#define MAIN_u8LIGHT_PIN		DIO_u8PIN7

#define MAIN_u8SERVO_PORT		DIO_u8PORTA
#define MAIN_u8SERVO_PIN		DIO_u8PIN6

#define MAIN_u8DC_PORT			DIO_u8PORTA
#define MAIN_u8DC_PIN			DIO_u8PIN5

#define MAIN_u8SERVO_CLOSED		3u
#define MAIN_u8SERVO_OPENED		12u

#define MAIN_u8ULTSONIC_TRIG_PORT	DIO_u8PORTA
#define MAIN_u8ULTSONIC_TRIG_PIN	DIO_u8PIN4


/*Declare Static Functions*/
static void Main_voidReceiveNotificFunc(void);

static uint8 Main_voidLogin(void);

static void Main_voidTimer0ISR(void);
static void Main_voidTimer2ISR(void);


/*Initialize Flags*/
static uint8 Main_u8UltraFlag = CLOSED;
static uint8 Main_u8LdrFlag = CLOSED;
static uint8 Main_u8AlarmFlag = CLOSED;


/*Initialize Variables*/
static uint8 Main_u8LightIntensity = 0u;
static uint8 Main_u8ServoState = MAIN_u8SERVO_CLOSED;
static uint8 Main_u8DcMotorSpeed = 0u;

static uint8 Main_u8ReceivedData = 0u;


/*Declare Timer 2 configuration structure*/
static TIMER0_2_CFG_t Local_stTimer2;

/*
 * HW Connections:	1- Take in order configurations from line 39 to line 55.
 * 					2- CLCD connections are configured in CLCD_config.h
 * 					3- Connect Ultrasonic Echo pin with D6.
 * 					4- Connect Buzzer pin with D7.
 * */

/*It is the main*/
void main(void)
{
	/*Initialize needed peripherals*/
	PORT_voidInit();
	USART_voidInit();
	ADC_voidInit();
	CLCD_voidInit();

	/*Enable Global Interrupt*/
	GIE_voidEnable();

	/*Initialize Timer 0*/
	TIMER0_2_CFG_t Local_stTimer0;
	Local_stTimer0.ClkSelect = TIMER0_u8SYS_CLK_BY_8;
	Local_stTimer0.OCMode = OC_DISCONNECTED;
	Local_stTimer0.WGM = CTC;
	TIMER0_u8Init(&Local_stTimer0);
	TIMER0_voidSetCompValue(200);
	TIMERS_u8SetCallBack(TIMER0_COMP, Main_voidTimer0ISR);
	TIMERS_u8IntEnable(TIMER0_COMP);

	/*Initialize Timer 2*/
	Local_stTimer2.ClkSelect = TIMER2_u8SYS_CLK_BY_8;
	Local_stTimer2.WGM = FAST_PWM;
	Local_stTimer2.OCMode = OC_DISCONNECTED;
	TIMER2_u8Init(&Local_stTimer2);
	TIMERS_u8SetCallBack(TIMER2_COMP, Main_voidTimer2ISR);

	/*Initialize Ultrosonic sensor*/
	ULTSONIC_t Local_stUltsonic;
	Local_stUltsonic.TrigPort = MAIN_u8ULTSONIC_TRIG_PORT;
	Local_stUltsonic.TrigPin = MAIN_u8ULTSONIC_TRIG_PIN;

	/*Initialize Variables*/
	uint16 Local_u16LDRVoltage = 0u;
	uint16 Local_u16Distance = 0u;
	uint8 Local_u8LoginState = IGNORED;

	/*Call Login Function*/
	/*
	 * ID: is any 4 digits number.
	 * Password: is the reverse of that number.
	 */
	Local_u8LoginState = PASSED;

	/*If user passed*/
	if(Local_u8LoginState == PASSED)
	{
		CLCD_u8GoToXY(4, 0);
		CLCD_u8SendString("Welcome");
		_delay_ms(1000);

		while(1)
		{
			/*Clear Display*/
			_delay_ms(100);
			CLCD_voidClearDisplay();

			/*Receive Character message from uart with asynchronous function*/
			USART_u8ReceiveBufferAsynch(&Main_u8ReceivedData, 1, Main_voidReceiveNotificFunc);

			/*If LDR is opened, manipulate its reading to the light intensity*/
			if(Main_u8LdrFlag == OPENED)
			{
				LDR_u8GetAnalogVolt(MAIN_u8LDR_CH, &Local_u16LDRVoltage);
				Main_u8LightIntensity = LIBRARY_s32Mapping(150u, 4850u, 100u, 1u, Local_u16LDRVoltage);
				CLCD_u8GoToXY(0, 0);
				CLCD_u8SendString("Voltage: ");
				CLCD_voidSendDecimalNumber(Local_u16LDRVoltage);
				CLCD_u8SendString(" mv");
			}

			/*If Ultrasonic sensor is opened, manipulate its reading to the motor speed*/
			if(Main_u8UltraFlag == OPENED)
			{
				ULTSONIC_u8MeasureDistance(&Local_stUltsonic, &Local_u16Distance);
				if(Local_u16Distance > 30)
				{
					Main_u8DcMotorSpeed = 100u;
				}
				else
				{
					Main_u8DcMotorSpeed = LIBRARY_s32Mapping(0u, 30u, 1u, 100u, Local_u16Distance);
				}
				CLCD_u8GoToXY(0, 1);
				CLCD_u8SendString("Distance: ");
				CLCD_voidSendDecimalNumber(Local_u16Distance);
				CLCD_u8SendString(" cm");
			}

			/*If the user send an alarm, turn on timer 2 to send control the buzzer*/
			if(Main_u8AlarmFlag == OPENED)
			{
				TIMER2_u8SetCompOutMode(&Local_stTimer2, NON_INVERTED_PWM);
				TIMERS_u8IntEnable(TIMER2_COMP);
				Main_u8AlarmFlag = CLOSED;
			}
		}
	}
	else
	{
		while(1)
		{
			/*Do nothing*/
		}
	}


}

void Main_voidReceiveNotificFunc(void)
{
	switch(Main_u8ReceivedData)
	{
	case TURN_ON_LIGHT:
		Main_u8LdrFlag = CLOSED;
		DIO_u8SetPortValue(MAIN_u8LIGHT_PORT, 0xff);
		break;
	case CONTROL_LIGHT_INTENSITY:
		Main_u8LdrFlag = OPENED;
		break;
	case TURN_OFF_LIGHT:
		Main_u8LdrFlag = CLOSED;
		DIO_u8SetPortValue(MAIN_u8LIGHT_PORT, 0x00);
		break;
	case OPEN_THE_DOOR:
		Main_u8ServoState = MAIN_u8SERVO_OPENED;
		break;
	case CLOSE_THE_DOOR:
		Main_u8ServoState = MAIN_u8SERVO_CLOSED;
		break;
	case OPEN_THE_FAN:
		Main_u8UltraFlag = CLOSED;
		DIO_u8SetPinValue(MAIN_u8DC_PORT, MAIN_u8DC_PIN, DIO_u8PIN_HIGH);
		break;
	case CONTROL_THE_FAN_SPEED:
		Main_u8UltraFlag = OPENED;
		break;
	case CLOSE_THE_FAN:
		Main_u8UltraFlag = CLOSED;
		DIO_u8SetPinValue(MAIN_u8DC_PORT, MAIN_u8DC_PIN, DIO_u8PIN_LOW);
		break;
	case SEND_ALARM:
		Main_u8AlarmFlag = OPENED;
		break;
	default:
		break;
	}
}

uint8 Main_voidLogin(void)
{
	/*Define Variables*/
	uint8 Local_u8ErrorFounder;
	uint8 Local_u8Iterator;
	uint8 Local_u8LoginState = IGNORED;
	uint8 Local_u8ID[4];
	uint8 Local_u8Password[4];
	uint8 Local_u8Attempts = 3u;

	while(Local_u8Attempts != 0)
	{
		/*Decrement the attempts counter*/
		Local_u8Attempts--;

		/*Get ID and Password from the user*/
		USART_u8SendBufferSynch("Enter ID: ", 10);
		USART_u8ReceiveBufferSynch(Local_u8ID, 4);

		Local_u8ErrorFounder = USART_u8SendBufferSynch("Enter Password: ", 16);
		USART_u8ReceiveBufferSynch(Local_u8Password, 4);

		/*Check ID and Password Received*/
		for(Local_u8Iterator = 0; Local_u8Iterator < 4; Local_u8Iterator++)
		{
			if(Local_u8ID[Local_u8Iterator] != Local_u8Password[3u - Local_u8Iterator])
			{
				break;
			}
		}

		/*Set the login state*/
		if(Local_u8Iterator == 4)
		{
			USART_u8SendBufferSynch("Passed", 6);
			Local_u8LoginState = PASSED;
			break;
		}
		else
		{
			USART_u8SendBufferSynch("Ignored, ", 9);
			USART_u8Send(Local_u8Attempts);
			USART_u8SendBufferSynch(" Attempts Left!", 15);
		}

	}

	/*Return Login State*/
	return Local_u8LoginState;
}


void Main_voidTimer0ISR(void)
{
	static uint8 Local_u8Counter = 0u;
	Local_u8Counter++;

	if(Local_u8Counter == Main_u8ServoState)
	{
		DIO_u8SetPinValue(MAIN_u8SERVO_PORT, MAIN_u8SERVO_PIN, DIO_u8PIN_LOW);
	}
	if((Local_u8Counter == Main_u8DcMotorSpeed) && (Main_u8UltraFlag == OPENED))
	{
		DIO_u8SetPinValue(MAIN_u8DC_PORT, MAIN_u8DC_PIN, DIO_u8PIN_LOW);
	}
	if((Local_u8Counter == Main_u8LightIntensity) && (Main_u8LdrFlag == OPENED))
	{
		DIO_u8SetPortValue(MAIN_u8LIGHT_PORT, 0x00);
	}
	if(Local_u8Counter == 100u)
	{
		Local_u8Counter = 0u;
		DIO_u8SetPinValue(MAIN_u8SERVO_PORT, MAIN_u8SERVO_PIN, DIO_u8PIN_HIGH);
		if(Main_u8UltraFlag == OPENED)
		{
			DIO_u8SetPinValue(MAIN_u8DC_PORT, MAIN_u8DC_PIN, DIO_u8PIN_HIGH);
		}
		if(Main_u8LdrFlag == OPENED)
		{
			DIO_u8SetPortValue(MAIN_u8LIGHT_PORT, 0xff);
		}
	}
}

void Main_voidTimer2ISR(void)
{
	static uint8 Local_u8HighCounter = 0u;
	static uint8 Local_u8LowCounter = 0u;
	static uint8 Local_u8MedCounter = 0u;

	if(Local_u8MedCounter == 5u)
	{
		TIMER2_u8SetCompOutMode(&Local_stTimer2, OC_DISCONNECTED);
		TIMERS_u8IntDisable(TIMER2_COMP);
		Local_u8MedCounter = 0;
	}
	else
	{
		Local_u8LowCounter++;
		if(Local_u8LowCounter == 250)
		{
			Local_u8LowCounter = 0u;
			Local_u8HighCounter++;

			if(Local_u8HighCounter == 5u)
			{
				Local_u8MedCounter++;
				TIMER2_voidSetCompValue(1);
			}
			else if(Local_u8HighCounter == 10u)
			{
				TIMER2_voidSetCompValue(255);
			}
			else if(Local_u8HighCounter == 15u)
			{
				TIMER2_voidSetCompValue(1);
			}
			else if(Local_u8HighCounter == 20u)
			{
				TIMER2_voidSetCompValue(150);
			}
			else if(Local_u8HighCounter == 24u)
			{
				TIMER2_voidSetCompValue(255);
			}
			else if(Local_u8HighCounter == 28u)
			{
				TIMER2_voidSetCompValue(150);
			}
			else if(Local_u8HighCounter == 32u)
			{
				TIMER2_voidSetCompValue(255);
			}
			else if(Local_u8HighCounter == 36u)
			{
				Local_u8HighCounter = 0u;
				TIMER2_voidSetCompValue(150);
			}
		}
	}
}
