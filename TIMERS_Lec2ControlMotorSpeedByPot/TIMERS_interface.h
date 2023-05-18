/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: TIMERS_interface.h		**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file TIMERS_interface.h
 * @author Ibrahim Tarek
 * @brief This file interfaces the TIMERS module functions.
 * @version 1.00
 */

#ifndef TIMERS_INTERFACE_H_
#define TIMERS_INTERFACE_H_

typedef enum
{
	TIMER0_OVF = 0,
	TIMER0_COMP
}TIMERS_Int_Src_t;

void TIMER0_voidInit(void);

void TIMER0_voidSetCompValue(uint8 Copy_u8Value);

void TIMER1_voidInit(void);

void TIMER1_voidSetCompValue(uint16 Copy_u16Value);

uint8 TIMERS_u8SetCallBack(TIMERS_Int_Src_t Copy_u8TimerIntSource, void (* Copy_pvCallBackFunc)(void));

#endif
