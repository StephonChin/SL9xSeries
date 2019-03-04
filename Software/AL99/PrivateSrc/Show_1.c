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
		
		All_Color(0,0,0);
		
		return;
	}
	
	
	/* Mode Control */
	TimeLine++;
	if (TimeLine == 1)									{ShowMode = 0;			ShowInit = TRUE;	}
	else if (TimeLine == 460)						{ShowMode = 1;			ShowInit = TRUE;	}
	else if (TimeLine == 2560)					{ShowMode = 2;			ShowInit = TRUE;	}
	else if (TimeLine == 3460)					{ShowMode = 3;			ShowInit = TRUE;	}
	else if (TimeLine == 4500)					{TimeLine = 0;			DisplayData.InitFlag = TRUE;  SynFlag = TRUE;}

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
		
		All_Color(0,0,0);
		
		SpeedTime 			= 0;
		TempR						= 0;
		TempG						= 0;
		TempB						= 0;
		TempCnt					= 0;
		TempColor				= 0;
		
		TempStep = 0;
		
		RndCnt = 0;
		
		return;
	}
	
	/* Speed Control */
	if (SpeedTime < 2)
	{
		SpeedTime++;
		return;
	}
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
			
			TempR += FadeR;
			TempG += FadeG;
			TempB += FadeB;
			
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
			TempCnt++;
			if (TempCnt >= 25)
			{
				TempCnt = 0;
				TempStep = 0;
				TempColor++;
				if (TempColor > 2)
				{
					TempStep = 2;
				}
			}
		} break;
		
		
		default:			break;
	}
	
	/* Led Data Get */
	All_Color(TempR, TempG, TempB);
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
		
		All_Color(0,0,0);
		
		SpeedTime		= 0;
		TempStep		= 0;
		
		for (TempCnt = 0; TempCnt < 50; TempCnt++)
		{
			ModeLed[TempCnt] = 0;
		}
		
		KeepTime = 0;
		
		RndCnt = 0;
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
					if (SpeedTime >= 5)
					{
						SpeedTime = 0;
						
						if (RndCnt < RAND_TOTAL)		
						{
							do
							{
								RAND();
								TempLed = (_Uint8)rand() % RAND_TOTAL;
							} while (ModeLed[TempLed] == 1);
							ModeLed[TempLed] = 1;
							
							TempColor = TempLed / 4;
							for (TempCnt = 0; TempCnt < GRP_MAX; TempCnt++)
							{
								ColorBuffer[TempCnt][TempLed].DutyR	= ColorData[TempColor][R];
								ColorBuffer[TempCnt][TempLed].DutyG	= ColorData[TempColor][G];
								ColorBuffer[TempCnt][TempLed].DutyB	= ColorData[TempColor][B];
							}
							
							RndCnt++;
						}
						else
						{
							RndCnt++;
						}
						
						if (RndCnt >= RAND_END_TOTAL)
						{
							TempStep++;
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
			
						TempR = ColorBuffer[0][LED_TOTAL - 1].DutyR;
						TempG = ColorBuffer[0][LED_TOTAL - 1].DutyG;
						TempB = ColorBuffer[0][LED_TOTAL - 1].DutyB;
						for (TempLed = LED_TOTAL - 1; TempLed > 0; TempLed--)
						{
							for (TempCnt = 0; TempCnt < GRP_MAX; TempCnt++)
							{
								ColorBuffer[TempCnt][TempLed].DutyR = ColorBuffer[TempCnt][TempLed - 1].DutyR;
								ColorBuffer[TempCnt][TempLed].DutyG = ColorBuffer[TempCnt][TempLed - 1].DutyG;
								ColorBuffer[TempCnt][TempLed].DutyB = ColorBuffer[TempCnt][TempLed - 1].DutyB;
							}
						}
						for (TempCnt = 0; TempCnt < GRP_MAX; TempCnt++)
						{
							ColorBuffer[TempCnt][0].DutyR = TempR;
							ColorBuffer[TempCnt][0].DutyG = TempG;
							ColorBuffer[TempCnt][0].DutyB = TempB;
						}

						
						/* Hold Time */
						KeepTime++;
						if (KeepTime >= 80)
						{
							KeepTime = 0;
							TempStep++;
							RndCnt = 0;
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
						
						if (RndCnt < 8)
						{
							for (TempCnt = 0; TempCnt < 5; TempCnt++)
							{
								if (TempCnt * 8 + RndCnt < LED_TOTAL)
								{
									for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++)
									{
										ColorBuffer[TempGrp][TempCnt * 8 + RndCnt].DutyR = ColorData[TempColor][R];
										ColorBuffer[TempGrp][TempCnt * 8 + RndCnt].DutyG = ColorData[TempColor][G];
										ColorBuffer[TempGrp][TempCnt * 8 + RndCnt].DutyB = ColorData[TempColor][B];
									}
								}
							}
							RndCnt++;
						}
						else
						{
							RndCnt++;
						}
						
						if (RndCnt >= SECTION_END_TOTAL)
						{
							TempStep++;
							TempColor++;
							if (TempColor >= ColorNum)	TempColor = 0;
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
						
						if (RndCnt < 8)
						{
							RndCnt++;
							for (TempLed = 0; TempLed < 5; TempLed++)
							{
								if (TempCnt * 8 + 8 - RndCnt < LED_TOTAL)
								{
									for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++)
									{
										ColorBuffer[TempGrp][TempCnt * 8 + 8 - RndCnt].DutyR = ColorData[TempColor][R];
										ColorBuffer[TempGrp][TempCnt * 8 + 8 - RndCnt].DutyG = ColorData[TempColor][G];
										ColorBuffer[TempGrp][TempCnt * 8 + 8 - RndCnt].DutyB = ColorData[TempColor][B];
									}
								}
							}
						}
						else
						{
							RndCnt++;
						}
						
						
						if (RndCnt >= SECTION_END_TOTAL)
						{
							TempStep++;
							TempColor++;
							if (TempColor >= ColorNum)	TempColor = 0;
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
						
						if (RndCnt < 8)
						{
							for (TempCnt = 0; TempCnt < 5; TempCnt++)
							{
								if (TempCnt * 8 + RndCnt < LED_TOTAL)
								{
									for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++)
									{
										ColorBuffer[TempGrp][TempCnt * 8 + RndCnt].DutyR = 0;
										ColorBuffer[TempGrp][TempCnt * 8 + RndCnt].DutyG = 0;
										ColorBuffer[TempGrp][TempCnt * 8 + RndCnt].DutyB = 0;
									}
								}
							}
							
							RndCnt++;
						}
						else
						{
							RndCnt++;
						}
						
						if (RndCnt >= SECTION_END_TOTAL)
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
		
		All_Color(0,0,0);
		
		SpeedTime	= 0;
		TempStep	= 0;
		TempColor = 0;
		RndCnt = 0;
		KeepTime = 0;
		return;
	}
	
	if (KeepTime >= 5)
	{
		SpeedTime++;
		if (SpeedTime >= 8)
		{
			SpeedTime = 0;
			
			for (TempLed = LED_TOTAL - 1; TempLed > 0; TempLed--)
			{
				for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++)
				{
					ColorBuffer[TempGrp][TempLed].DutyR = ColorBuffer[TempGrp][TempLed - 1].DutyR;
					ColorBuffer[TempGrp][TempLed].DutyG = ColorBuffer[TempGrp][TempLed - 1].DutyG;
					ColorBuffer[TempGrp][TempLed].DutyB = ColorBuffer[TempGrp][TempLed - 1].DutyB;
				}
			}
			for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++)
			{
				ColorBuffer[TempGrp][0].DutyR = ColorData[TempColor][R];
				ColorBuffer[TempGrp][0].DutyG = ColorData[TempColor][G];
				ColorBuffer[TempGrp][0].DutyB = ColorData[TempColor][B];
			}
			TempColor++;
			if (TempColor >= ColorNum) TempColor = 0;
		}
		return;
	}		
	
	SpeedTime++;
	if (SpeedTime >= 8)
	{
		SpeedTime = 0;
		
		for (TempLed = LED_TOTAL / 2 - 1; TempLed > 0; TempLed--)
		{
			for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++)
			{
				ColorBuffer[TempGrp][TempLed * 2].DutyR = ColorBuffer[TempGrp][TempLed * 2 - 2].DutyR;
				ColorBuffer[TempGrp][TempLed * 2].DutyG = ColorBuffer[TempGrp][TempLed * 2 - 2].DutyG;
				ColorBuffer[TempGrp][TempLed * 2].DutyB = ColorBuffer[TempGrp][TempLed * 2 - 2].DutyB;
			}
		}
		for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++)
		{
			ColorBuffer[TempGrp][0].DutyR = ColorData[TempColor][R];
			ColorBuffer[TempGrp][0].DutyG = ColorData[TempColor][G];
			ColorBuffer[TempGrp][0].DutyB = ColorData[TempColor][B];
		}

		for (TempLed = 0; TempLed < LED_TOTAL / 2 - 1; TempLed++)
		{
			for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++)
			{
				ColorBuffer[TempGrp][TempLed * 2 + 1].DutyR = ColorBuffer[TempGrp][TempLed * 2 + 3].DutyR;
				ColorBuffer[TempGrp][TempLed * 2 + 1].DutyG = ColorBuffer[TempGrp][TempLed * 2 + 3].DutyG;
				ColorBuffer[TempGrp][TempLed * 2 + 1].DutyB = ColorBuffer[TempGrp][TempLed * 2 + 3].DutyB;
			}
		}
		for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++)
		{
			ColorBuffer[TempGrp][LED_TOTAL - 1].DutyR = ColorData[TempColor + 1][R];
			ColorBuffer[TempGrp][LED_TOTAL - 1].DutyG = ColorData[TempColor + 1][G];
			ColorBuffer[TempGrp][LED_TOTAL - 1].DutyB = ColorData[TempColor + 1][B];
		}
		
		
		RndCnt++;
		if (RndCnt >= 6)
		{
			RndCnt = 0;
			TempColor++;
			if (TempColor >= ColorNum - 1)		TempColor = 0;
		}
	}
	
	/* Hold Time Control */
	SteadyTime++;
	if (SteadyTime >= 100)  //2s
	{
		SteadyTime  = 0;
		KeepTime++;
		if (KeepTime >= 5)
		{
			RndCnt = 0;
		}
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
		
		All_Color(0,0,0);
		
		SpeedTime			= 0;
		TempCnt				= 0;
		TempColor			= 0;
		TempStep			= 0;
		FadeR = ColorData[TempColor][R] / 25;
		FadeG = ColorData[TempColor][G] / 25;
		FadeB = ColorData[TempColor][B] / 25;
		TempR = 0;
		TempG = 0;
		TempB = 0;
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
						All_Color(TempR, TempG, TempB);
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
						}
					}
		} break;
		
		/* Jump to Next Color 70% */
		case 1:
		{
					TempR	= FadeR * 15;
					TempG	= FadeG * 15;
					TempB	= FadeB * 15;
					
					All_Color(TempR, TempG, TempB);
					
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
					}
		} break;
		
		/* Jump to Next Color 100% */
		case 2:
		{
					TempR	= ColorData[TempColor][R];
					TempG	= ColorData[TempColor][G];
					TempB	= ColorData[TempColor][B];
					All_Color(TempR, TempG, TempB);
					
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
						All_Color(TempR, TempG, TempB);
						
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
					if (SpeedTime >= 5)
					{
						SpeedTime = 0;
						
						if (RndCnt < RAND_TOTAL)		
						{
							do
							{
								RAND();
								TempLed = (_Uint8)rand() % RAND_TOTAL;
							} while (ModeLed[TempLed] == 1);
							ModeLed[TempLed] = 1;
							
							for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++)
							{
								ColorBuffer[TempGrp][TempLed].DutyR	= 0;
								ColorBuffer[TempGrp][TempLed].DutyG	= 0;
								ColorBuffer[TempGrp][TempLed].DutyB	= 0;
							}
							
							RndCnt++;
						}
						else
						{
							RndCnt++;
						}
						
						if (RndCnt >= RAND_END_TOTAL)
						{
							TempStep = 0;
							
							TempR = 0;
							TempG = 0;
							TempB = 0;
							FadeR = ColorData[TempColor][R] / 25;
							FadeG = ColorData[TempColor][G] / 25;
							FadeB = ColorData[TempColor][B] / 25;
							TempCnt = 0;
						}
					}
		} break;
		
		default:				break;
	}
}







 
 
