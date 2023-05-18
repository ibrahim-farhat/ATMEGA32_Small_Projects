/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: TIMER_interface.h		**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file TIMER_interface.h
 * @author Ibrahim Tarek
 * @brief This file interfaces the TIMER module functions.
 * @version 1.00
 */

#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_


void TIMER_voidInit(void);
uint8 TIMER_u8SetCallBackCompareMatch(void (* Copy_pvNotificationFunc)(void));
uint8 TIMER_u8SetCallBackOverflow(void (* Copy_pvNotificationFunc)(void));

#endif
