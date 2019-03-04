/*******************************************************************************
	*
	*		FILE NAME
	*								Led_Display.c
	*
*******************************************************************************/
#include "Display_Ctrl.h"


//===================================================================================
//
//																WARNING MODE
//														
//																Timer_Warning
//																Direct_Set
//																Horse_Set_Warning
//																Horse_Whole_Test
//																Horse_Single_Test
//
//=====================================================================================
/*
 * FunctionName All_Flash
 */
void All_Flash(uint8_t r, uint8_t g, uint8_t b)
{
	if (DisplayData.InitFlag == TRUE)
	{
		DisplayData.InitFlag = FALSE;
		TempR = 0;
		TempG = 0;
		TempB = 0;
		All_Color(0,0,0);
		SpeedTime = 0;
		ModeStep[0] = 0;

		return;
	}

	/* Speed Control */
	if (SpeedTime < 8)
	{
		SpeedTime++;
		return;
	}
	SpeedTime = 0;

	/* Flash Three Times */
	if (ModeStep[0] % 2 == 0)
	{
		TempR = r;
		TempG = g;
		TempB = b;
	}
	else							
	{
		TempR = 0;
		TempG = 0;
		TempB = 0;
	}

	/* Restore the mode */
	ModeStep[0]++;
	if (ModeStep[0] > 5)
	{
		DisplayData.Mode 		= DisplayData.ModeBuf;
		DisplayData.InitFlag 	= TRUE;
	}

	/* Led Data Update */
	All_Color(TempR, TempG, TempB);
}

/*
 * FunctionName		All_Color
 */
void All_Color(_Uint8 BufR, _Uint8 BufG, _Uint8 BufB)
{
	_Uint8		TempVar = 0;
	
	for (TempVar = 0; TempVar < LED_TOTAL; TempVar++)
	{
		LedData.Buffer[TempVar].DutyR = BufR;
		LedData.Buffer[TempVar].DutyG = BufG;
		LedData.Buffer[TempVar].DutyB = BufB;
	}
}



/**
	* FunctionName		All_Off
	*/
void All_Off(void)
{
	if (DisplayData.InitFlag == TRUE)
	{
		DisplayData.InitFlag		= FALSE;
		
		All_Color(0,0,0);
	}
}



/**
	* FunctionName		Steady
	*/
void Steady(void)
{
	if (DisplayData.InitFlag == TRUE)
	{
		DisplayData.InitFlag		= FALSE;
		
		for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++)
		{
			TempColor = TempGrp % ColorNum;
			for (TempLed = 0; TempLed < LED_MAX; TempLed++)
			{
				LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR		= ColorData[TempColor][R];
				LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG		= ColorData[TempColor][G];
				LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB		= ColorData[TempColor][B];
			}
		}
	}
}

/**
	* FunctionName		Blink
	*/
void Blink(void)
{
	if (DisplayData.InitFlag == TRUE)
	{
		DisplayData.InitFlag = FALSE;
		
		for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++)
		{
			TempColor = TempGrp % ColorNum;
			for (TempLed = 0; TempLed < LED_MAX; TempLed++)
			{
				LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR		= ColorData[TempColor][R];
				LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG		= ColorData[TempColor][G];
				LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB		= ColorData[TempColor][B];
			}
		}
		
		for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++)
		{
			srand(RndSeed);
			RndSeed += 17;
			HoldTime[TempGrp] = (_Uint8)rand() % 20;
			ModeStep[TempGrp] = 1;
			ModeTime[TempGrp] = 0;
		}
		
		SpeedTime = 0;
		
		return;
	}
	
	if (SpeedTime < 10)
	{
		SpeedTime++;
		return;
	}
	SpeedTime = 0;
	
	RndSeed++;
	for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++)
	{
		switch (ModeStep[TempGrp])
		{
			case 0:
			{
				TempColor = TempGrp % ColorNum;
				for (TempLed = 0; TempLed < LED_MAX; TempLed++)
				{
					LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR		= ColorData[TempColor][R];
					LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG		= ColorData[TempColor][G];
					LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB		= ColorData[TempColor][B];
				}
				ModeStep[TempGrp] ++;
			} break;
			
			case 1:
			{
				ModeTime[TempGrp]++;
				if (ModeTime[TempGrp] > HoldTime[TempGrp])
				{
					ModeTime[TempGrp] = 0;
					srand(RndSeed++);
					RndSeed += 17;
					HoldTime[TempGrp] = (_Uint8)rand() % 20;
					ModeStep[TempGrp]++;
				}
			} break;
			
			case 2:
			{
				TempColor = TempGrp % ColorNum;
				for (TempLed = 0; TempLed < LED_MAX; TempLed++)
				{
					LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR		= ColorData[TempColor][R] / FADE_LEVEL * 5;
					LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG		= ColorData[TempColor][G] / FADE_LEVEL * 5;
					LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB		= ColorData[TempColor][B] / FADE_LEVEL * 5;
				}
				ModeStep[TempGrp] = 0;
			} break;
		}
	}
}


/**
	* FunctionName		Sparkle
	*/
