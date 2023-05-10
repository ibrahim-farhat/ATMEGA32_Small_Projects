/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: EXTI_register.h		**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file EXTI_register.h
 * @author Ibrahim Tarek
 * @brief This file contains EXTI module registers' memory locations.
 * @version 1.00
 */

#ifndef EXTI_REGISTER_H_
#define EXTI_REGISTER_H_

#define GICR			*((volatile uint8 *) 0x5B)	/*General Interrupt Control Register*/
#define GICR_INT0		6u							/*INT0 Enable\Disable Bit*/
#define GICR_INT1		7u							/*INT1 Enable\Disable Bit*/
#define GICR_INT2		5u							/*INT2 Enable\Disable Bit*/

#define MCUCR			*((volatile uint8 *) 0x55)	/*MCU Control Register*/
#define MCUCR_ISC00		0u							/*INT0 Sense Control Bit 0*/
#define MCUCR_ISC01		1u							/*INT0 Sense Control Bit 1*/
#define MCUCR_ISC10		2u							/*INT1 Sense Control Bit 0*/
#define MCUCR_ISC11		3u							/*INT1 Sense Control Bit 1*/

#define MCUCSR			*((volatile uint8 *) 0x54)	/*MCU Control and Status Register*/
#define MCUCSR_ISC2		6u							/*INT2 Sense Control Bit*/

#endif
