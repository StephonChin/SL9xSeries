/*******************************************************************************
	*
	* FILE NAME
	*			Data_Process.c
	*
	* NODE
	*			About horse run mode
	*			if the mode is run mode, ripple mode, flower bloom mode, polar light mode, color show mode,
	*			only AL91 or AL94 have horse function.
	*
	*			if the mode is show1, show2, or show3
	*			all the product have horse function.
	*
*******************************************************************************/
#include "Data_Process.h"

//----------------------------------------------------------------------------
// Gloable Parameters
//----------------------------------------------------------------------------
_Flag					SynFlag;
_Uint8					ChkSumH;
_Uint8					ChkSumL;
_Uint8					ChkSumRst;
_Uint8					ChkSumRstSave;
_Uint8					PowerOnNum;
_Flag					WdtRstFlag;
TypeCustomT				CustomData[CUSTOM_MAX];

//----------------------------------------------------------------------------
// File Parameters
//----------------------------------------------------------------------------
_Uint8					NewChkSumH;
_Uint8					NewChkSumL;
_Uint8					ChkSumRstTime;
_Flag					PasswordFlag;				//Allow set the password flag
_Flag					SynRcvFlag;
_Uint8					FlagChkTime;
_Flag					FlagChkFlag;

/******************************************************************************
	*
	* COLOR_TABLE
	*
	* DESCRIPTION
	*								Color value combine with R value, G value and B value,
	*								or  with R value, G value , B value and W value
	*
*******************************************************************************/
#if !(COLOR_RGBW | COLOR_RGB)
	#error "Haven't define the theme COLOR_RGBW | COLOR_RGB !"

#elif COLOR_RGBW
const _Uint8 COLOR_VECTOR[18][4] =
{
    250,0,0,0,      		//0x00:	red
    0,250,0,0,      		//0x01:	green
    0,0,250,0,      		//0x02:	blue
    250,50,0,0,     		//0x03:	orange
    250,50,100,0,   		//0x04:	pink
    0,250,50,0,     		//0x05:	spring green
    250,150,0,0,    		//0x06:	gold
    250,0,50,0,     		//0x07:	peach
    150,250,0,0,    		//0x08:	lawn green
    250,0,250,0,    		//0x09:	cyan
    0,250,250,0,    		//0x0A:	sky blue
    250,250,0,0,    		//0x0B:	yellow
    100,0,250,0,     		//0x0C:	purple
	0,0,0,250,			    //0x0D:	pure white
    50,50,100,250,  		//0x0E: cold white
	100,100,0,250,		    //0x0F:	warm white
	0,150,0,0,			    //0x10: dark green
	50,0,250,0			    //0x11: dark purple
};

#elif COLOR_RGB
const _Uint8 COLOR_VECTOR[18][3] =
{
	#if AL94
    250,0,0,      		//0:red
    0,250,0,      		//1:green
    0,0,250,      		//2:blue
    250,50,0,     		//3:orange
    250,50,100,   		//4:pink
    0,250,50,     		//5:spring green
    250,150,0,    		//6:gold
    250,0,50,     		//7:peach
    100,200,0,    		//8:lawn green
    250,0,250,    		//9:Cyan
    0,250,250,    		//a:sky blue
    250,250,0,    		//b:yellow
    100,0,250,     		//c:purple
    200,250,200,
    150,250,250,
    250,250,50,
    0,150,0,			// dark green
    50,0,250,			// DARK_RED
  
  #elif AL91
    250,0,0,      		//0:red
    0,250,0,      		//1:green
    0,0,250,      		//2:blue
    250,25,0,     		//3:orange
    250,25,75,   		  //4:pink
    0,250,50,     		//5:spring green
    250,100,0,    		//6:gold
    250,0,50,     		//7:peach
    150,200,0,    		//8:lawn green
    250,0,250,    		//9:Cyan
    0,250,250,    		//a:sky blue
    250,175,0,    		//b:yellow
    100,0,250,     		//c:purple
    250,175,200,      //white
    200,150,250,      //cold white
    250,150,25,       //warm white
    0,150,0,		// dark green
    50,0,250,			   // DARK_RED
    
	#else
    250,0,0,      		//0:red
    0,250,0,      		//1:green
    0,0,250,      		//2:blue
    250,50,0,     		//3:orange
    250,50,50,   		//4:pink
    0,250,50,     		//5:spring green
    250,150,0,    		//6:gold
    250,0,50,     		//7:peach
    150,250,0,    		//8:lawn green
    250,0,150,    		//9:Cyan
    0,250,250,    		//a:sky blue
    250,250,0,    		//b:yellow
    150,0,250,     		//c:purple

    #if AL99
      200,200,200,		//d:pure white
      100,200,200,  		//e: cold white
      200,200,100,		//f:warm white

    #else
      250,250,250,		//d:pure white
      150,250,250,  		//e: cold white
      250,250,50,			//f:warm white
      
    #endif
    
    0,150,0,			// dark green
    50,0,250,			// DARK_RED
      
	#endif
};

#endif



/************************************************************************************
	*
	* FUNCTION NAME		|	User_Data_Init
	*	INPUT						|	None
	* OUTPUT					|	None
	* BRIEF						|	Initialize the user data after power on, include display
	*										mode, color theme, time count down hour and others
	*
*************************************************************************************/
void User_Data_Init(void)
{	
	/* Readt the data from APPROM */
	Flash_Read_Data();

	//-----------------------------------------------------------------
	// if the first time to power on
	//-----------------------------------------------------------------
	if (PowerOnNum != 0xAA)
	{
		DisplayData.ModeBuf 	= 0xA;
		DisplayData.ColorValue	= 0x1C;
		TimerData.CntDwnHour	= 0;
		ChkSumH					= 0;
		ChkSumL					= 0;
		ChkSumReply[0] 			= '0';
		ChkSumReply[1] 			= '0';
		ChkSumReply[2] 			= '0';
		ChkSumReply[3] 			= '0';
		ChkSumRst				= 0;
		PowerOnNum				= 0xAA;
		ChkSumRstSave			= 0;
		
		uint8_t i = 0;
		for (i = 0; i < CUSTOM_MAX; i++)
		{
			CustomData[i].EnFlag = FALSE;
			CustomData[i].Mode = 0;
			CustomData[i].Color = 0;
		}
    
	#if AL91 | AL94
		HorseOrder				= 0;
		HorseTotal				= 0;
		DirectFlag				= FALSE;
		HorseInfo.Grp			= 0;
		HorseInfo.PreLedCnt		= 0;
		
		#if _AL94_24V6_ | _AL91_48_
		HorseInfo.Len		= 2;
		HorseInfo.LenPre	= 2;
		#else
		HorseInfo.Len		= 1;
		HorseInfo.LenPre	= 1;
		#endif
		
		HorseInfo.AllLedCnt		= LED_TOTAL;
		LedTotal = BASE_LED_TOTAL * (uint16_t)HorseInfo.Len;
	#endif
    
		FlashSaveFlag			= TRUE;

		DisplayData.Mode 		= 0xA;
		DisplayData.InitFlag	= TRUE;
		Color_Value_Get(DisplayData.ColorValue);
		return;
	}

	//-----------------------------------------------------------------
	// Get the mode from eprom after power on
	// When display mode equl 0 (means turn off all leds, then set
	// the mode to 0xA (color show), and save it to eprom
	//-----------------------------------------------------------------
	if (DisplayData.ModeBuf == 0 || DisplayData.ModeBuf > 0xD)
	{
		DisplayData.ModeBuf 	= 0xA;
		FlashSaveFlag			= TRUE;
	}
	DisplayData.Mode			= DisplayData.ModeBuf;
	DisplayData.InitFlag		= TRUE;


	//---------------------------------------------------------------------
	// Get the color value from eprom after power on
	// When the color value is more than the COLOR_MAX, set it to COLOR_MAX
	// and save the value to eprom
	//----------------------------------------------------------------------
	if (DisplayData.ColorValue > COLOR_MAX)
	{
		DisplayData.ColorValue 	= COLOR_MAX;
		FlashSaveFlag			= TRUE;
	}
	Color_Value_Get(DisplayData.ColorValue);


	//----------------------------------------------------------------------
	// Get the count down hour from eprom after power on,
	// if valid value is more than 8 , seit it to 6,
	// and save6 to eprom
	// Set the OnOffFlag
	//----------------------------------------------------------------------
	if (TimerData.CntDwnHour > 12)
	{
		TimerData.CntDwnHour = 0;
		FlashSaveFlag = TRUE;
	}
	TimerData.InitFlag	= TRUE;
	TimerData.OnOffFlag = TRUE;


	/*
	 * Get the custom data value
	 */
	uint8_t i = 0;
	for (i = 0; i < CUSTOM_MAX; i++)
	{
		if (CustomData[i].EnFlag == FALSE)
		{
			CustomData[i].Mode = 0;
		}
		if (CustomData[i].Mode > MODE_MAX)
		{
			CustomData[i].Mode = 1;
			CustomData[i].Color = 0;
		}
	}


	/**
	 *	When the product is AL91A, AL91B, AL91C, AL91D or AL94
	 * Get the direct flag and horse order num and horse total number
	 */
#if AL91 | AL94
  
    //------------------------------------------------------------------------
    // Get the direction flag from ERPOM after power on
    // if the value is more than 0, it's forward directoin
    // if the value equal 0, it's reverse direction
    //------------------------------------------------------------------------
	if (DirectFlag > 0)
	{
		DirectFlag = TRUE;
	}
	else
	{
		DirectFlag = FALSE;
	}

      //------------------------------------------------------------------------
      // if the product has horse run function
      // Read the horse total number and order number
      //------------------------------------------------------------------------
		if (HorseTotal < HorseOrder)
		{
			HorseTotal 		= 0;
			HorseOrder 		= 0;
			FlashSaveFlag 	= TRUE;
		}
	  
		if (HorseInfo.Len > LENGTHEN_TOTAL || HorseInfo.Len == 0)
		{
			#if _AL94_24V6_ | _AL91_48_
			HorseInfo.Len = 2;
			#else
			HorseInfo.Len = 1;
			#endif
			FlashSaveFlag = TRUE;
		}
		LedTotal = (uint16_t)HorseInfo.Len * BASE_LED_TOTAL;
		HorseInfo.LenPre = HorseInfo.Len;

		if (HorseOrder > 0)
		{
			if (HorseInfo.AllLedCnt == 0)
			{
				HorseOrder = 0;
				HorseTotal = 0;
			}		  
		}
#endif  /* #if HORSE_ENABLE */


		//----------------------------------------------------------------------
		// Check the count
		// if power on 3 times in 5 seconds, reset the checksum
		// 1 -> write 0x55
		// 2 -> write 0xAA
		// 3 -> Reset
		//----------------------------------------------------------------------
		if (WdtRstFlag == FALSE)
		{
			if (ChkSumRst == 0)
			{
				ChkSumRstSave 	= 0x55;
				FlashSaveFlag	= TRUE;
			}
			else if (ChkSumRst == 0x55)
			{
				ChkSumRstSave	= 0xAA;
				FlashSaveFlag	= TRUE;
			}
			else if (ChkSumRst == 0xAA)
			{
				ChkSumH			= 0;
				ChkSumL			= 0;
				ChkSumRstSave	= 0;
				ChkSumRst		= 0;
				FlashSaveFlag	= TRUE;

				DisplayData.Mode		= 0xFD;
				DisplayData.InitFlag	= TRUE;
			}
		}

		ChkSumReply[0] = Hex_To_Char(ChkSumH >> 4);
		ChkSumReply[1] = Hex_To_Char(ChkSumH & 0x0F);
		ChkSumReply[2] = Hex_To_Char(ChkSumL >> 4);
		ChkSumReply[3] = Hex_To_Char(ChkSumL & 0x0F);
}



/*************************************************************************************
	*
	* FUNCTION NAME		|	Data_Process
	* INPUT						|	None
	* OUTPUT					|	None
	* DESCRIPTION			|	Process all the data here. change the mode , color, timer or
	*										other parameters after received valid data from CSR1010
	*
***************************************************************************************/
void Data_Process(void)
{
	/* Key Process */
	#if AL99 | AL94
		Key_Process();
	#endif

	/* Timer Process */
	Count_Down_Process();

	/* Password Process */
	Password_Process();

	/* Synchronize Process */
	Syn_Process();

	/* CSR1010 Process */
	CSR1010_Process();
}


/************************************************************
	*
	* @FunctonName	Key_Process
	* @Brief				Process the key
	* 							Change the color and mode after short key
	*/