void Sparkle(void)
{
	if (DisplayData.InitFlag == TRUE)
	{
		DisplayData.InitFlag = FALSE;
		
		for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++)
		{
			TempColor = TempGrp % ColorNum;
			for (TempLed = 0; TempLed < LED_MAX; TempLed++)
			{
				LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR		= ColorData[TempColor][R] / FADE_LEVEL * 20;
				LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG		= ColorData[TempColor][G] / FADE_LEVEL * 20;
				LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB		= ColorData[TempColor][B] / FADE_LEVEL * 20;
			}
		}
		
		
		for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++)
		{
			srand(RndSeed++);
			ModeTime[TempGrp]		= (_Uint8)rand() % 10;
			srand(RndSeed++);
			HoldTime[TempGrp]		= (_Uint8)rand() % 20 + 10;
		}
		
		SpeedTime = 0;
		
		return;
	}
	
	/* Speed Control */
	if (SpeedTime < 1)
	{
		SpeedTime++;
		return;
	}
	SpeedTime = 0;
	
	/* Sparkle Mode Control */
	RndSeed++;
	for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++)
	{
		ModeTime[TempGrp]++;
		if (ModeTime[TempGrp] > HoldTime[TempGrp])
		{
			ModeTime[TempGrp] = 0;
			TempColor 	= TempGrp % ColorNum;
			TempR				= ColorData[TempColor][R];
			TempG				= ColorData[TempColor][G];
			TempB				= ColorData[TempColor][B];
		
			switch (ModeStep[TempGrp])
			{
				case 0:
				{
					for (TempLed = 0; TempLed < LED_MAX; TempLed++)
					{
						LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR		= TempR / 3;
						LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG		= TempG / 3;
						LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB		= TempB / 3;
					}
					ModeStep[TempGrp]++;
					RAND();
					HoldTime[TempGrp] = (_Uint8)rand() % 10 + 2;
				} break;
				
				default:
				{
					for (TempLed = 0; TempLed < LED_MAX; TempLed++)
					{
						LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR		= TempR;
						LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG		= TempG;
						LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB		= TempB;
					}
					ModeStep[TempGrp] = 0;
					RAND();
					HoldTime[TempGrp] = (_Uint8)rand() % 20 + 10;
				} break;
			}
		}
	}
}

/**
	* FunctionName	Instead
	*/
void Instead(void)
{
	/* Initialize */
	if (DisplayData.InitFlag == TRUE)
	{
		DisplayData.InitFlag		= FALSE;
		
		ModeStep[0] = 0;
		SpeedTime		= 0;
		LedCnt			= 0;
		TempColor		= 0;
		HoldTime[0] = 0;
		
		if (ModeSynFlag == FALSE)
		{
			for (TempLed = 0; TempLed < LED_TOTAL; TempLed++)
			{
				LedData.Buffer[TempLed].DutyR = 0;
				LedData.Buffer[TempLed].DutyG = 0;
				LedData.Buffer[TempLed].DutyB = 0;
			}
		}
		else
		{
			ModeSynFlag = FALSE;
		}
		
		FadeR = ColorData[0][R] / FADE_LEVEL;
		FadeG = ColorData[0][G] / FADE_LEVEL;
		FadeB = ColorData[0][B] / FADE_LEVEL;
		return;
	}
	
	/* Speed Control */
  SpeedTime++;
  if (SpeedTime >= 6){
    SpeedTime = 0;
	
    /* Mode Control */
    if (ColorNum == 1)
    {
      switch (ModeStep[0])
      {
        case 0:
        {
          TempR	= ColorData[TempColor][R];
          TempG	= ColorData[TempColor][G];
          TempB	= ColorData[TempColor][B];
          
          LedCnt++;
          if (LedCnt >= GRP_MAX)
          {
            LedCnt = 0;
            ModeStep[0]++;
          }
          
          for (TempLed = 0; TempLed < LED_MAX; TempLed++)
          {
            LedData.Buffer[LedCnt * LED_MAX + TempLed].DutyR = TempR;
            LedData.Buffer[LedCnt * LED_MAX + TempLed].DutyG = TempG;
            LedData.Buffer[LedCnt * LED_MAX + TempLed].DutyB = TempB;
          }
        } break;
        
        case 1:
        {
          HoldTime[0]++;
          if (HoldTime[0] >= (50 - GRP_MAX))
          {
            HoldTime[0] = 0;
            ModeStep[0]++;
          }
        } break;
        
        default:
        {
          if (LedData.Buffer[0].DutyR > 0
              || LedData.Buffer[0].DutyG > 0
                || LedData.Buffer[0].DutyB > 0)
          {
            for (TempCnt = 0; TempCnt < LED_TOTAL; TempCnt++)
            {
              LedData.Buffer[TempCnt].DutyR -= FadeR;
              LedData.Buffer[TempCnt].DutyG -= FadeG;
              LedData.Buffer[TempCnt].DutyB -= FadeB;
            }
          }
          else
          {
            ModeStep[0] = 0;
            HorseCnt++;
            if (HorseCnt > 20)
            {
              HorseCnt = 0;
              SynFlag = TRUE;
              DisplayData.InitFlag = TRUE;
            }
          }
        } break;
      }
    }
      
    else
    {
      switch (ModeStep[0])
      {
        case 0:
        {
          TempR	= ColorData[TempColor][R];
          TempG	= ColorData[TempColor][G];
          TempB	= ColorData[TempColor][B];
          
          LedCnt++;
          if (LedCnt >= LED_TOTAL)
          {
            LedCnt = 0;
            TempColor++;
            if (TempColor >= ColorNum)		TempColor = 0x0;
            ModeStep[0]++;
          }
        } break;
        
        default:
        {
          HoldTime[0]++;
          if (HoldTime[0] >= (50 - LED_TOTAL))
          {
            HoldTime[0] = 0;
            ModeStep[0] = 0;
            HorseCnt++;
            if (HorseCnt > 20)
            {
              HorseCnt = 0;
              DisplayData.InitFlag = TRUE;
              SynFlag = TRUE;
            }
          }
        } break;
      }
    
      #if _AL92A_
      if (LedCnt > 0)
      {
        LedData.Buffer[LedCnt - 1].DutyR	= TempR;
        LedData.Buffer[LedCnt - 1].DutyG	= TempG;
        LedData.Buffer[LedCnt - 1].DutyB	= TempB;
      }
      else
      {
        LedData.Buffer[LED_TOTAL - 1].DutyR	= TempR;
        LedData.Buffer[LED_TOTAL - 1].DutyG	= TempG;
        LedData.Buffer[LED_TOTAL - 1].DutyB	= TempB;
      }
      
      #elif _AL92B_
      switch (LedCnt)
      {
        case 1:		ModeLed[0] = 1;			ModeLed[1] = 8;			 ModeLed[2] = 15;	break;
        case 3:		ModeLed[0] = 2;			ModeLed[1] = 9;			 ModeLed[2] = 16;	break;
        case 5:		ModeLed[0] = 3;			ModeLed[1] = 10;		 ModeLed[2] = 17;	break;
        case 7:		ModeLed[0] = 4;			ModeLed[1] = 11;		 ModeLed[2] = 18;	break;
        case 9:		ModeLed[0] = 5;			ModeLed[1] = 12;		 ModeLed[2] = 19;	break;
        case 11:	ModeLed[0] = 6;			ModeLed[1] = 13;		 ModeLed[2] = 20;	break;
        case 13:	ModeLed[0] = 0;			ModeLed[1] = 7;			 ModeLed[2] = 14;	break;
      }
      
      LedData.Buffer[ModeLed[0]].DutyR	= TempR;
      LedData.Buffer[ModeLed[0]].DutyG	= TempG;
      LedData.Buffer[ModeLed[0]].DutyB	= TempB;
      LedData.Buffer[ModeLed[1]].DutyR	= TempR;
      LedData.Buffer[ModeLed[1]].DutyG	= TempG;
      LedData.Buffer[ModeLed[1]].DutyB	= TempB;
      LedData.Buffer[ModeLed[2]].DutyR	= TempR;
      LedData.Buffer[ModeLed[2]].DutyG	= TempG;
      LedData.Buffer[ModeLed[2]].DutyB	= TempB;
      
      #elif _AL92C_
      switch (LedCnt)
      {
        case 1:		ModeLed[0] = 0;			ModeLed[1] = 6;			 	break;
        case 2:		ModeLed[0] = 1;			ModeLed[1] = 5;			 	break;
        case 3:		ModeLed[0] = 2;			ModeLed[1] = 4;			 	break;
        case 4:		ModeLed[0] = 3;			ModeLed[1] = 3;			 	break;
        case 5:		ModeLed[0] = 7;			ModeLed[1] = 13;			break;
        case 6:		ModeLed[0] = 8;			ModeLed[1] = 12;			break;
        case 7:		ModeLed[0] = 9;			ModeLed[1] = 11;			break;
        case 8:		ModeLed[0] = 10;		ModeLed[1] = 10;			break;
        case 9:		ModeLed[0] = 14;		ModeLed[1] = 20;			break;
        case 10:	ModeLed[0] = 15;		ModeLed[1] = 19;			break;
        case 11:	ModeLed[0] = 16;		ModeLed[1] = 18;			break;
        case 12:	ModeLed[0] = 17;		ModeLed[1] = 17;			break;
      }
      
      LedData.Buffer[ModeLed[0]].DutyR	= TempR;
      LedData.Buffer[ModeLed[0]].DutyG	= TempG;
      LedData.Buffer[ModeLed[0]].DutyB	= TempB;
      LedData.Buffer[ModeLed[1]].DutyR	= TempR;
      LedData.Buffer[ModeLed[1]].DutyG	= TempG;
      LedData.Buffer[ModeLed[1]].DutyB	= TempB;
      
      #elif _AL95_
      switch (LedCnt)
      {
        case 0:			ModeLed[0] = 0;	break;
        case 1:			ModeLed[0] = 1;	break;
        case 2:			ModeLed[0] = 2;	break;
      }
      
      LedData.Buffer[ModeLed[0]].DutyR	= TempR;
      LedData.Buffer[ModeLed[0]].DutyG	= TempG;
      LedData.Buffer[ModeLed[0]].DutyB	= TempB;
      
      #endif
    }
  }
}



