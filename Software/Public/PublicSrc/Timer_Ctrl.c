/*************************************************************
	*
	* @FileName			Timer_Ctrl.c
	* @Date					2017.03.17
	* @Author				DS.Chin
	* @Description	Timer through 24 hours
	*
**************************************************************/
#include "Timer_Ctrl.h"



//every TIMER_OFFSET millisecond
#if _AL91A_
	#if _AL91_48_
	#define		TIMER_OFFSET	13600
	
	#else
	#define		TIMER_OFFSET	8760
	
	#endif
	
#elif _AL91B_
	#if _AL91_48_
	#define		TIMER_OFFSET	11300
	
	#else
	#define		TIMER_OFFSET	13600
	
	#endif
	
#elif _AL92A_
#define		TIMER_OFFSET	11500

#elif _AL94_24V3_
#define		TIMER_OFFSET	12300

#elif _AL94_24V6_
#define		TIMER_OFFSET	11750

#elif _AL95_
#define		TIMER_OFFSET	26500

#elif _AL99B_
#define		TIMER_OFFSET	14400

#endif



/* @Brief Gloable Variables */
_TypeStructTime		TimerData;

//_Flag	SecondFlag;


///*****************************************************
// *
// * FunctionName		TMR1_IRQHandler
// * Brief				Timer1 interrupt every 1 second
// *
//******************************************************/
//void TMR1_IRQHandler(void)
//{
//	// Clear interrupt flag
//	TIMER_ClearIntFlag(TIMER1);
//	
//	if (TimerData.CntDwnHour != 0)
//	{
//		SecondFlag = TRUE;
//	}
//}

/*****************************************************
	*
	* @FunctionName		Count_Down_Control
	*
*****/
void Count_Down_Control(void)
{
	_Uint32	TimerRegBuf = 0;
	static _Uint16 TimerChk;
	
	/* if count down hour equals 0, then exit this function */
	if (TimerData.CntDwnHour == 0)			
	{
		TimerRegBuf = TIMER1->CTL;
		if ((TimerRegBuf & (1 << 25)) == (1 << 25))
		{
			TIMER1->CTL &= ~(1 << 26);			//Reset timer1
			TIMER_ClearIntFlag(TIMER1);		//Clear flag
		}
		return;
	}
	
	
	/* if count down hour unequals 0, then start the time */
	// Initial the real time
	if (TimerData.InitFlag == TRUE)
	{
		TimerData.InitFlag = FALSE;
		TimerData.RealTime.MicroSec		= 0;
		TimerData.RealTime.Second			= 0;
		TimerData.RealTime.Minute			= 0;
		TimerData.RealTime.Hour				= 0;
		TimerChk = 0;
		TIMER_Start(TIMER1);
		TIMER_ClearIntFlag(TIMER1);		//Clear flag
	}
	
	
	/* Real Time */
	if (TIMER_GetIntFlag(TIMER1))
	{
		TIMER_ClearIntFlag(TIMER1);
		TimerChk++;
		if (TimerChk >= TIMER_OFFSET)
		{
			TimerChk = 0;
			return;
		}
		TimerData.RealTime.Second++;
		
		if (TimerData.RealTime.Second >= 60)		// 1minute
		{
			TimerData.RealTime.Second		= 0;
			TimerData.RealTime.Minute ++;
			if (TimerData.RealTime.Minute >= 60)	// 1hour
			{
				TimerData.RealTime.Minute	= 0;
				TimerData.RealTime.Hour	++;
				if (TimerData.RealTime.Hour >= 24)	// 1day
				{
					TimerData.RealTime.Hour	= 0;
				}
			}
		}

		
		
		/* Get the timer hour status */
		if (TimerData.RealTime.MicroSec		== 0
			&&TimerData.RealTime.Second			== 0
			&&TimerData.RealTime.Minute			== 0
			&&TimerData.RealTime.Hour				== 0)
		{
			TimerData.Status		= TIM_OPEN;
			TimerData.OnOffFlag	= TRUE;
		}
		
		else
		if (TimerData.RealTime.MicroSec		== 0
			&&TimerData.RealTime.Second			== 0
			&&TimerData.RealTime.Minute			== 0
			&&TimerData.RealTime.Hour				== TimerData.CntDwnHour)
		{
			TimerData.Status		= TIM_CLOSE;
			TimerData.OnOffFlag = FALSE;
		}
	}
}










