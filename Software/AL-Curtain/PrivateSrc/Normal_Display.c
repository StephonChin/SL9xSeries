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
/**
	* FunctionName	Timer_Warning
	*/
void Blue_Flash(void)
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
	All_Color(TempR, TempG, TempB);
}


/**
	* FunctionName	Direct_Set
	*/
void Direct_Set(void)
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
		
		TempR = 255;
		TempG = 0;
		TempB = 0;
		
		HorseStep = 0;
		
		return;
	}
	
	/* Speed Control */
	if (SpeedTime < 3)
	{
		SpeedTime++;
		return;
	}
	SpeedTime = 0;
	
	for (TempLed = LED_TOTAL - 1; TempLed > 0; TempLed--)
	{
		LedData.Buffer[TempLed].DutyR	= LedData.Buffer[TempLed - 1].DutyR; 
		LedData.Buffer[TempLed].DutyG	= LedData.Buffer[TempLed - 1].DutyG; 
		LedData.Buffer[TempLed].DutyB	= LedData.Buffer[TempLed - 1].DutyB; 
	}
	LedData.Buffer[0].DutyR	= TempR; 
	LedData.Buffer[0].DutyG	= TempG; 
  LedData.Buffer[0].DutyB	= TempB; 
	 
	HorseStep++;
	if (HorseStep > LED_TOTAL)
	{
		HorseStep = 0;

		DisplayData.Mode 			= DisplayData.ModeBuf;
		DisplayData.InitFlag 	= TRUE;
	}
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
	All_Color(TempR, TempG, TempB);
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
	All_Color(TempR, TempG, TempB);
}


/**
	* FunctionName	Horse_Whole_Test
	*/
void Horse_Whole_Test(void)
{
	if (DisplayData.InitFlag == TRUE)
	{
		DisplayData.InitFlag = FALSE;
		TempR = 0;
		TempG = 0;
		TempB = 0;
		All_Color(0, 0, 0);
		SpeedTime = 0;
		ModeStep[0] = 0;
		
		HorseWaitTime = 0;
		HorseStep			= 0;
		
		TempR = 255;
		TempG = 0;
		TempB = 0;
		
		return;
	}
	
	/* Speed Control */
	if (SpeedTime < 3)
	{
		SpeedTime++;
		return;
	}
	SpeedTime = 0;
	
	if (HorseWaitTime < (_Uint16)(HorseOrder - 1) * LED_TOTAL)
	{
		HorseWaitTime++;
		return;
	}
	
	for (TempLed = LED_TOTAL - 1; TempLed > 0; TempLed--)
	{
		LedData.Buffer[TempLed].DutyR	= LedData.Buffer[TempLed - 1].DutyR;
		LedData.Buffer[TempLed].DutyG	= LedData.Buffer[TempLed - 1].DutyG;
		LedData.Buffer[TempLed].DutyB	= LedData.Buffer[TempLed - 1].DutyB;
	}
	LedData.Buffer[0].DutyR	= TempR;
	LedData.Buffer[0].DutyG	= TempG;
  LedData.Buffer[0].DutyB	= TempB;
	
	HorseStep++;
	if (HorseStep > LED_TOTAL * HorseTotal)
	{
		HorseStep = 0;
		
		switch (ModeStep[0])
		{
			case 0:
			{
				TempR = 0;
				TempG = 255;
				TempB = 0;
				ModeStep[0]++;
			} break;
			
			case 1:
			{
				TempR = 0;
				TempG = 0;
				TempB = 255;
				ModeStep[0]++;
			} break;
			
			default:
			{
				DisplayData.Mode 			= DisplayData.ModeBuf;
				DisplayData.InitFlag 	= TRUE;
			} break;
		}
	}
	
}



/*
 * FunctionName		All_Color
 */
void All_Color(_Uint8 BufR, _Uint8 BufG, _Uint8 BufB)
{
	_Uint8		TempVar = 0;
	
	for (TempVar = 0; TempVar < LedTotal; TempVar++)
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
		
		for (TempLed = 0; TempLed < LedTotal; TempLed++)
		{
			TempColor	= TempLed % ColorNum;
			LedData.Buffer[TempLed].DutyR		= ColorData[TempColor][R];
			LedData.Buffer[TempLed].DutyG		= ColorData[TempColor][G];
			LedData.Buffer[TempLed].DutyB		= ColorData[TempColor][B];
		}
	}
}

/**
	* FunctionName		Blink
	*/