/**
	* FunctionName	Sea_Wave
	*/
void Sea_Wave(void)
{
	//--------------------------------------------------------------------
	// Initialize
	//--------------------------------------------------------------------
	if (DisplayData.InitFlag == TRUE)
	{
		DisplayData.InitFlag = FALSE;
		
		for (TempLed = 0; TempLed < LED_TOTAL; TempLed++)
		{
			LedData.Buffer[TempLed].DutyR	= 0;
			LedData.Buffer[TempLed].DutyG	= 0;
			LedData.Buffer[TempLed].DutyB	= 0;
		}
		
		ModeTime[0] = 0;
		ModeStep[0] = 0;
		TempColor		= 0;
		SpeedTime 	= 0;
		HoldTime[0] = 0;
		TempR				= 0;
		TempG				= 0;
		TempB				= 0;
		FadeR				= ColorData[TempColor][R] / FADE_LEVEL;
		FadeG				= ColorData[TempColor][G] / FADE_LEVEL;
		FadeB				= ColorData[TempColor][B] / FADE_LEVEL;
		ModeSynFlag = FALSE;
		return;
	}
	
	
	//------------------------------------------------------------------
	// Speed Control
	//------------------------------------------------------------------
  SpeedTime++;
	if (SpeedTime >= 4)
	{
    SpeedTime = 0;
	
	
    //------------------------------------------------------------------
    // Mode Control
    //------------------------------------------------------------------
    switch (ModeStep[0])
    {
      case 0:			/* Fade in */
      {
              if (TempR < ColorData[TempColor][R]
                  || TempG < ColorData[TempColor][G]
                    || TempB < ColorData[TempColor][B])
              {
                TempR += FadeR;
                TempG += FadeG;
                TempB += FadeB;
              }
              else
              {
                ModeStep[0]++;
                HoldTime[0] = 0;
              }
      } break;
      
      case 1:			/* Hold for 5 seconds */
      {
              HoldTime[0]++;
              if (HoldTime[0] >= 50)
              {
                HoldTime[0] = 0;
                ModeStep[0]++;
              }
      } break;
      
      case 2:		/* Fade out */
      {
              if (TempR > 0 || TempG > 0 || TempB > 0)
              {
                TempR -= FadeR;
                TempG -= FadeG;
                TempB -= FadeB;
              }
              else
              {
                ModeStep[0] = 0;
                TempColor++;
                if (TempColor >= ColorNum)		
                {
                  TempColor = 0;
                  HorseCnt++;
                  if (HorseCnt > 6)
                  {
                    HorseCnt = 0;
                    DisplayData.InitFlag = TRUE;
                    SynFlag = TRUE;
                  }
                }
                FadeR				= ColorData[TempColor][R] / FADE_LEVEL;
                FadeG				= ColorData[TempColor][G] / FADE_LEVEL;
                FadeB				= ColorData[TempColor][B] / FADE_LEVEL;
              }
      } break;
    }
    
    //----------------------------------------------------------------
    // Led Data Get
    //----------------------------------------------------------------
    for (TempLed = 0; TempLed < LED_TOTAL; TempLed++)
    {
      LedData.Buffer[TempLed].DutyR	= TempR;
      LedData.Buffer[TempLed].DutyG	= TempG;
      LedData.Buffer[TempLed].DutyB	= TempB;
    }
  }
}


