/********************************************************************
	*
	* FILE NAME
	*									Show_1.c
	* DATE
	*									02 NOV. 2017
	* AUTHOR			
	*									DS.Chin
	* DESCRIPTION
	*									Display Show One Mode
	*                 All Off Mode
	*                 Power On Mode
	*                 Some Public Functions
	*
*********************************************************************/
#include "Display_Ctrl.h"


/**
	* FunctionName	Show_1
	*/
void Show_1(void)
{
	/* Initalize */
	if (DisplayData.InitFlag == TRUE)
	{
		DisplayData.InitFlag = FALSE;
			
		TimeLine = 0;
		ShowMode = 0;
		StepCnt	= 0;
#if _AL96_
		All_Color(0,0,0,0);
#else
		All_Color(0,0,0);
#endif
		
		return;
	}
	
	
	/* Mode Control */
	
	if (TimeLine == 0)									{ShowMode = 0;			ShowInit = TRUE;	}
	else if (TimeLine == 460)						{ShowMode = 1;			ShowInit = TRUE;	}
	else if (TimeLine == 2560)					{ShowMode = 2;			ShowInit = TRUE;	}
	else if (TimeLine == 3460)					{ShowMode = 3;			ShowInit = TRUE;	}
	else if (TimeLine == 4500)					{TimeLine = 0;			DisplayData.InitFlag = TRUE; SynFlag = TRUE;}
  TimeLine++;
	switch (ShowMode)
	{
		case 0:			Show_1_0();		break;
		case 1:			Show_1_1();		break;
		case 2:			Show_1_2();		break;
		case 3:			Show_1_3();		break;
	}
}


/*
 * FunctionName		Show_1_0
 * Duration				TimeLine = 460
 */
void Show_1_0(void)
{
	if (ShowInit == TRUE)
	{
		ShowInit = FALSE;
		
#if _AL96_
		All_Color(0,0,0,0);
		TempW = 0;
#else
		All_Color(0,0,0);
#endif
		
		SpeedTime 			= 0;
		TempR						= 0;
		TempG						= 0;
		TempB						= 0;
		TempCnt					= 0;
		TempColor				= 0;
		
		TempStep = 0;
		KeepTime = 0;
		StepCnt = 0;
		
		return;
	}
	
	/* Speed Control */
  SpeedTime++;
	if (SpeedTime >= 2)
	{
    SpeedTime = 0;
	
    /* Mode Control
     * Fade in from the middle led to head and tail
     * then fade out.Three color will be display in
     * this mode.
     * At last, all turned off
     */
    switch (TempStep)
    {
      case 0:
      {
        FadeR = ColorData[TempColor][R] / 25;
        FadeG = ColorData[TempColor][G] / 25;
        FadeB = ColorData[TempColor][B] / 25;
  #if _AL96_
        FadeW = ColorData[TempColor][W] / 25;
  #endif
        
        TempR += FadeR;
        TempG += FadeG;
        TempB += FadeB;
  #if _AL96_
        TempW += FadeW;
  #endif
        
        TempCnt++;
        if (TempCnt >= 25)
        {
          TempCnt = 0;
          TempStep++;
        }
      } break;
      
      case 1:
      {
        TempR -= FadeR;
        TempG -= FadeG;
        TempB -= FadeB;
  #if _AL96_
        TempW -= FadeW;
  #endif
        TempCnt++;
        if (TempCnt >= 25)
        {
          TempCnt = 0;
          TempStep = 0;
          TempColor++;
          if (TempColor > 3)
          {
            TempStep = 2;
          }
        }
      } break;
      
      
      default:			break;
    }
    
    /* Led Data Get */
  #if _AL96_
      All_Color(TempR,TempG,TempB,TempW);
  #else
      All_Color(TempR,TempG,TempB);
  #endif
  }
}


/*
 * FunctionName		Show_1_1
 * Duration				TimeLine = 2501
 */
