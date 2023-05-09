/*********************************************************************************/
/*********************************************************************************/
/**********************			Author: Ibrahim Tarek		**********************/
/**********************			File: CLCD_interface.h		**********************/
/**********************			Version: 1.00				**********************/
/*********************************************************************************/
/*********************************************************************************/

#ifndef CLCD_INTERFACE_H_
#define CLCD_INTERFACE_H_

/**
 * @brief Function to send command order to the lcd
 * @param Copy_u8Cmd Parameter which take the number of the command as 1 byte
 */
void CLCD_voidSendCmd(uint8 Copy_u8Cmd);

/**
 * @brief Function to send data to the lcd
 * @param Copy_c8Data Parameter which take 1 byte data to be set
 */
void CLCD_voidSendData(char Copy_c8Data);

/**
 * @brief Function to send string to be printed on the lcd
 * @param Copy_ch8String Pointer to the string which needed to be printed
 * @return Error State
 */
uint8 CLCD_u8SendString(const char *Copy_ch8String);

void CLCD_voidSendDecimalNumber(sint32 Copy_s32Number);

void CLCD_voidSendBinaryNumber(sint16 Copy_s32Number);

void CLCD_voidSendHexaNumber(sint32 Copy_s32Number);

void CLCD_voidSendSpecialCharacter(uint8 *Copy_pu8Pattern, uint8 Copy_u8PatternNum, uint8 Copy_u8XPos, uint8 Copy_u8YPos);

void CLCD_voidInit(void);

void CLCD_voidClearDisplay(void);

uint8 CLCD_u8GoToXY(uint8 Copy_u8XPos, uint8 Copy_u8YPos);

#endif
