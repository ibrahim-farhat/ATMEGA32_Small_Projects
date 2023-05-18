/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: SWITCH_interface.h	**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

#ifndef SWITCH_INTERFACE_H_
#define SWITCH_INTERFACE_H_

#define SWITCH_u8PULL_UP	1u
#define SWITCH_u8PULL_DOWN	2u

#define SWITCH_u8PRESSED	1u
#define SWITCH_u8RELEASED	2u

typedef struct SWITCH_t
{
	uint8 Type;
	uint8 Port;
	uint8 Pin;
}SWITCH_t;

uint8 SWITCH_u8GetState(const SWITCH_t *Copy_pswitchtSwitchInformation, uint8 *Copy_pu8State);

#endif