void Blink(void)
{
  #if 0
	if (DisplayData.InitFlag == TRUE)
	{
		DisplayData.InitFlag = FALSE;
		
		for (TempLed = 0; TempLed < LED_TOTAL; TempLed++)
		{
			TempColor = TempLed % ColorNum;
			LedData.Buffer[TempLed].DutyR		= ColorData[TempColor][R];
			LedData.Buffer[TempLed].DutyG		= ColorData[TempColor][G];
			LedData.Buffer[TempLed].DutyB		= ColorData[TempColor][B];
		}
		
		for (TempLed = 0; TempLed < RAND_TOTAL; TempLed++)
		{
			RAND();
			HoldTime[TempLed] = (_Uint8)rand() % 10 + 10;
			ModeStep[TempLed] = 1;
			RAND();
			ModeTime[TempLed] = (_Uint8)rand() % 30 + 10;
		}
		
		SpeedTime = 0;
		
		return;
	}
	
	/* Speed Control */
	if (SpeedTime < 10)
	{
		SpeedTime++;
		return;
	}
	SpeedTime = 0;
	
	/* Mode Start */
	for (TempLed = 0; TempLed < RAND_TOTAL; TempLed++)
	{
		switch (ModeStep[TempLed])
		{
			case 0:
			{
				TempColor = TempLed % ColorNum;
				LedData.Buffer[TempLed].DutyR		= ColorData[TempColor][R];
				LedData.Buffer[TempLed].DutyG		= ColorData[TempColor][G];
				LedData.Buffer[TempLed].DutyB		= ColorData[TempColor][B];
				ModeStep[TempLed] ++;
			} break;
			
			case 1:
			{
				ModeTime[TempLed]++;
				if (ModeTime[TempLed] > HoldTime[TempLed])
				{
					ModeTime[TempLed] = 0;
					srand(RndSeed++);
					HoldTime[TempLed] = (_Uint8)rand() % 10 + 10;
					ModeStep[TempLed]++;
				}
			} break;
			
			default:
			{
				TempColor = TempLed % ColorNum;
				LedData.Buffer[TempLed].DutyR		= ColorData[TempColor][R] / FADE_LEVEL * 5;
				LedData.Buffer[TempLed].DutyG		= ColorData[TempColor][G] / FADE_LEVEL * 5;
				LedData.Buffer[TempLed].DutyB		= ColorData[TempColor][B] / FADE_LEVEL * 5;
				ModeStep[TempLed] = 0;
			} break;
		}
	}
  
  
  #else
  
  uint16_t  i = 0;
  uint16_t  j = 0;
  
  if (DisplayData.InitFlag == TRUE){
    DisplayData.InitFlag = FALSE;
  
    
		SpeedTime = 0;
    TempColor = 0;
    
    for (i = 0; i < LED_TOTAL; i++){
      TempColor = i % ColorNum;
      FadeR = ColorData[TempColor][R] / FADE_LEVEL;
      FadeG = ColorData[TempColor][G] / FADE_LEVEL;
      FadeB = ColorData[TempColor][B] / FADE_LEVEL;
      RAND();
      j = (uint8_t)rand() % FADE_LEVEL;
      LedData.Buffer[i].DutyR = FadeR * j;
      LedData.Buffer[i].DutyG = FadeG * j;
      LedData.Buffer[i].DutyB = FadeB * j;
      ModeStep[i] = 0;
      ModeTime[i] = 0;
      ModeLed[i] = 0;
    }

    return;
  }

  
  for (i = 0; i < LED_TOTAL; i++){
    TempColor = i % ColorNum;
    FadeR = ColorData[TempColor][R] / FADE_LEVEL;
    FadeG = ColorData[TempColor][G] / FADE_LEVEL;
    FadeB = ColorData[TempColor][B] / FADE_LEVEL;
    
    //Fade in and fade out
    if (ModeLed[i] == 0){
      
      ModeTime[i]++;
      RAND();
      if (ModeTime[i] > ((_Uint8)rand() % 3 + 1))
      {
        ModeTime[i] = 0;
        switch (ModeStep[i]){
          case 0:{
            if (LedData.Buffer[i].DutyR > 0 || LedData.Buffer[i].DutyG > 0 || LedData.Buffer[i].DutyB > 0){
              LedData.Buffer[i].DutyR -= FadeR;
              LedData.Buffer[i].DutyG -= FadeG;
              LedData.Buffer[i].DutyB -= FadeB;
            }
            else ModeStep[i]++;
          } break;

          default:{
            if (LedData.Buffer[i].DutyR < (FadeR * FADE_LEVEL) || 
                LedData.Buffer[i].DutyG < (FadeG * FADE_LEVEL) || 
                LedData.Buffer[i].DutyB < (FadeB * FADE_LEVEL)){
              LedData.Buffer[i].DutyR += FadeR;
              LedData.Buffer[i].DutyG += FadeG;
              LedData.Buffer[i].DutyB += FadeB;
            }
            else ModeStep[i] = 0;
          } break;
        }
      }
    }

    //flash
    else{
      ModeTime[i]++;
      RAND();
      if (ModeTime[i] > ((_Uint8)rand() % 5 + 3))
      {
        ModeTime[i] = 0;
        switch (ModeStep[i]){
          case 0:{
            LedData.Buffer[i].DutyR = FadeR * FADE_LEVEL;
            LedData.Buffer[i].DutyG = FadeG * FADE_LEVEL;
            LedData.Buffer[i].DutyB = FadeB * FADE_LEVEL;
            ModeStep[i]++;
          } break;

          default:{
            LedData.Buffer[i].DutyR = 0;
            LedData.Buffer[i].DutyG = 0;
            LedData.Buffer[i].DutyB = 0;
            ModeStep[i] = 0;
            ModeLed[i] = 0;
          }break;
        }
      }
    }
  }

  //get random leds to flash
  SpeedTime++;
  if (SpeedTime >= 20){
    SpeedTime = 0;
    for (i = 0; i < 4; i++){
      do{
        RAND();
        j = (uint16_t)(rand() % LED_TOTAL);
      } while(ModeLed[j] == 1);
      ModeLed[j] = 1;
      ModeStep[j] = 0;
      ModeTime[j] = 0;
      TempColor = j % ColorNum;
      LedData.Buffer[j].DutyR = ColorData[TempColor][R];
      LedData.Buffer[j].DutyG = ColorData[TempColor][G];
      LedData.Buffer[j].DutyB = ColorData[TempColor][B];
    }
  }
  
  #endif
}


