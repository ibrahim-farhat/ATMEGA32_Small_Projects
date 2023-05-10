/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: KEYPAD_interface.h	**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_

#define KEYPAD_u8NO_PRESSED_KEY		255u

/**
 * @brief Function to return data of the pressed key
 * @return data of the pressed key
 */
uint8 KEYPAD_u8GetPressedKey(void);

#endif

