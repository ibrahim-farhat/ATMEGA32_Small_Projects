/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: STEPPER_interface.h	**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

#ifndef STEPPER_INTERFACE_H_
#define STEPPER_INTERFACE_H_


#define STEPPER_u8ROTATE_CW		1
#define STEPPER_u8ROTATE_CCW	2

#define STEPPER_u8SPEED_SLOW	10u
#define STEPPER_u8SPEED_MEDIUM	6u
#define STEPPER_u8SPEED_FAST	2u


typedef struct STEPPER_t
{
	uint8 Port;
	uint8 BluePin;
	uint8 PinkPin;
	uint8 YellowPin;
	uint8 OrangePin;
}STEPPER_t;


uint8 STEPPER_u8RotateWithFixedSpeed(const STEPPER_t *Copy_psteppertMotorInfo, uint16 Copy_u16Angle, uint8 Copy_u8Direction);

uint8 STEPPER_u8RotateWithAngle(const STEPPER_t *Copy_psteppertMotorInfo, uint16 Copy_u16Angle, uint8 Copy_u8Direction, uint8 Copy_u8Speed);

uint8 STEPPER_u8RotateWithRolls(const STEPPER_t *Copy_psteppertMotorInfo, uint8 Copy_u8RollsNumber, uint8 Copy_u8Direction, uint8 Copy_u8Speed);


#endif
