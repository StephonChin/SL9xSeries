/*******************************************************************************
	*
	* @FileName			Flash_Prgrm.h
	* @Date					2017.12.07
	* @Author				DS.Chin
	* @Description	Save/Read the mode, color, timer, checksum to/from LDROM
	*
*******************************************************************************/
#ifndef __FLASH_PRGRM_H__
#define __FLASH_PRGRM_H__


/* Include files--------------------------------------------------------------*/
#include "Type_Def.h"
#include "Display_Ctrl.h"
#include "Timer_Ctrl.h"
#include "Data_Process.h"


/* Exported Functions --------------------------------------------------------*/
void Flash_Read_Data(void);
void Flash_Write_Data(void);



/* Exported Parameters -------------------------------------------------------*/
extern _Flag				FlashSaveFlag;



#endif

