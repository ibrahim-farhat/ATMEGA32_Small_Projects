/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: TIMER_register.h		**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file TIMER_register.h
 * @author Ibrahim Tarek
 * @brief This file contains TIMER module registers' memory locations.
 * @version 1.00
 */

#ifndef TIMER_REGISTER_H_
#define TIMER_REGISTER_H_

#define TCCR0               *((volatile uint8 *) 0x53)  /*Timer/Counter 0 Control Register*/
#define TCCR0_CS00          0u                          //Clock Select for Timer/Counter 0 Bit 0
#define TCCR0_CS01          1u                          //Clock Select for Timer/Counter 0 Bit 1
#define TCCR0_CS02          2u                          //Clock Select for Timer/Counter 0 Bit 2
#define TCCR0_WGM01         3u                          //Wave Generation Mode for Timer/Counter 0 Bit 1
#define TCCR0_COM00         4u                          //Compare Match Output Mode for Timer/Counter 0 Bit 0
#define TCCR0_COM01         5u                          //Compare Match Output Mode for Timer/Counter 0 Bit 1
#define TCCR0_WGM00         6u                          //Wave Generation Mode for Timer/Counter 0 Bit 0
#define TCCR0_FOC0          7u                          //Force Output Compare for Timer/Counter 0

#define TCNT0               *((volatile uint8 *) 0x52)  /*Timer/Counter 0 Register*/

#define OCR0                *((volatile uint8 *) 0x5C)  /*Output Compare Register for Timer/Counter 0*/

#define TIMSK               *((volatile uint8 *) 0x59)  /*Timer/Counter Interrupt Mask Register*/
#define TIMSK_TOIE0         0u                          //Tiemr/Counter 0 Overflow Interrupt Enable
#define TIMSK_OCIE0         1u                          //Timer/Counter 0 Output Compare Match Interrupt Enable

#endif
