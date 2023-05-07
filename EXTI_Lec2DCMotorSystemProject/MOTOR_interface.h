/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: MOTOR_interface.h	**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

#ifndef MOTOR_INTERFACE_H_
#define MOTOR_INTERFACE_H_

typedef struct MOTOR_t
{
	uint8 Port;
	uint8 Pin1;
	uint8 Pin2;
}MOTOR_t;

uint8 MOTOR_u8RotateCW(const MOTOR_t *Copy_pmotortMotorInfo);
uint8 MOTOR_u8RotateCCW(const MOTOR_t *Copy_pmotortMotorInfo);
uint8 MOTOR_u8Stop(const MOTOR_t *Copy_pmotortMotorInfo);


#endif
