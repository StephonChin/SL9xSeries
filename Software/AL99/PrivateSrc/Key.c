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


/*
 * FunctionName		Key_Scan
 */
void Key_Scan(void)
{
	static _Flag			KeyDoneFlag;
	static _Uint8			KeyTime;
	
	if (PORT_KEY == RESET)
	{
		if (KeyDoneFlag == FALSE)
		{
			KeyTime++;
			if (KeyTime > 70)
			{
				KeyDoneFlag = TRUE;
				KeyStatus = KEY_LONG;
			}
		}
	}
	
	else
	{
		if (KeyDoneFlag == FALSE && KeyTime > 1)
		{
			KeyStatus = KEY_SHORT;
		}
		KeyTime = 0;
		KeyDoneFlag = FALSE;
	}
}
