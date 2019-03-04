/*************************************************************************
 *
 * File Name  CSR1010.c
 *
 * Brief
 *						Communicate withe the bluetooth smart CSR1010
 *            9600 + 1bit stop + no checksum
 *		
 * Tech
 *						FIFO 8bytes -- FD xx xx xx xx xx xx FE
 * 						TOCNTEN = 1, TOIC = 40
 * 
*****************************************************************************/
#include "CSR1010.h"

/* <-------------Gloable Variables-------------------> */
_TypeStructRcv 	RcvData;
_TypeStructSnd 	SndData;
_Flag						RcvFlag;
_Uint8					SynData[5];										/* send synchronization data buffer 		*/
_Uint8					ChkSumReply[4];


/* <-------------File Variables----------------------> */
_Uint8	RcvBuffer[RCV_BYTE_MAX];			/* received data buffer from CSR1010 		*/
_Uint8	RcvByteStatus;








/*******************************************************************************
	*
 	* FunctionName: UART_Clear_Buf
 	*/
void Uart_Clear_Buf(void)
{
	_Uint8 			RcvCnt = 0;
	
	for (RcvCnt = 0; RcvCnt < RCV_BYTE_MAX; RcvCnt++)
	{
		RcvBuffer[RcvCnt] = UART0->DAT;
		if (UART0->FIFOSTS & UART_FIFOSTS_RXEMPTY_Msk)  break;
	}
	
	for (RcvCnt = 0; RcvCnt < RCV_BYTE_MAX; RcvCnt++)
	{
		RcvBuffer[RcvCnt] = 0;
	}
}


/*******************************************************************************
	*
 	* FunctionName: Uart_Rcv_Interrupt
 	*/
void UART0_IRQHandler(void)
{  
	Csr1010_Rcv_Byte();
}



/***********************************************************
	*
	* @FunctionName	Csr1010_Rcv_Byte
	*
****/
static void Csr1010_Rcv_Byte(void)
{
	_Uint8 	RcvCnt = 0;
	
	for (RcvCnt = 0; RcvCnt < RCV_BYTE_MAX; RcvCnt++)
	{
		RcvBuffer[RcvCnt] = UART0->DAT;
		if (UART0->FIFOSTS & UART_FIFOSTS_RXEMPTY_Msk)  break;
	}
	
	switch (RcvCnt)
	{
			/* Power On Command Received : FD F0 FE */
			case 0x2:
			{
				if (RcvBuffer[0] == 0xFD && RcvBuffer[1] == 0xF0 && RcvBuffer[2] == 0xFE)
				{
					RcvByteStatus = RCV_END;
				}
				else
				{
					RcvByteStatus = RCV_ERR;
				}
			} break;
			/* Normal Command Received */
			default:
			{
				if (RcvBuffer[0] == 0xFD && RcvBuffer[7] == 0xFE)
				{
					RcvByteStatus = RCV_END;
				}
				else
				{
					RcvByteStatus = RCV_ERR;
				}
        UART->FIFO |= BIT1;		//RXRST = 1, reset
			} break;
		}
}



/************************************************************
	*
	* @FunctionName	Csr1010_Rcv_Data
	*
****/
void Csr1010_Rcv_Data(void)
{
	 _Uint8		TempCnt = 0;
	
	
	switch(RcvByteStatus)
	{
		/* Exit when receive status is idle or working */
		case RCV_IDLE:
		{
			
		}break;
		
		/* received error */
		case RCV_ERR:
		{
			for (TempCnt = 0; TempCnt < RCV_BYTE_MAX; TempCnt++)		RcvBuffer[TempCnt]	= 0;			// clear the buffer
			RcvByteStatus = RCV_IDLE;																									// clear the status
		} break;
	
		/* received success */
		case RCV_END:
		{
			RcvFlag	= TRUE;
			for (TempCnt = 0; TempCnt < 6; TempCnt++)									// move the buffer to rcvdata
			{
				RcvData.DataBuf[TempCnt]	= RcvBuffer[TempCnt + 1];
			}
			for (TempCnt = 0; TempCnt < RCV_BYTE_MAX; TempCnt++)
			{
				RcvBuffer[TempCnt] = 0;
			}
			RcvByteStatus = RCV_IDLE;																	// clear status
		} break;
	}
}



/***********************************************************
	*
	* @FunctionName	Csr1010_Snd_Data
	*
*****/
void Csr1010_Snd_Data(void)
{
	_Uint8	TempCnt = 0;
	
	/* when snd data is idle , exit */
	if (SndData.SndStatus == SND_IDLE)
	{
		return;
	}
	
	
	/* type send LA1 */
	if (SndData.SndStatus == SND_TYPE)
	{
		// Send type command "LA1"
		Csr1010_Snd_Byte(0xFC);
		Csr1010_Snd_Byte(DEVICE_NAME_ONE);
		Csr1010_Snd_Byte(DEVICE_NAME_TWO);
		Csr1010_Snd_Byte(DEVICE_NUM);
		for (TempCnt = 0; TempCnt < 4; TempCnt++)
		{
			Csr1010_Snd_Byte(ChkSumReply[TempCnt]);
		}
		Csr1010_Snd_Byte(0xFE);
		
		// Send power on command after type command sent completed
		SndData.SndStatus = SND_NORMAL;	
		return;
	}
	
	/* Send syn single */
	if (SndData.SndStatus == SND_HORSE)
	{
		SndData.SndStatus = SND_IDLE;
		Csr1010_Snd_Byte(0xFA);
		Csr1010_Snd_Byte(0x00);
		Csr1010_Snd_Byte(0x00);
		Csr1010_Snd_Byte(0x0e);
		for (TempCnt = 0; TempCnt < 5; TempCnt++)		Csr1010_Snd_Byte(SynData[TempCnt]);
		Csr1010_Snd_Byte(0xFE);
		return;
	}
	
	
	/* Send syn single */
	if (SndData.SndStatus == SND_SYN)
	{
		SndData.SndStatus = SND_IDLE;
		Csr1010_Snd_Byte(0xFA);
		Csr1010_Snd_Byte(0x00);
		Csr1010_Snd_Byte(0x00);
		Csr1010_Snd_Byte(0x0f);
		for (TempCnt = 0; TempCnt < 5; TempCnt++)		Csr1010_Snd_Byte(SynData[TempCnt]);
		Csr1010_Snd_Byte(0xFE);
		return;
	}
	
	
	/* Send normally */
	if (SndData.SndStatus == SND_NORMAL)
	{
		Csr1010_Snd_Byte(0xFD);
		for (TempCnt = 0; TempCnt < 8; TempCnt++)		Csr1010_Snd_Byte(SndData.DataBuf[TempCnt]);
		Csr1010_Snd_Byte(0xFE);
		SndData.SndStatus = SND_IDLE;
	}
}



/******************************************************
	*
	* @Function Name	Csr1010_Snd_Byte
	*
****/
static void Csr1010_Snd_Byte(_Uint8 SndBuf)
{
	UART_WRITE(UART0, SndBuf);
}




