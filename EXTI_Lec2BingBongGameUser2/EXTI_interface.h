/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: EXTI_interface.h		**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file EXTI_interface.h
 * @author Ibrahim Tarek
 * @brief This file interfaces the EXTI module functions.
 * @version 1.00
 */

#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

#define EXTI_u8INT0		1u
#define EXTI_u8INT1		2u
#define EXTI_u8INT2		3u

#define EXTI_u8LOW_LEVEL		1u
#define EXTI_u8ON_CHANGE		2u
#define EXTI_u8FALLING_EDGE		3u
#define EXTI_u8RISING_EDGE		4u

/**
 * @brief Function to initialize external interrupt channels with prebuild configuration.
 */
void EXTI_voidInit(void);

/**
 * @brief Function to change the sense control of an interrupt channel during runtime.
 * @param Copy_u8IntNum	Interrupt Channel Number.
 * @param Copy_u8Sense	Interrupt Sense Control.
 * @return	Error State.
 */
uint8 EXTI_u8SetSenseCtrl(uint8 Copy_u8IntNum, uint8 Copy_u8Sense);

/**
 * @brief Function to enable an interrupt channel.
 * @param Copy_u8IntNum	Interrupt Channel Number.
 * @return	Error State.
 */
uint8 EXTI_u8IntEnable(uint8 Copy_u8IntNum);

/**
 * @brief Function to disable an interrupt channel.
 * @param Copy_u8IntNum	Interrupt Channel Number.
 * @return	Error State.
 */
uint8 EXTI_u8IntDisable(uint8 Copy_u8IntNum);

/**
 * @brief Function to call back the ISR functions for any interrupt.
 * @param Copy_u8IntNum	Interrupt Channel Number.
 * @param Copy_pfFunctionPtr Pointer to the ISR function that is needed to set.
 * @return Error State.
 */
uint8 EXTI_u8SetCallBack(uint8 Copy_u8IntNum, void (* Copy_pfFunctionPtr)(void));

#endif