void Show_1_1(void)
{
	/* Initalize */
	if (ShowInit == TRUE)
	{
		ShowInit = FALSE;
		
#if _AL96_
		All_Color(0,0,0,0);
#else
		All_Color(0,0,0);
#endif
		
		SpeedTime		= 0;
		TempStep		= 0;
		
		for (TempCnt = 0; TempCnt < 50; TempCnt++)
		{
			ModeLed[TempCnt] = 0;
		}
		
		RndCnt = 0;
		
		KeepTime = 0;
		StepCnt = 0;
		return;
	}
	
	
	
	switch (TempStep)
	{
		/* Appear 
		 * Apear three color random follow the below simple
		 * 0,1,2 		- Color0
		 * 3,4,5 		- Color1
		 * 6,7,8		- Color2
		 * 9,10,11	- Color0
		 *...
		 */
		case 0:
		{
					SpeedTime++;
					if (SpeedTime >= 4)
					{
						SpeedTime = 0;
						
						
						KeepTime++;
						if (KeepTime > 3)
						{
							KeepTime = 0;
								
//----------------------------------------------------------------------------------------------
#if _AL92C_
						if (RndCnt < 12)
						{
							RndCnt++;
							switch (RndCnt)
							{
								case 1:			ModeLed[0] = 0;			ModeLed[1] = 6;		 	break;
								case 2:			ModeLed[0] = 1;			ModeLed[1] = 5;	  	break;
								case 3:			ModeLed[0] = 2;			ModeLed[1] = 4;	   	break;
								case 4:			ModeLed[0] = 3;		 	ModeLed[1] = 3;			break;
								case 5:			ModeLed[0] = 7;			ModeLed[1] = 13;	  break;
								case 6:			ModeLed[0] = 8;			ModeLed[1] = 12;	  break;
								case 7:			ModeLed[0] = 9;			ModeLed[1] = 11;	 	break;
								case 8:			ModeLed[0] = 10;		ModeLed[1] = 10; 		break;
								case 9:			ModeLed[0] = 14;		ModeLed[1] = 20;	  break;
								case 10:		ModeLed[0] = 15;		ModeLed[1] = 19;	  break;
								case 11:		ModeLed[0] = 16;		ModeLed[1] = 18;	  break;
								case 12:		ModeLed[0] = 17;		ModeLed[1] = 17; 		break;
							}
							
							TempColor = (RndCnt -1) / 4;
							TempR = ColorData[TempColor][R];
							TempG = ColorData[TempColor][G];
							TempB = ColorData[TempColor][B];
		
							LedData.Buffer[ModeLed[0]].DutyR	= TempR;
							LedData.Buffer[ModeLed[0]].DutyG	= TempG;
							LedData.Buffer[ModeLed[0]].DutyB	= TempB;
							LedData.Buffer[ModeLed[1]].DutyR	= TempR;
							LedData.Buffer[ModeLed[1]].DutyG	= TempG;
							LedData.Buffer[ModeLed[1]].DutyB	= TempB;
						}
						
//----------------------------------------------------------------------------------------------
#elif _AL92B_
						if (RndCnt < 7)
						{
							RndCnt++;
							switch (RndCnt)
							{
								case 1:		ModeLed[0] = 0;			ModeLed[1] = 7;			 ModeLed[2] = 14;	break;
								case 2:		ModeLed[0] = 1;			ModeLed[1] = 8;			 ModeLed[2] = 15;	break;
								case 3:		ModeLed[0] = 2;			ModeLed[1] = 9;			 ModeLed[2] = 16;	break;
								case 4:		ModeLed[0] = 3;			ModeLed[1] = 10;		 ModeLed[2] = 17;	break;
								case 5:		ModeLed[0] = 4;			ModeLed[1] = 11;		 ModeLed[2] = 18;	break;
								case 6:		ModeLed[0] = 5;			ModeLed[1] = 12;		 ModeLed[2] = 19;	break;
								case 7:		ModeLed[0] = 6;			ModeLed[1] = 13;		 ModeLed[2] = 20;	break;
							}
							
							LedData.Buffer[ModeLed[0]].DutyR	= ColorData[3][R];
							LedData.Buffer[ModeLed[0]].DutyG	= ColorData[3][G];
							LedData.Buffer[ModeLed[0]].DutyB	= ColorData[3][B];

							LedData.Buffer[ModeLed[1]].DutyR	= ColorData[4][R];
							LedData.Buffer[ModeLed[1]].DutyG	= ColorData[4][G];
							LedData.Buffer[ModeLed[1]].DutyB	= ColorData[4][B];
							
							LedData.Buffer[ModeLed[2]].DutyR	= ColorData[5][R];
							LedData.Buffer[ModeLed[2]].DutyG	= ColorData[5][G];
							LedData.Buffer[ModeLed[2]].DutyB	= ColorData[5][B];
						}
//----------------------------------------------------------------------------------------------
#elif _AL92A_
							if (RndCnt < 6)
							{
								for (TempCnt = 0; TempCnt < 4; TempCnt++)
								{
									LedData.Buffer[RndCnt * 4 + TempCnt].DutyR	= ColorData[RndCnt][R];
									LedData.Buffer[RndCnt * 4 + TempCnt].DutyG	= ColorData[RndCnt][G];
									LedData.Buffer[RndCnt * 4 + TempCnt].DutyB	= ColorData[RndCnt][B];
								}
								
								RndCnt++;
							}
//----------------------------------------------------------------------------------------------
#elif _AL95_
						if (RndCnt < 3)
						{
							LedData.Buffer[RndCnt].DutyR	= ColorData[RndCnt][R];
							LedData.Buffer[RndCnt].DutyG	= ColorData[RndCnt][G];
							LedData.Buffer[RndCnt].DutyB	= ColorData[RndCnt][B];
							RndCnt++;
						}
						
//----------------------------------------------------------------------------------------------
#elif _AL96_
							DutyR = ColorData[0][R];
							DutyG = ColorData[0][G];
							DutyB = ColorData[0][B];
							DutyW = ColorData[0][W];
//----------------------------------------------------------------------------------------------						
#endif
						}
						
						
						StepCnt++;
						if (StepCnt >= RAND_END_TOTAL)
						{
							TempStep++;
							ModeColor[0] = 6;
							RndCnt = 0;
              KeepTime = 0;
						}
					}
		} break;
		
		/* Rolling from head to tail circle*/
		case 1:
		{
					SpeedTime++;
					if (SpeedTime >= 10)
					{
						SpeedTime = 0;
			
						KeepTime++;
						if (KeepTime >= 3)
						{
							KeepTime = 0;
							
//----------------------------------------------------------------------------------------
#if _AL92C_
							for (TempCnt = 0; TempCnt < 3; TempCnt++)
							{
								LedData.Buffer[TempCnt * 7 + 3].DutyR = LedData.Buffer[TempCnt * 7 + 2].DutyR;
								LedData.Buffer[TempCnt * 7 + 3].DutyG = LedData.Buffer[TempCnt * 7 + 2].DutyG;
								LedData.Buffer[TempCnt * 7 + 3].DutyB = LedData.Buffer[TempCnt * 7 + 2].DutyB;
								
								LedData.Buffer[TempCnt * 7 + 2].DutyR = LedData.Buffer[TempCnt * 7 + 1].DutyR;
								LedData.Buffer[TempCnt * 7 + 2].DutyG = LedData.Buffer[TempCnt * 7 + 1].DutyG;
								LedData.Buffer[TempCnt * 7 + 2].DutyB = LedData.Buffer[TempCnt * 7 + 1].DutyB;
								LedData.Buffer[TempCnt * 7 + 4].DutyR = LedData.Buffer[TempCnt * 7 + 1].DutyR;
								LedData.Buffer[TempCnt * 7 + 4].DutyG = LedData.Buffer[TempCnt * 7 + 1].DutyG;
								LedData.Buffer[TempCnt * 7 + 4].DutyB = LedData.Buffer[TempCnt * 7 + 1].DutyB;
								
								LedData.Buffer[TempCnt * 7 + 1].DutyR = LedData.Buffer[TempCnt * 7 + 0].DutyR;
								LedData.Buffer[TempCnt * 7 + 1].DutyG = LedData.Buffer[TempCnt * 7 + 0].DutyG;
								LedData.Buffer[TempCnt * 7 + 1].DutyB = LedData.Buffer[TempCnt * 7 + 0].DutyB;
								LedData.Buffer[TempCnt * 7 + 5].DutyR = LedData.Buffer[TempCnt * 7 + 0].DutyR;
								LedData.Buffer[TempCnt * 7 + 5].DutyG = LedData.Buffer[TempCnt * 7 + 0].DutyG;
								LedData.Buffer[TempCnt * 7 + 5].DutyB = LedData.Buffer[TempCnt * 7 + 0].DutyB;
								
								LedData.Buffer[TempCnt * 7 + 0].DutyR = ColorData[ModeColor[0]][R];
								LedData.Buffer[TempCnt * 7 + 0].DutyG = ColorData[ModeColor[0]][G];
								LedData.Buffer[TempCnt * 7 + 0].DutyB = ColorData[ModeColor[0]][B];
								LedData.Buffer[TempCnt * 7 + 6].DutyR = ColorData[ModeColor[0]][R];
								LedData.Buffer[TempCnt * 7 + 6].DutyG = ColorData[ModeColor[0]][G];
								LedData.Buffer[TempCnt * 7 + 6].DutyB = ColorData[ModeColor[0]][B];
							}
							
							RndCnt++;
							if (RndCnt >= 4)
							{
								RndCnt = 0;
								ModeColor[0]++;
								if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
							}
							
							
//----------------------------------------------------------------------------------------
#elif _AL92B_
							for (TempCnt = 0; TempCnt < 3; TempCnt++)
							{
								for (TempLed = 6; TempLed > 0; TempLed--)
								{
									LedData.Buffer[TempCnt * 7 + TempLed].DutyR = LedData.Buffer[TempCnt * 7 + TempLed - 1].DutyR;
									LedData.Buffer[TempCnt * 7 + TempLed].DutyG = LedData.Buffer[TempCnt * 7 + TempLed - 1].DutyG;
									LedData.Buffer[TempCnt * 7 + TempLed].DutyB = LedData.Buffer[TempCnt * 7 + TempLed - 1].DutyB;
								}
								
								LedData.Buffer[TempCnt * 7].DutyR = ColorData[ModeColor[0]][R];
								LedData.Buffer[TempCnt * 7].DutyG = ColorData[ModeColor[0]][G];
								LedData.Buffer[TempCnt * 7].DutyB = ColorData[ModeColor[0]][B];
							}
							
							RndCnt++;
							if (RndCnt >= 7)
							{
								RndCnt = 0;
								ModeColor[0]++;
								if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
							}
							
//----------------------------------------------------------------------------------------
#elif _AL92A_
							for (TempCnt = 5; TempCnt > 0; TempCnt--)
							{
								for (TempLed = 0; TempLed < 4; TempLed++)
								{
									LedData.Buffer[TempCnt * 4 + TempLed].DutyR = LedData.Buffer[TempCnt * 4 + TempLed - 4].DutyR;
									LedData.Buffer[TempCnt * 4 + TempLed].DutyG = LedData.Buffer[TempCnt * 4 + TempLed - 4].DutyG;
									LedData.Buffer[TempCnt * 4 + TempLed].DutyB = LedData.Buffer[TempCnt * 4 + TempLed - 4].DutyB;
								}
							}
							for (TempLed = 0; TempLed < 4; TempLed++)
							{
								LedData.Buffer[TempLed].DutyR = ColorData[ModeColor[0]][R];
								LedData.Buffer[TempLed].DutyG = ColorData[ModeColor[0]][G];
								LedData.Buffer[TempLed].DutyB = ColorData[ModeColor[0]][B];
							}
							
							ModeColor[0]++;
							if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
							
//----------------------------------------------------------------------------------------
#elif _AL95_
							for (TempCnt = 2; TempCnt > 0; TempCnt--)
							{
								LedData.Buffer[TempCnt].DutyR = LedData.Buffer[TempCnt - 1].DutyR;
								LedData.Buffer[TempCnt].DutyG = LedData.Buffer[TempCnt - 1].DutyG;
								LedData.Buffer[TempCnt].DutyB = LedData.Buffer[TempCnt - 1].DutyB;
							}
							LedData.Buffer[0].DutyR = ColorData[ModeColor[0]][R];
							LedData.Buffer[0].DutyG = ColorData[ModeColor[0]][G];
							LedData.Buffer[0].DutyB = ColorData[ModeColor[0]][B];
							
							ModeColor[0]++;
							if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
							
//----------------------------------------------------------------------------------------
#elif _AL96_
							DutyR = ColorData[ModeColor[0]][R];
							DutyG = ColorData[ModeColor[0]][G];
							DutyB = ColorData[ModeColor[0]][B];
							DutyW = ColorData[ModeColor[0]][W];
							ModeColor[0]++;
							if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
//----------------------------------------------------------------------------------------						
#endif
						}

						
						/* Hold Time */
						KeepTime++;
						if (KeepTime >= 80)
						{
							KeepTime = 0;
							TempStep++;
							RndCnt = 0;
							StepCnt = 0;
							TempColor = 0;
						}
					}
		} break;
		
		/* Instead several section 0~5 , 6~11, 12~17, 18~23*/
		case 2:
		case 4:
		case 6:
		{
					SpeedTime++;
					if (SpeedTime >= 20)
					{
						SpeedTime = 0;
						
//-----------------------------------------------------------------------------
#if _AL92C_
						for (TempCnt = 2; TempCnt > 0; TempCnt--)
						{
							for (TempLed = 0; TempLed < 7; TempLed++)
							{
								LedData.Buffer[TempCnt * 7 + TempLed].DutyR = LedData.Buffer[TempCnt * 7 + TempLed - 7].DutyR;
								LedData.Buffer[TempCnt * 7 + TempLed].DutyG = LedData.Buffer[TempCnt * 7 + TempLed - 7].DutyG;
								LedData.Buffer[TempCnt * 7 + TempLed].DutyB = LedData.Buffer[TempCnt * 7 + TempLed - 7].DutyB;
							}
						}
						for (TempLed = 0; TempLed < 7; TempLed++)
						{
							LedData.Buffer[TempLed].DutyR = ColorData[TempColor][R];
							LedData.Buffer[TempLed].DutyG = ColorData[TempColor][G];
							LedData.Buffer[TempLed].DutyB = ColorData[TempColor][B];
						}
						
//-----------------------------------------------------------------------------
#elif _AL92B_
						for (TempCnt = 2; TempCnt > 0; TempCnt--)
						{
							for (TempLed = 0; TempLed < 7; TempLed++)
							{
								LedData.Buffer[TempCnt * 7 + TempLed].DutyR = LedData.Buffer[TempCnt * 7 + TempLed - 7].DutyR;
								LedData.Buffer[TempCnt * 7 + TempLed].DutyG = LedData.Buffer[TempCnt * 7 + TempLed - 7].DutyG;
								LedData.Buffer[TempCnt * 7 + TempLed].DutyB = LedData.Buffer[TempCnt * 7 + TempLed - 7].DutyB;
							}
						}
						for (TempLed = 0; TempLed < 7; TempLed++)
						{
							LedData.Buffer[TempLed].DutyR = ColorData[TempColor][R];
							LedData.Buffer[TempLed].DutyG = ColorData[TempColor][G];
							LedData.Buffer[TempLed].DutyB = ColorData[TempColor][B];
						}
						
//-----------------------------------------------------------------------------
#elif _AL92A_
						for (TempCnt = 5; TempCnt > 0; TempCnt--)
						{
							for (TempLed = 0; TempLed < 4; TempLed++)
							{
								LedData.Buffer[TempCnt * 4 + TempLed].DutyR = LedData.Buffer[TempCnt * 4 + TempLed - 4].DutyR;
								LedData.Buffer[TempCnt * 4 + TempLed].DutyG = LedData.Buffer[TempCnt * 4 + TempLed - 4].DutyG;
								LedData.Buffer[TempCnt * 4 + TempLed].DutyB = LedData.Buffer[TempCnt * 4 + TempLed - 4].DutyB;
							}
						}
						for (TempLed = 0; TempLed < 4; TempLed++)
						{
							LedData.Buffer[TempLed].DutyR = ColorData[TempColor][R];
							LedData.Buffer[TempLed].DutyG = ColorData[TempColor][G];
							LedData.Buffer[TempLed].DutyB = ColorData[TempColor][B];
						}
//-----------------------------------------------------------------------------
#elif _AL95_
						for (TempCnt = 2; TempCnt > 0; TempCnt--)
						{
							LedData.Buffer[TempCnt].DutyR = LedData.Buffer[TempCnt - 1].DutyR;
							LedData.Buffer[TempCnt].DutyG = LedData.Buffer[TempCnt - 1].DutyG;
							LedData.Buffer[TempCnt].DutyB = LedData.Buffer[TempCnt - 1].DutyB;
						}
						LedData.Buffer[0].DutyR = ColorData[TempColor][R];
						LedData.Buffer[0].DutyG = ColorData[TempColor][G];
						LedData.Buffer[0].DutyB = ColorData[TempColor][B];
						
						
//-----------------------------------------------------------------------------
#elif _AL96_
						DutyR = ColorData[TempColor][R];
						DutyG = ColorData[TempColor][G];
						DutyB = ColorData[TempColor][B];
						DutyW = ColorData[TempColor][W];
//-----------------------------------------------------------------------------
#endif					
						TempColor++;
						if (TempColor >= ColorNum)		TempColor = 0;
						
						StepCnt++;
						if (StepCnt >= 8)
						{
							TempStep++;
							TempColor++;
							if (TempColor >= ColorNum)	TempColor = 0;
							StepCnt = 0;
							RndCnt = 0;
						}
					}
		} break;
		
		case 3:
		case 5:
		case 7:
		{
					SpeedTime++;
					if (SpeedTime >= 20)
					{
						SpeedTime = 0;
						
//--------------------------------------------------------------------------------------------------------------						
#if _AL92C_
						for (TempCnt = 0; TempCnt < 2; TempCnt++)
						{
							for (TempLed = 0; TempLed < 7; TempLed++)
							{
								LedData.Buffer[TempCnt * 7 + TempLed].DutyR = LedData.Buffer[TempCnt * 7 + TempLed + 7].DutyR;
								LedData.Buffer[TempCnt * 7 + TempLed].DutyG = LedData.Buffer[TempCnt * 7 + TempLed + 7].DutyG;
								LedData.Buffer[TempCnt * 7 + TempLed].DutyB = LedData.Buffer[TempCnt * 7 + TempLed + 7].DutyB;
							}
						}
						for (TempLed = 0; TempLed < 7; TempLed++)
						{
							LedData.Buffer[TempLed + 14].DutyR = ColorData[TempColor][R];
							LedData.Buffer[TempLed + 14].DutyG = ColorData[TempColor][G];
							LedData.Buffer[TempLed + 14].DutyB = ColorData[TempColor][B];
						}
						
						
//--------------------------------------------------------------------------------------------------------------						
#elif _AL92B_
						for (TempCnt = 0; TempCnt < 2; TempCnt++)
						{
							for (TempLed = 0; TempLed < 7; TempLed++)
							{
								LedData.Buffer[TempCnt * 7 + TempLed].DutyR = LedData.Buffer[TempCnt * 7 + TempLed + 7].DutyR;
								LedData.Buffer[TempCnt * 7 + TempLed].DutyG = LedData.Buffer[TempCnt * 7 + TempLed + 7].DutyG;
								LedData.Buffer[TempCnt * 7 + TempLed].DutyB = LedData.Buffer[TempCnt * 7 + TempLed + 7].DutyB;
							}
						}
						for (TempLed = 0; TempLed < 7; TempLed++)
						{
							LedData.Buffer[TempLed + 14].DutyR = ColorData[TempColor][R];
							LedData.Buffer[TempLed + 14].DutyG = ColorData[TempColor][G];
							LedData.Buffer[TempLed + 14].DutyB = ColorData[TempColor][B];
						}
						
						
//--------------------------------------------------------------------------------------------------------------						
#elif _AL92A_
						for (TempCnt = 0; TempCnt < 5; TempCnt++)
						{
							for (TempLed = 0; TempLed < 4; TempLed++)
							{
								LedData.Buffer[TempCnt * 4 + TempLed].DutyR = LedData.Buffer[TempCnt * 4 + TempLed + 4].DutyR;
								LedData.Buffer[TempCnt * 4 + TempLed].DutyG = LedData.Buffer[TempCnt * 4 + TempLed + 4].DutyG;
								LedData.Buffer[TempCnt * 4 + TempLed].DutyB = LedData.Buffer[TempCnt * 4 + TempLed + 4].DutyB;
							}
						}
						for (TempLed = 0; TempLed < 4; TempLed++)
						{
							LedData.Buffer[TempLed + 20].DutyR = ColorData[TempColor][R];
							LedData.Buffer[TempLed + 20].DutyG = ColorData[TempColor][G];
							LedData.Buffer[TempLed + 20].DutyB = ColorData[TempColor][B];
						}
						
						
//--------------------------------------------------------------------------------------------------------------						
#elif _AL95_
						for (TempCnt = 0; TempCnt < 2; TempCnt++)
						{
							LedData.Buffer[TempCnt].DutyR = LedData.Buffer[TempCnt + 1].DutyR;
							LedData.Buffer[TempCnt].DutyG = LedData.Buffer[TempCnt + 1].DutyG;
							LedData.Buffer[TempCnt].DutyB = LedData.Buffer[TempCnt + 1].DutyB;
						}
						LedData.Buffer[2].DutyR = ColorData[TempColor][R];
						LedData.Buffer[2].DutyG = ColorData[TempColor][G];
						LedData.Buffer[2].DutyB = ColorData[TempColor][B];
						
						
//--------------------------------------------------------------------------------------------------------------						
#elif _AL96_
						DutyR = ColorData[TempColor][R];
						DutyG = ColorData[TempColor][G];
						DutyB = ColorData[TempColor][B];
						DutyW = ColorData[TempColor][W];
//--------------------------------------------------------------------------------------------------------------						
#endif
						
						TempColor++;
						if (TempColor >= ColorNum)	TempColor = 0;
					
						if (StepCnt >= 8)
						{
							TempStep++;
							StepCnt = 0;
							RndCnt = 0;
						}
					}
		} break;
		
		case 8:
		{
					SpeedTime++;
					if (SpeedTime >= 10)
					{
						SpeedTime = 0;

//--------------------------------------------------------------------------------------------------------------							
#if _AL92C_
						for (TempCnt = 0; TempCnt < 3; TempCnt++)
						{
							LedData.Buffer[TempCnt * 7 + 3].DutyR = LedData.Buffer[TempCnt * 7 + 2].DutyR;
							LedData.Buffer[TempCnt * 7 + 3].DutyG = LedData.Buffer[TempCnt * 7 + 2].DutyG;
							LedData.Buffer[TempCnt * 7 + 3].DutyB = LedData.Buffer[TempCnt * 7 + 2].DutyB;
							
							LedData.Buffer[TempCnt * 7 + 2].DutyR = LedData.Buffer[TempCnt * 7 + 1].DutyR;
							LedData.Buffer[TempCnt * 7 + 2].DutyG = LedData.Buffer[TempCnt * 7 + 1].DutyG;
							LedData.Buffer[TempCnt * 7 + 2].DutyB = LedData.Buffer[TempCnt * 7 + 1].DutyB;
							LedData.Buffer[TempCnt * 7 + 4].DutyR = LedData.Buffer[TempCnt * 7 + 1].DutyR;
							LedData.Buffer[TempCnt * 7 + 4].DutyG = LedData.Buffer[TempCnt * 7 + 1].DutyG;
							LedData.Buffer[TempCnt * 7 + 4].DutyB = LedData.Buffer[TempCnt * 7 + 1].DutyB;
							
							LedData.Buffer[TempCnt * 7 + 1].DutyR = LedData.Buffer[TempCnt * 7 + 0].DutyR;
							LedData.Buffer[TempCnt * 7 + 1].DutyG = LedData.Buffer[TempCnt * 7 + 0].DutyG;
							LedData.Buffer[TempCnt * 7 + 1].DutyB = LedData.Buffer[TempCnt * 7 + 0].DutyB;
							LedData.Buffer[TempCnt * 7 + 5].DutyR = LedData.Buffer[TempCnt * 7 + 0].DutyR;
							LedData.Buffer[TempCnt * 7 + 5].DutyG = LedData.Buffer[TempCnt * 7 + 0].DutyG;
							LedData.Buffer[TempCnt * 7 + 5].DutyB = LedData.Buffer[TempCnt * 7 + 0].DutyB;

							
							LedData.Buffer[TempCnt * 7 + 0].DutyR = 0;
							LedData.Buffer[TempCnt * 7 + 0].DutyG = 0;
							LedData.Buffer[TempCnt * 7 + 0].DutyB = 0;
							LedData.Buffer[TempCnt * 7 + 6].DutyR = 0;
							LedData.Buffer[TempCnt * 7 + 6].DutyG = 0;
							LedData.Buffer[TempCnt * 7 + 6].DutyB = 0;
						}
						
//--------------------------------------------------------------------------------------------------------------							
#elif _AL92B_
						for (TempCnt = 0; TempCnt < 3; TempCnt++)
						{
							for (TempLed = 6; TempLed > 0; TempLed--)
							{
								LedData.Buffer[TempCnt * 7 + TempLed].DutyR = LedData.Buffer[TempCnt * 7 + TempLed - 1].DutyR;
								LedData.Buffer[TempCnt * 7 + TempLed].DutyG = LedData.Buffer[TempCnt * 7 + TempLed - 1].DutyG;
								LedData.Buffer[TempCnt * 7 + TempLed].DutyB = LedData.Buffer[TempCnt * 7 + TempLed - 1].DutyB;
							}
							
							LedData.Buffer[TempCnt * 7].DutyR = 0;
							LedData.Buffer[TempCnt * 7].DutyG = 0;
							LedData.Buffer[TempCnt * 7].DutyB = 0;
						}
						
//--------------------------------------------------------------------------------------------------------------	
#elif _AL92A_
						for (TempCnt = 5; TempCnt > 0; TempCnt--)
						{
							for (TempLed = 0; TempLed < 4; TempLed++)
							{
								LedData.Buffer[TempCnt * 4 + TempLed].DutyR = LedData.Buffer[TempCnt * 4 + TempLed - 4].DutyR;
								LedData.Buffer[TempCnt * 4 + TempLed].DutyG = LedData.Buffer[TempCnt * 4 + TempLed - 4].DutyG;
								LedData.Buffer[TempCnt * 4 + TempLed].DutyB = LedData.Buffer[TempCnt * 4 + TempLed - 4].DutyB;
							}
						}
						for (TempLed = 0; TempLed < 4; TempLed++)
						{
							LedData.Buffer[TempLed].DutyR = 0;
							LedData.Buffer[TempLed].DutyG = 0;
							LedData.Buffer[TempLed].DutyB = 0;
						}

//--------------------------------------------------------------------------------------------------------------
#elif _AL95_			
						for (TempCnt = 2; TempCnt > 0; TempCnt--)
						{
							LedData.Buffer[TempCnt].DutyR = LedData.Buffer[TempCnt - 1].DutyR;
							LedData.Buffer[TempCnt].DutyG = LedData.Buffer[TempCnt - 1].DutyG;
							LedData.Buffer[TempCnt].DutyB = LedData.Buffer[TempCnt - 1].DutyB;
						}
						LedData.Buffer[0].DutyR = 0;
						LedData.Buffer[0].DutyG = 0;
						LedData.Buffer[0].DutyB = 0;
						
//--------------------------------------------------------------------------------------------------------------
#elif _AL96_
						DutyR = 0;
						DutyG = 0;
						DutyB = 0;
						DutyW = 0;
						
//--------------------------------------------------------------------------------------------------------------	
#endif
						RndCnt++;
						if (RndCnt >= 8)
						{
							TempStep++;
							RndCnt = 0;
						}
					}
		} break;
		
		default:		
		{
					TempStep = 0xFF;
		}break;
	}
}



