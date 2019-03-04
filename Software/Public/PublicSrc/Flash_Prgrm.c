/*******************************************************************************
	*
	* @FileName			Flash_Prgrm.c
	* @Date					2017.12.07
	* @Author				DS.Chin
	* @Description	Save/Read the mode, color, timer, checksum to/from LDROM
	*
*******************************************************************************/
#include "Flash_Prgrm.h"


/* Gloable Parameters ---------------------------------------------------*/
_Flag				FlashSaveFlag;




/*
 * FunctionName		Flash_Write_Data
 */
void Flash_Write_Data(void)
{
	_Uint32		AddStart = FMC_LDROM_BASE;
	
	if (FlashSaveFlag == TRUE)
	{
		FlashSaveFlag = FALSE;
		
		SYS_UnlockReg();

		FMC_Open();
		
		FMC_ENABLE_LD_UPDATE();
		
		FMC_Erase(AddStart);
		FMC_Write(AddStart, (_Uint32)DisplayData.ModeBuf);
		AddStart += 4;
		FMC_Write(AddStart, (_Uint32)DisplayData.ColorValue);
		AddStart += 4;
		FMC_Write(AddStart, (_Uint32)TimerData.CntDwnHour);
		AddStart += 4;
		FMC_Write(AddStart, (_Uint32)DirectFlag);
		AddStart += 4;
		FMC_Write(AddStart, (_Uint32)HorseOrder);
		AddStart += 4;
		FMC_Write(AddStart, (_Uint32)HorseTotal);
		AddStart += 4;
		FMC_Write(AddStart, (_Uint32)ChkSumRstSave);
		AddStart += 4;
		FMC_Write(AddStart, (_Uint32)ChkSumH);
		AddStart += 4;
		FMC_Write(AddStart, (_Uint32)ChkSumL);
		AddStart += 4;
		FMC_Write(AddStart, (_Uint32)PowerOnNum);
		
		uint8_t i = 0;
		for (i = 0; i < CUSTOM_MAX; i++)
		{
			AddStart += 4;
			FMC_Write(AddStart, (_Uint32)CustomData[i].EnFlag);
			AddStart += 4;
			FMC_Write(AddStart, (_Uint32)CustomData[i].Mode);
			AddStart += 4;
			FMC_Write(AddStart, (_Uint32)CustomData[i].Color);
		}
    
    #if _AL94_24V3_ | _AL94_24V6_
      AddStart += 4;
      FMC_Write(AddStart, (_Uint32)HorseInfo.Grp);
	  AddStart += 4;
	  FMC_Write(AddStart, (_Uint32)HorseInfo.Len);
	  AddStart += 4;
	  FMC_Write(AddStart, (_Uint32)HorseInfo.AllLedCnt);
	  AddStart += 4;
	  FMC_Write(AddStart, (_Uint32)HorseInfo.PreLedCnt);

    #endif
		
		SYS_LockReg();
	}
}


/*
 * FunctionName		Flash_Read_Data
 */
void Flash_Read_Data(void)
{
	_Uint32			AddStart = FMC_LDROM_BASE;

	SYS_UnlockReg();

	FMC_Open();

	FMC_ENABLE_LD_UPDATE();

	DisplayData.ModeBuf 	= (_Uint8)FMC_Read(AddStart);
	AddStart += 4;
	DisplayData.ColorValue 	= (_Uint8)FMC_Read(AddStart);
	AddStart += 4;
	TimerData.CntDwnHour 	= (_Uint8)FMC_Read(AddStart);
	AddStart += 4;
	DirectFlag 				= (_Uint8)FMC_Read(AddStart);
	AddStart += 4;
	HorseOrder 				= (_Uint8)FMC_Read(AddStart);
	AddStart += 4;
	HorseTotal 				= (_Uint8)FMC_Read(AddStart);
	AddStart += 4;
	ChkSumRst 				= (_Uint8)FMC_Read(AddStart);
	AddStart += 4;
	ChkSumH 				= (_Uint8)FMC_Read(AddStart);
	AddStart += 4;
	ChkSumL 				= (_Uint8)FMC_Read(AddStart);
	AddStart += 4;
	PowerOnNum 				= (_Uint8)FMC_Read(AddStart);
	
	uint8_t i = 0;
	for (i = 0; i < CUSTOM_MAX; i++)
	{
		AddStart += 4;
		CustomData[i].EnFlag 	= (_Uint8)FMC_Read(AddStart);
		AddStart += 4;
		CustomData[i].Mode 		= (_Uint8)FMC_Read(AddStart);
		AddStart += 4;
		CustomData[i].Color 	= (_Uint8)FMC_Read(AddStart);
	}

#if AL94
	AddStart += 4;
	HorseInfo.Grp			= (_Uint8)FMC_Read(AddStart);
	AddStart += 4;
	HorseInfo.Len			= (_Uint8)FMC_Read(AddStart);
	AddStart += 4;
	HorseInfo.AllLedCnt		= (_Uint16)FMC_Read(AddStart);
	AddStart += 4;
	HorseInfo.PreLedCnt		= (_Uint16)FMC_Read(AddStart);

#endif

	SYS_LockReg();
}






