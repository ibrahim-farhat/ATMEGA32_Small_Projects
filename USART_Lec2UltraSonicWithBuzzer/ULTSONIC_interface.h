/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: ULTSONIC_interface.h	**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file ULTSONIC_interface.h
 * @author Ibrahim Tarek
 * @brief This file interfaces the ULTSONIC sensor module functions.
 * @version 1.00
 */

#ifndef ULTSONIC_INTERFACE_H_
#define ULTSONIC_INTERFACE_H_

typedef struct
{
	uint8 TrigPort;
	uint8 TrigPin;
}
ULTSONIC_t;

uint8 ULTSONIC_u8MeasureDistance(const ULTSONIC_t *Copy_stUltsonicData, uint16 *Copy_u16Distance);

#endif
