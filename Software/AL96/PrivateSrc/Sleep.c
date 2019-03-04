/*********************************************************************
	*
	* FILE NAME		Sleep.c
	*
**********************************************************************/
#include "Sleep.h"


//-------------------------< Gloable Parameters >-------------------------------//
_Flag		SleepFlag;
_Flag		SleepKeyFlag;

_Uint8		SleepTime;

/**
	* FunctionName		Sleep_Control
	*/
void Sleep_Control(void)
{
	if ((DisplayData.Mode != 0) || (SleepFlag == FALSE) || SleepKeyFlag == FALSE)
	{
			SleepTime = 0;
			return;
	}
	
	
	SleepTime++;
	
	if (SleepTime == 3)
	{
		BtConStatus = BT_POWER_OFF;
		BtPowerInitFlag = TRUE;
	}
	else if (SleepTime > 5)
	{
		SleepTime = 0;
		
		P1->INTSRC |= GP_PIN_PIN5_Msk;
		GPIO_EnableInt(P1, 5, GPIO_INT_FALLING);
		
		SYS_UnlockReg();
		CLK_PowerDown();
		SYS_LockReg();
		
		if (SleepFlag == FALSE)				//Only Trigged by key
		{
			BtConStatus = BT_POWER_ON;
			BtPowerInitFlag = TRUE;
		}
		
		TimerData.InitFlag = TRUE;		//Reset the timer data
	}
}



/**
	* FunctionName		GPIO01_IRQnHandler
	*/
void GPIO01_IRQHandler(void)
{
	P1->INTSRC |= GP_PIN_PIN5_Msk;
	GPIO_DisableInt(P1, 5);
	
	SleepFlag = FALSE;
}



