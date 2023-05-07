/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: KEYPAD_config.h		**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_

#define KEYPAD_u8COLUMN_NUM			4u
#define KEYPAD_u8ROW_NUM			4u

#define KEYPAD_u8ROW_PORT			DIO_u8PORTA
#define KEYPAD_u8ROW1_PIN			DIO_u8PIN3
#define KEYPAD_u8ROW2_PIN			DIO_u8PIN2
#define KEYPAD_u8ROW3_PIN			DIO_u8PIN1
#define KEYPAD_u8ROW4_PIN			DIO_u8PIN0

#define KEYPAD_u8COLUMN_PORT		DIO_u8PORTA
#define KEYPAD_u8COLUMN1_PIN		DIO_u8PIN4
#define KEYPAD_u8COLUMN2_PIN		DIO_u8PIN5
#define KEYPAD_u8COLUMN3_PIN		DIO_u8PIN6
#define KEYPAD_u8COLUMN4_PIN		DIO_u8PIN7

#define KEYPAD_u8BUTTON_ARR			{{1, 2, 3, 11}, {4, 5, 6, 11}, {7, 8, 9, 11}, {11, 0, 11, 11}}

#endif
