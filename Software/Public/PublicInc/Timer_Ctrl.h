/**************************************************************
	*
	* @FileName	Timer_Ctrl.h
	* 
***************************************************************/
#ifndef __TIMER_CTRL_H__
#define __TIMER_CTRL_H__


/* @Brief Include Files */
#include "Type_Def.h"



/* @Brief Type Defines */
typedef struct _TIMER_TYPE
{
	enum	_TIMER_STATUS
	{
		TIM_IDLE,
		TIM_OPEN,
		TIM_CLOSE
	}Status;
	struct _REAL_TIME
	{
		_Uint8	MicroSec;
		_Uint8	Second;
		_Uint8	Minute;
		_Uint8	Hour;
	}RealTime;
	_Flag			InitFlag;
	_Uint8		CntDwnHour;
	_Flag			OnOffFlag;			/* = TRUE : at on period, = FALSE : at off period */
}_TypeStructTime;



/* @Brief Exported Functions */
void Count_Down_Control(void);


/*@Brief Exprted Variables */
extern _TypeStructTime		TimerData;


#endif
