/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: ICU_program.c			**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file ICU_program.c
 * @author Ibrahim Tarek
 * @brief This file implements the ICU service functions.
 * @version 1.00
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DEFINES.h"

#include "ICU_interface.h"
#include "ICU_config.h"
#include "ICU_private.h"

#include "TIMERS_interface.h"

static void ICU_voidCaptureISR(void);
static void ICU_voidOvfISR(void);

static uint16 ICU_u16Capture1 = 0u;
static uint16 ICU_u16Capture2 = 0u;
static uint16 ICU_u16Capture3 = 0u;
static uint8 ICU_u8OvfCounter = 0u;
static uint8 ICU_u8PeriodOvfCounter = 0u;
static uint8 ICU_u8DutyCycleOvfCounter = 0u;

void ICU_voidMeasurePWM(uint8 *Copy_pu8DutyCycle, uint32 *Copy_pu32PeriodTime)
{
	uint32 Local_u32PeriodTime = 0u;
	uint8 Local_u8DutyCycle = 0u;

	TIMER1_CFG_t Local_stTimer1Cfg;
	Local_stTimer1Cfg.ClkSelect = TIMER1_u8SYS_CLK_BY_8;
	Local_stTimer1Cfg.WGM = NORMAL_16_BITS;
	Local_stTimer1Cfg.OCAMode = OC_DISCONNECTED;
	Local_stTimer1Cfg.OCBMode = OC_DISCONNECTED;
	TIMER1_u8Init(&Local_stTimer1Cfg);

	TIMERS_u8IntEnable(TIMER1_CAPT);
	TIMER1_u8SetInputCaptTriggerSrc(TIMER1_u8ICU_RISING_EDGE);
	TIMERS_u8SetCallBack(TIMER1_CAPT, ICU_voidCaptureISR);

	TIMERS_u8IntEnable(TIMER1_OVF);
	TIMERS_u8SetCallBack(TIMER1_OVF, ICU_voidOvfISR);
	while((ICU_u16Capture1 == 0u) || (ICU_u16Capture2 == 0u) || (ICU_u16Capture3 == 0u));

	if(ICU_u8PeriodOvfCounter == 0u)
	{
		Local_u32PeriodTime = ICU_u16Capture2 - ICU_u16Capture1;
		Local_u8DutyCycle = (((f32) (ICU_u16Capture3 - ICU_u16Capture2)) / (f32) Local_u32PeriodTime) * 100;
	}
	else
	{
		if(ICU_u16Capture2 >= ICU_u16Capture1)
		{
			Local_u32PeriodTime = ICU_u16Capture2 - ICU_u16Capture1 + (ICU_u8PeriodOvfCounter * 65536u);
		}
		else if(ICU_u16Capture2 < ICU_u16Capture1)
		{
			Local_u32PeriodTime = ICU_u16Capture1 - ICU_u16Capture2 + (ICU_u8PeriodOvfCounter * 65536u);
		}

		if(ICU_u8DutyCycleOvfCounter == 0u)
		{
			Local_u8DutyCycle = (((f32) (ICU_u16Capture3 - ICU_u16Capture2)) / (f32) Local_u32PeriodTime) * 100;
		}
		else
		{
			if(ICU_u16Capture3 >= ICU_u16Capture2)
			{
				Local_u8DutyCycle = ICU_u16Capture3 - ICU_u16Capture2 + (ICU_u8DutyCycleOvfCounter * 65536u);
				Local_u8DutyCycle = ((f32) Local_u8DutyCycle / (f32) Local_u32PeriodTime) * 100;
			}
			else if(ICU_u16Capture3 < ICU_u16Capture2)
			{
				Local_u8DutyCycle = ICU_u16Capture2 - ICU_u16Capture3 + (ICU_u8DutyCycleOvfCounter * 65536u);
				Local_u8DutyCycle = ((f32) Local_u8DutyCycle / (f32) Local_u32PeriodTime) * 100;
			}
		}

	}

	*Copy_pu32PeriodTime = Local_u32PeriodTime;
	*Copy_pu8DutyCycle = Local_u8DutyCycle;
	TIMERS_u8IntDisable(TIMER1_OVF);
	TIMERS_u8Disable(TIMER1);
}

static void ICU_voidCaptureISR(void)
{
	static uint8 Local_u8Counter = 0u;

	Local_u8Counter++;

	if(Local_u8Counter == 1u)
	{
		ICU_u16Capture1 = TIMER1_u16GetInputCaptValue();
	}
	else if(Local_u8Counter == 2u)
	{
		ICU_u16Capture2 = TIMER1_u16GetInputCaptValue();
		TIMER1_u8SetInputCaptTriggerSrc(TIMER1_u8ICU_FALLING_EDGE);
		ICU_u8PeriodOvfCounter = ICU_u8OvfCounter;
	}
	else if(Local_u8Counter == 3u)
	{
		ICU_u16Capture3 = TIMER1_u16GetInputCaptValue();
		TIMERS_u8IntDisable(TIMER1_CAPT);
		ICU_u8DutyCycleOvfCounter = ICU_u8OvfCounter - ICU_u8PeriodOvfCounter;
	}
}

static void ICU_voidOvfISR(void)
{
	ICU_u8OvfCounter++;
}