/**
	* FunctionName	Roll
	*/
#if _AL92A_
void Roll(void)
{
	if (DisplayData.InitFlag == TRUE)
	{
		DisplayData.InitFlag = FALSE;
		
		FadeR = ColorData[0][R] / FADE_LEVEL;
		FadeG = ColorData[0][G] / FADE_LEVEL;
		FadeB = ColorData[0][B] / FADE_LEVEL;
		
		if (ColorNum == 1)
		{
			for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++)
			{
				if (TempGrp % 2 == 0)
				{
					for (TempLed = 0; TempLed < LED_MAX; TempLed++)
					{
						LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR  = FadeR * 20;  
						LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG  = FadeG * 20;  
						LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB  = FadeB * 20;  
					}
				}
				else
				{
					for (TempLed = 0; TempLed < LED_MAX; TempLed++)
					{
						LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR  = FadeR * 50;  
						LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG  = FadeG * 50;  
						LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB  = FadeB * 50;  
					}
				}
			}
		}
		else
		{
			for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++)
			{
				TempColor = TempGrp % ColorNum;
				for (TempLed = 0; TempLed < LED_MAX; TempLed++)
				{
					LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR  = ColorData[TempColor][R];  
					LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG  = ColorData[TempColor][G];
					LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB  = ColorData[TempColor][B];
				}
			}
		}
		
		SpeedTime 		= 0;
		ModeStep[0]		= 0;
		TempColor			= 0;
		return;
	}
	
	/* Speed Control */
	if (SpeedTime < 40)
	{
		SpeedTime++;
		return;
	}
	SpeedTime = 0;
	
	/* Mode Control */
	if (ColorNum == 1)
	{
		switch (ModeStep[0])
		{
				case 0:
				{
					TempR    = FadeR * 20;
					TempG    = FadeG * 20;
					TempB    = FadeB * 20;
					ModeStep[0]++;
				}	break;

				default:
				{
					TempR = ColorData[0][R];
					TempG = ColorData[0][G];
					TempB = ColorData[0][B];
					ModeStep[0] = 0;
				}	break;
		}
		
		for (TempGrp = GRP_MAX - 1; TempGrp > 0; TempGrp--)
		{
			for (TempLed = 0; TempLed < LED_MAX; TempLed++)
			{
				LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR	= LedData.Buffer[(TempGrp - 1) * LED_MAX + TempLed].DutyR;
				LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG	= LedData.Buffer[(TempGrp - 1) * LED_MAX + TempLed].DutyG;
				LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB	= LedData.Buffer[(TempGrp - 1) * LED_MAX + TempLed].DutyB;
			}
		}
		
		for (TempLed = 0; TempLed < LED_MAX; TempLed++)
		{
			LedData.Buffer[TempLed].DutyR		= TempR;
			LedData.Buffer[TempLed].DutyG		= TempG;
			LedData.Buffer[TempLed].DutyB		= TempB;
		}
	}
	else
	{
		TempR	= ColorData[TempColor][R];
		TempG = ColorData[TempColor][G];
		TempB = ColorData[TempColor][B];
		
		TempColor++;
		if (TempColor >= ColorNum)		TempColor = 0;
		
		
		
		for (TempGrp = GRP_MAX - 1; TempGrp > 0; TempGrp--)
		{
			for (TempLed = 0; TempLed < LED_MAX; TempLed++)
			{
				LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR	= LedData.Buffer[(TempGrp - 1)* LED_MAX + TempLed].DutyR;
				LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG	= LedData.Buffer[(TempGrp - 1)* LED_MAX + TempLed].DutyG;
				LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB	= LedData.Buffer[(TempGrp - 1)* LED_MAX + TempLed].DutyB;
			}
		}
		
		for (TempLed = 0; TempLed < LED_MAX; TempLed++)
		{
			LedData.Buffer[TempLed].DutyR	= TempR;
			LedData.Buffer[TempLed].DutyG	= TempG;
			LedData.Buffer[TempLed].DutyB	= TempB;
		}
	}
}

