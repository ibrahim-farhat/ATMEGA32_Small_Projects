/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: TIMERS_private.h		**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file TIMERS_private.h
 * @author Ibrahim Tarek
 * @brief This file contains TIMERS module private defines.
 * @version 1.00
 */

#ifndef TIMERS_PRIVATE_H_
#define TIMERS_PRIVATE_H_

/*BITS' MASKS*/
#define PRESCALER_MASK			0b11111000
#define TIMER0_2_OCMATCH_MASK	0b11001111
#define TIMER1_OCMATCH_A_MASK	0b00111111
#define TIMER1_OCMATCH_B_MASK	0b11001111
#define TIMER1_WGM_MASK_A		0b11111100
#define TIMER1_WGM_MASK_B		0b11100111
#define WDT_PRESCALER_MASK		0b11111000

///*Timer/Counter 0/2 Prescaler Options*/
//#define NO_CLOCK_SOURCE						0b000
//#define DIVISION_BY_1						0b001
//#define DIVISION_BY_8						0b010
//#define DIVISION_BY_64						0b011
//#define DIVISION_BY_256						0b100
//#define DIVISION_BY_1024					0b101
//#define EXTERN_CLK_SRC_fALLING_EDGE			0b110
//#define EXTERN_CLK_SRC_RISING_EDGE			0b111

/*ICU_TRIGGER_SRC OTIONS*/
#define RISING_EDGE				1u
#define FALLING_EDGE			2u

#endif