#if AL99 | AL94
static void Key_Process(void)
{
	if (KeyStatus == KEY_SHORT)
	{
		KeyStatus = KEY_IDLE;

		if (DisplayData.Mode == 0)
		{
			DisplayData.Mode = DisplayData.ModeBuf;
		}
		else
		{
			FlashSaveFlag = TRUE;
			DisplayData.ColorValue++;
			if (DisplayData.ColorValue > 0x6)
			{
				DisplayData.ColorValue = 0;
				DisplayData.ModeBuf++;
				DisplayData.Mode = DisplayData.ModeBuf;
				if (DisplayData.ModeBuf > 0xD)
				{
					DisplayData.ModeBuf = 0xB;
					DisplayData.Mode = 0;
				}
			}
		}

		if (DisplayData.ModeBuf != 0xB && DisplayData.ModeBuf != 0xC && DisplayData.ModeBuf != 0xD)
		{
			DisplayData.ModeBuf = 0xB;
			DisplayData.Mode 	= DisplayData.ModeBuf;
			FlashSaveFlag = TRUE;
		}

		if (DisplayData.ColorValue > 0x6)
		{
			DisplayData.ColorValue = 0x6;
			FlashSaveFlag = TRUE;
		}

		Color_Value_Get(DisplayData.ColorValue);
		DisplayData.InitFlag 	= TRUE;

		return;
	}

	/* Key Long Pressed */
	if (KeyStatus == KEY_LONG)
	{
		KeyStatus = KEY_IDLE;

#if AL94
		#if _AL94_24V3_
		HorseInfo.Len++;
		#else
		HorseInfo.Len += 2;
		#endif
		if (HorseInfo.Len > LENGTHEN_TOTAL)
		{
			DisplayData.Mode = GRN_FLASH;
			#if _AL94_24V3_
			HorseInfo.Len = 1;
			#else
			HorseInfo.Len = 2;
			#endif
		}
		
		LedTotal = (uint16_t)HorseInfo.Len * BASE_LED_TOTAL;
		DisplayData.InitFlag = TRUE;
		FlashSaveFlag = TRUE;
		
		SndData.SndStatus = SND_HORSE;
		SynData[0]	= HorseInfo.Grp;
		SynData[1]	= HorseOrder;
		SynData[2]	= (HorseInfo.LenPre << 4) + HorseInfo.Len;
		SynData[3]	= ChkSumH;
		SynData[4]	= ChkSumL;
		HorseInfo.LenPre = HorseInfo.Len;
#else

		if (DisplayData.Mode != 0)
		{
			DisplayData.Mode 	= 0;
			DisplayData.InitFlag = TRUE;
		}

#endif
	}
  
#if AL94

	if (KeyStatus == KEY_LONG_LONG)
	{
		KeyStatus = KEY_IDLE;
		
		#if _AL94_24V3_
		HorseInfo.Len = 1;
		#else
		HorseInfo.Len = 2;
		#endif
		
		LedTotal = (uint16_t)HorseInfo.Len * BASE_LED_TOTAL;
		DisplayData.Mode = GRN_FLASH;
		DisplayData.InitFlag = TRUE;
		FlashSaveFlag = TRUE; 

		SndData.SndStatus = SND_HORSE;
		SynData[0]	= HorseInfo.Grp;
		SynData[1]	= HorseOrder;
		SynData[2]	= (HorseInfo.LenPre << 4) + HorseInfo.Len;
		SynData[3]	= ChkSumH;
		SynData[4]	= ChkSumL;
		HorseInfo.LenPre = HorseInfo.Len;
	}

	#endif
}
#endif


/************************************************************
	*
	* @FunctonName	Password_Process
	*
*****/
static void Password_Process(void)
{
	static	_Uint8			PasswordTime;

	// Reset checksum time caculate
	if (ChkSumRst != 0)
	{
		ChkSumRstTime++;
		if (ChkSumRstTime >= 250)
		{
			ChkSumRstTime = 0;
			ChkSumRst 		= 0;
			ChkSumRstSave	= 0;
			FlashSaveFlag = TRUE;
		}
	}


	//----------------------------------------------------------------------------------------
	// About Password Set
	//
	// * When received the single that allow set the password, then caculate 5 seconds
	//   if haven't received any password, reset the allow flag
	//-----------------------------------------------------------------------------------------
	if (PasswordFlag)
	{
		PasswordTime++;
		if (PasswordTime >= 250)				PasswordFlag = FALSE;
	}
	else
	{
		PasswordTime = 0;
	}
}


/****************************************************************************
 *
 * @FunctonName	Syn_Process
 * if SynRcvFlag is TRUE(when received synchronize single),
   the next 3 seconds do not allowed to receive the same command

 * if the flag of synchronization is true, send data mode + serias + checksum

 * SynData[2] used for horse mode under AL91 or AL94
 *
******************************************************************************/
static void Syn_Process(void)
{
	static	_Uint8			SynRcvTime	= 0;

	if (SynRcvFlag == TRUE)
	{
		SynFlag = FALSE;
		SynRcvTime++;
		if (SynRcvTime > 150)
		{
			SynRcvTime = 0;
			SynRcvFlag = FALSE;
		}
	}
	else
	{
		SynRcvTime = 0;
		if (SynFlag == TRUE)
		{
			SynFlag				= FALSE;
			ModeSynFlag			= TRUE;					// Set the flag if send the synflag
			SndData.SndStatus 	= SND_SYN;
			SynData[0]			= DisplayData.Mode;
			SynData[1]			= DisplayData.ColorValue;
			#if HORSE_ENABLE
			SynData[2]			= SYN_NUM;
			#else
			SynData[2]			= 0;
			#endif
			SynData[3]			= ChkSumH;
			SynData[4]			= ChkSumL;
		}
	}
}



/************************************************************
	*
	* @FunctonName	Count_Down_Process
	*
*****/
static void Count_Down_Process(void)
{
	/* When TimerData.Status equals TIM_IDLE, exit this function */
	if (TimerData.Status == TIM_IDLE)	return;

	/* Open */
	if (TimerData.Status == TIM_OPEN)
	{
		TimerData.Status		= TIM_IDLE;
		DisplayData.Mode		= DisplayData.ModeBuf;
		DisplayData.InitFlag	= TRUE;
		return;
	}

	/* Close */
	if (TimerData.Status == TIM_CLOSE)
	{
		TimerData.Status		= TIM_IDLE;
		DisplayData.Mode		= 0x0;
		DisplayData.InitFlag	= TRUE;
		return;
	}
}