#elif _AL92B_ | _AL92C_ | _AL95_
void Roll(void)
{
	if (DisplayData.InitFlag == TRUE)
	{
		DisplayData.InitFlag = FALSE;
		
		FadeR = ColorData[0][R] / FADE_LEVEL;
		FadeG = ColorData[0][G] / FADE_LEVEL;
		FadeB = ColorData[0][B] / FADE_LEVEL;
		
		if (ColorNum == 1)
		{
			for (TempLed = 0; TempLed < LED_TOTAL; TempLed++)
			{
				TempColor = TempLed % ColorNum;
				if ((TempLed % 2) == 0)
				{
					LedData.Buffer[TempLed].DutyR		= FadeR * 10;
					LedData.Buffer[TempLed].DutyG		= FadeG * 10;
					LedData.Buffer[TempLed].DutyB		= FadeB * 10;
				}
				else
				{
					LedData.Buffer[TempLed].DutyR		= FadeR * 50;
					LedData.Buffer[TempLed].DutyG		= FadeG * 50;
					LedData.Buffer[TempLed].DutyB		= FadeB * 50;
				}
			}
		}
		else
		{
			for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++)
			{
				TempColor = TempGrp % ColorNum;
				for (TempLed = 0; TempLed < LED_MAX; TempLed++)
				{
					LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR  = ColorData[TempColor][R];  
					LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG  = ColorData[TempColor][G];
					LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB  = ColorData[TempColor][B];
				}
			}
		}
		
		SpeedTime 		= 0;
		ModeStep[0]		= 0;
		TempColor			= 0;
		return;
	}
	
	/* Speed Control */
	if (SpeedTime < 40)
	{
		SpeedTime++;
		return;
	}
	SpeedTime = 0;
	
	/* Mode Control */
	if (ColorNum == 1)
	{
		switch (ModeStep[0])
		{
				case 0:
				{
					TempR    = FadeR * 20;
					TempG    = FadeG * 20;
					TempB    = FadeB * 20;
					ModeStep[0]++;
				}	break;

				default:
				{
					TempR = ColorData[0][R];
					TempG = ColorData[0][G];
					TempB = ColorData[0][B];
					ModeStep[0] = 0;
				}	break;
		}
		
		for (TempLed = LED_TOTAL - 1; TempLed > 0; TempLed--)
		{
			LedData.Buffer[TempLed].DutyR	= LedData.Buffer[TempLed - 1].DutyR;
			LedData.Buffer[TempLed].DutyG	= LedData.Buffer[TempLed - 1].DutyG;
			LedData.Buffer[TempLed].DutyB	= LedData.Buffer[TempLed - 1].DutyB;
		}
		
		LedData.Buffer[0].DutyR		= TempR;
		LedData.Buffer[0].DutyG		= TempG;
		LedData.Buffer[0].DutyB		= TempB;
	}
	else
	{
		TempR	= ColorData[TempColor][R];
		TempG = ColorData[TempColor][G];
		TempB = ColorData[TempColor][B];
		
		TempColor++;
		if (TempColor >= ColorNum)		TempColor = 0;
		
		
		
		for (TempGrp = GRP_MAX - 1; TempGrp > 0; TempGrp--)
		{
			for (TempLed = 0; TempLed < LED_MAX; TempLed++)
			{
				LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR	= LedData.Buffer[(TempGrp - 1)* LED_MAX + TempLed].DutyR;
				LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG	= LedData.Buffer[(TempGrp - 1)* LED_MAX + TempLed].DutyG;
				LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB	= LedData.Buffer[(TempGrp - 1)* LED_MAX + TempLed].DutyB;
			}
		}
		
		for (TempLed = 0; TempLed < LED_MAX; TempLed++)
		{
			LedData.Buffer[TempLed].DutyR	= TempR;
			LedData.Buffer[TempLed].DutyG	= TempG;
			LedData.Buffer[TempLed].DutyB	= TempB;
		}
	}
}
#endif



/**
	* FunctionName	Ripple
	*/
void Ripple(void)
{
	/* Initialize */
	if (DisplayData.InitFlag == TRUE)
	{
		DisplayData.InitFlag 		= FALSE;
		
		for (TempLed = 0; TempLed < LED_TOTAL; TempLed++)
		{
			LedData.Buffer[TempLed].DutyR			= 0;
			LedData.Buffer[TempLed].DutyG 		= 0;
			LedData.Buffer[TempLed].DutyB			= 0;
			
			ModeTime[TempLed]		= 0;
			ModeStep[TempLed]		= 0;
			srand(RndSeed++);
			HoldTime[TempLed]		= (_Uint8)rand() % 25 + 26;
		}
		
		SpeedTime		= 0;
		return;
	}
	
	/* Mode Control */
	for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++)
	{
		RndSeed += 7;
		ModeTime[TempGrp]++;
		if (ModeTime[TempGrp] > (_Uint8)rand() % 5)
		{
			ModeTime[TempGrp] = 0;
			TempColor		= TempGrp % ColorNum;
			FadeR				= ColorData[TempColor][R] / FADE_LEVEL;
			FadeG				= ColorData[TempColor][G] / FADE_LEVEL;
			FadeB				= ColorData[TempColor][B] / FADE_LEVEL;
			
			switch (ModeStep[TempGrp])
			{
				case 0:
				{
					if 
					(		(LedData.Buffer[TempGrp * LED_MAX].DutyR < FadeR * HoldTime[TempGrp])
					 || (LedData.Buffer[TempGrp * LED_MAX].DutyG < FadeG * HoldTime[TempGrp])
					 || (LedData.Buffer[TempGrp * LED_MAX].DutyB < FadeB * HoldTime[TempGrp])
					)
					{
						for (TempLed = 0; TempLed < LED_MAX; TempLed++)
						{
							LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR		+= FadeR;
							LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG		+= FadeG;
							LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB		+= FadeB;
						}
					}
					else
					{
						ModeStep[TempGrp]++;
						HoldTime[TempGrp] 	= (_Uint8)rand() % 10;
					}
				} break;
				
				default:
				{
					if 
					(		(LedData.Buffer[TempGrp * LED_MAX].DutyR > FadeR * HoldTime[TempGrp])
					 || (LedData.Buffer[TempGrp * LED_MAX].DutyG > FadeG * HoldTime[TempGrp])
					 || (LedData.Buffer[TempGrp * LED_MAX].DutyB > FadeB * HoldTime[TempGrp])
					)
					{
						for (TempLed = 0; TempLed < LED_MAX; TempLed++)
						{
							LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR		-= FadeR;
							LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG		-= FadeG;
							LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB		-= FadeB;
						}
					}
					else
					{
						ModeStep[TempGrp] = 0;
						HoldTime[TempGrp] 	= (_Uint8)rand() % 25 + 26;
					}
				} break;
			}
		}
	}
}



