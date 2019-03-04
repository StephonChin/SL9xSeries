/****************************************************************************
 *
 * FunctionName		Key.c
 *
 * Brief
 *								Get the key status
 *
*****************************************************************************/
#include "Key.h"


/*------------------------< Gloable Parameters >------------------------*/
_EnKey KeyStatus;
_Flag		RstFlag;


/*
 * FunctionName		Key_Scan
 */
void Key_Scan(void)
{
	static _Flag			KeyDoneFlag;
	static _Uint8			KeyTime;
	static _Uint8			RstTime;
	static _Flag			RstDoneFlag;
	
	if (PORT_KEY == RESET)
	{
		SleepKeyFlag = FALSE;
		if (KeyDoneFlag == FALSE)
		{
			KeyTime++;
			if (KeyTime > 70)
			{
				KeyDoneFlag = TRUE;
				KeyStatus = KEY_LONG;
			}
		}
		
		if (RstDoneFlag == FALSE)
		{
			RstTime++;
			if (RstTime >= 250)
			{
				RstTime = 0;
				RstDoneFlag = TRUE;
				RstFlag = TRUE;
			}
		}
	}
	
	else
	{
		RstTime = 0;
		RstDoneFlag = FALSE;
		if (KeyDoneFlag == FALSE && KeyTime > 1)
		{
			KeyStatus = KEY_SHORT;
		}
		KeyTime = 0;
		KeyDoneFlag = FALSE;
		SleepKeyFlag = TRUE;
	}
}
