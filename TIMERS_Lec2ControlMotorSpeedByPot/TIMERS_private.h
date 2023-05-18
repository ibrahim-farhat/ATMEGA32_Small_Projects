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

/*ADC_u8PRESCALER_VALUE OPTIONS*/
#define DIVISION_BY_2			1u
#define DIVISION_BY_4			2u
#define DIVISION_BY_8			3u
#define DIVISION_BY_16			4u
#define DIVISION_BY_32			5u
#define DIVISION_BY_64			6u
#define DIVISION_BY_128			7u


/*ADC_u8REF_VOLT OPTIONS*/
#define AREF_REF				1u
#define AVCC_REF				2u
#define INTERNAL_2560mV_REF		3u


#endif