/**
	* FunctionName		Sparkle
	*/
void Sparkle(void)
{
	if (DisplayData.InitFlag == TRUE)
	{
		DisplayData.InitFlag = FALSE;
		
		for (TempLed = 0; TempLed < LED_TOTAL; TempLed++)
		{
			TempColor = TempLed % ColorNum;
			LedData.Buffer[TempLed].DutyR			= ColorData[TempColor][R];
			LedData.Buffer[TempLed].DutyG			= ColorData[TempColor][G];
			LedData.Buffer[TempLed].DutyB			= ColorData[TempColor][B];
		}
		
		
		for (TempLed = 0; TempLed < RAND_TOTAL; TempLed++)
		{
			srand(RndSeed++);
			ModeTime[TempLed]		= (_Uint8)rand() % 10 + 10;
			srand(RndSeed++);
			HoldTime[TempLed]		= (_Uint8)rand() % 20 + 10;
		}
		
		SpeedTime = 2;
		
		return;
	}
	
	//---------------------------------------------
	// Speed Control
	//---------------------------------------------
	if (SpeedTime < 2)
	{
		SpeedTime++;
		return;
	}
	SpeedTime = 0;
	
	/* Sparkle Mode Control */
	for (TempLed = 0; TempLed < RAND_TOTAL; TempLed++)
	{
		ModeTime[TempLed]++;
		if (ModeTime[TempLed] > HoldTime[TempLed])
		{
			ModeTime[TempLed] = 0;
			TempR				= LedData.Buffer[TempLed].DutyR;
			TempG				= LedData.Buffer[TempLed].DutyG;
			TempB				= LedData.Buffer[TempLed].DutyB;
		
			switch (ModeStep[TempLed])
			{
				case 0:
				{
					LedData.Buffer[TempLed].DutyR		= TempR / 2;
					LedData.Buffer[TempLed].DutyG		= TempG / 2;
					LedData.Buffer[TempLed].DutyB		= TempB / 2;
					ModeStep[TempLed]++;
				} break;
				
				default:
				{
					RAND();
					TempColor = (_Uint8)rand() % ColorNum;
					LedData.Buffer[TempLed].DutyR		= ColorData[TempColor][R];
					LedData.Buffer[TempLed].DutyG		= ColorData[TempColor][G];
					LedData.Buffer[TempLed].DutyB		= ColorData[TempColor][B];
					ModeStep[TempLed] = 0;
					RAND();
					HoldTime[TempLed] = (_Uint8)rand() % 15 + 5;
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
		RndCnt = 0;
		
		for (TempCnt = 0; TempCnt < RAND_TOTAL; TempCnt++)
		{
			ModeLed[TempCnt] = 0;
		}
		
		if (ModeSynFlag == FALSE)		//The leds only turned off when controled by APP command
		{
			for (TempCnt = 0; TempCnt < RAND_TOTAL; TempCnt++)
			{
				LedData.Buffer[TempCnt].DutyR = 0;
				LedData.Buffer[TempCnt].DutyG = 0;
				LedData.Buffer[TempCnt].DutyB = 0;
			}
		}
		else
		{
			ModeSynFlag = FALSE;		// clear the flag
		}
		
		FadeR = ColorData[0][R] / FADE_LEVEL;
		FadeG = ColorData[0][G] / FADE_LEVEL;
		FadeB = ColorData[0][B] / FADE_LEVEL;
		
		SynFlag 		= FALSE;
		HorseCnt		= 0;
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
            if (RndCnt < RAND_TOTAL)
            {
              do
              {
                RAND();
                TempLed = (_Uint8)rand() % RAND_TOTAL;
              }while(	ModeLed[TempLed] == 1);
              ModeLed[TempLed] = 1;
              
              LedData.Buffer[TempLed].DutyR = ColorData[TempColor][R];
              LedData.Buffer[TempLed].DutyG = ColorData[TempColor][G];
              LedData.Buffer[TempLed].DutyB = ColorData[TempColor][B];
              RndCnt++;
            }
            else
            {
              RndCnt++;
            }
            
            if (RndCnt >= RAND_END_TOTAL)
            {
              RndCnt = 0;
              ModeStep[0]++;
              for (TempCnt = 0; TempCnt < RAND_TOTAL; TempCnt++)
              {
                ModeLed[TempCnt] = 0;
              }
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
              if (HorseCnt > 10)
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
          if (RndCnt < RAND_TOTAL)
          {
            do
            {
              RAND();
              TempLed = (_Uint8)rand() % RAND_TOTAL;
            }while(	ModeLed[TempLed] == 1);
            ModeLed[TempLed] = 1;
            
            LedData.Buffer[TempLed].DutyR = ColorData[TempColor][R];
            LedData.Buffer[TempLed].DutyG = ColorData[TempColor][G];
            LedData.Buffer[TempLed].DutyB = ColorData[TempColor][B];
            RndCnt++;
          }
          else
          {
            RndCnt++;
          }
          
          if (RndCnt >= RAND_END_TOTAL)
          {
            RndCnt = 0;
            TempColor++;
            if (TempColor >= ColorNum)		
            {
              TempColor = 0x0;
              HorseCnt++;
              if (HorseCnt > 5)
              {
                HorseCnt = 0;
                DisplayData.InitFlag = TRUE;
                SynFlag = TRUE;
              }
            }
            
            for (TempCnt = 0; TempCnt < RAND_TOTAL; TempCnt++)
            {
              ModeLed[TempCnt] = 0;
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
		
		SynFlag 		= FALSE;
		HorseCnt		= 0;
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
                  if (HorseCnt > 5)
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
    All_Color(TempR, TempG, TempB);
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
      
      FadeR = ColorData[0][R] / FADE_LEVEL;
      FadeG = ColorData[0][G] / FADE_LEVEL;
      FadeB = ColorData[0][B] / FADE_LEVEL;
      

      TempColor 		= 0;
      HorseWaitTime = 0;
      HorseStep			= 0;
      HoldTime[1]   = 0;
      HorseCnt 			= 0;
      SynFlag 			= FALSE;
      
      // Turn off all LEDs when controlled by APP
      if (ModeSynFlag == FALSE)
      {
        for (TempLed = 0; TempLed < LED_TOTAL; TempLed++)
        {
          LedData.Buffer[TempLed].DutyR  = 0;  
          LedData.Buffer[TempLed].DutyG  = 0;
          LedData.Buffer[TempLed].DutyB  = 0;
        }
        TempR = 0;
        TempG = 0;
        TempB = 0;
      }
      
      // Keep status when controlled by other MCU
      else
      {
        
      }
      
      
      SpeedTime 		= 0;
      ModeStep[0]		= 0;
      ModeStep[1]   = 0;
      ModeStep[2]		= 0;
      
      HorseCnt		= 0;
      ModeSynFlag = FALSE;
      
      return;
    }
    
    
    {
      /* Speed Control */
      if (SpeedTime < 6)
      {
        SpeedTime++;
        return;
      }
      SpeedTime = 0;
      
      if (HorseWaitTime < (_Uint16)((HorseOrder - 1) * LED_TOTAL))
      {
        HorseWaitTime++;
        return;
      }
      
      /* Horse Roll */
      for (TempLed = LED_TOTAL - 1; TempLed > 0; TempLed--)
      {
        LedData.Buffer[TempLed].DutyR	= LedData.Buffer[TempLed - 1].DutyR;
        LedData.Buffer[TempLed].DutyG	= LedData.Buffer[TempLed - 1].DutyG;
        LedData.Buffer[TempLed].DutyB	= LedData.Buffer[TempLed - 1].DutyB;
      }
      LedData.Buffer[0].DutyR	= TempR;
      LedData.Buffer[0].DutyG	= TempG;
      LedData.Buffer[0].DutyB	= TempB;
      
      
      
      switch (ColorNum)
      {
        // Only one color ROLL under horse mode
        case 1:
        {
              switch (ModeStep[0])
              {
                case 0:
                {
                  TempR = ColorData[0][R];
                  TempG = ColorData[0][G];
                  TempB = ColorData[0][B];
                  ModeStep[1]++;
                  if (ModeStep[1] > HoldTime[1])
                  {
                    ModeStep[1] = 0;
                    HoldTime[1]++;
                    if (HoldTime[1] > LED_TOTAL - 2)
                    {
                      HoldTime[1] = 0;
                      
                      HorseCnt++;
                      if (HorseCnt > 5)
                      {
                        HorseCnt = 0;
                        DisplayData.InitFlag = TRUE;
                        SynFlag = TRUE;
                      }
                    }
                    
                    ModeStep[0]++;
                  }
                } break;
                
                default:
                {
                  TempR = 0;
                  TempG = 0;
                  TempB = 0;
                  ModeStep[0] = 0;
                } break;
              }
        } break;
        
        
        default:
        {
              switch (ModeStep[0])
              {
                case 0:
                {
                        TempR = ColorData[TempColor][R];
                        TempG = ColorData[TempColor][G];
                        TempB = ColorData[TempColor][B];
                        HorseStep++;
                        if (HorseStep > LED_TOTAL * HorseTotal)
                        {
                          HorseStep = 0;
                          
                          TempColor++;
                          if (TempColor >= ColorNum)		TempColor = 0;
                          
                          ModeStep[1]++;
                          if (ModeStep[1] > 2)
                          {
                            ModeStep[1] = 0;
                            ModeStep[2] = TempColor;
                            ModeStep[0]++;
                            HoldTime[0] = 0;
                            TempColor = 0;
                          }
                        }
                } break;
                
                
                          
                
                case 1:
                {
                        TempR = ColorData[TempColor][R];
                        TempG = ColorData[TempColor][G];
                        TempB = ColorData[TempColor][B];
                        
                        ModeStep[1]++;
                        if (ModeStep[1] > 6)
                        {
                          ModeStep[1] = 0;
                          TempColor++;
                          if (TempColor >= ColorNum)		
                          {
                            TempColor = 0;
                            HoldTime[0]++;
                            if (HoldTime[0] > 3)
                            {
                              HoldTime[0] = 0;
                              ModeStep[0] = 0;
                              
                              TempColor = ModeStep[2];
                              
                              HorseCnt++;
                              if (HorseCnt > 5)
                              {
                                HorseCnt = 0;
                                DisplayData.InitFlag = TRUE;
                                SynFlag = TRUE;
                              }
                            }
                          }
                        }
                } break;
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
      
      for (TempLed = 0; TempLed < RAND_TOTAL; TempLed++)
      {
        ModeTime[TempLed]		= 0;
        ModeStep[TempLed]		= 0;
        HoldTime[TempLed]		= 0;
        ModeColor[TempLed]	= 0;
      }
      
      SpeedTime		= 0;
      TempDuty		= 0;
      TempColor		= 0;
      FadeR			=  ColorData[TempColor][R] / FADE_LEVEL;
      FadeG			=  ColorData[TempColor][G] / FADE_LEVEL;
      FadeB			=  ColorData[TempColor][B] / FADE_LEVEL;
      
      if (ModeSynFlag == FALSE)
      {
        All_Color(0, 0, 0);
      }
      
      if (HorseOrder > 0)
      {
        HorseWaitTime = 0;
        HorseStep			= 0;
        HorseCnt 			= 0;
        SynFlag 			= FALSE;
      }
      
      ModeSynFlag = FALSE;		// clear the flag
      return;
    }
    
    //-----------------------------------------------------------------
    // Speed Control
    //-----------------------------------------------------------------
    if (SpeedTime < 8)
    {
      SpeedTime++;
      return;
    }
    SpeedTime = 0;
    
    
    
    
    //------------------------------------------------------------------
    // Mode Control
    //-------------------------------------------------------------------
    switch (ModeStep[0])
    {
      // Dark To Bright
      case 0:
      {
              if (TempDuty < FADE_LEVEL)
              {
                TempDuty += 5;
              }
              else
              {
                ModeStep[0]++;
              }
      } break;
      
      // Bright to Dark
      case 1:
      {
              if (TempDuty > 5)
              {
                TempDuty -= 5;
              }
              else
              {
                ModeStep[0] = 0;
                TempColor++;
                if (TempColor >= ColorNum)	
                {
                  TempColor = 0;
                  HorseCnt++;
                  if (HorseCnt > 5)
                  {
                    HorseCnt = 0;
                    DisplayData.InitFlag = TRUE;
                    SynFlag = TRUE;
                  }
                }
                FadeR			=  ColorData[TempColor][R] / FADE_LEVEL;
                FadeG			=  ColorData[TempColor][G] / FADE_LEVEL;
                FadeB			=  ColorData[TempColor][B] / FADE_LEVEL;
              }
      } break;
    }
    
    //----------------------------------------------------------------------
    // Led Data Get
    //----------------------------------------------------------------------
    for (TempLed = LED_TOTAL - 1; TempLed > 0; TempLed--)
    {
      LedData.Buffer[TempLed].DutyR	= LedData.Buffer[TempLed - 1].DutyR;
      LedData.Buffer[TempLed].DutyG	= LedData.Buffer[TempLed - 1].DutyG;
      LedData.Buffer[TempLed].DutyB	= LedData.Buffer[TempLed - 1].DutyB;
    }
    LedData.Buffer[0].DutyR = FadeR * TempDuty;
    LedData.Buffer[0].DutyG = FadeG * TempDuty;
    LedData.Buffer[0].DutyB = FadeB * TempDuty;
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
      
      if (HorseOrder == 0)
      {
        All_Color(0,0,0);
        for (TempLed = 0; TempLed < RAND_TOTAL; TempLed++)
        {
          srand(RndSeed++);
          RndSeed += 17;
          HoldTime[TempLed] = (_Uint8)rand() % 30;
          ModeStep[TempLed] = 0;
          ModeTime[TempLed] = 0;
        }
        
        SpeedTime = 50;
        LedCnt		= 0;
      }
      
      else
      {
        if (ModeSynFlag == FALSE)
        {
          All_Color(0,0,0);
        }
        ModeStep[0]   = 0;
        SpeedTime			= 0;
        HorseWaitTime = 0;
        HorseStep			= 0;
        HorseCnt 			= 0;
        SynFlag 			= FALSE;
        TempR					= 0;
        TempG					= 0;
        TempB					= 0;
        TempColor			= 0;
        FadeR					= ColorData[TempColor][R] / FADE_LEVEL * 5;
        FadeG					= ColorData[TempColor][G] / FADE_LEVEL * 5;
        FadeB					= ColorData[TempColor][B] / FADE_LEVEL * 5;
      }
      
      ModeSynFlag = FALSE;		// clear the flag
      return;
    }
    
    
    //--------------------------------------------------------
    // Mode if horse function disable
    //--------------------------------------------------------
    if (HorseOrder == 0)
    {
      for (TempLed = 0; TempLed < RAND_TOTAL; TempLed++)
      {
        
        TempColor 	= TempLed % ColorNum;
        FadeR				= ColorData[TempColor][R] / FADE_LEVEL;
        FadeG				= ColorData[TempColor][G] / FADE_LEVEL;
        FadeB				= ColorData[TempColor][B] / FADE_LEVEL;
        switch (ModeStep[TempLed])
        {
          case 0:
          {
            ModeTime[TempLed]++;
            if (ModeTime[TempLed] > HoldTime[TempLed])
            {
              ModeTime[TempLed] = 0;
              if
              (
                  (LedData.Buffer[TempLed].DutyR < ColorData[TempColor][R] / 5)
                ||(LedData.Buffer[TempLed].DutyG < ColorData[TempColor][G] / 5)
                ||(LedData.Buffer[TempLed].DutyB < ColorData[TempColor][B] / 5)
              )
              {
                LedData.Buffer[TempLed].DutyR		+= FadeR;
                LedData.Buffer[TempLed].DutyG		+= FadeG;
                LedData.Buffer[TempLed].DutyB		+= FadeB;
              }
              else
              {
                ModeStep[TempLed]++;
              }
            } 
          } break;
          
          case 1:
          {
            LedData.Buffer[TempLed].DutyR	= ColorData[TempColor][R];
            LedData.Buffer[TempLed].DutyG	= ColorData[TempColor][G];
            LedData.Buffer[TempLed].DutyB	= ColorData[TempColor][B];
            ModeStep[TempLed]++;
          } break;
          
          case 2:
          {
            ModeTime[TempLed]++;
            if (ModeTime[TempLed] > SpeedTime)
            {
              ModeTime[TempLed] = 0;
              ModeStep[TempLed]++;
              srand(RndSeed);
              RndSeed += 17;
              HoldTime[TempLed]	= (_Uint8)rand() % 10;
            }
          } break;
          
          default:
          {
            ModeTime[TempLed]++;
            if (ModeTime[TempLed] > HoldTime[TempLed])
            {
              ModeTime[TempLed] = 0;
              if
              (
                  (LedData.Buffer[TempLed].DutyR > 0)
                ||(LedData.Buffer[TempLed].DutyG > 0)
                ||(LedData.Buffer[TempLed].DutyB > 0)
              )
              {
                LedData.Buffer[TempLed].DutyR		-= FadeR;
                LedData.Buffer[TempLed].DutyG		-= FadeG;
                LedData.Buffer[TempLed].DutyB		-= FadeB;
              }
              else
              {
                ModeStep[TempLed] = 0;
                srand(RndSeed);
                RndSeed += 17;
                HoldTime[TempLed]	= (_Uint8)rand() % 30;
                ModeStep[TempLed] = 0;
              }
            } 
          } break;
        }
      }
      
      return;
    }
    
    //--------------------------------------------------------------
    // Mode with horse function
    //--------------------------------------------------------------
    if (SpeedTime < 8)
    {
      SpeedTime++;
      return;
    }
    SpeedTime = 0;
    
    if ((HorseTotal * (LED_TOTAL / 2)) >= (1 * LED_TOTAL)) 						/* middle node is behind this string*/
    {
      if (HorseWaitTime < (HorseTotal * (LED_TOTAL / 2) - 1 * LED_TOTAL))
      {
        HorseWaitTime++;
        return;
      }
    }
    else if ((HorseOrder - 1) * LED_TOTAL >= (HorseTotal * (LED_TOTAL / 2)))				/* middle node is before the string	*/
    {
      if (HorseWaitTime < ((1 - 1) * LED_TOTAL - HorseTotal * (LED_TOTAL / 2)))
      {
        HorseWaitTime++;
        return;
      }
    }
    
    switch (ModeStep[0])
    {
      case 0:
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
              }
      } break;
      
      case 1:
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
                }
                FadeR					= ColorData[TempColor][R] / FADE_LEVEL * 5;
                FadeG					= ColorData[TempColor][G] / FADE_LEVEL * 5;
                FadeB					= ColorData[TempColor][B] / FADE_LEVEL * 5;
              }
      } break;
    }
    
    

    for (TempLed = 0; TempLed < (LED_TOTAL - 1) / 2; TempLed++)
    {
      LedData.Buffer[TempLed].DutyR	= LedData.Buffer[TempLed + 1].DutyR;
      LedData.Buffer[TempLed].DutyG	= LedData.Buffer[TempLed + 1].DutyG;
      LedData.Buffer[TempLed].DutyB	= LedData.Buffer[TempLed + 1].DutyB;
    }
    for (TempLed = LED_TOTAL - 1; TempLed > (LED_TOTAL - 1) / 2; TempLed--)
    {
      LedData.Buffer[TempLed].DutyR	= LedData.Buffer[TempLed - 1].DutyR;
      LedData.Buffer[TempLed].DutyG	= LedData.Buffer[TempLed - 1].DutyG;
      LedData.Buffer[TempLed].DutyB	= LedData.Buffer[TempLed - 1].DutyB;
    }
    LedData.Buffer[(LED_TOTAL - 1) / 2].DutyR	= TempR;
    LedData.Buffer[(LED_TOTAL - 1) / 2].DutyG	= TempG;
    LedData.Buffer[(LED_TOTAL - 1) / 2].DutyB	= TempB;
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
      
      ModeTime[0]++;
      ModeStep[0] = 0;
      
      TempR = 255;
      TempG = 0;
      TempB = 0;
      SpeedTime = 0;
      
      HorseWaitTime = 0;
      HorseStep			= 0;
      HorseCnt 			= 0;
      SynFlag 			= FALSE;
      
      if (ModeSynFlag == FALSE)
      {
        All_Color(0,0,0);
      }
      
      ModeSynFlag = FALSE;		// clear the flag
      return;
    }
    
    //------------------------------------------------------------------
    // Speed Control
    //------------------------------------------------------------------
    if (SpeedTime < 5)
    {
      SpeedTime++;
      return;
    }
    SpeedTime = 0;
    
    
    
    
    //------------------------------------------------------------------
    // Horse run wait time when the product allow horse mode
    //------------------------------------------------------------------
    switch (ModeStep[0])
    {
      case 0:
      {
            if (TempG < 255)			TempG += 15;
            else									ModeStep[0]++;
      } break;
      
      case 1:
      {
            if (TempR > 0)				TempR -= 15;
            else									ModeStep[0]++;
      } break;
      
      case 2:
      {
            if (TempB < 255)			TempB += 15;
            else									ModeStep[0]++;
      } break;
      
      case 3:
      {
            if (TempG > 0)				TempG -= 15;
            else									ModeStep[0]++;
      } break;
      
      case 4:
      {
            if (TempR < 255)			TempR += 15;
            else									ModeStep[0]++;
      } break;
      
      case 5:
      {
            if (TempB > 0)				TempB -= 15;
            else									ModeStep[0]++;
      } break;
      
      case 6:
      {
            if (TempB < 255)			TempB += 15;
            else									ModeStep[0]++;
      } break;
      
      case 7:
      {
            if (TempR > 0)				TempR -= 15;
            else									ModeStep[0]++;
      } break;
      
      case 8:
      {
            if (TempG < 255)			TempG += 15;
            else									ModeStep[0]++;
      } break;
      
      case 9:
      {
            if (TempB > 0)				TempB -= 15;
            else									ModeStep[0]++;
      } break;
      
      case 10:
      {
            if (TempR < 255)			TempR += 15;
            else									ModeStep[0]++;
      } break;
      
      default:
      {
            if (TempG > 0)				
            {
              TempG -= 15;
            }
            else									
            {
              ModeStep[0] = 0;
              HorseCnt++;
              if (HorseCnt > 5)
              {
                HorseCnt = 0;
                DisplayData.InitFlag = TRUE;
                SynFlag = TRUE;
              }
            }
      } break;
    }
    
    for (TempLed = LED_TOTAL - 1; TempLed > 0; TempLed--)
    {
      LedData.Buffer[TempLed].DutyR	= LedData.Buffer[TempLed - 1].DutyR;
      LedData.Buffer[TempLed].DutyG	= LedData.Buffer[TempLed - 1].DutyG;
      LedData.Buffer[TempLed].DutyB = LedData.Buffer[TempLed - 1].DutyB;
    }
    
    LedData.Buffer[0].DutyR	= TempR;
    LedData.Buffer[0].DutyG = TempG;
    LedData.Buffer[0].DutyB = TempB;
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
      ModeTime[2] = 0;
      ModeStep[0] = 0;
      
      ModeStep[1] = 5;
      ModeStep[2] = 3;
        
      for(TempLed = 0; TempLed < LED_TOTAL; TempLed++)
      {
        HoldTime[TempLed]	= 0;
      }
      
      TempR = 0;
      TempG = 0;
      TempB = 0;
      HorseCnt 			= 0;
      SynFlag 			= FALSE;
      
      HorseWaitTime = 0;
      HorseStep			= 0;
        
      if (ModeSynFlag == FALSE)
      {
        All_Color(0,0,0);
      }
      
      ModeSynFlag = FALSE;		// clear the flag
      
      return;
    }

        

    
    //--------------------------------------------------------
    // Hold Time
    //--------------------------------------------------------
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
            if (HorseCnt > 5)
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
    
      
      
      //-----------------------------------------------------------------
      // Led Data Get
      //------------------------------------------------------------------
      for (TempLed = LED_TOTAL - 1; TempLed > 0; TempLed--)
      {
        LedData.Buffer[TempLed].DutyG	= LedData.Buffer[TempLed - 1].DutyG;
        LedData.Buffer[TempLed].DutyR	= LedData.Buffer[TempLed - 1].DutyR;
        LedData.Buffer[TempLed].DutyB	= LedData.Buffer[TempLed - 1].DutyB;
      }
      LedData.Buffer[0].DutyR	= TempR;
      LedData.Buffer[0].DutyG	= TempG;
      LedData.Buffer[0].DutyB	= TempB;
    }
}


