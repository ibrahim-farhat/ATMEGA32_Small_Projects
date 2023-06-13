/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: TIMERS_interface.h		**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

/**
 * @file TIMERS_interface.h
 * @author Ibrahim Tarek
 * @brief This file interfaces the TIMERS module functions.
 * @version 1.00
 */

#ifndef TIMERS_INTERFACE_H_
#define TIMERS_INTERFACE_H_


/*Copy_u8WatchDogTime Options*/
#define WDT_16K_CYCLES			0u
#define WDT_32K_CYCLES			1u
#define WDT_64K_CYCLES			2u
#define WDT_128K_CYCLES			3u
#define WDT_256K_CYCLES			4u
#define WDT_512K_CYCLES			5u
#define WDT_1024K_CYCLES		6u
#define WDT_1048K_CYCLES		7u


/*WGM Options for timers 0 or 2*/
typedef enum
{
	NORMAL = 0,
	PHASE_CORR,
	CTC,
	FAST_PWM
}
TIMER0_2_WGM_t;

/*WGM Options for timer 1*/
typedef enum
{
	NORMAL_16_BITS = 0,
	PHASE_CORR_8_BITS,
	PHASE_CORR_9_BITS,
	PHASE_CORR_10_BITS,
	CTC_OCR1A,
	FAST_PWM_8_BITS,
	FAST_PWM_9_BITS,
	FAST_PWM_10_BITS,
	PHASE_FREQ_CORR_ICR1,
	PHASE_FREQ_CORR_OCR1A,
	PHASE_CORR_ICR1,
	PHASE_CORR_OCR1A,
	CTC_ICR1,
	RESERVED,
	FAST_PWM_ICR1,
	FAST_PWM_OCR1A
}
TIMER1_WGM_t;

/*CompOutMode Options - fast or phase correct PWM mode*/
/*
 * For fast PWM: NON_INVERTED -->> Clear OC0 on compare match, Set OC0 on Top.
 * 				 INVERTED 	  -->> Set OC0 on compare match, Clear OC0 on Top.
 *
 * For phase correct PWM: NON_INVERTED -->> Clear OC0 on compare match when up counting,
 * 											Set OC0 on compare match when down counting.
 * 				 		  INVERTED 	   -->> Set OC0 on compare match when up counting,
 * 											Clear OC0 on compare match when down counting.
 */
/*Compare Match Output Options for all timers*/
typedef enum
{
	OC_DISCONNECTED = 0,
	TOG_OC,
	CLR_OC,
	SET_OC,
	NON_INVERTED_PWM,
	INVERTED_PWM,
	DO_NOT_CHANGE
}
TIMERS_OC_MODE_t;

/*Structure to carry configuration data for timer 0 and timer 2 only*/
typedef struct
{
	uint8 ClkSelect;
	TIMER0_2_WGM_t WGM;
	TIMERS_OC_MODE_t OCMode;
}
TIMER0_2_CFG_t;

/*Structure to carry configuration data for timer 1 only*/
typedef struct
{
	uint8 ClkSelect;
	TIMER1_WGM_t WGM;
	TIMERS_OC_MODE_t OCAMode;
	TIMERS_OC_MODE_t OCBMode;
}
TIMER1_CFG_t;


/*ClkSelect Options for each timer*/
#define TIMER0_u8NO_CLK_SRC				0u
#define TIMER0_u8SYS_CLK_BY_1			1u
#define TIMER0_u8SYS_CLK_BY_8			2u
#define TIMER0_u8SYS_CLK_BY_64			3u
#define TIMER0_u8SYS_CLK_BY_256			4u
#define TIMER0_u8SYS_CLK_BY_1024		5u
#define TIMER0_u8EXT_CLK_FALLING		6u
#define TIMER0_u8EXT_CLK_RISING			7u

#define TIMER1_u8NO_CLK_SRC				0u
#define TIMER1_u8SYS_CLK_BY_1			1u
#define TIMER1_u8SYS_CLK_BY_8			2u
#define TIMER1_u8SYS_CLK_BY_64			3u
#define TIMER1_u8SYS_CLK_BY_256			4u
#define TIMER1_u8SYS_CLK_BY_1024		5u
#define TIMER1_u8EXT_CLK_FALLING		6u
#define TIMER1_u8EXT_CLK_RISING			7u