/**
	* FunctionName	Flower_Bloom
	*/
void Flower_Bloom(void)
{
	/* Initialize */
	if (DisplayData.InitFlag == TRUE)
	{
		DisplayData.InitFlag = FALSE;
		
		for (TempLed = 0; TempLed < LED_TOTAL; TempLed++)
		{
			LedData.Buffer[TempLed].DutyR		= 0;
			LedData.Buffer[TempLed].DutyG		= 0;
			LedData.Buffer[TempLed].DutyB		= 0;
			
			srand(RndSeed++);
			RndSeed += 17;
			HoldTime[TempLed] = (_Uint8)rand() % 20;
			ModeStep[TempLed] = 0;
			ModeTime[TempLed] = 0;
		}
		
		SpeedTime = 50;
		LedCnt		= 0;
		return;
	}
	
	for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++)
	{
		
		TempColor 	= TempGrp % ColorNum;
		FadeR				= ColorData[TempColor][R] / FADE_LEVEL;
		FadeG				= ColorData[TempColor][G] / FADE_LEVEL;
		FadeB				= ColorData[TempColor][B] / FADE_LEVEL;
		switch (ModeStep[TempGrp])
		{
			case 0:
			{
				ModeTime[TempGrp]++;
				if (ModeTime[TempGrp] > HoldTime[TempGrp])
				{
					ModeTime[TempGrp] = 0;
					if
					(
							(LedData.Buffer[TempGrp * LED_MAX].DutyR < ColorData[TempColor][R] / 5)
						||(LedData.Buffer[TempGrp * LED_MAX].DutyG < ColorData[TempColor][G] / 5)
						||(LedData.Buffer[TempGrp * LED_MAX].DutyB < ColorData[TempColor][B] / 5)
					)
					{
						for (TempLed = 0; TempLed < LED_MAX; TempLed++)
						{
							LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR		+= FadeR;
							LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG		+= FadeG;
							LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB		+= FadeB;
						}
					}
					else
					{
						ModeStep[TempGrp]++;
					}
				} 
			} break;
			
			case 1:
			{
				for (TempLed = 0; TempLed < LED_MAX; TempLed++)
				{
					LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR	= ColorData[TempColor][R];
					LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG	= ColorData[TempColor][G];
					LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB	= ColorData[TempColor][B];
				}
				ModeStep[TempGrp]++;
			} break;
			
			case 2:
			{
				ModeTime[TempGrp]++;
				if (ModeTime[TempGrp] > SpeedTime)
				{
					ModeTime[TempGrp] = 0;
					ModeStep[TempGrp]++;
					srand(RndSeed);
					RndSeed += 17;
					HoldTime[TempGrp]	= (_Uint8)rand() % 10;
				}
			} break;
			
			default:
			{
				ModeTime[TempGrp]++;
				if (ModeTime[TempGrp] > HoldTime[TempGrp])
				{
					ModeTime[TempGrp] = 0;
					if
					(
							(LedData.Buffer[TempGrp * LED_MAX].DutyR > 0)
						||(LedData.Buffer[TempGrp * LED_MAX].DutyG > 0)
						||(LedData.Buffer[TempGrp * LED_MAX].DutyB > 0)
					)
					{
						for (TempLed = 0; TempLed < LED_MAX; TempLed++)
						{
							LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR		-= FadeR;
							LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG		-= FadeG;
							LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB		-= FadeB;
						}
					}
					else
					{
						ModeStep[TempGrp] = 0;
						srand(RndSeed);
						RndSeed += 17;
						HoldTime[TempGrp]	= (_Uint8)rand() % 20;
						ModeStep[TempGrp] = 0;
					}
				} 
			} break;
		}
	}
}


/**
	* FunctionName	Polar_Light
	*/
void Polar_Light(void)
{
	/* Initialize */
	if (DisplayData.InitFlag == TRUE)
	{
		DisplayData.InitFlag = FALSE;
		
		TempR = 255;
		TempG = 0;
		TempB = 0;
		
		ModeTime[0]++;
		ModeStep[0] = 0;
		
		SpeedTime = 0;
		
		return;
	}
	
	/* Speed Control */
	if (SpeedTime < 5)
	{
		SpeedTime++;
		return;
	}
	SpeedTime = 0;
	
	/* Mode Control */
	switch (ModeStep[0])
	{
		case 0:
		{
			if (TempG < 255)			TempG++;
			else									ModeStep[0]++;
		} break;
		
		case 1:
		{
			if (TempR > 0)				TempR--;
			else									ModeStep[0]++;
		} break;
		
		case 2:
		{
			if (TempB < 255)			TempB++;
			else									ModeStep[0]++;
		} break;
		
		case 3:
		{
			if (TempG > 0)				TempG--;
			else									ModeStep[0]++;
		} break;
		
		case 4:
		{
			if (TempR < 255)			TempR++;
			else									ModeStep[0]++;
		} break;
		
		case 5:
		{
			if (TempB > 0)				TempB--;
			else									ModeStep[0]++;
		} break;
		
		case 6:
		{
			if (TempB < 255)			TempB++;
			else									ModeStep[0]++;
		} break;
		
		case 7:
		{
			if (TempR > 0)				TempR--;
			else									ModeStep[0]++;
		} break;
		
		case 8:
		{
			if (TempG < 255)			TempG++;
			else									ModeStep[0]++;
		} break;
		
		case 9:
		{
			if (TempB > 0)				TempB--;
			else									ModeStep[0]++;
		} break;
		
		case 10:
		{
			if (TempR < 255)			TempR++;
			else									ModeStep[0]++;
		} break;
		
		default:
		{
			if (TempG > 0)				TempG--;
			else									
			{
				ModeStep[0] = 0;
				HorseCnt++;
				if (HorseCnt > 20)
				{
					HorseCnt = 0;
					DisplayData.InitFlag = TRUE;
					SynFlag = TRUE;
				}
			}
		} break;
	}
	
	for (TempLed = 0; TempLed < LED_TOTAL; TempLed++)
	{
		LedData.Buffer[TempLed].DutyR		= TempR;
		LedData.Buffer[TempLed].DutyG		= TempG;
		LedData.Buffer[TempLed].DutyB		= TempB;
	}
}