/****************************************************************************************
	*
	* FUNCTIONNAME		| CSR1010_Process
	*	INPUT			| None
	* OUTPUT			| None
	* DESCRIPTION		| Send data to or received data from CSR1010
	*					| Process the data
	*
*****************************************************************************************/
static void CSR1010_Process(void)
{
	static	_Uint8		TypeReplyTime;
	static 	_Flag       BtInitFlag;         //bluetooth intialization' flag
	static 	_Uint8		FlagBuffer = 0xFF;
	_Uint16				ChkSumBuf = 0;

	/* Initialize the CSR1010's broadcast name after 3 seconds*/
	if (BtInitFlag == FALSE)
	{
		//----------------------------------------------------------------------
		// if device haven't received command FD F0 FE within 1 second after power on,
		// send the type to CSR1010
		//-----------------------------------------------------------------------
		TypeReplyTime++;
		if (TypeReplyTime >= 150)
		{
			BtInitFlag 			= TRUE;
			SndData.SndStatus	= SND_TYPE;
			SndData.DataBuf[0]	= 0x01;
			SndData.DataBuf[1]	= DEVICE_NAME_ONE;
			SndData.DataBuf[2]	= DEVICE_NAME_TWO;
			SndData.DataBuf[3]	= DEVICE_NUM;

		#if AL91 | AL94
			SndData.DataBuf[4]  = HorseOrder;
			SndData.DataBuf[5]  = HorseTotal;
			
		#else
			SndData.DataBuf[4]	= TimerData.CntDwnHour;
			SndData.DataBuf[5]	= 0;
      
		#endif /* #if HORSE_ENABLE */

			SndData.DataBuf[6]	= ChkSumH;
			SndData.DataBuf[7]	= ChkSumL;
		}
	}

	//-----------------------------------------------------------------------
	// if the device haven't received any command within 300ms,
	// clear the flagstatus
	//-----------------------------------------------------------------------
	if (FlagChkFlag)
	{
		FlagChkTime++;
		if (FlagChkTime >= 15)
		{
			FlagChkTime 	= 0;
			FlagBuffer 		= 0xFF;
			FlagChkFlag 	= FALSE;
		}
	}

	// Check the received flag, when it is false, return
	if (RcvFlag == FALSE)		return;


	/* 
	 * Received the command from CSR1010
	 * Clear the received flag
	 */
	RcvFlag 		= FALSE;
	FlagChkFlag		= TRUE;
	FlagChkTime		= 0;
	BtRcvDataFlag	= TRUE;

	// CSR1010 Initialize
	//if (BtInitFlag == FALSE)
	{
		if (RcvData.DataBuf[0] == 0xF0)
		{
			SndData.SndStatus	= SND_TYPE;
			SndData.DataBuf[0]	= 0x01;
			SndData.DataBuf[1]	= DEVICE_NAME_ONE;
			SndData.DataBuf[2]	= DEVICE_NAME_TWO;
			SndData.DataBuf[3]	= DEVICE_NUM;

		#if AL91 | AL94
			SndData.DataBuf[4]  = HorseOrder;
			SndData.DataBuf[5]  = HorseTotal;
			
		#else
			SndData.DataBuf[4]	= TimerData.CntDwnHour;
			SndData.DataBuf[5]	= 0;
      
		#endif /* #if HORSE_ENABLE */

			SndData.DataBuf[6]	= ChkSumH;
			SndData.DataBuf[7]	= ChkSumL;
			return;
		}
	}

	/* CheckSum
	 * if the command is not 0x7(set the password),
	 * check the password if checksum isn't default value 0x0000
	 */
	if ((RcvData.DataBuf[0]& 0x0F) != 0x7 && (RcvData.DataBuf[0]& 0x0F) != 0xB)
	{
		if ((RcvData.DataBuf[4] != ChkSumH) || (RcvData.DataBuf[5] != ChkSumL))
		{
			return;
		}
	}

	/* Normal Command
	 * Check the Flag
	 * If the command is not synchronize single			
	 */
	if (RcvData.DataBuf[0] != 0x0F)
	{
		if (FlagBuffer == (RcvData.DataBuf[0] >> 4))		return;
		FlagBuffer = RcvData.DataBuf[0] >> 4;
	}

	/* 
	 *Received command	
	 * FD xE 00 00 00 00 00 FE
	 * FD x3 MODE COLOR SPEED 00 00 FE
	 * FD x4 HOUR 00 00 00 00
	 */
	switch (RcvData.DataBuf[0] & 0x0F)
	{
		/* 
		 * FD x1 00 00 00 00 00 FE
		 * FD x2 00 00 00 00 00 FE	
		 * Seach Command									
		 */
		case 0x1:
		case 0x2:
		{
			SndData.SndStatus	= SND_NORMAL;
			SndData.DataBuf[0]	= 0x01;
			SndData.DataBuf[1]	= DEVICE_NAME_ONE;
			SndData.DataBuf[2]	= DEVICE_NAME_TWO;
			SndData.DataBuf[3]	= DEVICE_NUM;
			
		#if AL91 | AL94
			SndData.DataBuf[4]  = HorseOrder;
			SndData.DataBuf[5]  = HorseTotal;
			
		#else
			SndData.DataBuf[4]	= TimerData.CntDwnHour;
			SndData.DataBuf[5]	= 0;
      
		#endif /* #if HORSE_ENABLE */
			
			SndData.DataBuf[6]	= ChkSumH;
			SndData.DataBuf[7]	= ChkSumL;
		} break;

		/* 
		 * FD x3 MODE COLOR 00 00 00 FE
		 * Set the mode, color
		 */
		case 0x3:
		{
			// Err check
			// DisplayData.Mode = 0x0~0xA || 0xFF
			// ColorNum	= 0x0 ~ 0x1C
			if ((RcvData.DataBuf[1] > 0xA) && (RcvData.DataBuf[1] != 0xFF))		break;
			if (RcvData.DataBuf[2] > 0x1C)										break;

			// Get the mode value
			DisplayData.Mode				= RcvData.DataBuf[1];
			DisplayData.InitFlag 		= TRUE;
			switch (DisplayData.Mode)
			{
				case 0x0:
				{
				}
				break;

				case 0xFF:
				{
					DisplayData.Mode 		= DisplayData.ModeBuf;
				} break;

				default:
				{
					// Get the color
					DisplayData.ColorValue 		= RcvData.DataBuf[2];
					Color_Value_Get(DisplayData.ColorValue);

					// Save
					DisplayData.ModeBuf 		= DisplayData.Mode;
					FlashSaveFlag						= TRUE;

				} break;
			}
		} break;

		//---------------------------------------------------------------------------
		// FD x5 HOUR 00 00 00 00 FE
		// Set the timer
		//---------------------------------------------------------------------------
		case 0x5:
		{
			if (RcvData.DataBuf[2] > 12)			break;
			TimerData.CntDwnHour	= RcvData.DataBuf[2];
			TimerData.InitFlag		= TRUE;
			FlashSaveFlag			= TRUE;

			DisplayData.Mode		= 0xFB;
			DisplayData.InitFlag	= TRUE;
		} break;
		
		//---------------------------------------------------------------------------
		// Set horse number, only AL91 AL94 serials have this function
		//---------------------------------------------------------------------------
		#if HORSE_ENABLE
		case 0x6:
		{
			switch (RcvData.DataBuf[1])
			{
				/* Reset the horse number */
				case 0x0:
				{
					HorseOrder = 0;
					HorseTotal = 0;

					DisplayData.Mode 		= 0xFD;
					DisplayData.InitFlag 	= TRUE;
					FlashSaveFlag			= TRUE;
				} break;

				/* All test */
				case 0x1:
				{
					if (HorseOrder == 0)	break;

					if (RcvData.DataBuf[2] == 0)
					{
						break;
					}
					HorseTotal = RcvData.DataBuf[2];
					DisplayData.Mode 			= 0xFE;
					DisplayData.InitFlag 	= TRUE;
				} break;

				/* Set order number */
				case 0x3:
				{
					HorseOrder = RcvData.DataBuf[2];
					DisplayData.Mode 			= 0xFD;
					DisplayData.InitFlag 	= TRUE;
					FlashSaveFlag					= TRUE;
				} break;

				/* Set horse total number and save the data */
				case 0x4:
				{
					if (HorseOrder == 0x0)
					{
						break;
					}

					HorseTotal = RcvData.DataBuf[2];
					if (HorseTotal < HorseOrder)
					{
						HorseOrder = 0;
						HorseTotal = 0;
						DisplayData.Mode 	 = 0xFF;
						DisplayData.InitFlag = TRUE;
						FlashSaveFlag		 = TRUE;
						break;
					}

					DisplayData.Mode 	 = 0xFD;
					DisplayData.InitFlag = TRUE;

					FlashSaveFlag = TRUE;
				} break;

				/* One teset */
				case 0x2:
				{
					DisplayData.Mode 		= 0xFB;
					DisplayData.InitFlag 	= TRUE;
				} break;

				/* Set the direction flag */
				case 0x5:
				{
					if (RcvData.DataBuf[2] == 0x0)
					{
						DirectFlag 		= TRUE;
						FlashSaveFlag	= TRUE;
					}
					else
					{
						DirectFlag 		= FALSE;
						FlashSaveFlag	= TRUE;
					}

					DisplayData.Mode 	 = 0xFC;
					DisplayData.InitFlag = TRUE;
				} break;
				
				case 0x6:
				{
					SndData.SndStatus = SND_NORMAL;
					SndData.DataBuf[0] = 0x6;
					SndData.DataBuf[1] = 0x6;
					SndData.DataBuf[2] = HorseInfo.Len;
					SndData.DataBuf[3] = 0;
					SndData.DataBuf[4] = 0;
					SndData.DataBuf[5] = 0;
					SndData.DataBuf[6] = ChkSumH;
					SndData.DataBuf[7] = ChkSumL;
				}break;
				
				case 0x7:
				{
					HorseInfo.AllLedCnt = BASE_LED_TOTAL * (uint16_t)RcvData.DataBuf[2];
					HorseInfo.PreLedCnt = BASE_LED_TOTAL * (uint16_t)RcvData.DataBuf[3];
					FlashSaveFlag = TRUE;
				}break;
			}
		} break;
		#endif /* #if HORSE_ENABLE */
		
		/*
		 * Password Set
		 * Test -  x8 01 CRCH CRCL 00 00  --- BLUE Flash
		 * Set Confirm - x8 02 CRCH CRCL 00 00, return x8 02 CRCH CRCL
		 * Set Password - x7 ID1 ID2 ID3 ID4 CHK
		 * Successfully - GREEN FLASH
		 */
		case 0x7:
		{
			if (PasswordFlag == TRUE)
			{
				PasswordFlag = FALSE;
				if ((RcvData.DataBuf[1] ^ RcvData.DataBuf[2] ^ RcvData.DataBuf[3] ^ 
				RcvData.DataBuf[4]) != 	RcvData.DataBuf[5])	// Password is wrong
				{
					DisplayData.Mode = 0xFF;
					DisplayData.InitFlag = TRUE;
					SndData.SndStatus 	= SND_NORMAL;
					SndData.DataBuf[0]	= 0x8;
					SndData.DataBuf[1]	= 0x4;
					SndData.DataBuf[2]	= 0;
					SndData.DataBuf[3]	= 0;
					SndData.DataBuf[4]	= NewChkSumH;
					SndData.DataBuf[5]	= NewChkSumL;
					SndData.DataBuf[6]	= ChkSumH;
					SndData.DataBuf[7]	= ChkSumL;
					break;
				}

				ChkSumBuf = CRC16_Cal(&RcvData.DataBuf[1]);
				
				//ID1 ID2 ID3 ID4 CRC16-CCITT-FALSE  isn't equal the new checksum
				if (ChkSumBuf != (_Uint16)(((_Uint16)NewChkSumH * 256) + (_Uint16)NewChkSumL))
				{
					DisplayData.Mode = 0xFF;
					DisplayData.InitFlag = TRUE;				
					
					SndData.SndStatus 	= SND_NORMAL;
					SndData.DataBuf[0]	= 0x8;
					SndData.DataBuf[1]	= 0x4;
					SndData.DataBuf[2]	= 0;
					SndData.DataBuf[3]	= 0;
					SndData.DataBuf[4]	= NewChkSumH;
					SndData.DataBuf[5]	= NewChkSumL;
					SndData.DataBuf[6]	= ChkSumH;
					SndData.DataBuf[7]	= ChkSumL;

					break;
				}

				// Set the pass word
				ChkSumReply[0] 		= Hex_To_Char(NewChkSumH >> 4);
				ChkSumReply[1] 		= Hex_To_Char(NewChkSumH & 0x0F);
				ChkSumReply[2] 		= Hex_To_Char(NewChkSumL >> 4);
				ChkSumReply[3] 		= Hex_To_Char(NewChkSumL & 0x0F);
				SndData.SndStatus 	= SND_TYPE;				// First send data to change the broadcast name, then reply the APP
				SndData.DataBuf[0]	= 0x8;
				SndData.DataBuf[1]	= 0x3;
				SndData.DataBuf[2]	= 0;
				SndData.DataBuf[3]	= 0;
				SndData.DataBuf[4]	= NewChkSumH;
				SndData.DataBuf[5]	= NewChkSumL;
				SndData.DataBuf[6]	= ChkSumH;
				SndData.DataBuf[7]	= ChkSumL;
				ChkSumH 			= NewChkSumH;
				ChkSumL 			= NewChkSumL;
				NewChkSumH 			= 0;
				NewChkSumL 			= 0;

				DisplayData.Mode 	 = 0xFD;
				DisplayData.InitFlag = TRUE;
				FlashSaveFlag		 = TRUE;
			}

			// time out
			else
			{
				SndData.SndStatus 	= SND_NORMAL;
				SndData.DataBuf[0]	= 0x8;
				SndData.DataBuf[1]	= 0x4;
				SndData.DataBuf[2]	= 0;
				SndData.DataBuf[3]	= 0;
				SndData.DataBuf[4]	= NewChkSumH;
				SndData.DataBuf[5]	= NewChkSumL;
				SndData.DataBuf[6]	= ChkSumH;
				SndData.DataBuf[7]	= ChkSumL;
			}
		} break;

		case 0x8:
		{
			if (RcvData.DataBuf[1] == 0x1)
			{
				DisplayData.Mode 		= 0xFB;
				DisplayData.InitFlag 	= TRUE;
			}
			else if (RcvData.DataBuf[1] == 0x2)
			{
				PasswordFlag = TRUE;	// Allow set the password within 5 seconds

				NewChkSumH = RcvData.DataBuf[2];
				NewChkSumL = RcvData.DataBuf[3];
				SndData.SndStatus 	= SND_NORMAL;
				SndData.DataBuf[0]	= RcvData.DataBuf[0];
				SndData.DataBuf[1]	= 0x2;
				SndData.DataBuf[2]	= 0;
				SndData.DataBuf[3]	= 0;
				SndData.DataBuf[4]	= NewChkSumH;
				SndData.DataBuf[5]	= NewChkSumL;
				SndData.DataBuf[6]	= ChkSumH;
				SndData.DataBuf[7]	= ChkSumL;
			}
		} break;

		//---------------------------------------------------------------------------
		// FD xA MODE COLOR 00 00 00 FE
		// Set the show mode, color
		//---------------------------------------------------------------------------
		case 0xA:
		{
			// Err check
			// DisplayData.Mode 		= 0x0~0xA || 0xFF
			// ColorNum		= 0x0 ~ 0x1C
			if ((RcvData.DataBuf[1] > 0x3) || (RcvData.DataBuf[1] == 0x0))		break;
			if (RcvData.DataBuf[2] > 0x8)	break;

			// Get the mode value
			DisplayData.Mode	= RcvData.DataBuf[1] + 0xA;
			DisplayData.ModeBuf	= DisplayData.Mode;
			DisplayData.InitFlag = TRUE;

			// Get the color
			DisplayData.ColorValue 	= RcvData.DataBuf[2];
			Color_Value_Get(DisplayData.ColorValue);

			FlashSaveFlag	= TRUE;
		} break;
    
    
		//Music mode
		case 0xB:
		{
			if (DisplayData.Mode == 0)    break;

			if (DisplayData.Mode != 0xE)
			{
				DisplayData.Mode = 0xE;
				DisplayData.InitFlag = TRUE;
			}

			#if AL99
			MusicMode.TotalMode = RcvData.DataBuf[1];
			MusicMode.Byte1.All = RcvData.DataBuf[2];
			MusicMode.Byte2.All = RcvData.DataBuf[3];
			MusicMode.Byte3.All = RcvData.DataBuf[4];

			#else
			MusicMode = RcvData.DataBuf[1];

			#endif

			MusicEnFlag = TRUE;
			MusicTrigFlag = TRUE;
			MusicEnTime = 0;

		} break;
	
		//user-defined mode command
		case 0xC:
		{
			uint8_t cmd = RcvData.DataBuf[1];
			switch(cmd)
			{
				//set user-defined group
				case 0:
				{
					uint8_t grp = RcvData.DataBuf[3];
					if (grp >= CUSTOM_MAX)		break;
					if (RcvData.DataBuf[2] == 0)
					{
						CustomData[grp].EnFlag = FALSE;
						CustomData[grp].Mode = 0;
					}
					else
					{
						CustomData[grp].EnFlag = TRUE;
						if (CustomData[grp].Mode == 0)
						{
							CustomData[grp].Mode = DisplayData.ModeBuf;
							CustomData[grp].Color = DisplayData.ColorValue;
						}
					}
					FlashSaveFlag = TRUE;
				}break;
				
				//enter the user-defined mode
				case 1:
				{
					uint8_t grp = RcvData.DataBuf[3];
					if (grp >= CUSTOM_MAX)	break;
					if (CustomData[grp].EnFlag)
					{
						DisplayData.ModeBuf = CustomData[grp].Mode;
						DisplayData.Mode = DisplayData.ModeBuf;
						DisplayData.ColorValue = CustomData[grp].Color;
						Color_Value_Get(DisplayData.ColorValue);
						DisplayData.InitFlag = TRUE;
						FlashSaveFlag = TRUE;
					}
				}break;
				
				//test the position
				case 2:
				{
					DisplayData.Mode = BLU_FLASH;
					DisplayData.InitFlag = TRUE;
				}break;
				
				//ensure the user-defined group
				case 3:
				{
					uint8_t grp = RcvData.DataBuf[3];
					if (grp >= CUSTOM_MAX)	break;
					if (CustomData[grp].EnFlag)
					{
						DisplayData.Mode = BLU_FLASH;
						DisplayData.InitFlag = TRUE;
					}
				}break;
				
				//require the mode and color
				case 4:
				{
					uint8_t grp = RcvData.DataBuf[3];
					if (grp >= CUSTOM_MAX)	break;
					SndData.SndStatus 	= SND_NORMAL;
					SndData.DataBuf[0]	= 0xc;
					SndData.DataBuf[1] 	= 0x4;
					SndData.DataBuf[2] 	= grp;
					SndData.DataBuf[3] 	= CustomData[grp].Mode;
					SndData.DataBuf[4] 	= CustomData[grp].Color;
					SndData.DataBuf[5]	= 0;
					SndData.DataBuf[6]	= ChkSumH;
					SndData.DataBuf[7]	= ChkSumL;
				}break;
				
				//set the group mode and color
				case 5:
				case 6:
				case 7:
				case 8:
				case 9:
				{
					uint8_t grp = cmd - 5;
					if (CustomData[grp].EnFlag == FALSE)
					{
						CustomData[grp].EnFlag = TRUE;
					}
					CustomData[grp].Mode = RcvData.DataBuf[2];
					CustomData[grp].Color = RcvData.DataBuf[3];
					DisplayData.ModeBuf = CustomData[grp].Mode;
					DisplayData.Mode = DisplayData.ModeBuf;
					DisplayData.ColorValue = CustomData[grp].Color;
					Color_Value_Get(DisplayData.ColorValue);
					FlashSaveFlag = TRUE;
				}break;
				
				//default
				default:
				{
					//no actions
				}break;
			}
		}break;
		
		/*
		 * TEST command 1,2...
		 * xD 00 00 00 00 00
		 * xD 01 00 00 00 00
		 * Reply the equipment type and HSE status, version number...
		 */
		case 0xD:
		{
			if (RcvData.DataBuf[1] == 0x0)
			{
				SndData.SndStatus 	= SND_NORMAL;
				SndData.DataBuf[0]	= 0xD;
				SndData.DataBuf[1] 	= DEVICE_NAME_ONE;
				SndData.DataBuf[2] 	= DEVICE_NAME_TWO;
				SndData.DataBuf[3] 	= DEVICE_NUM;
				SndData.DataBuf[4] 	= HorseOrder;
				SndData.DataBuf[5]	= TimerData.CntDwnHour;
				SndData.DataBuf[6]	= ChkSumH;
				SndData.DataBuf[7]	= ChkSumL;
				break;
			}

			if (RcvData.DataBuf[1] == 0x1)
			{
				SndData.SndStatus 	= SND_NORMAL;
				SndData.DataBuf[0]	= 0xD;
				SndData.DataBuf[1] 	= HseStatus;			// HSE status
				SndData.DataBuf[2] 	= WdtRstFlag;			// Watch Dog status
				SndData.DataBuf[3] 	= PROTOCOL_VER;			// Protocol version
				SndData.DataBuf[4] 	= SOFT_VER;				// Software version
				SndData.DataBuf[5]	= 0x18;					// Year 2018
				SndData.DataBuf[6]	= 'W';					// Company Willis Co.
				SndData.DataBuf[7]	= 'C';					// Author DS.Chin(James.Chin or Jim.C)
			}
		} break;

		
		#if AL94
		case 0xE:
		{
			uint8_t grp = RcvData.DataBuf[1];
			uint8_t ord = RcvData.DataBuf[2];
			uint8_t len_pre = (RcvData.DataBuf[3] >> 4) & 0xf;
			uint8_t len = RcvData.DataBuf[3] & 0xf;
			
			if (grp != HorseInfo.Grp)		break;
			
			if (len_pre != len)
			{
				HorseInfo.AllLedCnt -= ((uint16_t)len_pre * BASE_LED_TOTAL);
				HorseInfo.AllLedCnt += ((uint16_t)len * BASE_LED_TOTAL);
			}
			
			if (ord < HorseOrder)
			{
				HorseInfo.AllLedCnt -= ((uint16_t)len_pre * BASE_LED_TOTAL);
				HorseInfo.AllLedCnt += ((uint16_t)len * BASE_LED_TOTAL);
			}
		} break;	
		#endif
		
		//---------------------------------------------------------------------------
		// process the synchronizaton data
		// All products would be synchronize when display mode is 0xB | 0xC | 0xD
		// Only AL91 and AL94(Horse Enable) products would be synchronize when mode is 0x6
		//---------------------------------------------------------------------------
		case 0xF:
		{
			switch (RcvData.DataBuf[1])
			{
				/*	When the mode is 0x4(Instead), 0x5(Sea Wave) ,0x9(Polar Light) or show mode,
				 *  the projector will check and process the synchronize single
				 *	in order to keep all conformity
				 *  NOTION: Because the 0x9(Polar Light) and 0xA (color show)Mode need to be 
				 *  synchronize if it's under horse mode or not, so the case is deal here.
				 */
				case 0x4:
				case 0x5:
				case 0x9:
				case 0xA:
				case 0xB:
				case 0xC:
				case 0xD:
				{
					if (DisplayData.Mode == RcvData.DataBuf[1] && SynRcvFlag == FALSE)
					{
						DisplayData.InitFlag = TRUE;
						SynRcvFlag = TRUE;
						ModeSynFlag = TRUE;
					}
				}
				break;



				#if HORSE_ENABLE
				/*	When the mode is under horse mode, 0x6(Roll), 0x7(Ripple), 0x8(Flower Bloom),
				 *	it should to check the serias(AL91 or AL94)	yet.
				 */
				case 0x6:
				case 0x7:
				case 0x8:
				{
					if ((DisplayData.Mode == RcvData.DataBuf[1]) && 
					(HorseOrder != 0) && 
					(RcvData.DataBuf[3] == SYN_NUM) && 
					(SynRcvFlag == FALSE))
					{
						DisplayData.InitFlag 	= TRUE;
						SynRcvFlag 				= TRUE;
						ModeSynFlag 			= TRUE;
					}
				}
				break;

				#endif /* #if HORSE_ENABLE */
			}

//			// if the device's mode or theme isn't as same as received data
//			// Change the device's mode or color
//			if (RcvData.DataBuf[1] > 0xA && DisplayData.Mode != 0)
//			{
//				if (DisplayData.Mode != RcvData.DataBuf[1])
//				{
//					DisplayData.Mode 			= RcvData.DataBuf[1];
//					DisplayData.ModeBuf 	= RcvData.DataBuf[1];
//					DisplayData.InitFlag 	= TRUE;
//					FlashSaveFlag					= TRUE;
//					Color_Value_Get(DisplayData.ColorValue);
//				}

//				if (DisplayData.ColorValue != RcvData.DataBuf[2])
//				{
//					DisplayData.ColorValue 	= RcvData.DataBuf[2];
//					DisplayData.InitFlag 		= TRUE;
//					FlashSaveFlag						= TRUE;
//					Color_Value_Get(DisplayData.ColorValue);
//				}
//			}
		} break;
	}
}


