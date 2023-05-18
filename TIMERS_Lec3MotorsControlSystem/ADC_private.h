/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: ADC_private.h			**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file ADC_private.h
 * @author Ibrahim Tarek
 * @brief This file contains ADC module private defines.
 * @version 1.00
 */

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

/*BITS' MASKS*/
#define PRESCALER_MASK			0b11111000
#define CHANNEL_MASK			0b11100000

/*ADC_u8REF_VOLT OPTIONS*/
#define AREF_REF				1u
#define AVCC_REF				2u
#define INTERNAL_2560mV_REF		3u

/*ADC_u8RESOLUTION OPTIONS*/
#define EIGHT_BITS				1u
#define TEN_BITS				2u

/*Timer/Counter 0 Prescaler Options*/
#define NO_CLOCK_SOURCE			0b000
#define DIVISION_BY_1			0b001
#define DIVISION_BY_8			0b010
#define DIVISION_BY_32			0b011
#define DIVISION_BY_64			0b100
#define DIVISION_BY_128			0b101
#define DIVISION_BY_256			0b110
#define DIVISION_BY_1024		0b111

#endif
