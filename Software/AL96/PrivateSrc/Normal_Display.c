/*******************************************************************************
	*
	*		FILE NAME
	*								Led_Display.c
	*
*******************************************************************************/
#include "Display_Ctrl.h"

/*
 * FunctionName		All_Color
 */
void All_Color(_Uint8 BufR, _Uint8 BufG, _Uint8 BufB, _Uint8 BufW)
{
	DutyR = BufR;
	DutyG = BufG;
	DutyB = BufB;
	DutyW = BufW;
}

/**
	* FunctionName	Blue_Flash
	*/
void Blue_Flash(void)
{
	if (DisplayData.InitFlag == TRUE)
	{
		DisplayData.InitFlag = FALSE;
		TempR = 0;
		TempG = 0;
		TempB = 0;
		All_Color(0,0,0,0);
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
	if (ModeStep[0] % 2 == 0)		TempB = 255;
	else												TempB = 0;

	/* Restore the mode */
	ModeStep[0]++;
	if (ModeStep[0] > 5)
	{
		DisplayData.Mode 			= DisplayData.ModeBuf;
		DisplayData.InitFlag 	= TRUE;
	}
	
	/* Led Data Update */
	All_Color(TempR, TempG, TempB, TempW);
}

/**
	* FunctionName	Green_Flash
	*/
void Green_Flash(void)
{
	if (DisplayData.InitFlag == TRUE)
	{
		DisplayData.InitFlag = FALSE;
		TempR = 0;
		TempG = 0;
		TempB = 0;
		All_Color(0,0,0,0);
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
	if (ModeStep[0] % 2 == 0)		TempG = 255;
	else												TempG = 0;

	/* Restore the mode */
	ModeStep[0]++;
	if (ModeStep[0] > 5)
	{
		DisplayData.Mode 			= DisplayData.ModeBuf;
		DisplayData.InitFlag 	= TRUE;
	}
	
	/* Led Data Update */
	All_Color(TempR, TempG, TempB, TempW);
}


/**
	* FunctionName	Red_Flash
	*/
void Red_Flash(void)
{
	if (DisplayData.InitFlag == TRUE)
	{
		DisplayData.InitFlag = FALSE;
		TempR = 0;
		TempG = 0;
		TempB = 0;
		All_Color(0,0,0,0);
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
	if (ModeStep[0] % 2 == 0)		TempR = 255;
	else												TempR = 0;

	/* Restore the mode */
	ModeStep[0]++;
	if (ModeStep[0] > 5)
	{
		DisplayData.Mode 			= DisplayData.ModeBuf;
		DisplayData.InitFlag 	= TRUE;
	}
	
	/* Led Data Update */
	All_Color(TempR, TempG, TempB, TempW);
}

/**
	* FunctionName		All_Off
	*/
void All_Off(void)
{
	if (DisplayData.InitFlag == TRUE)
	{
		DisplayData.InitFlag		= FALSE;
		
		DutyR = 0;
		DutyG = 0;
		DutyB = 0;
		DutyW = 0;
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

		DutyR		= ColorData[0][R];
		DutyG		= ColorData[0][G];
		DutyB		= ColorData[0][B];
		DutyW		= ColorData[0][W];
	}
}

/**
	* FunctionName		Blink
	*/
void Blink(void)
{
	/* Initialize */
	if (DisplayData.InitFlag == TRUE)
	{
		DisplayData.InitFlag 	= FALSE;
		SpeedTime = 10;
		ModeTime[0] = 0;
		ModeTime[1] = 0;
		ModeStep[0]	= 0;
		TempColor 	= 0;
		DutyR 	= ColorData[TempColor][R];
		DutyG		= ColorData[TempColor][G];
		DutyB 	= ColorData[TempColor][B];
		DutyW 	= ColorData[TempColor][W];
		
		srand(RndSeed);
		RndSeed += 17;
		HoldTime[0] = (_Uint8)rand() % 30 + 5;
		
		return;
	}

	
	/* Speed Control */
	if (SpeedTime < 10)
	{
		SpeedTime++;
		return;
	}
	SpeedTime = 0;
	

	ModeTime[0]++;
	if (ModeTime[0] > HoldTime[0])
	{
		ModeTime[0] = 0;
		
		switch (ModeStep[0])
		{
			case 0:
			{
				DutyR 	= 0;
				DutyG 	= 0;
				DutyB 	= 0;
				DutyW 	= 0;
				srand(RndSeed);
				RndSeed += 17;
				HoldTime[0] = 0;
				ModeStep[0]++;
			} break;

			case 1:
			{
				DutyR   = ColorData[TempColor][R];
				DutyG   = ColorData[TempColor][G];
				DutyB   = ColorData[TempColor][B];
				DutyW   = ColorData[TempColor][W];
				srand(RndSeed);
				RndSeed += 17;
				HoldTime[0] = (_Uint8)rand() % 30;
				ModeStep[0] = 0;
			} break;
		}
	}
	
	if (ColorNum == 1)  return;
	
	ModeTime[1]++;
	if (ModeTime[1] > 250)
	{
		ModeTime[1] = 0;
		TempColor++;
		if (TempColor >= ColorNum)	TempColor = 0;
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
		
		TempColor	= 0;
		DutyR		= ColorData[TempColor][R];
		DutyG		= ColorData[TempColor][G];
		DutyB		= ColorData[TempColor][B];
		DutyW		= ColorData[TempColor][W];
		
		srand(RndSeed++);
		ModeTime[0]		= (_Uint8)rand() % 10;
		srand(RndSeed++);
		HoldTime[0]	= (_Uint8)rand() % 20 + 10;
		HoldTime[1] = 0;
		ModeTime[0] = 0;
		ModeTime[1] = 0;
		ModeTime[2] = 0;
		ModeStep[0] = 0;
		SpeedTime = 0;
		
		return;
	}
	
	/* Sparkle Mode Control */
	ModeTime[0]++;
	if (ModeTime[0] > HoldTime[0])
	{
		ModeTime[0] = 0;
		
		switch (ModeStep[0])
		{
			case 0:
			{
				DutyR		/= 5;
				DutyG		/= 5;
				DutyB		/= 5;
				DutyW		/= 5;
				ModeStep[0]++;
				HoldTime[0] = (_Uint8)rand() % 20 + 10;
			} break;
			
			default:
			{
				DutyR		*= 5;
				DutyG		*= 5;
				DutyB		*= 5;
				DutyW   *= 5;
				ModeStep[0] = 0;
				HoldTime[0] = (_Uint8)rand() % 20 + 10;
			} break;
		}
	}
	
	if (ColorNum == 1)  return;
	
	ModeTime[2]++;
	if (ModeTime[2] > 250)
	{
		ModeTime[2] = 0;
		TempColor++;
		if (TempColor >= ColorNum)	TempColor = 0;
		DutyR		= ColorData[TempColor][R];
		DutyG		= ColorData[TempColor][G];
		DutyB		= ColorData[TempColor][B];
		DutyW		= ColorData[TempColor][W];
		ModeStep[0] = 0;
		ModeTime[0] = 0;
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
		
		FadeR = ColorData[0][R] / FADE_LEVEL;
		FadeG = ColorData[0][G] / FADE_LEVEL;
		FadeB = ColorData[0][B] / FADE_LEVEL;
		FadeW = ColorData[0][W] / FADE_LEVEL;
		
		if (ModeSynFlag == FALSE)
		{
			DutyR = 0;
			DutyG = 0;
			DutyB = 0;
			DutyW = 0;
		}
		else
		{
			ModeSynFlag = FALSE;
		}
		return;
	}
	
	/* Speed Control */
  SpeedTime++;
	if (SpeedTime >= 6)
	{
    SpeedTime = 0;
	
    /* Mode Control */
    switch (ColorNum)
    {
      case 1:
      {
        switch (ModeStep[0])
        {
          case 0:
          {
            LedCnt++;
            if (LedCnt == 1)
            {
              DutyR = ColorData[TempColor][R];
              DutyG = ColorData[TempColor][G];
              DutyB = ColorData[TempColor][B];
              DutyW = ColorData[TempColor][W];
              
              ModeStep[0]++;
            }
          } break;
          
          case 1:
          {
            LedCnt++;
            if (LedCnt > 49)
            {
              LedCnt = 0;
              ModeStep[0]++;
            }
          } break;
          
          default:
          {
            if (DutyR > 0	|| DutyG > 0 || DutyB > 0	|| DutyW > 0)
            {
              DutyR -= FadeR;
              DutyG -= FadeG;
              DutyB -= FadeB;
              DutyW -= FadeW;
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
      } break;
      
      default:
      {
            HoldTime[0]++;
            if (HoldTime[0] == 1)
            {
              DutyR = ColorData[TempColor][R];
              DutyG = ColorData[TempColor][G];
              DutyB = ColorData[TempColor][B];
              DutyW = ColorData[TempColor][W];
            }
            else if (HoldTime[0] > 50)
            {
              HoldTime[0] = 0;
              TempColor++;
              if (TempColor >= ColorNum)	
              {
                TempColor = 0;
                if (HorseCnt > 20)
                {
                  HorseCnt = 0;
                  DisplayData.InitFlag = TRUE;
                  SynFlag = TRUE;
                }
              }
            }
      } break;
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
		
		DutyR = 0;
		DutyG = 0;
		DutyB = 0;
		DutyW = 0;
		
		ModeTime[0] = 0;
		ModeStep[0] = 0;
		TempColor		= 0;
		SpeedTime 	= 0;
		HoldTime[0] = 0;
		TempR				= 0;
		TempG				= 0;
		TempB				= 0;
		TempW				= 0;
		FadeR				= ColorData[TempColor][R] / FADE_LEVEL;
		FadeG				= ColorData[TempColor][G] / FADE_LEVEL;
		FadeB				= ColorData[TempColor][B] / FADE_LEVEL;
		FadeW				= ColorData[TempColor][W] / FADE_LEVEL;
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
                    || TempB < ColorData[TempColor][B]
                      || TempW < ColorData[TempColor][W])
              {
                TempR += FadeR;
                TempG += FadeG;
                TempB += FadeB;
                TempW += FadeW;
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
              if (TempR > 0 || TempG > 0 || TempB > 0 || TempW > 0)
              {
                TempR -= FadeR;
                TempG -= FadeG;
                TempB -= FadeB;
                TempW -= FadeW;
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
                FadeW				= ColorData[TempColor][W] / FADE_LEVEL;
              }
      } break;
    }
    
    //----------------------------------------------------------------
    // Led Data Get
    //----------------------------------------------------------------
    DutyR = TempR;
    DutyG = TempG;
    DutyB = TempB;
    DutyW = TempW;
  }
}


/**
	* FunctionName	Roll
	*/
void Roll(void)
{
	if (DisplayData.InitFlag == TRUE)
	{
		DisplayData.InitFlag = FALSE;
		
		ModeTime[0] = 0;
		ModeStep[0] = 0;
		TempColor 	= 0;
		DutyR     	= 0;
		DutyG   		= 0;
		DutyB    		= 0;
		DutyW   		= 0;
		FadeR     	= ColorData[0][R] / FADE_LEVEL;
		FadeG   		= ColorData[0][G] / FADE_LEVEL;
		FadeB    		= ColorData[0][B] / FADE_LEVEL;
		FadeW   		= ColorData[0][W] / FADE_LEVEL;
		
		return;
	}
	
	ModeTime[0]++;
	if (ModeTime[0] > 40)
	{
			ModeTime[0] = 0;

			switch (ModeStep[0])
			{
					case 0:
					case 5:
					{
							DutyR   = FadeR * 10;
							DutyG   = FadeG * 10;
							DutyB   = FadeB * 10;
							DutyW   = FadeW * 10;
							ModeStep[0]++;
					} break;

					case 1:
					case 4:
					{
							DutyR   = FadeR * 20;
							DutyG   = FadeG * 20;
							DutyB   = FadeB * 20;
							DutyW   = FadeW * 20;
							ModeStep[0]++;
					} break;

					case 2:
					{
							DutyR   = FadeR * 50;
							DutyG   = FadeG * 50;
							DutyB   = FadeB * 50;
							DutyW   = FadeW * 50;
							ModeStep[0]++;
					} break;

					case 3:
					case 6:
					{
							TempColor++;
							if (TempColor >= ColorNum)							TempColor = 0;
							FadeR   = ColorData[TempColor][R] / FADE_LEVEL;
							FadeG   = ColorData[TempColor][G] / FADE_LEVEL;
							FadeB   = ColorData[TempColor][B] / FADE_LEVEL;
							FadeW   = ColorData[TempColor][W] / FADE_LEVEL;

							if (ModeStep[0] == 3)
							{
									DutyR   = FadeR * 50;
									DutyG   = FadeG * 50;
									DutyB   = FadeB * 50;
									DutyW   = FadeW * 50;
									ModeStep[0]++;
							}

							else
							{
									DutyR   = 0;
									DutyG   = 0;
									DutyB   = 0;
									DutyW   = 0;
									ModeStep[0] = 0;
							}
					} break;
			}
	}
}





/**
	* FunctionName	Ripple
	*/
void Ripple(void)
{
	/* Initialize */
	if (DisplayData.InitFlag == TRUE)
	{
		DisplayData.InitFlag 		= FALSE;
		
		DutyR			= 0;
		DutyG 		= 0;
		DutyB			= 0;
		DutyW			= 0;
		
		ModeTime[0]		= 0;
		ModeStep[0]		= 0;
		srand(RndSeed);
		RndSeed += 17;
		HoldTime[0]		= (_Uint8)rand() % 25 + 26;
		TempColor			= 0;
		FadeR				= ColorData[TempColor][R] / FADE_LEVEL;
		FadeG				= ColorData[TempColor][G] / FADE_LEVEL;
		FadeB				= ColorData[TempColor][B] / FADE_LEVEL;
		FadeW				= ColorData[TempColor][W] / FADE_LEVEL;
		ModeTime[1] = 0;
		ModeTime[2] = 0;
		
		SpeedTime		= 0;
		return;
	}
	
	/* Mode Control */
	RAND();
	ModeTime[0]++;
	if (ModeTime[0] > (_Uint8)rand() % 5)
	{
		ModeTime[0] = 0;
		switch (ModeStep[0])
		{
			case 0:
			{
				if 
				(		(DutyR < FadeR * HoldTime[0])
				 || (DutyG < FadeG * HoldTime[0])
				 || (DutyB < FadeB * HoldTime[0])
				 ||	(DutyW < FadeW * HoldTime[0])
				)
				{
					DutyR		+= FadeR;
					DutyG		+= FadeG;
					DutyB		+= FadeB;
					DutyW   += FadeW;
				}
				else
				{
					ModeStep[0]++;
					RAND();
					HoldTime[0] 	= (_Uint8)rand() % 10;
				}
			} break;
			
			default:
			{
				if 
				(		(DutyR > FadeR * HoldTime[0])
				 || (DutyG > FadeG * HoldTime[0])
				 || (DutyB > FadeB * HoldTime[0])
				 || (DutyW > FadeW * HoldTime[0])
				)
				{
					DutyR		-= FadeR;
					DutyG		-= FadeG;
					DutyB		-= FadeB;
					DutyW		-= FadeW;
				}
				else
				{
					ModeStep[0] = 0;
					HoldTime[0] 	= (_Uint8)rand() % 25 + 26;
				}
			} break;
		}
	}
	
	if (ColorNum == 1)  return;
	
	ModeTime[1]++;
	if (ModeTime[1] > 100)
	{
		ModeTime[1] = 0;
		ModeTime[2]++;
		if (ModeTime[2] > 4)
		{
			ModeTime[2] = 0;
			RAND();
			TempColor++;
			if (TempColor >= ColorNum)		TempColor = 0; 
			FadeR				= ColorData[TempColor][R] / FADE_LEVEL;
			FadeG				= ColorData[TempColor][G] / FADE_LEVEL;
			FadeB				= ColorData[TempColor][B] / FADE_LEVEL;
			FadeW				= ColorData[TempColor][W] / FADE_LEVEL;
			DutyR				= FadeR * FADE_LEVEL;
			DutyG				= FadeG * FADE_LEVEL;
			DutyB				= FadeB * FADE_LEVEL;
			DutyW				= FadeW * FADE_LEVEL;
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
		
		DutyR		= 0;
		DutyG		= 0;
		DutyB		= 0;
		DutyW		= 0;
			

		TempColor = 0;
		
		FadeR				= ColorData[TempColor][R] / FADE_LEVEL;
		FadeG				= ColorData[TempColor][G] / FADE_LEVEL;
		FadeB				= ColorData[TempColor][B] / FADE_LEVEL;
		FadeW				= ColorData[TempColor][W] / FADE_LEVEL;
		ModeStep[0] = 0;
		ModeTime[0] = 0;
		
		SpeedTime = 0;
		LedCnt		= 0;
		return;
	}
	
	if (SpeedTime < 5)
	{
		SpeedTime++;
		return;
	}
	SpeedTime = 0;
	
	switch (ModeStep[0])
	{
		case 0:
		{
			if
			(
					(DutyR < ColorData[TempColor][R] / 2)
				||(DutyG < ColorData[TempColor][G] / 2)
				||(DutyB < ColorData[TempColor][B] / 2)
				||(DutyW < ColorData[TempColor][W] / 2)
			)
			{
				DutyR		+= FadeR;
				DutyG		+= FadeG;
				DutyB		+= FadeB;
				DutyW		+= FadeW;
			}
			else
			{
				ModeStep[0]++;
			}
		} break;
		
		case 1:
		{
			DutyR	= ColorData[TempColor][R];
			DutyG	= ColorData[TempColor][G];
			DutyB	= ColorData[TempColor][B];
			DutyW	= ColorData[TempColor][W];
			ModeStep[0]++;
		} break;
		
		
		default:
		{
			if
			(
					(DutyR > 0)
				||(DutyG > 0)
				||(DutyB > 0)
				||(DutyW > 0)
			)
			{
				DutyR		-= FadeR;
				DutyG		-= FadeG;
				DutyB		-= FadeB;
				DutyW		-= FadeW;
			}
			else
			{
				ModeStep[0] = 0;
				TempColor++;
				if(TempColor >= ColorNum)			TempColor = 0;
				FadeR				= ColorData[TempColor][R] / FADE_LEVEL;
				FadeG				= ColorData[TempColor][G] / FADE_LEVEL;
				FadeB				= ColorData[TempColor][B] / FADE_LEVEL;
				FadeW				= ColorData[TempColor][W] / FADE_LEVEL;
				ModeStep[0] = 0;
			}
		} break;
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
		
		DutyR	= 255;
		DutyG	= 0;
		DutyB	= 0;
		DutyW = 0;
		
		ModeTime[0]++;
		ModeStep[0] = 0;
		
		TempR = 255;
		TempG = 0;
		TempB = 0;
		TempW = 0;
		
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
				if (HorseCnt > 20)
				{
					HorseCnt = 0;
					DisplayData.InitFlag = TRUE;
					SynFlag = TRUE;
				}
			}
		} break;
	}
	

	DutyR		= TempR;
	DutyG		= TempG;
	DutyB		= TempB;
	DutyW   = TempW;
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
			
		ModeTime[0] = 0;
		ModeTime[1] = 0;
		ModeStep[0] = 0;
		
		ModeStep[1] = 0;
		
		HorseCnt = 0;
		SynFlag = FALSE;
			
		DutyR	 = 0;
		DutyG	 = 0;
		DutyB	 = 0;
		DutyW  = 0;
		
		TempR = 0;
		TempG = 0;
		TempB = 0;
		TempW = 0;
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
			
			/* Color Change */
			switch (ModeStep[1])
			{
				case 0:
				{
							DutyR = TempR;
							DutyG = TempG;
							DutyB = TempB;
							DutyW = TempW;
				} break;
				
				case 5:
				{
							ModeStep[1] = 0;
				} break;


				default:
				{
							ModeStep[1]++;
				} break;
			}
		}
	}
}







