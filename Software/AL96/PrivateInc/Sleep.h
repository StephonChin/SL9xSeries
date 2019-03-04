/********************************************************************************
 *
 * FILE NAME			Sleep.h
 *
*********************************************************************************/
#ifndef __SLEEP_H__
#define __SLEEP_H__

//--------------------------< Include Files >-----------------------------------//
#include "Type_Def.h"
#include "Display_Ctrl.h"
#include "BT_Control.h"
#include "Timer_Ctrl.h"


//--------------------------< Exported Functions >------------------------------//
void Sleep_Control(void);

//---------------------------< Exported Parameters >----------------------------//
extern _Flag		SleepFlag;
extern _Flag		SleepKeyFlag;

#endif