#define TIMER2_u8NO_CLK_SRC				0u
#define TIMER2_u8SYS_CLK_BY_1			1u
#define TIMER2_u8SYS_CLK_BY_8			2u
#define TIMER2_u8SYS_CLK_BY_32			3u
#define TIMER2_u8SYS_CLK_BY_64			4u
#define TIMER2_u8SYS_CLK_BY_128			5u
#define TIMER2_u8SYS_CLK_BY_256			6u
#define TIMER2_u8SYS_CLK_BY_1024		7u


/*Enum to configure the interrupt source of the function TIMERS_u8SetCallBack*/
typedef enum
{
	TIMER0_OVF = 0,
	TIMER0_COMP,
	TIMER1_OVF,
	TIMER1_COMPA,
	TIMER1_COMPB,
	TIMER1_CAPT,
	TIMER2_OVF,
	TIMER2_COMP
}
TIMERS_Int_Src_t;

typedef enum
{
	TIMER0,
	TIMER1,
	TIMER2
}
TIMERS_NUM;

#define TIMER1_u8ICU_RISING_EDGE	0u
#define TIMER1_u8ICU_FALLING_EDGE	1u

uint8 TIMER0_u8Init(const TIMER0_2_CFG_t *Copy_pstTimerConfig);
uint8 TIMER1_u8Init(const TIMER1_CFG_t *Copy_pstTimerConfig);
uint8 TIMER2_u8Init(const TIMER0_2_CFG_t *Copy_pstTimerConfig);

uint8 TIMER0_u8SetCompOutMode(const TIMER0_2_CFG_t *Copy_pstTimerConfig, TIMERS_OC_MODE_t Copy_u8Mode);
uint8 TIMER1_u8SetCompOutModeChA(const TIMER1_CFG_t *Copy_pstTimerConfig, TIMERS_OC_MODE_t Copy_u8Mode);
uint8 TIMER1_u8SetCompOutModeChB(const TIMER1_CFG_t *Copy_pstTimerConfig, TIMERS_OC_MODE_t Copy_u8Mode);
uint8 TIMER2_u8SetCompOutMode(const TIMER0_2_CFG_t *Copy_pstTimerConfig, TIMERS_OC_MODE_t Copy_u8Mode);

uint8 TIMERS_u8IntEnable(TIMERS_Int_Src_t Copy_u8TimerInt);
uint8 TIMERS_u8IntDisable(TIMERS_Int_Src_t Copy_u8TimerInt);

uint8 TIMERS_u8Disable(TIMERS_NUM Copy_u8Timer);

uint8 TIMERS_u8SetCallBack(TIMERS_Int_Src_t Copy_u8TimerIntSource, void (* Copy_pvCallBackFunc)(void));

void TIMER0_voidSetCompValue(uint8 Copy_u8Value);
void TIMER0_voidSetOvfValue(uint8 Copy_u8Value);
uint8 TIMER0_u8GetTimerValue(void);

void TIMER2_voidSetCompValue(uint8 Copy_u8Value);
void TIMER2_voidSetOvfValue(uint8 Copy_u8Value);
uint8 TIMER2_u8GetTimerValue(void);

void TIMER1_voidSetCompValueChA(uint16 Copy_u16Value);
void TIMER1_voidSetCompValueChB(uint16 Copy_u16Value);
void TIMER1_voidSetOvfValue(uint16 Copy_u16Value);
void TIMER1_voidSetInputCaptValue(uint16 Copy_u16Value);
uint16 TIMER1_u16GetTimerValue(void);
uint16 TIMER1_u16GetInputCaptValue(void);
uint8 TIMER1_u8SetInputCaptTriggerSrc(uint8 Copy_u8TriggerSrc);

void WDT_voidEnable(void);
void WDT_voidDisable(void);
uint8 WDT_u8SetTime(uint8 Copy_u8WatchDogTime);

#endif
