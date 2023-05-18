/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: SSD_interface.h		**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

#ifndef SSD_INTERFACE_H_
#define SSD_INTERFACE_H_

#define SSD_u8ANODE		1u
#define SSD_u8CATHODE	2u

typedef struct SSD_t
{
	uint8 Type;
	uint8 Port;
	uint8 LedPin;
	uint8 EnablePort;
	uint8 EnablePin;
}SSD_t;

uint8 SSD_u8SetNumber(const SSD_t *Copy_pssdtSSDInformation, uint8 Copy_u8Number);
uint8 SSD_u8Disable(const SSD_t *Copy_pssdtSSDInformation);

#endif
