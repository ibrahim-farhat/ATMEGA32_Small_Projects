/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: CLCD_config.h			**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

#ifndef CLCD_CONFIG_H_
#define CLCD_CONFIG_H_

/*
 * Please choose the mode you want to work on with lcd,
 * Options: 1- EIGHT_BIT_MODE
 * 			2- FOUR_BIT_MODE
 */
#define CLCD_OP_MODE	FOUR_BIT_MODE

/*
 * Please choose which port to connect control pins: RS, RW, E,
 * Options: 1- DIO_u8PORTA
 * 			2- DIO_u8PORTB
 * 			3- DIO_u8PORTC
 * 			4- DIO_u8PORTD
 */
#define CLCD_CTRL_PORT	DIO_u8PORTB

/*
 * Please choose which pins to connect control pins: RS, RW, E,
 * Options: 1- DIO_u8PIN0
 * 			2- DIO_u8PIN1
 * 			3- DIO_u8PIN2
 * 			4- DIO_u8PIN3
 * 			5- DIO_u8PIN4
 * 			6- DIO_u8PIN5
 * 			7- DIO_u8PIN6
 * 			8- DIO_u8PIN7
 */
#define CLCD_RS_PIN		DIO_u8PIN4
#define CLCD_RW_PIN		DIO_u8PIN5
#define CLCD_E_PIN		DIO_u8PIN6

/*
 * Please choose which port to connect data pins,
 * Options: 1- DIO_u8PORTA
 * 			2- DIO_u8PORTB
 * 			3- DIO_u8PORTC
 * 			4- DIO_u8PORTD
 */
#define CLCD_DATA_PORT	DIO_u8PORTB

/*
 * Please choose which pins to connect data pins (if Four_BIT_MODE is enabled): D4, D5, D6, D7,
 * Options: 1- DIO_u8PIN0
 *
 * 			2- DIO_u8PIN1
 * 			3- DIO_u8PIN2
 * 			4- DIO_u8PIN3
 * 			5- DIO_u8PIN4
 * 			6- DIO_u8PIN5
 * 			7- DIO_u8PIN6
 * 			8- DIO_u8PIN7
 */
#if CLCD_OP_MODE == FOUR_BIT_MODE
#define CLCD_D4_PIN		DIO_u8PIN0
#define CLCD_D5_PIN		DIO_u8PIN1
#define CLCD_D6_PIN		DIO_u8PIN2
#define CLCD_D7_PIN		DIO_u8PIN3
#endif

#endif
