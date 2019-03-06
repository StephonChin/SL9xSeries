/*********************************************************
	*
	* FILE NAME			BT_Control.c
	* BRIEF					Control the bluetooth power
	*
**********************************************************/
#include "BT_Control.h"



//------------------------< Gloable Parameters >-----------------------------//
_TypeBtCon	BtConStatus;
_Flag		BtRcvDataFlag;
_Flag		BtPowerInitFlag;
_Flag 		BtPowerDetFlag = FALSE;


/**
	* FunctionName		Bt_Work_Detect
	*/
void BT_Work_Detect(void)
{
	static _Uint16		PIO11_HighTime;
	static _Uint16		PIO11_LowTime;
//	static _Uint16		BtRcvDataTime;
	
	//Control the BT power
	BT_Power_Control();
	
	//Detect the PWM signal after received the command "FD F0 FE"
	if (!BtPowerDetFlag)
	{
		PIO11_HighTime = 0;
		PIO11_LowTime = 0;
		return;
	}
	
	// Detect the PIO11:it should be ouput PWM wave
	// 6s H + 6sL
	if (PORT_BT_DT == SET)
	{
		PIO11_LowTime = 0;

		PIO11_HighTime++;
		if (PIO11_HighTime >= 500)			//20ms * 500 = 10s
		{	
			PIO11_HighTime  = 0;
			BtConStatus 	= BT_RESTART;
			BtPowerInitFlag = TRUE;
		}
	}
	else
	{
		PIO11_HighTime = 0;
		
		PIO11_LowTime++;
		if (PIO11_LowTime >= 500)			//20ms * 500 = 10s
		{	
			PIO11_LowTime = 0;

			BtConStatus 	= BT_RESTART;
			BtPowerInitFlag = TRUE;
		}
	}
	
//	// if the bluetooth haven't receive command without 1hour, restart it.
//	if (BtRcvDataFlag == TRUE)
//	{
//		BtRcvDataFlag = FALSE;
//		BtRcvDataTime = 0;
//	}
//	
//	BtRcvDataTime++;
//	if (BtRcvDataTime >= 15000)	//20 * 15000 = 5minute
//	{
//		BtRcvDataTime = 0;
//		BtConStatus 	= BT_RESTART;
//		BtPowerInitFlag = TRUE;
//	}
}




/************************************************************
	*
	* @FunctonName	BT_Power_Control
	* @Brief		Control the power of bluetooth
	* 							
	*/
static void BT_Power_Control(void)
{
	static _Uint8		BtTime;
	
	switch (BtConStatus)
	{
		case BT_IDLE:		break;
		
		case BT_POWER_ON:
		{
			if (BtPowerInitFlag == TRUE)
			{
				BtPowerInitFlag = FALSE;
				BtTime = 0;
				GPIO_SetMode(P1, GP_PIN_PIN2_Msk | GP_PIN_PIN3_Msk, GPIO_MODE_INPUT);
				
			#if AL91 | AL92
				PORT_BT_CE = RESET;
			#else
				PORT_BT_CE = SET;
			#endif
			}
			
			BtTime++;
			if (BtTime > 20)
			{
				BtTime = 0;
				BtConStatus = BT_IDLE;
				SYS->P1_MFP &= ~(SYS_MFP_P12_Msk | SYS_MFP_P13_Msk);
				SYS->P1_MFP |= (SYS_MFP_P12_UART0_RXD | SYS_MFP_P13_UART0_TXD);
			}
		} break;
		
		case BT_POWER_OFF:
		{
				BtPowerInitFlag = FALSE;
				BtTime = 0;
			#if AL91 | AL92 | AL_CURTAIN
				PORT_BT_CE = SET;
			#else
				PORT_BT_CE = RESET;
			#endif
				BtConStatus = BT_IDLE;
				SYS->P1_MFP &= ~(SYS_MFP_P12_Msk | SYS_MFP_P13_Msk);
				SYS->P1_MFP |= (SYS_MFP_P12_GPIO | SYS_MFP_P13_GPIO);
				PORT_RX = RESET;
				PORT_TX = RESET;
		} break;
		
		
		case BT_RESTART:
		{
			if (BtPowerInitFlag == TRUE)
			{
				BtPowerInitFlag = FALSE;
				BtTime = 0;
			#if AL91 | AL92 | AL_CURTAIN
				PORT_BT_CE = SET;
			#else
				PORT_BT_CE = RESET;
			#endif
				SYS->P1_MFP &= ~(SYS_MFP_P12_Msk | SYS_MFP_P13_Msk);
				SYS->P1_MFP |= (SYS_MFP_P12_GPIO | SYS_MFP_P13_GPIO);
				PORT_RX = RESET;
				PORT_TX = RESET;
			}
			
			BtTime++;
			if (BtTime > 5)
			{
				BtTime = 0;
				BtConStatus = BT_POWER_ON;
				BtPowerInitFlag = TRUE;
			}
		} break;
	}
}