/*
 * FunctionName	Show_1_2
 * TimeLine		 = 3345
 */
void Show_1_2(void)
{
	/* Initalize */
	if (ShowInit == TRUE)
	{
		ShowInit = FALSE;
		
#if _AL96_
		All_Color(0,0,0,0);
#else
		All_Color(0,0,0);
#endif
		
		SpeedTime	= 0;
		TempStep	= 0;
		TempColor = 0;
		RndCnt = 0;
		SteadyTime = 0;
		KeepTime = 0;
		
		ModeColor[0] = 0;
		return;
	}
	
	
	SpeedTime++;
	if (SpeedTime >= 8)
	{
		SpeedTime = 0;
		
//-------------------------------------------------------------------------
#if _AL92C_
		if (RndCnt < 12)
		{
			RndCnt++;
			switch (RndCnt)
			{
				case 1:			ModeLed[0] = 0;			ModeLed[1] = 6;		 	break;
				case 2:			ModeLed[0] = 1;			ModeLed[1] = 5;	  	break;
				case 3:			ModeLed[0] = 2;			ModeLed[1] = 4;	   	break;
				case 4:			ModeLed[0] = 3;		 	ModeLed[1] = 3;			break;
				case 5:			ModeLed[0] = 7;			ModeLed[1] = 13;	  break;
				case 6:			ModeLed[0] = 8;			ModeLed[1] = 12;	  break;
				case 7:			ModeLed[0] = 9;			ModeLed[1] = 11;	 	break;
				case 8:			ModeLed[0] = 10;		ModeLed[1] = 10; 		break;
				case 9:			ModeLed[0] = 14;		ModeLed[1] = 20;	  break;
				case 10:		ModeLed[0] = 15;		ModeLed[1] = 19;	  break;
				case 11:		ModeLed[0] = 16;		ModeLed[1] = 18;	  break;
				case 12:		ModeLed[0] = 17;		ModeLed[1] = 17; 		break;
			}

			LedData.Buffer[ModeLed[0]].DutyR	= ColorData[ModeColor[0]][R];
			LedData.Buffer[ModeLed[0]].DutyG	= ColorData[ModeColor[0]][G];
			LedData.Buffer[ModeLed[0]].DutyB	= ColorData[ModeColor[0]][B];
			LedData.Buffer[ModeLed[1]].DutyR	= ColorData[ModeColor[0]][R];
			LedData.Buffer[ModeLed[1]].DutyG	= ColorData[ModeColor[0]][G];
			LedData.Buffer[ModeLed[1]].DutyB	= ColorData[ModeColor[0]][B];
		}
		else
		{
			RndCnt = 0;
			ModeColor[0]++;
			if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
		}
		
//-------------------------------------------------------------------------
#elif _AL92B_
		if (RndCnt < 7)
		{
			RndCnt++;
			switch (RndCnt)
			{
				case 1:		ModeLed[0] = 0;			ModeLed[1] = 7;			 ModeLed[2] = 14;	break;
				case 2:		ModeLed[0] = 1;			ModeLed[1] = 8;			 ModeLed[2] = 15;	break;
				case 3:		ModeLed[0] = 2;			ModeLed[1] = 9;			 ModeLed[2] = 16;	break;
				case 4:		ModeLed[0] = 3;			ModeLed[1] = 10;		 ModeLed[2] = 17;	break;
				case 5:		ModeLed[0] = 4;			ModeLed[1] = 11;		 ModeLed[2] = 18;	break;
				case 6:		ModeLed[0] = 5;			ModeLed[1] = 12;		 ModeLed[2] = 19;	break;
				case 7:		ModeLed[0] = 6;			ModeLed[1] = 13;		 ModeLed[2] = 20;	break;
			}
			
			LedData.Buffer[ModeLed[0]].DutyR	= ColorData[ModeColor[0]][R];
			LedData.Buffer[ModeLed[0]].DutyG	= ColorData[ModeColor[0]][G];
			LedData.Buffer[ModeLed[0]].DutyB	= ColorData[ModeColor[0]][B];

			LedData.Buffer[ModeLed[1]].DutyR	= ColorData[ModeColor[0]][R];
			LedData.Buffer[ModeLed[1]].DutyG	= ColorData[ModeColor[0]][G];
			LedData.Buffer[ModeLed[1]].DutyB	= ColorData[ModeColor[0]][B];
			
			LedData.Buffer[ModeLed[2]].DutyR	= ColorData[ModeColor[0]][R];
			LedData.Buffer[ModeLed[2]].DutyG	= ColorData[ModeColor[0]][G];
			LedData.Buffer[ModeLed[2]].DutyB	= ColorData[ModeColor[0]][B];
		}
		else
		{
			RndCnt = 0;
			ModeColor[0]++;
			if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
		}
		
//-------------------------------------------------------------------------
#elif _AL92A_
		if (RndCnt < 6)
		{
			for (TempCnt = 0; TempCnt < 4; TempCnt++)
			{
				LedData.Buffer[RndCnt * 4 + TempCnt].DutyR	= ColorData[TempColor][R];
				LedData.Buffer[RndCnt * 4 + TempCnt].DutyG	= ColorData[TempColor][G];
				LedData.Buffer[RndCnt * 4 + TempCnt].DutyB	= ColorData[TempColor][B];
			}
			
			RndCnt++;
		}
		else
		{
			RndCnt = 0;
			TempColor++;
			if (TempColor >= ColorNum)		TempColor = 0;
		}
		
//-------------------------------------------------------------------------
#elif _AL95_
		if (RndCnt < 3)
		{
			LedData.Buffer[RndCnt].DutyR	= ColorData[TempColor][R];
			LedData.Buffer[RndCnt].DutyG	= ColorData[TempColor][G];
			LedData.Buffer[RndCnt].DutyB	= ColorData[TempColor][B];
			RndCnt++;
		}
		else
		{
			RndCnt = 0;
			TempColor++;
			if (TempColor >= ColorNum)		TempColor = 0;
		}
		
//-------------------------------------------------------------------------
#elif _AL96_
			DutyR = ColorData[TempColor][R];
			DutyG = ColorData[TempColor][G];
			DutyB = ColorData[TempColor][B];
			DutyW = ColorData[TempColor][W];
			KeepTime++;
			if (KeepTime > 4)
			{
				KeepTime = 0;
				TempColor++;
				if (TempColor >= ColorNum)		TempColor = 0;
			}
//-------------------------------------------------------------------------
#endif	
	}
	
}

