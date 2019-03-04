/**********************************************************************************
	*
	* FUNCTION NAME				ShowHomeApp.proj
	* AUTHOR							DS.Chin
	* COPYRIGHT						(C) CopyRight  @2017 ~ 2027 Willis Ltd. Co.
	*
	
	VERSION	0.0.0	
	* Protocol Version		1.8
	*	Date								2017.12.07
	
	VERSION	0.1.0	
	* Protocol Version		1.8
	*	Date								2017.12.11
	* Brief								New UART receive method
	
	VERSION	0.1.1	
	* Protocol Version		1.8
	*	Date								2017.12.12
	* Brief								
	*											Synchronize mode update
	*											  >> Add the flag HorseSynFlag in order to distinguishes the 
	*													 command from APP or MCU
	*											Modify the mode ROLL, RIPPLE, FLOWER BLOOM to better display
	
	VERSION	0.1.2	
	* Protocol Version		1.9
	*	Date								2017.12.21
	* Brief								
	*											AL94 R<->G
	*											AL94 Led_Class modify
	*											AL95 AL96 PWM modify
	*											AL94 AL96 add key function
	*											Modify the AL91 & AL94 mode: instead, roll, ripple... (which need syn)
	*											Add the WDT
	
	
	VERSION 0.2.0
	* Protocol Version		1.9
	* Date								2018.03.10
	* Brief
	*											AL96 Low Power Shut down
	*											MCU control the BT power when there is no single with 1 hour
	*											or CSR1010 haven't output the PWM with 10 seconds
	*
************************************************************************************/
#include "ShowHomeApp.h"

	
/************************************************************************************
	*
	* FunctionName	main
	*
	* Brief					The Programme entrance
	*
*************************************************************************************/
int main(void)
{
	/* If the MCU reset by WDT,
	 *  then set the flag WdtRstFlag, else reset the flag WdtRstFlag,
	 */
	if ((WDT->CTL & WDT_CTL_RSTF_Msk) == WDT_CTL_RSTF_Msk)
	{
		WdtRstFlag = TRUE;
	}
	else
	{
		WdtRstFlag = FALSE;
	}
	
	/* Initialize the MCU peripheral */
	MCU_Config();

	/* Read the Mode, Coor & Timer after Power On */
	User_Data_Init();

	/* Clear the UART0 receive FIFO */
	Uart_Clear_Buf();

	while (1)
	{
		if (TIMER_GetIntFlag(TIMER0))
		{
			TIMER_ClearIntFlag(TIMER0);
			
			// Clear the WDT count number
			SYS_UnlockReg();
			WDT->CTL &= WDT_CTL_RSTCNT_Msk;			//Clear WDT Cnt
			SYS_LockReg();
			

			#if AL99 | AL94 | AL96
			Key_Scan();
			#endif
			
			Data_Process();
      
      Csr1010_Rcv_Data();
			
			Csr1010_Snd_Data();
			
			Led_Display();
			
			Led_Update();
			
			Count_Down_Control();	
			
			Flash_Write_Data();
			
			BT_Work_Detect();
			
			#if AL96
			Sleep_Control();
			#endif
		}
	}
}