/*******************************************************************************
	*
 	* FunctionName		CRC16_Cal
	*
********************************************************************************/
_Uint16	CRC16_Cal(_Uint8 Buffer[])
{
	_Uint16		ResultBuf = 0x0000;
	_Uint8		CntBuf = 0;
	_Uint8		BitBuf = 0;

	for (CntBuf = 0; CntBuf < 4; CntBuf++)
	{
		ResultBuf ^= (((_Uint16)Buffer[CntBuf]) << 8);

		for (BitBuf = 0; BitBuf < 8; BitBuf++)
		{
			if ((ResultBuf & 0x8000) == 0x8000)
			{
				ResultBuf = (ResultBuf << 1) ^ 0x1021;
			}
			else
			{
				ResultBuf <<= 1;
			}
		}
	}

	return ResultBuf;
}

/****************************************************************************
 * Color_Value_Get
 */
void Color_Value_Get(_Uint8 ColorNumBuf)
{
	_Uint8	TempCnt = 0;

#if !(COLOR_RGB | COLOR_RGBW)
	#error "No color defined !!!"


#elif COLOR_RGBW
	if (DisplayData.Mode > 0xA)
	{
		ColorNum = 12;
		switch (ColorNumBuf)
		{
			case 0x6:
			{
				for (TempCnt = 0; TempCnt < 16; TempCnt++)
				{
					ColorData[TempCnt][0] = COLOR_VECTOR[TempCnt][0];
					ColorData[TempCnt][1] = COLOR_VECTOR[TempCnt][1];
					ColorData[TempCnt][2] = COLOR_VECTOR[TempCnt][2];
					ColorData[TempCnt][3] = COLOR_VECTOR[TempCnt][3];
				}
			} break;

			/* christmas */
			case 0x0:
			{
				for (TempCnt = 0; TempCnt < 16; TempCnt++)
				{
					if ( (TempCnt % 5) == 0)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[GREEN][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[GREEN][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[GREEN][2];
						ColorData[TempCnt][3] = COLOR_VECTOR[GREEN][3];
					}
					else
					if ((TempCnt % 5) == 1)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[RED][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[RED][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[RED][2];
						ColorData[TempCnt][3] = COLOR_VECTOR[RED][3];
					}
					else
					if ((TempCnt % 5) == 2)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[WHITE][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[WHITE][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[WHITE][2];
						ColorData[TempCnt][3] = COLOR_VECTOR[WHITE][3];
					}
					else
					if ((TempCnt % 5) == 3)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[DARK_GREEN][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[DARK_GREEN][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[DARK_GREEN][2];
						ColorData[TempCnt][3] = COLOR_VECTOR[DARK_GREEN][3];
					}
					else
					if ((TempCnt % 5) == 4)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[COLD_WHITE][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[COLD_WHITE][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[COLD_WHITE][2];
						ColorData[TempCnt][3] = COLOR_VECTOR[COLD_WHITE][3];
					}
				}
			} break;


			/* Valentines' Day */
			case 0x1:
			{
				for (TempCnt = 0; TempCnt < 16; TempCnt++)
				{
					if ((TempCnt % 7) == 0)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[PINK][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[PINK][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[PINK][2];
						ColorData[TempCnt][3] = COLOR_VECTOR[PINK][3];
					}
					else if ((TempCnt % 7) == 1)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[PEACH][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[PEACH][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[PEACH][2];
						ColorData[TempCnt][3] = COLOR_VECTOR[PEACH][3];
					}
					else if ( (TempCnt % 7) == 2)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[PINK][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[PINK][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[PINK][2];
						ColorData[TempCnt][3] = COLOR_VECTOR[PINK][3];
					}
					else if ((TempCnt % 7) == 3)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[LAWN_GREEN][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[LAWN_GREEN][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[LAWN_GREEN][2];
						ColorData[TempCnt][3] = COLOR_VECTOR[LAWN_GREEN][3];
					}
					else if ((TempCnt % 7) == 4)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[PEACH][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[PEACH][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[PEACH][2];
						ColorData[TempCnt][3] = COLOR_VECTOR[PEACH][3];
					}
					else if ( (TempCnt % 7) == 5)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[PINK][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[PINK][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[PINK][2];
						ColorData[TempCnt][3] = COLOR_VECTOR[PINK][3];
					}
					else if ((TempCnt % 7) == 6)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[PEACH][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[PEACH][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[PEACH][2];
						ColorData[TempCnt][3] = COLOR_VECTOR[PEACH][3];
					}
				}
			} break;


			/* Independence day */
			case 0x2:
			{
			#ifdef	_USA_
				for (TempCnt = 0; TempCnt < 16; TempCnt++)
				{
					if ( TempCnt % 4 == 0)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[RED][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[RED][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[RED][2];
						ColorData[TempCnt][3] = COLOR_VECTOR[RED][3];
					}
					else
					if (TempCnt % 4 == 1)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[BLUE][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[BLUE][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[BLUE][2];
						ColorData[TempCnt][3] = COLOR_VECTOR[BLUE][3];
					}
					else
					if (TempCnt % 4 == 2)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[COLD_WHITE][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[COLD_WHITE][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[COLD_WHITE][2];
						ColorData[TempCnt][3] = COLOR_VECTOR[COLD_WHITE][3];
					}
					else
					if (TempCnt % 4 == 3)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[BLUE][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[BLUE][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[BLUE][2];
						ColorData[TempCnt][3] = COLOR_VECTOR[BLUE][3];
					}
				}
			#endif

			#ifdef	_CAN_
				for (TempCnt = 0; TempCnt < 16; TempCnt++)
				{
					if ( TempCnt % 2 == 0)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[RED][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[RED][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[RED][2];
						ColorData[TempCnt][3] = COLOR_VECTOR[RED][3];
					}
					else
					if (TempCnt % 2 == 1)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[COLD_WHITE][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[COLD_WHITE][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[COLD_WHITE][2];
						ColorData[TempCnt][3] = COLOR_VECTOR[COLD_WHITE][3];
					}
				}
#endif
			} break;

			/* Thanks giving */
			case 0x3:
			{
				for (TempCnt = 0; TempCnt < 16; TempCnt++)
				{
					if ( (TempCnt % 5) == 0)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[SPRING_GREEN][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[SPRING_GREEN][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[SPRING_GREEN][2];
						ColorData[TempCnt][3] = COLOR_VECTOR[SPRING_GREEN][3];
					}
					else
					if ((TempCnt % 5) == 1)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[ORANGE][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[ORANGE][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[ORANGE][2];
						ColorData[TempCnt][3] = COLOR_VECTOR[ORANGE][3];
					}
					else
					if ((TempCnt % 5) == 2)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[LAWN_GREEN][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[LAWN_GREEN][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[LAWN_GREEN][2];
						ColorData[TempCnt][3] = COLOR_VECTOR[LAWN_GREEN][3];
					}
					else
					if ((TempCnt % 5) == 3)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[RED][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[RED][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[RED][2];
						ColorData[TempCnt][3] = COLOR_VECTOR[RED][3];
					}
					else
					if ((TempCnt % 5) == 4)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[GOLD][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[GOLD][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[GOLD][2];
						ColorData[TempCnt][3] = COLOR_VECTOR[GOLD][3];
					}
				}
			} break;

			/* st. patrick's day */
			case 0x4:
			{
				for (TempCnt = 0; TempCnt < 16; TempCnt++)
				{
					if ( (TempCnt % 4) == 0)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[GREEN][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[GREEN][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[GREEN][2];
						ColorData[TempCnt][3] = COLOR_VECTOR[GREEN][3];
					}
					else
					if ((TempCnt % 4) == 1)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[SPRING_GREEN][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[SPRING_GREEN][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[SPRING_GREEN][2];
						ColorData[TempCnt][3] = COLOR_VECTOR[SPRING_GREEN][3];
					}
					else
					if ((TempCnt % 4) == 2)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[DARK_GREEN][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[DARK_GREEN][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[DARK_GREEN][2];
						ColorData[TempCnt][3] = COLOR_VECTOR[DARK_GREEN][3];
					}
					else
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[LAWN_GREEN][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[LAWN_GREEN][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[LAWN_GREEN][2];
						ColorData[TempCnt][3] = COLOR_VECTOR[LAWN_GREEN][3];
					}
				}
			} break;

			/* Halloween */
			case 0x5:
			{
				for (TempCnt = 0; TempCnt < 16; TempCnt++)
				{
					if ( (TempCnt % 9) == 0)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[ORANGE][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[ORANGE][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[ORANGE][2];
						ColorData[TempCnt][3] = COLOR_VECTOR[ORANGE][3];
					}
					else
					if ((TempCnt % 9) == 1)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[PURPLE][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[PURPLE][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[PURPLE][2];
						ColorData[TempCnt][3] = COLOR_VECTOR[PURPLE][3];
					}
					else
					if ((TempCnt % 9) == 2)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[DARK_GREEN][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[DARK_GREEN][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[DARK_GREEN][2];
						ColorData[TempCnt][3] = COLOR_VECTOR[DARK_GREEN][3];
					}
					else
					if ((TempCnt % 9) == 3)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[DARK_RED][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[DARK_RED][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[DARK_RED][2];
						ColorData[TempCnt][3] = COLOR_VECTOR[DARK_RED][3];
					}
					else
					if ((TempCnt % 9) == 4)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[PURPLE][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[PURPLE][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[PURPLE][2];
						ColorData[TempCnt][3] = COLOR_VECTOR[PURPLE][3];
					}
					else
					if ((TempCnt % 9) == 5)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[GREEN][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[GREEN][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[GREEN][2];
						ColorData[TempCnt][3] = COLOR_VECTOR[GREEN][3];
					}
					else
					if ((TempCnt % 9) == 6)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[PURPLE][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[PURPLE][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[PURPLE][2];
						ColorData[TempCnt][3] = COLOR_VECTOR[PURPLE][3];
					}
					else
					if ((TempCnt % 9) == 7)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[DARK_GREEN][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[DARK_GREEN][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[DARK_GREEN][2];
						ColorData[TempCnt][3] = COLOR_VECTOR[DARK_GREEN][3];
					}
					else
					if ((TempCnt % 9) == 8)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[DARK_RED][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[DARK_RED][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[DARK_RED][2];
						ColorData[TempCnt][3] = COLOR_VECTOR[DARK_RED][3];
					}
				}
			} break;
		}
	}


	else
	{
		// single color
		if (ColorNumBuf < 0x10)
		{
			for (TempCnt = 0; TempCnt < 16; TempCnt++)
			{
				ColorData[TempCnt][0] = COLOR_VECTOR[ColorNumBuf][0];
				ColorData[TempCnt][1] = COLOR_VECTOR[ColorNumBuf][1];
				ColorData[TempCnt][2] = COLOR_VECTOR[ColorNumBuf][2];
				ColorData[TempCnt][3] = COLOR_VECTOR[ColorNumBuf][3];
			}
			ColorNum = 1;
		
    } // single color

		// many color
		else
		{
				switch (ColorNumBuf)
				{
						/* spring */
						case 0x10:
								ColorData[0][0] = COLOR_VECTOR[SPRING_GREEN][0];
								ColorData[0][1] = COLOR_VECTOR[SPRING_GREEN][1];
								ColorData[0][2] = COLOR_VECTOR[SPRING_GREEN][2];
								ColorData[0][3] = COLOR_VECTOR[SPRING_GREEN][3];

								ColorData[1][0] = COLOR_VECTOR[LAWN_GREEN][0];
								ColorData[1][1] = COLOR_VECTOR[LAWN_GREEN][1];
								ColorData[1][2] = COLOR_VECTOR[LAWN_GREEN][2];
								ColorData[1][3] = COLOR_VECTOR[LAWN_GREEN][3];

								ColorData[2][0] = COLOR_VECTOR[PINK][0];
								ColorData[2][1] = COLOR_VECTOR[PINK][1];
								ColorData[2][2] = COLOR_VECTOR[PINK][2];
								ColorData[2][3] = COLOR_VECTOR[PINK][3];

								ColorNum = 3;
						break;

						/* summer*/
						case 0x11:
								ColorData[0][0] = COLOR_VECTOR[GREEN][0];
								ColorData[0][1] = COLOR_VECTOR[GREEN][1];
								ColorData[0][2] = COLOR_VECTOR[GREEN][2];
								ColorData[0][3] = COLOR_VECTOR[GREEN][3];

								ColorData[1][0] = COLOR_VECTOR[RED][0];
								ColorData[1][1] = COLOR_VECTOR[RED][1];
								ColorData[1][2] = COLOR_VECTOR[RED][2];
								ColorData[1][3] = COLOR_VECTOR[RED][3];

								ColorData[2][0] = COLOR_VECTOR[LAWN_GREEN][0];
								ColorData[2][1] = COLOR_VECTOR[LAWN_GREEN][1];
								ColorData[2][2] = COLOR_VECTOR[LAWN_GREEN][2];
								ColorData[2][3] = COLOR_VECTOR[LAWN_GREEN][3];

								ColorData[3][0] = COLOR_VECTOR[ORANGE][0];
								ColorData[3][1] = COLOR_VECTOR[ORANGE][1];
								ColorData[3][2] = COLOR_VECTOR[ORANGE][2];
								ColorData[3][3] = COLOR_VECTOR[ORANGE][3];

								ColorNum = 4;
						break;

						/* autumn*/
						case 0x12:
								ColorData[0][0] = COLOR_VECTOR[ORANGE][0];
								ColorData[0][1] = COLOR_VECTOR[ORANGE][1];
								ColorData[0][2] = COLOR_VECTOR[ORANGE][2];
								ColorData[0][3] = COLOR_VECTOR[ORANGE][3];

								ColorData[1][0] = COLOR_VECTOR[GOLD][0];
								ColorData[1][1] = COLOR_VECTOR[GOLD][1];
								ColorData[1][2] = COLOR_VECTOR[GOLD][2];
								ColorData[1][3] = COLOR_VECTOR[GOLD][3];

								ColorData[2][0] = COLOR_VECTOR[ORANGE][0];
								ColorData[2][1] = COLOR_VECTOR[ORANGE][1];
								ColorData[2][2] = COLOR_VECTOR[ORANGE][2];
								ColorData[2][3] = COLOR_VECTOR[ORANGE][3];

								ColorData[3][0] = COLOR_VECTOR[CYAN][0];
								ColorData[3][1] = COLOR_VECTOR[CYAN][1];
								ColorData[3][2] = COLOR_VECTOR[CYAN][2];
								ColorData[3][3] = COLOR_VECTOR[CYAN][3];

								ColorNum = 4;

						break;

						/* winter */
						case 0x13:
								ColorData[0][0] = COLOR_VECTOR[COLD_WHITE][0];
								ColorData[0][1] = COLOR_VECTOR[COLD_WHITE][1];
								ColorData[0][2] = COLOR_VECTOR[COLD_WHITE][2];
								ColorData[0][3] = COLOR_VECTOR[COLD_WHITE][3];

								ColorData[1][0] = COLOR_VECTOR[SKY_BLUE][0];
								ColorData[1][1] = COLOR_VECTOR[SKY_BLUE][1];
								ColorData[1][2] = COLOR_VECTOR[SKY_BLUE][2];
								ColorData[1][3] = COLOR_VECTOR[SKY_BLUE][3];

								ColorData[2][0] = COLOR_VECTOR[BLUE][0];
								ColorData[2][1] = COLOR_VECTOR[BLUE][1];
								ColorData[2][2] = COLOR_VECTOR[BLUE][2];
								ColorData[2][3] = COLOR_VECTOR[BLUE][3];

								ColorNum = 3;
						break;

						/* Christmas' day */
						case 0x14:
								ColorData[0][0] = COLOR_VECTOR[RED][0];
								ColorData[0][1] = COLOR_VECTOR[RED][1];
								ColorData[0][2] = COLOR_VECTOR[RED][2];
								ColorData[0][3] = COLOR_VECTOR[RED][3];

								ColorData[1][0] = COLOR_VECTOR[GREEN][0];
								ColorData[1][1] = COLOR_VECTOR[GREEN][1];
								ColorData[1][2] = COLOR_VECTOR[GREEN][2];
								ColorData[1][3] = COLOR_VECTOR[GREEN][3];

								ColorData[2][0] = COLOR_VECTOR[WHITE][0];
								ColorData[2][1] = COLOR_VECTOR[WHITE][1];
								ColorData[2][2] = COLOR_VECTOR[WHITE][2];
								ColorData[2][3] = COLOR_VECTOR[WHITE][3];

								ColorNum = 3;
						break;

						/* Valentines' day */
						case 0x15:
								for (TempCnt = 0; TempCnt < 16; TempCnt++)
								{
									if ((TempCnt % 7) == 0)
									{
										ColorData[TempCnt][0] = COLOR_VECTOR[PINK][0];
										ColorData[TempCnt][1] = COLOR_VECTOR[PINK][1];
										ColorData[TempCnt][2] = COLOR_VECTOR[PINK][2];
										ColorData[TempCnt][3] = COLOR_VECTOR[PINK][3];
									}
									else if ((TempCnt % 7) == 1)
									{
										ColorData[TempCnt][0] = COLOR_VECTOR[PEACH][0];
										ColorData[TempCnt][1] = COLOR_VECTOR[PEACH][1];
										ColorData[TempCnt][2] = COLOR_VECTOR[PEACH][2];
										ColorData[TempCnt][3] = COLOR_VECTOR[PEACH][3];
									}
									else if ( (TempCnt % 7) == 2)
									{
										ColorData[TempCnt][0] = COLOR_VECTOR[PINK][0];
										ColorData[TempCnt][1] = COLOR_VECTOR[PINK][1];
										ColorData[TempCnt][2] = COLOR_VECTOR[PINK][2];
										ColorData[TempCnt][3] = COLOR_VECTOR[PINK][3];
									}
									else if ((TempCnt % 7) == 3)
									{
										ColorData[TempCnt][0] = COLOR_VECTOR[LAWN_GREEN][0];
										ColorData[TempCnt][1] = COLOR_VECTOR[LAWN_GREEN][1];
										ColorData[TempCnt][2] = COLOR_VECTOR[LAWN_GREEN][2];
										ColorData[TempCnt][3] = COLOR_VECTOR[LAWN_GREEN][3];
									}
									else if ((TempCnt % 7) == 4)
									{
										ColorData[TempCnt][0] = COLOR_VECTOR[PEACH][0];
										ColorData[TempCnt][1] = COLOR_VECTOR[PEACH][1];
										ColorData[TempCnt][2] = COLOR_VECTOR[PEACH][2];
										ColorData[TempCnt][3] = COLOR_VECTOR[PEACH][3];
									}
									else if ( (TempCnt % 7) == 5)
									{
										ColorData[TempCnt][0] = COLOR_VECTOR[PINK][0];
										ColorData[TempCnt][1] = COLOR_VECTOR[PINK][1];
										ColorData[TempCnt][2] = COLOR_VECTOR[PINK][2];
										ColorData[TempCnt][3] = COLOR_VECTOR[PINK][3];
									}
									else if ((TempCnt % 7) == 6)
									{
										ColorData[TempCnt][0] = COLOR_VECTOR[PEACH][0];
										ColorData[TempCnt][1] = COLOR_VECTOR[PEACH][1];
										ColorData[TempCnt][2] = COLOR_VECTOR[PEACH][2];
										ColorData[TempCnt][3] = COLOR_VECTOR[PEACH][3];
									}
								}
								ColorNum = 7;
						break;

						/* Independence day */
						case 0x16:
#ifdef	_USA_
								ColorData[0][0] = COLOR_VECTOR[RED][0];
								ColorData[0][1] = COLOR_VECTOR[RED][1];
								ColorData[0][2] = COLOR_VECTOR[RED][2];
								ColorData[0][3] = COLOR_VECTOR[RED][3];

								ColorData[1][0] = COLOR_VECTOR[WHITE][0];
								ColorData[1][1] = COLOR_VECTOR[WHITE][1];
								ColorData[1][2] = COLOR_VECTOR[WHITE][2];
								ColorData[1][3] = COLOR_VECTOR[WHITE][3];

								ColorData[2][0] = COLOR_VECTOR[BLUE][0];
								ColorData[2][1] = COLOR_VECTOR[BLUE][1];
								ColorData[2][2] = COLOR_VECTOR[BLUE][2];
								ColorData[2][3] = COLOR_VECTOR[BLUE][3];

								ColorNum = 3;

#endif


#ifdef	_CAN_
								ColorData[0][0] = COLOR_VECTOR[RED][0];
								ColorData[0][1] = COLOR_VECTOR[RED][1];
								ColorData[0][2] = COLOR_VECTOR[RED][2];
								ColorData[0][3] = COLOR_VECTOR[RED][3];

								ColorData[1][0] = COLOR_VECTOR[WHITE][0];
								ColorData[1][1] = COLOR_VECTOR[WHITE][1];
								ColorData[1][2] = COLOR_VECTOR[WHITE][2];
								ColorData[1][3] = COLOR_VECTOR[WHITE][3];

								ColorData[2][0] = COLOR_VECTOR[RED][0];
								ColorData[2][1] = COLOR_VECTOR[RED][1];
								ColorData[2][2] = COLOR_VECTOR[RED][2];
								ColorData[2][3] = COLOR_VECTOR[RED][3];

								ColorNum = 2;

#endif
						break;

						/* Thanks giving */
						case 0x17:
								ColorData[0][0] = COLOR_VECTOR[SPRING_GREEN][0];
								ColorData[0][1] = COLOR_VECTOR[SPRING_GREEN][1];
								ColorData[0][2] = COLOR_VECTOR[SPRING_GREEN][2];
								ColorData[0][3] = COLOR_VECTOR[SPRING_GREEN][3];

								ColorData[1][0] = COLOR_VECTOR[ORANGE][0];
								ColorData[1][1] = COLOR_VECTOR[ORANGE][1];
								ColorData[1][2] = COLOR_VECTOR[ORANGE][2];
								ColorData[1][3] = COLOR_VECTOR[ORANGE][3];

								ColorData[2][0] = COLOR_VECTOR[RED][0];
								ColorData[2][1] = COLOR_VECTOR[RED][1];
								ColorData[2][2] = COLOR_VECTOR[RED][2];
								ColorData[2][3] = COLOR_VECTOR[RED][3];

								ColorData[3][0] = COLOR_VECTOR[LAWN_GREEN][0];
								ColorData[3][1] = COLOR_VECTOR[LAWN_GREEN][1];
								ColorData[3][2] = COLOR_VECTOR[LAWN_GREEN][2];
								ColorData[3][3] = COLOR_VECTOR[LAWN_GREEN][3];

								ColorData[4][0] = COLOR_VECTOR[GOLD][0];
								ColorData[4][1] = COLOR_VECTOR[GOLD][1];
								ColorData[4][2] = COLOR_VECTOR[GOLD][2];
								ColorData[4][3] = COLOR_VECTOR[GOLD][3];
								ColorNum = 5;
						break;

						/* st. patrick's day */
						case 0x18:
								ColorData[0][0] = COLOR_VECTOR[GREEN][0];
								ColorData[0][1] = COLOR_VECTOR[GREEN][1];
								ColorData[0][2] = COLOR_VECTOR[GREEN][2];
								ColorData[0][3] = COLOR_VECTOR[GREEN][3];

								ColorData[1][0] = COLOR_VECTOR[SPRING_GREEN][0];
								ColorData[1][1] = COLOR_VECTOR[SPRING_GREEN][1];
								ColorData[1][2] = COLOR_VECTOR[SPRING_GREEN][2];
								ColorData[1][3] = COLOR_VECTOR[SPRING_GREEN][3];

								ColorData[2][0] = COLOR_VECTOR[LAWN_GREEN][0];
								ColorData[2][1] = COLOR_VECTOR[LAWN_GREEN][1];
								ColorData[2][2] = COLOR_VECTOR[LAWN_GREEN][2];
								ColorData[2][3] = COLOR_VECTOR[LAWN_GREEN][3];

								ColorNum = 3;
						break;

						/* Halloween */
						case 0x19:
								for (TempCnt = 0; TempCnt < 16; TempCnt++)
								{
									if ( (TempCnt % 9) == 0)
									{
										ColorData[TempCnt][0] = COLOR_VECTOR[ORANGE][0];
										ColorData[TempCnt][1] = COLOR_VECTOR[ORANGE][1];
										ColorData[TempCnt][2] = COLOR_VECTOR[ORANGE][2];
										ColorData[TempCnt][3] = COLOR_VECTOR[ORANGE][3];
									}
									else
									if ((TempCnt % 9) == 1)
									{
										ColorData[TempCnt][0] = COLOR_VECTOR[PURPLE][0];
										ColorData[TempCnt][1] = COLOR_VECTOR[PURPLE][1];
										ColorData[TempCnt][2] = COLOR_VECTOR[PURPLE][2];
										ColorData[TempCnt][3] = COLOR_VECTOR[PURPLE][3];
									}
									else
									if ((TempCnt % 9) == 2)
									{
										ColorData[TempCnt][0] = COLOR_VECTOR[DARK_GREEN][0];
										ColorData[TempCnt][1] = COLOR_VECTOR[DARK_GREEN][1];
										ColorData[TempCnt][2] = COLOR_VECTOR[DARK_GREEN][2];
										ColorData[TempCnt][3] = COLOR_VECTOR[DARK_GREEN][3];
									}
									else
									if ((TempCnt % 9) == 3)
									{
										ColorData[TempCnt][0] = COLOR_VECTOR[DARK_RED][0];
										ColorData[TempCnt][1] = COLOR_VECTOR[DARK_RED][1];
										ColorData[TempCnt][2] = COLOR_VECTOR[DARK_RED][2];
										ColorData[TempCnt][3] = COLOR_VECTOR[DARK_RED][3];
									}
									else
									if ((TempCnt % 9) == 4)
									{
										ColorData[TempCnt][0] = COLOR_VECTOR[PURPLE][0];
										ColorData[TempCnt][1] = COLOR_VECTOR[PURPLE][1];
										ColorData[TempCnt][2] = COLOR_VECTOR[PURPLE][2];
										ColorData[TempCnt][3] = COLOR_VECTOR[PURPLE][3];
									}
									else
									if ((TempCnt % 9) == 5)
									{
										ColorData[TempCnt][0] = COLOR_VECTOR[GREEN][0];
										ColorData[TempCnt][1] = COLOR_VECTOR[GREEN][1];
										ColorData[TempCnt][2] = COLOR_VECTOR[GREEN][2];
										ColorData[TempCnt][3] = COLOR_VECTOR[GREEN][3];
									}
									else
									if ((TempCnt % 9) == 6)
									{
										ColorData[TempCnt][0] = COLOR_VECTOR[PURPLE][0];
										ColorData[TempCnt][1] = COLOR_VECTOR[PURPLE][1];
										ColorData[TempCnt][2] = COLOR_VECTOR[PURPLE][2];
										ColorData[TempCnt][3] = COLOR_VECTOR[PURPLE][3];
									}
									else
									if ((TempCnt % 9) == 7)
									{
										ColorData[TempCnt][0] = COLOR_VECTOR[DARK_GREEN][0];
										ColorData[TempCnt][1] = COLOR_VECTOR[DARK_GREEN][1];
										ColorData[TempCnt][2] = COLOR_VECTOR[DARK_GREEN][2];
										ColorData[TempCnt][3] = COLOR_VECTOR[DARK_GREEN][3];
									}
									else
									if ((TempCnt % 9) == 8)
									{
										ColorData[TempCnt][0] = COLOR_VECTOR[DARK_RED][0];
										ColorData[TempCnt][1] = COLOR_VECTOR[DARK_RED][1];
										ColorData[TempCnt][2] = COLOR_VECTOR[DARK_RED][2];
										ColorData[TempCnt][3] = COLOR_VECTOR[DARK_RED][3];
									}
								}

								ColorNum = 9;
						break;

						/* sun */
						case 0x1A:
								ColorData[0][0] = COLOR_VECTOR[RED][0];
								ColorData[0][1] = COLOR_VECTOR[RED][1];
								ColorData[0][2] = COLOR_VECTOR[RED][2];
								ColorData[0][3] = COLOR_VECTOR[RED][3];

								ColorData[1][0] = COLOR_VECTOR[ORANGE][0];
								ColorData[1][1] = COLOR_VECTOR[ORANGE][1];
								ColorData[1][2] = COLOR_VECTOR[ORANGE][2];
								ColorData[1][3] = COLOR_VECTOR[ORANGE][3];

								ColorData[2][0] = COLOR_VECTOR[GOLD][0];
								ColorData[2][1] = COLOR_VECTOR[GOLD][1];
								ColorData[2][2] = COLOR_VECTOR[GOLD][2];
								ColorData[2][3] = COLOR_VECTOR[GOLD][3];

								ColorData[3][0] = COLOR_VECTOR[YELLOW][0];
								ColorData[3][1] = COLOR_VECTOR[YELLOW][1];
								ColorData[3][2] = COLOR_VECTOR[YELLOW][2];
								ColorData[3][3] = COLOR_VECTOR[YELLOW][3];

								ColorNum = 4;
						break;

						/* earth */
						case 0x1B:
								ColorData[0][0] = COLOR_VECTOR[BLUE][0];
								ColorData[0][1] = COLOR_VECTOR[BLUE][1];
								ColorData[0][2] = COLOR_VECTOR[BLUE][2];
								ColorData[0][3] = COLOR_VECTOR[BLUE][3];

								ColorData[1][0] = COLOR_VECTOR[GREEN][0];
								ColorData[1][1] = COLOR_VECTOR[GREEN][1];
								ColorData[1][2] = COLOR_VECTOR[GREEN][2];
								ColorData[1][3] = COLOR_VECTOR[GREEN][3];

								ColorData[2][0] = COLOR_VECTOR[SKY_BLUE][0];
								ColorData[2][1] = COLOR_VECTOR[SKY_BLUE][1];
								ColorData[2][2] = COLOR_VECTOR[SKY_BLUE][2];
								ColorData[2][3] = COLOR_VECTOR[SKY_BLUE][3];


								ColorData[3][0] = COLOR_VECTOR[ORANGE][0];
								ColorData[3][1] = COLOR_VECTOR[ORANGE][1];
								ColorData[3][2] = COLOR_VECTOR[ORANGE][2];
								ColorData[3][3] = COLOR_VECTOR[ORANGE][3];

								ColorNum = 4;
						break;

						/* Multi */
						case 0x1C:
							for (TempCnt = 0; TempCnt < 12; TempCnt++)
								{
										ColorData[TempCnt][0] = COLOR_VECTOR[TempCnt][0];
										ColorData[TempCnt][1] = COLOR_VECTOR[TempCnt][1];
										ColorData[TempCnt][2] = COLOR_VECTOR[TempCnt][2];
										ColorData[TempCnt][3] = COLOR_VECTOR[TempCnt][3];
								}

								ColorNum = 12;
						break;
				}//switch (RcvData[1])
		} // many color
	} // else


#elif COLOR_RGB
	if (DisplayData.Mode > 0xA)
	{
		ColorNum = 12;
		switch (ColorNumBuf)
		{
			case 0x6:
			{
				for (TempCnt = 0; TempCnt < 16; TempCnt++)
				{
					ColorData[TempCnt][0] = COLOR_VECTOR[TempCnt][0];
					ColorData[TempCnt][1] = COLOR_VECTOR[TempCnt][1];
					ColorData[TempCnt][2] = COLOR_VECTOR[TempCnt][2];
				}
			} break;

			/* christmas */
			case 0:
			{
				for (TempCnt = 0; TempCnt < 16; TempCnt++)
				{
					if ( (TempCnt % 5) == 0)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[GREEN][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[GREEN][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[GREEN][2];
					}
					else
					if ((TempCnt % 5) == 1)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[RED][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[RED][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[RED][2];
					}
					else
					if ((TempCnt % 5) == 2)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[WHITE][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[WHITE][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[WHITE][2];
					}
					else
					if ((TempCnt % 5) == 3)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[DARK_GREEN][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[DARK_GREEN][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[DARK_GREEN][2];
					}
					else
					if ((TempCnt % 5) == 4)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[COLD_WHITE][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[COLD_WHITE][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[COLD_WHITE][2];
					}
				}
			} break;


			/* Valentines' Day */
			case 1:
			{
				for (TempCnt = 0; TempCnt < 16; TempCnt++)
				{
					if ((TempCnt % 7) == 0)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[PINK][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[PINK][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[PINK][2];
					}
					else if ((TempCnt % 7) == 1)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[PEACH][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[PEACH][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[PEACH][2];
					}
					else if ( (TempCnt % 7) == 2)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[PINK][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[PINK][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[PINK][2];
					}
					else if ((TempCnt % 7) == 3)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[LAWN_GREEN][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[LAWN_GREEN][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[LAWN_GREEN][2];
					}
					else if ((TempCnt % 7) == 4)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[PEACH][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[PEACH][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[PEACH][2];
					}
					else if ( (TempCnt % 7) == 5)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[PINK][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[PINK][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[PINK][2];
					}
					else if ((TempCnt % 7) == 6)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[PEACH][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[PEACH][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[PEACH][2];
					}
				}
			} break;


			/* Independence day */
			case 2:
			{
				#ifdef	_USA_
					for (TempCnt = 0; TempCnt < 16; TempCnt++)
					{
						if ( (TempCnt % 4) == 0)
						{
							ColorData[TempCnt][0] = COLOR_VECTOR[RED][0];
							ColorData[TempCnt][1] = COLOR_VECTOR[RED][1];
							ColorData[TempCnt][2] = COLOR_VECTOR[RED][2];
						}
						else
						if ((TempCnt % 4) == 1)
						{
							ColorData[TempCnt][0] = COLOR_VECTOR[BLUE][0];
							ColorData[TempCnt][1] = COLOR_VECTOR[BLUE][1];
							ColorData[TempCnt][2] = COLOR_VECTOR[BLUE][2];
						}
						else
						if ((TempCnt % 4) == 2)
						{
							ColorData[TempCnt][0] = COLOR_VECTOR[COLD_WHITE][0];
							ColorData[TempCnt][1] = COLOR_VECTOR[COLD_WHITE][1];
							ColorData[TempCnt][2] = COLOR_VECTOR[COLD_WHITE][2];
						}
						else
						if ((TempCnt % 4) == 3)
						{
							ColorData[TempCnt][0] = COLOR_VECTOR[BLUE][0];
							ColorData[TempCnt][1] = COLOR_VECTOR[BLUE][1];
							ColorData[TempCnt][2] = COLOR_VECTOR[BLUE][2];
						}
					}
				#endif

				#ifdef	_CAN_
					for (TempCnt = 0; TempCnt < 16; TempCnt++)
					{
						if ( (TempCnt % 2) == 0)
						{
							ColorData[TempCnt][0] = COLOR_VECTOR[RED][0];
							ColorData[TempCnt][1] = COLOR_VECTOR[RED][1];
							ColorData[TempCnt][2] = COLOR_VECTOR[RED][2];
						}
						else
						if ((TempCnt % 2) == 1)
						{
							ColorData[TempCnt][0] = COLOR_VECTOR[COLD_WHITE][0];
							ColorData[TempCnt][1] = COLOR_VECTOR[COLD_WHITE][1];
							ColorData[TempCnt][2] = COLOR_VECTOR[COLD_WHITE][2];
						}
					}
				#endif
			} break;

			/* Thanks giving */
			case 3:
			{
				for (TempCnt = 0; TempCnt < 16; TempCnt++)
				{
					if ( (TempCnt % 5) == 0)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[SPRING_GREEN][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[SPRING_GREEN][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[SPRING_GREEN][2];
					}
					else
					if ((TempCnt % 5) == 1)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[ORANGE][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[ORANGE][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[ORANGE][2];
					}
					else
					if ((TempCnt % 5) == 2)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[LAWN_GREEN][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[LAWN_GREEN][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[LAWN_GREEN][2];
					}
					else
					if ((TempCnt % 5) == 3)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[RED][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[RED][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[RED][2];
					}
					else
					if ((TempCnt % 5) == 4)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[GOLD][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[GOLD][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[GOLD][2];
					}
				}
			} break;

			/* st. patrick's day */
			case 4:
			{
				for (TempCnt = 0; TempCnt < 16; TempCnt++)
				{
					if ( (TempCnt % 4) == 0)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[GREEN][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[GREEN][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[GREEN][2];
					}
					else
					if ((TempCnt % 4) == 1)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[SPRING_GREEN][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[SPRING_GREEN][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[SPRING_GREEN][2];
					}
					else
					if ((TempCnt % 4) == 2)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[DARK_GREEN][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[DARK_GREEN][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[DARK_GREEN][2];
					}
					else
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[LAWN_GREEN][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[LAWN_GREEN][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[LAWN_GREEN][2];
					}
				}
			} break;

			/* Halloween */
			case 5:
			{
				for (TempCnt = 0; TempCnt < 16; TempCnt++)
				{
					if ( (TempCnt % 9) == 0)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[ORANGE][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[ORANGE][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[ORANGE][2];
					}
					else
					if ((TempCnt % 9) == 1)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[PURPLE][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[PURPLE][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[PURPLE][2];
					}
					else
					if ((TempCnt % 9) == 2)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[DARK_GREEN][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[DARK_GREEN][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[DARK_GREEN][2];
					}
					else
					if ((TempCnt % 9) == 3)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[DARK_RED][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[DARK_RED][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[DARK_RED][2];
					}
					else
					if ((TempCnt % 9) == 4)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[PURPLE][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[PURPLE][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[PURPLE][2];
					}
					else
					if ((TempCnt % 9) == 5)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[GREEN][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[GREEN][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[GREEN][2];
					}
					else
					if ((TempCnt % 9) == 6)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[PURPLE][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[PURPLE][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[PURPLE][2];
					}
					else
					if ((TempCnt % 9) == 7)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[DARK_GREEN][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[DARK_GREEN][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[DARK_GREEN][2];
					}
					else
					if ((TempCnt % 9) == 8)
					{
						ColorData[TempCnt][0] = COLOR_VECTOR[DARK_RED][0];
						ColorData[TempCnt][1] = COLOR_VECTOR[DARK_RED][1];
						ColorData[TempCnt][2] = COLOR_VECTOR[DARK_RED][2];
					}
				}
			} break;
		}
	}

	else
	{
		//ColorNumBuf = 0x0d;
		// single color
		if (ColorNumBuf < 0x10)
		{
			ColorData[0][0] = COLOR_VECTOR[ColorNumBuf][0];
			ColorData[0][1] = COLOR_VECTOR[ColorNumBuf][1];
			ColorData[0][2] = COLOR_VECTOR[ColorNumBuf][2];
			ColorNum = 1;
		} // single color

		// many color
		else
		{
				switch (ColorNumBuf)
				{
						/* spring */
						case 0x10:
								ColorData[0][0] = COLOR_VECTOR[SPRING_GREEN][0];
								ColorData[0][1] = COLOR_VECTOR[SPRING_GREEN][1];
								ColorData[0][2] = COLOR_VECTOR[SPRING_GREEN][2];

								ColorData[1][0] = COLOR_VECTOR[LAWN_GREEN][0];
								ColorData[1][1] = COLOR_VECTOR[LAWN_GREEN][1];
								ColorData[1][2] = COLOR_VECTOR[LAWN_GREEN][2];

								ColorData[2][0] = COLOR_VECTOR[PINK][0];
								ColorData[2][1] = COLOR_VECTOR[PINK][1];
								ColorData[2][2] = COLOR_VECTOR[PINK][2];

								ColorNum = 3;
						break;

						/* summer*/
						case 0x11:
								ColorData[0][0] = COLOR_VECTOR[GREEN][0];
								ColorData[0][1] = COLOR_VECTOR[GREEN][1];
								ColorData[0][2] = COLOR_VECTOR[GREEN][2];

								ColorData[1][0] = COLOR_VECTOR[RED][0];
								ColorData[1][1] = COLOR_VECTOR[RED][1];
								ColorData[1][2] = COLOR_VECTOR[RED][2];

								ColorData[2][0] = COLOR_VECTOR[LAWN_GREEN][0];
								ColorData[2][1] = COLOR_VECTOR[LAWN_GREEN][1];
								ColorData[2][2] = COLOR_VECTOR[LAWN_GREEN][2];

								ColorData[3][0] = COLOR_VECTOR[ORANGE][0];
								ColorData[3][1] = COLOR_VECTOR[ORANGE][1];
								ColorData[3][2] = COLOR_VECTOR[ORANGE][2];

								ColorNum = 4;
						break;

						/* autumn*/
						case 0x12:
								ColorData[0][0] = COLOR_VECTOR[ORANGE][0];
								ColorData[0][1] = COLOR_VECTOR[ORANGE][1];
								ColorData[0][2] = COLOR_VECTOR[ORANGE][2];

								ColorData[1][0] = COLOR_VECTOR[GOLD][0];
								ColorData[1][1] = COLOR_VECTOR[GOLD][1];
								ColorData[1][2] = COLOR_VECTOR[GOLD][2];

								ColorData[2][0] = COLOR_VECTOR[ORANGE][0];
								ColorData[2][1] = COLOR_VECTOR[ORANGE][1];
								ColorData[2][2] = COLOR_VECTOR[ORANGE][2];

								ColorData[3][0] = COLOR_VECTOR[CYAN][0];
								ColorData[3][1] = COLOR_VECTOR[CYAN][1];
								ColorData[3][2] = COLOR_VECTOR[CYAN][2];

								ColorNum = 4;

						break;

						/* winter */
						case 0x13:
								ColorData[0][0] = COLOR_VECTOR[COLD_WHITE][0];
								ColorData[0][1] = COLOR_VECTOR[COLD_WHITE][1];
								ColorData[0][2] = COLOR_VECTOR[COLD_WHITE][2];

								ColorData[1][0] = COLOR_VECTOR[SKY_BLUE][0];
								ColorData[1][1] = COLOR_VECTOR[SKY_BLUE][1];
								ColorData[1][2] = COLOR_VECTOR[SKY_BLUE][2];


								ColorData[2][0] = COLOR_VECTOR[BLUE][0];
								ColorData[2][1] = COLOR_VECTOR[BLUE][1];
								ColorData[2][2] = COLOR_VECTOR[BLUE][2];

								ColorNum = 3;
						break;

						/* Christmas' day */
						case 0x14:
								ColorData[0][0] = COLOR_VECTOR[RED][0];
								ColorData[0][1] = COLOR_VECTOR[RED][1];
								ColorData[0][2] = COLOR_VECTOR[RED][2];;

								ColorData[1][0] = COLOR_VECTOR[GREEN][0];
								ColorData[1][1] = COLOR_VECTOR[GREEN][1];
								ColorData[1][2] = COLOR_VECTOR[GREEN][2];

								ColorData[2][0] = COLOR_VECTOR[WHITE][0];
								ColorData[2][1] = COLOR_VECTOR[WHITE][1];
								ColorData[2][2] = COLOR_VECTOR[WHITE][2];

								ColorNum = 3;
						break;

						/* Valentines' day */
						case 0x15:
								for (TempCnt = 0; TempCnt < 16; TempCnt++)
								{
									if ((TempCnt % 7) == 0)
									{
										ColorData[TempCnt][0] = COLOR_VECTOR[PINK][0];
										ColorData[TempCnt][1] = COLOR_VECTOR[PINK][1];
										ColorData[TempCnt][2] = COLOR_VECTOR[PINK][2];
									}
									else if ((TempCnt % 7) == 1)
									{
										ColorData[TempCnt][0] = COLOR_VECTOR[PEACH][0];
										ColorData[TempCnt][1] = COLOR_VECTOR[PEACH][1];
										ColorData[TempCnt][2] = COLOR_VECTOR[PEACH][2];
									}
									else if ( (TempCnt % 7) == 2)
									{
										ColorData[TempCnt][0] = COLOR_VECTOR[PINK][0];
										ColorData[TempCnt][1] = COLOR_VECTOR[PINK][1];
										ColorData[TempCnt][2] = COLOR_VECTOR[PINK][2];
									}
									else if ((TempCnt % 7) == 3)
									{
										ColorData[TempCnt][0] = COLOR_VECTOR[LAWN_GREEN][0];
										ColorData[TempCnt][1] = COLOR_VECTOR[LAWN_GREEN][1];
										ColorData[TempCnt][2] = COLOR_VECTOR[LAWN_GREEN][2];
									}
									else if ((TempCnt % 7) == 4)
									{
										ColorData[TempCnt][0] = COLOR_VECTOR[PEACH][0];
										ColorData[TempCnt][1] = COLOR_VECTOR[PEACH][1];
										ColorData[TempCnt][2] = COLOR_VECTOR[PEACH][2];
									}
									else if ( (TempCnt % 7) == 5)
									{
										ColorData[TempCnt][0] = COLOR_VECTOR[PINK][0];
										ColorData[TempCnt][1] = COLOR_VECTOR[PINK][1];
										ColorData[TempCnt][2] = COLOR_VECTOR[PINK][2];
									}
									else if ((TempCnt % 7) == 6)
									{
										ColorData[TempCnt][0] = COLOR_VECTOR[PEACH][0];
										ColorData[TempCnt][1] = COLOR_VECTOR[PEACH][1];
										ColorData[TempCnt][2] = COLOR_VECTOR[PEACH][2];
									}
								}


								ColorNum = 7;
						break;

						/* Independence day */
						case 0x16:
							#ifdef	_USA_
								ColorData[0][0] = COLOR_VECTOR[RED][0];
								ColorData[0][1] = COLOR_VECTOR[RED][1];
								ColorData[0][2] = COLOR_VECTOR[RED][2];

								ColorData[1][0] = COLOR_VECTOR[WHITE][0];
								ColorData[1][1] = COLOR_VECTOR[WHITE][1];
								ColorData[1][2] = COLOR_VECTOR[WHITE][2];

								ColorData[2][0] = COLOR_VECTOR[BLUE][0];
								ColorData[2][1] = COLOR_VECTOR[BLUE][1];
								ColorData[2][2] = COLOR_VECTOR[BLUE][2];

								ColorNum = 3;
							#endif

							#ifdef	_CAN_
								ColorData[0][0] = COLOR_VECTOR[RED][0];
								ColorData[0][1] = COLOR_VECTOR[RED][1];
								ColorData[0][2] = COLOR_VECTOR[RED][2];

								ColorData[1][0] = COLOR_VECTOR[WHITE][0];
								ColorData[1][1] = COLOR_VECTOR[WHITE][1];
								ColorData[1][2] = COLOR_VECTOR[WHITE][2];

								ColorNum = 2;
							#endif


						break;

						/* Thanks giving */
						case 0x17:
								ColorData[0][0] = COLOR_VECTOR[SPRING_GREEN][0];
								ColorData[0][1] = COLOR_VECTOR[SPRING_GREEN][1];
								ColorData[0][2] = COLOR_VECTOR[SPRING_GREEN][2];

								ColorData[1][0] = COLOR_VECTOR[ORANGE][0];
								ColorData[1][1] = COLOR_VECTOR[ORANGE][1];
								ColorData[1][2] = COLOR_VECTOR[ORANGE][2];

								ColorData[2][0] = COLOR_VECTOR[RED][0];
								ColorData[2][1] = COLOR_VECTOR[RED][1];
								ColorData[2][2] = COLOR_VECTOR[RED][2];

								ColorData[3][0] = COLOR_VECTOR[LAWN_GREEN][0];
								ColorData[3][1] = COLOR_VECTOR[LAWN_GREEN][1];
								ColorData[3][2] = COLOR_VECTOR[LAWN_GREEN][2];

								ColorData[4][0] = COLOR_VECTOR[GOLD][0];
								ColorData[4][1] = COLOR_VECTOR[GOLD][1];
								ColorData[4][2] = COLOR_VECTOR[GOLD][2];

								ColorNum = 5;
						break;

						/* st. patrick's day */
						case 0x18:
								ColorData[0][0] = COLOR_VECTOR[GREEN][0];
								ColorData[0][1] = COLOR_VECTOR[GREEN][1];
								ColorData[0][2] = COLOR_VECTOR[GREEN][2];

								ColorData[1][0] = COLOR_VECTOR[SPRING_GREEN][0];
								ColorData[1][1] = COLOR_VECTOR[SPRING_GREEN][1];
								ColorData[1][2] = COLOR_VECTOR[SPRING_GREEN][2];

								ColorData[2][0] = COLOR_VECTOR[LAWN_GREEN][0];
								ColorData[2][1] = COLOR_VECTOR[LAWN_GREEN][1];
								ColorData[2][2] = COLOR_VECTOR[LAWN_GREEN][2];



								ColorNum = 3;
						break;

						/* Halloween */
						case 0x19:
								for (TempCnt = 0; TempCnt < 16; TempCnt++)
								{
									if ( (TempCnt % 9) == 0)
									{
										ColorData[TempCnt][0] = COLOR_VECTOR[ORANGE][0];
										ColorData[TempCnt][1] = COLOR_VECTOR[ORANGE][1];
										ColorData[TempCnt][2] = COLOR_VECTOR[ORANGE][2];
									}
									else
									if ((TempCnt % 9) == 1)
									{
										ColorData[TempCnt][0] = COLOR_VECTOR[PURPLE][0];
										ColorData[TempCnt][1] = COLOR_VECTOR[PURPLE][1];
										ColorData[TempCnt][2] = COLOR_VECTOR[PURPLE][2];
									}
									else
									if ((TempCnt % 9) == 2)
									{
										ColorData[TempCnt][0] = COLOR_VECTOR[DARK_GREEN][0];
										ColorData[TempCnt][1] = COLOR_VECTOR[DARK_GREEN][1];
										ColorData[TempCnt][2] = COLOR_VECTOR[DARK_GREEN][2];
									}
									else
									if ((TempCnt % 9) == 3)
									{
										ColorData[TempCnt][0] = COLOR_VECTOR[DARK_RED][0];
										ColorData[TempCnt][1] = COLOR_VECTOR[DARK_RED][1];
										ColorData[TempCnt][2] = COLOR_VECTOR[DARK_RED][2];
									}
									else
									if ((TempCnt % 9) == 4)
									{
										ColorData[TempCnt][0] = COLOR_VECTOR[PURPLE][0];
										ColorData[TempCnt][1] = COLOR_VECTOR[PURPLE][1];
										ColorData[TempCnt][2] = COLOR_VECTOR[PURPLE][2];
									}
									else
									if ((TempCnt % 9) == 5)
									{
										ColorData[TempCnt][0] = COLOR_VECTOR[GREEN][0];
										ColorData[TempCnt][1] = COLOR_VECTOR[GREEN][1];
										ColorData[TempCnt][2] = COLOR_VECTOR[GREEN][2];
									}
									else
									if ((TempCnt % 9) == 6)
									{
										ColorData[TempCnt][0] = COLOR_VECTOR[PURPLE][0];
										ColorData[TempCnt][1] = COLOR_VECTOR[PURPLE][1];
										ColorData[TempCnt][2] = COLOR_VECTOR[PURPLE][2];
									}
									else
									if ((TempCnt % 9) == 7)
									{
										ColorData[TempCnt][0] = COLOR_VECTOR[DARK_GREEN][0];
										ColorData[TempCnt][1] = COLOR_VECTOR[DARK_GREEN][1];
										ColorData[TempCnt][2] = COLOR_VECTOR[DARK_GREEN][2];
									}
									else
									if ((TempCnt % 9) == 8)
									{
										ColorData[TempCnt][0] = COLOR_VECTOR[DARK_RED][0];
										ColorData[TempCnt][1] = COLOR_VECTOR[DARK_RED][1];
										ColorData[TempCnt][2] = COLOR_VECTOR[DARK_RED][2];
									}
								}

								ColorNum = 9;
						break;

						/* sun */
						case 0x1A:
								ColorData[0][0] = COLOR_VECTOR[RED][0];
								ColorData[0][1] = COLOR_VECTOR[RED][1];
								ColorData[0][2] = COLOR_VECTOR[RED][2];

								ColorData[1][0] = COLOR_VECTOR[ORANGE][0];
								ColorData[1][1] = COLOR_VECTOR[ORANGE][1];
								ColorData[1][2] = COLOR_VECTOR[ORANGE][2];

								ColorData[2][0] = COLOR_VECTOR[GOLD][0];
								ColorData[2][1] = COLOR_VECTOR[GOLD][1];
								ColorData[2][2] = COLOR_VECTOR[GOLD][2];

								ColorData[3][0] = COLOR_VECTOR[YELLOW][0];
								ColorData[3][1] = COLOR_VECTOR[YELLOW][1];
								ColorData[3][2] = COLOR_VECTOR[YELLOW][2];

								ColorNum = 4;
						break;

						/* earth */
						case 0x1B:
								ColorData[0][0] = COLOR_VECTOR[BLUE][0];
								ColorData[0][1] = COLOR_VECTOR[BLUE][1];
								ColorData[0][2] = COLOR_VECTOR[BLUE][2];

								ColorData[1][0] = COLOR_VECTOR[GREEN][0];
								ColorData[1][1] = COLOR_VECTOR[GREEN][1];
								ColorData[1][2] = COLOR_VECTOR[GREEN][2];

								ColorData[2][0] = COLOR_VECTOR[SKY_BLUE][0];
								ColorData[2][1] = COLOR_VECTOR[SKY_BLUE][1];
								ColorData[2][2] = COLOR_VECTOR[SKY_BLUE][2];


								ColorData[3][0] = COLOR_VECTOR[ORANGE][0];
								ColorData[3][1] = COLOR_VECTOR[ORANGE][1];
								ColorData[3][2] = COLOR_VECTOR[ORANGE][2];

								ColorNum = 4;
						break;

						/* Multi */
						case 0x1C:
							for (TempCnt = 0; TempCnt < 12; TempCnt++)
								{
										ColorData[TempCnt][0] = COLOR_VECTOR[TempCnt][0];
										ColorData[TempCnt][1] = COLOR_VECTOR[TempCnt][1];
										ColorData[TempCnt][2] = COLOR_VECTOR[TempCnt][2];
								}

								ColorNum = 12;
						break;
				}//switch (RcvData[1])
		} // many color
	}



#elif COLOR_RGB_3D
	if (DisplayData.Mode > 0xA)
	{
		for (TempCnt = 0; TempCnt < 7; TempCnt++)
		{
			ColorData[TempCnt][0] = COLOR_VECTOR[TempCnt + 1][0];
			ColorData[TempCnt][1] = COLOR_VECTOR[TempCnt + 1][1];
			ColorData[TempCnt][2] = COLOR_VECTOR[TempCnt + 1][2];
		}
	}
	else
	{
		ColorData[0][0]	= COLOR_VECTOR[ColorNumBuf][0];
		ColorData[0][1]	= COLOR_VECTOR[ColorNumBuf][1];
		ColorData[0][2]	= COLOR_VECTOR[ColorNumBuf][2];
	}

#endif
}






/************************************************************************
 *
 * FunctionName   Hex_To_Char
 *
 *  Input					 HexBuf
 *								 HexBuf < 0x10
*************************************************************************/
static _Uint8		Hex_To_Char(_Uint8 HexBuf)
{
	if (HexBuf > 0x0F)		HexBuf &= 0x0F;

	//Hex = 0x0,0x1...0x9
	if (HexBuf < 0xA)
	{
		return (HexBuf + '0');
	}

	// Hex = 0xA,0xB ... 0xF
	HexBuf -= 0xA;
	return (HexBuf + 'A');
}