/**
	* FunctionName	Color_Show
	*/
void Color_Show(void)
{
	/* initialize */
if (DisplayData.InitFlag == TRUE)
	{
		DisplayData.InitFlag = FALSE;
			
		ModeStep[0] = 0;
		
		for(TempLed = 0; TempLed < LED_TOTAL; TempLed++)
		{
			LedData.Buffer[TempLed].DutyR	 = 0;
			LedData.Buffer[TempLed].DutyG	 = 0;
			LedData.Buffer[TempLed].DutyB	 = 0;
		}
		
		TempR = 0;
		TempG = 0;
		TempB = 0;
		
		HorseCnt = 0;
		SynFlag = FALSE;
		
		ModeStep[1] = 0;
		
		for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++)
		{
			ModeTime[TempGrp] = 0;
			HoldTime[TempGrp] = 0;
		}

		LedCnt 	= 0;
	}
	
	/* Mode Control */
	else
	{
		ModeTime[0]++;
		if (ModeTime[0] >= 4)
		{
			ModeTime[0] = 0;
			
			ModeTime[1]++;
			if (ModeTime[1] >= 30)
			{
				ModeTime[1] = 0;
				ModeTime[2]++;
				if (ModeTime[2] >= 1)
				{
					ModeTime[2] = 0;
				
					ModeStep[0]++;
					if (ModeStep[0] > 5)	
					{
						ModeStep[0] = 0;
						
						HorseCnt++;
						if (HorseCnt > 20)
						{
							HorseCnt = 0;
							DisplayData.InitFlag = TRUE;
							SynFlag = TRUE;
						}
					}
				}
			}
			
				
			switch (ModeStep[0])
			{
				case 0:
				{
						TempB   = 0;
						TempR  += 5;
						TempG  -= 7;
				}	break;
					
				case 1:
				{
						TempG  	 = 0;
						TempB   -= 6;
						TempR   += 9;
				}	break;
						
				case 2:
				{
						TempR      = 0;
						TempG     += 7;
						TempB     -= 4;
				}	break;
				
				case 3:
				{
						TempB   = 0;
						TempR  -= 5;
						TempG  += 8;
				}	break;
					
				case 4:
				{
						TempG  	 = 0;
						TempB   += 3;
						TempR   -= 7;
				}	break;
						
				case 5:
				{
						TempR      = 0;
						TempG     -= 8;
						TempB     += 3;
				}	break;
			}
			
			
			#if _AL92A_
			switch (ModeStep[1])
			{
				case 0:
				{			
							TempCnt = 0;
							for (TempLed = 0; TempLed < 4; TempLed++)
							{
								LedData.Buffer[TempCnt * 4 + TempLed].DutyR = TempR;
								LedData.Buffer[TempCnt * 4 + TempLed].DutyG = TempG;
								LedData.Buffer[TempCnt * 4 + TempLed].DutyB = TempB;
							}
							ModeStep[1]++;
				} break;
				
				case 1:
				{
							TempCnt = 2;
							for (TempLed = 0; TempLed < 4; TempLed++)
							{
								LedData.Buffer[TempCnt * 4 + TempLed].DutyR = TempR;
								LedData.Buffer[TempCnt * 4 + TempLed].DutyG = TempG;
								LedData.Buffer[TempCnt * 4 + TempLed].DutyB = TempB;
							}
							ModeStep[1]++;
				} break;
				
				case 2:
				{
							TempCnt = 1;
							for (TempLed = 0; TempLed < 4; TempLed++)
							{
								LedData.Buffer[TempCnt * 4 + TempLed].DutyR = TempR;
								LedData.Buffer[TempCnt * 4 + TempLed].DutyG = TempG;
								LedData.Buffer[TempCnt * 4 + TempLed].DutyB = TempB;
							}
							ModeStep[1]++;
				} break;
				
				case 3:
				{
							TempCnt = 5;
							for (TempLed = 0; TempLed < 4; TempLed++)
							{
								LedData.Buffer[TempCnt * 4 + TempLed].DutyR = TempR;
								LedData.Buffer[TempCnt * 4 + TempLed].DutyG = TempG;
								LedData.Buffer[TempCnt * 4 + TempLed].DutyB = TempB;
							}
							ModeStep[1]++;
				} break;
				
				case 4:
				{
							TempCnt = 3;
							for (TempLed = 0; TempLed < 4; TempLed++)
							{
								LedData.Buffer[TempCnt * 4 + TempLed].DutyR = TempR;
								LedData.Buffer[TempCnt * 4 + TempLed].DutyG = TempG;
								LedData.Buffer[TempCnt * 4 + TempLed].DutyB = TempB;
							}
							ModeStep[1]++;
				} break;
				
				case 5:
				{
							TempCnt = 4;
							for (TempLed = 0; TempLed < 4; TempLed++)
							{
								LedData.Buffer[TempCnt * 4 + TempLed].DutyR = TempR;
								LedData.Buffer[TempCnt * 4 + TempLed].DutyG = TempG;
								LedData.Buffer[TempCnt * 4 + TempLed].DutyB = TempB;
							}
							ModeStep[1]++;
				} break;
				
				default:
				{
							for (TempCnt = 0; TempCnt < 6; TempCnt++)
							{
								for (TempLed = 0; TempLed < 4; TempLed++)
								{
									LedData.Buffer[TempCnt * 4 + TempLed].DutyR = TempR;
									LedData.Buffer[TempCnt * 4 + TempLed].DutyG = TempG;
									LedData.Buffer[TempCnt * 4 + TempLed].DutyB = TempB;
								}
							}
							ModeStep[1] = 0;
				} break;
			}
			
			#elif _AL92B_
			switch (ModeStep[1])
			{
				case 0:
				{
							TempCnt = 2;
							for (TempLed = 0; TempLed < 7; TempLed++)
							{
								LedData.Buffer[TempCnt * 7 + TempLed].DutyR = TempR;
								LedData.Buffer[TempCnt * 7 + TempLed].DutyG = TempG;
								LedData.Buffer[TempCnt * 7 + TempLed].DutyB = TempB;
							}
							ModeStep[1]++;
				} break;
				
				case 1:
				{
							TempCnt = 0;
							for (TempLed = 0; TempLed < 7; TempLed++)
							{
								LedData.Buffer[TempCnt * 7 + TempLed].DutyR = TempR;
								LedData.Buffer[TempCnt * 7 + TempLed].DutyG = TempG;
								LedData.Buffer[TempCnt * 7 + TempLed].DutyB = TempB;
							}
							ModeStep[1]++;
				} break;
				
				case 2:
				{
							TempCnt = 1;
							for (TempLed = 0; TempLed < 7; TempLed++)
							{
								LedData.Buffer[TempCnt * 7 + TempLed].DutyR = TempR;
								LedData.Buffer[TempCnt * 7 + TempLed].DutyG = TempG;
								LedData.Buffer[TempCnt * 7 + TempLed].DutyB = TempB;
							}
							ModeStep[1]++;
				} break;
				
				default:
				{
							for (TempCnt = 0; TempCnt < 3; TempCnt++)
							{
								for (TempLed = 0; TempLed < 7; TempLed++)
								{
									LedData.Buffer[TempCnt * 7 + TempLed].DutyR = TempR;
									LedData.Buffer[TempCnt * 7 + TempLed].DutyG = TempG;
									LedData.Buffer[TempCnt * 7 + TempLed].DutyB = TempB;
								}
							}
							ModeStep[1] = 0;
				} break;
			}
			
			#elif _AL92C_
			switch (ModeStep[1])
			{
				case 0:
				{
							TempCnt = 0;
							for (TempLed = 0; TempLed < 7; TempLed++)
							{
								LedData.Buffer[TempCnt * 7 + TempLed].DutyR = TempR;
								LedData.Buffer[TempCnt * 7 + TempLed].DutyG = TempG;
								LedData.Buffer[TempCnt * 7 + TempLed].DutyB = TempB;
							}
							ModeStep[1]++;
				} break;
				
				case 1:
				{
							TempCnt = 2;
							for (TempLed = 0; TempLed < 7; TempLed++)
							{
								LedData.Buffer[TempCnt * 7 + TempLed].DutyR = TempR;
								LedData.Buffer[TempCnt * 7 + TempLed].DutyG = TempG;
								LedData.Buffer[TempCnt * 7 + TempLed].DutyB = TempB;
							}
							ModeStep[1]++;
				} break;
				
				case 2:
				{
							TempCnt = 1;
							for (TempLed = 0; TempLed < 7; TempLed++)
							{
								LedData.Buffer[TempCnt * 7 + TempLed].DutyR = TempR;
								LedData.Buffer[TempCnt * 7 + TempLed].DutyG = TempG;
								LedData.Buffer[TempCnt * 7 + TempLed].DutyB = TempB;
							}
							ModeStep[1]++;
				} break;
				
				default:
				{
							for (TempCnt = 0; TempCnt < 3; TempCnt++)
							{
								for (TempLed = 0; TempLed < 7; TempLed++)
								{
									LedData.Buffer[TempCnt * 7 + TempLed].DutyR = TempR;
									LedData.Buffer[TempCnt * 7 + TempLed].DutyG = TempG;
									LedData.Buffer[TempCnt * 7 + TempLed].DutyB = TempB;
								}
							}
							ModeStep[1] = 0;
				} break;
			}
			
			#elif _AL95_
			switch (ModeStep[1])
			{
				case 0:
				{
							LedData.Buffer[0].DutyR = TempR;
							LedData.Buffer[0].DutyG = TempG;
							LedData.Buffer[0].DutyB = TempB;
							ModeStep[1]++;
				} break;
				
				case 1:
				{
							LedData.Buffer[2].DutyR = TempR;
							LedData.Buffer[2].DutyG = TempG;
							LedData.Buffer[2].DutyB = TempB;
							ModeStep[1]++;
				} break;
				
				case 2:
				{
							LedData.Buffer[1].DutyR = TempR;
							LedData.Buffer[1].DutyG = TempG;
							LedData.Buffer[1].DutyB = TempB;
							ModeStep[1]++;
				} break;
				
				default:
				{
							for (TempCnt = 0; TempCnt < 3; TempCnt++)
							{
								LedData.Buffer[TempCnt].DutyR = TempR;
								LedData.Buffer[TempCnt].DutyG = TempG;
								LedData.Buffer[TempCnt].DutyB = TempB;
							}
							ModeStep[1] = 0;
				} break;
			}
			
			
			#endif
		}
	}
}