/*
 * FunctionName		Show_1_3
 * Duration				TimeLine += 2305 
 */
void Show_1_3(void)
{
	if (ShowInit == TRUE)
	{
		ShowInit = FALSE;
		
#if _AL96_
		All_Color(0,0,0,0);
		TempR = 0;
		TempG = 0;
		TempB = 0;
		TempW = 0;
		FadeR = ColorData[TempColor][R] / 25;
		FadeG = ColorData[TempColor][G] / 25;
		FadeB = ColorData[TempColor][B] / 25;
		FadeW = ColorData[TempColor][W] / 25;
#else
		All_Color(0,0,0);
		TempR = 0;
		TempG = 0;
		TempB = 0;
		FadeR = ColorData[TempColor][R] / 25;
		FadeG = ColorData[TempColor][G] / 25;
		FadeB = ColorData[TempColor][B] / 25;
#endif
		
		SpeedTime			= 0;
		TempCnt				= 0;
		TempColor			= 0;
		TempStep			= 0;		
		return;
	}
	
	switch (TempStep)
	{
		/* Fade in untill 40% */
		case 0:
		{
					SpeedTime++;
					if (SpeedTime >= 8)
					{
						SpeedTime = 0;
						
						TempR += FadeR;
						TempG += FadeG;
						TempB += FadeB;
#if _AL96_
						TempW += FadeW;
						All_Color(TempR, TempG, TempB, TempW);
#else
						All_Color(TempR, TempG, TempB);
#endif
						TempCnt++;
						if (TempCnt > 10)
						{
							TempCnt = 0;
							TempStep++;
							SteadyTime = 0;
							TempColor++;
							if (TempColor >= ColorNum)		TempColor = 0;
							FadeR = ColorData[TempColor][R] / 25;
							FadeG = ColorData[TempColor][G] / 25;
							FadeB = ColorData[TempColor][B] / 25;
#if _AL96_
							FadeW = ColorData[TempColor][W] / 25;
#endif
						}
					}
		} break;
		
		/* Jump to Next Color 70% */
		case 1:
		{
					TempR	= FadeR * 15;
					TempG	= FadeG * 15;
					TempB	= FadeB * 15;
#if _AL96_
					TempW = FadeW * 15;
					All_Color(TempR, TempG, TempB, TempW);
#else			
					All_Color(TempR, TempG, TempB);
#endif
					
					SteadyTime++;
					if (SteadyTime > 40)
					{
						SteadyTime = 0;
						TempStep++;
						TempColor++;
						if (TempColor >= ColorNum)		TempColor = 0;
						FadeR = ColorData[TempColor][R] / 25;
						FadeG = ColorData[TempColor][G] / 25;
						FadeB = ColorData[TempColor][B] / 25;
#if _AL96_
						FadeW = ColorData[TempColor][W] / 25;
#endif
					}
		} break;
		
		/* Jump to Next Color 100% */
		case 2:
		{
					TempR	= ColorData[TempColor][R];
					TempG	= ColorData[TempColor][G];
					TempB	= ColorData[TempColor][B];
#if _AL96_
					TempW = ColorData[TempColor][W];
					All_Color(TempR, TempG, TempB, TempW);
#else
					All_Color(TempR, TempG, TempB);
#endif
					
					SteadyTime++;
					if (SteadyTime > 80)
					{
						SteadyTime = 0;
						TempStep++;
						TempCnt = 0;
					}
		} break;
		
		/* Fade out until 40% */
		case 3:
		{
					SpeedTime++;
					if (SpeedTime >= 6)
					{
						SpeedTime = 0;
						
						TempR	-= FadeR;
						TempG	-= FadeG;
						TempB	-= FadeB;
#if _AL96_
						TempW -= FadeW;
						All_Color(TempR, TempG, TempB, TempW);
#else
						All_Color(TempR, TempG, TempB);
#endif
						
						TempCnt++;
						if (TempCnt > 15)
						{
							TempCnt = 0;
							TempStep++;
							SteadyTime = 0;
							for (TempCnt = 0; TempCnt < 50; TempCnt++)
							{
								ModeLed[TempCnt] = 0;
							}
						
							RndCnt = 0;
						}
					}
		} break;
		
		/* Turn off random */
		case 4:
		{
					SpeedTime++;
					if (SpeedTime >= 6)
					{
						SpeedTime = 0;
//-------------------------------------------------------------------------
#if _AL92C_
						if (RndCnt < 12)
						{
							RndCnt++;
							switch (RndCnt)
							{
								case 1:			ModeLed[0] = 0;			ModeLed[1] = 6;		 	break;
								case 2:			ModeLed[0] = 1;			ModeLed[1] = 5;	  	break;
								case 3:			ModeLed[0] = 2;			ModeLed[1] = 4;	   	break;
								case 4:			ModeLed[0] = 3;		 	ModeLed[1] = 3;			break;
								case 5:			ModeLed[0] = 7;			ModeLed[1] = 13;	  break;
								case 6:			ModeLed[0] = 8;			ModeLed[1] = 12;	  break;
								case 7:			ModeLed[0] = 9;			ModeLed[1] = 11;	 	break;
								case 8:			ModeLed[0] = 10;		ModeLed[1] = 10; 		break;
								case 9:			ModeLed[0] = 14;		ModeLed[1] = 20;	  break;
								case 10:		ModeLed[0] = 15;		ModeLed[1] = 19;	  break;
								case 11:		ModeLed[0] = 16;		ModeLed[1] = 18;	  break;
								case 12:		ModeLed[0] = 17;		ModeLed[1] = 17; 		break;
							}
							
							LedData.Buffer[ModeLed[0]].DutyR	= 0;
							LedData.Buffer[ModeLed[0]].DutyG	= 0;
							LedData.Buffer[ModeLed[0]].DutyB	= 0;
							LedData.Buffer[ModeLed[1]].DutyR	= 0;
							LedData.Buffer[ModeLed[1]].DutyG	= 0;
							LedData.Buffer[ModeLed[1]].DutyB	= 0;
						}
						
//-------------------------------------------------------------------------
#elif _AL92B_
						if (RndCnt < 7)
						{
							RndCnt++;
							switch (RndCnt)
							{
								case 1:		ModeLed[0] = 0;			ModeLed[1] = 7;			 ModeLed[2] = 14;	break;
								case 2:		ModeLed[0] = 1;			ModeLed[1] = 8;			 ModeLed[2] = 15;	break;
								case 3:		ModeLed[0] = 2;			ModeLed[1] = 9;			 ModeLed[2] = 16;	break;
								case 4:		ModeLed[0] = 3;			ModeLed[1] = 10;		 ModeLed[2] = 17;	break;
								case 5:		ModeLed[0] = 4;			ModeLed[1] = 11;		 ModeLed[2] = 18;	break;
								case 6:		ModeLed[0] = 5;			ModeLed[1] = 12;		 ModeLed[2] = 19;	break;
								case 7:		ModeLed[0] = 6;			ModeLed[1] = 13;		 ModeLed[2] = 20;	break;
							}
							
							LedData.Buffer[ModeLed[0]].DutyR	= 0;
							LedData.Buffer[ModeLed[0]].DutyG	= 0;
							LedData.Buffer[ModeLed[0]].DutyB	= 0;

							LedData.Buffer[ModeLed[1]].DutyR	= 0;
							LedData.Buffer[ModeLed[1]].DutyG	= 0;
							LedData.Buffer[ModeLed[1]].DutyB	= 0;
							
							LedData.Buffer[ModeLed[2]].DutyR	= 0;
							LedData.Buffer[ModeLed[2]].DutyG	= 0;
							LedData.Buffer[ModeLed[2]].DutyB	= 0;
						}
						
//-------------------------------------------------------------------------
#elif _AL92A_
						if (RndCnt < 6)
						{
							for (TempCnt = 0; TempCnt < 4; TempCnt++)
							{
								LedData.Buffer[RndCnt * 4 + TempCnt].DutyR	= 0;
								LedData.Buffer[RndCnt * 4 + TempCnt].DutyG	= 0;
								LedData.Buffer[RndCnt * 4 + TempCnt].DutyB	= 0;
							}
							
							RndCnt++;
						}
						
//-------------------------------------------------------------------------
#elif _AL95_
						if (RndCnt < 3)
						{
							LedData.Buffer[RndCnt].DutyR	= 0;
							LedData.Buffer[RndCnt].DutyG	= 0;
							LedData.Buffer[RndCnt].DutyB	= 0;
							RndCnt++;
						}
						
//-------------------------------------------------------------------------
#elif _AL96_
						DutyR = 0;
						DutyG = 0;
						DutyB = 0;
						DutyW = 0;
//-------------------------------------------------------------------------
#endif
						StepCnt++;
						if (StepCnt >= RAND_END_TOTAL)
						{
							TempStep = 0;
							StepCnt = 0;
							
							TempR = 0;
							TempG = 0;
							TempB = 0;
							FadeR = ColorData[TempColor][R] / 25;
							FadeG = ColorData[TempColor][G] / 25;
							FadeB = ColorData[TempColor][B] / 25;
#if _AL96_
							TempW = 0;
							FadeW = ColorData[TempColor][W] / 25;
#endif
							TempCnt = 0;;
						}
					}
		} break;
		
		default:				break;
	}
}







 
 
