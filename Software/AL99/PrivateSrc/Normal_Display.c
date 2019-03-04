/*****************************************************
	* 
	* File Name				: DisplayMode.c
	* Date						: 2016.11.01
	* Author					: DS.Chin
	* Description			: LED显示模式
	*
*******************************************************/
#include "Display_Ctrl.h"

/*
 * FunctionName		All_Color
 */
void All_Color(_Uint8 BufR, _Uint8 BufG, _Uint8 BufB)
{
	_Uint8 TempA = 0;
	_Uint8 TempB = 0;
	for (TempA = 0; TempA < GRP_MAX; TempA++)
	{
		for (TempB = 0; TempB < GRP_LED; TempB++)
		{
			ColorBuffer[TempA][TempB].DutyR = BufR;
			ColorBuffer[TempA][TempB].DutyG = BufG;
			ColorBuffer[TempA][TempB].DutyB = BufB;
		}
	}
}


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


/**********************************************************
	*
	* Function Name			: All_Off()
	*
***********************************************************/
void All_Off(void)
{
	if (DisplayData.InitFlag == FALSE)
	{
		return;
	}
	
	DisplayData.InitFlag = FALSE;
	
	for (TempGrp = GRP_ONE; TempGrp <= GRP_SEVEN; TempGrp++)
	{
		for (TempLed = 0; TempLed < GRP_LED; TempLed++)
		{
			ColorBuffer[TempGrp][TempLed].DutyR			= 0;
			ColorBuffer[TempGrp][TempLed].DutyG		= 0;
			ColorBuffer[TempGrp][TempLed].DutyB		= 0;
		}
	}
}

/**********************************************************
	*
	* Function Name			: Steady()
	*
***********************************************************/
void Steady(void)
{
	if (DisplayData.InitFlag == FALSE)
	{
		return;
	}
	
	DisplayData.InitFlag = FALSE;
	
	for (TempGrp = GRP_ONE; TempGrp <= GRP_SEVEN; TempGrp++)
	{
		for (TempLed = 0; TempLed < GRP_LED; TempLed++)
		{
			TempColor = TempLed  % ColorNum;
			ColorBuffer[TempGrp][TempLed].DutyR			= ColorData[TempColor][R];
			ColorBuffer[TempGrp][TempLed].DutyG		= ColorData[TempColor][G];
			ColorBuffer[TempGrp][TempLed].DutyB		= ColorData[TempColor][B];
		}
	}
}

/**********************************************************
	*
	* Function Name			: Blink()
	*
***********************************************************/
void Blink(void)
{
	/* 初始化 */
	if (DisplayData.InitFlag == TRUE)
	{
		DisplayData.InitFlag = FALSE;
		
		for (TempGrp = GRP_ONE; TempGrp <= GRP_SIX; TempGrp++)
		{
			ModeTime[TempGrp]	= 0;
			ModeStep[TempGrp]	= 0;
			ModeLed[TempGrp]	= 0;
			ModeColor[TempGrp]= 0;
		}
		
		for (TempGrp = GRP_ONE; TempGrp <= GRP_SIX; TempGrp++)
		{
			for (TempLed = 0; TempLed < GRP_LED; TempLed++)
			{
				TempColor = TempLed % ColorNum;
				ColorBuffer[TempGrp][TempLed].DutyR			= ColorData[TempColor][R];
				ColorBuffer[TempGrp][TempLed].DutyG		= ColorData[TempColor][G];
				ColorBuffer[TempGrp][TempLed].DutyB		= ColorData[TempColor][B];
				
				LedNum[TempGrp][TempLed]	= 0;
			}
		}
		
		/* get the led number */
		for (TempGrp = GRP_ONE; TempGrp <= GRP_SIX; TempGrp++)
		{
			for (TempCnt = 0; TempCnt < 3; TempCnt++)
			{
				srand(RndSeed++);
				LedNum[TempGrp][TempCnt] = (_Uint8)(rand() % GRP_LED );
			}
		}
		
		return;
	}
	
	ModeTime[0]++;
	if (ModeTime[0] > 10)
	{
			ModeTime[0] = 0;
			
			switch (ModeStep[0])
			{
					/* turn off */
					case 0:
						{
							for (TempGrp = GRP_ONE; TempGrp <= GRP_SIX; TempGrp++)
							{
								for (TempCnt = 0; TempCnt < 3; TempCnt++)
								{
									ColorBuffer[TempGrp][LedNum[TempGrp][TempCnt]].DutyR    = 0;
									ColorBuffer[TempGrp][LedNum[TempGrp][TempCnt]].DutyG  = 0;
									ColorBuffer[TempGrp][LedNum[TempGrp][TempCnt]].DutyB   = 0;
								}
							}
							
							/* start */
							for (TempLed = 0; TempLed < 7; TempLed++)
							{
								ColorBuffer[GRP_SEVEN][TempLed].DutyR 		= 0;
								ColorBuffer[GRP_SEVEN][TempLed].DutyG	 	= 0;
								ColorBuffer[GRP_SEVEN][TempLed].DutyB		= 0;
							}
							
							ModeStep[0]++;
						}break;
					
					/* recovery */
					case 1:
						{
							for (TempGrp = GRP_ONE; TempGrp <= GRP_SIX; TempGrp++)
							{
								for (TempCnt = 0; TempCnt < 3; TempCnt++)
								{
									/* get color num */
									TempColor = LedNum[TempGrp][TempCnt] % ColorNum;
									/* recovery color value */
									ColorBuffer[TempGrp][LedNum[TempGrp][TempCnt]].DutyR   = ColorData[TempColor][R];
									ColorBuffer[TempGrp][LedNum[TempGrp][TempCnt]].DutyG = ColorData[TempColor][G];
									ColorBuffer[TempGrp][LedNum[TempGrp][TempCnt]].DutyB  = ColorData[TempColor][B];
								}
							}
							
							/* start */
							for (TempLed = 0; TempLed < 7; TempLed++)
							{
								ColorBuffer[GRP_SEVEN][TempLed].DutyR 		= ColorData[0][R];
								ColorBuffer[GRP_SEVEN][TempLed].DutyG	 	= ColorData[0][G];
								ColorBuffer[GRP_SEVEN][TempLed].DutyB		= ColorData[0][B];
							}
							
							/* step control */
							ModeStep[0] = 0;
							
							/* get random led number again */
							for (TempGrp = GRP_ONE; TempGrp <= GRP_SIX; TempGrp++)
							{
								for (TempCnt = 0; TempCnt < 3; TempCnt++)
								{
									srand(RndSeed++);
									LedNum[TempGrp][TempCnt] = (_Uint8)(rand() % GRP_LED );
								}
							}
						}break;
			}//switch
	}//if (ModeTime[0])
}


/**********************************************************
	*
	* Function Name			: Sparkle()
	*
***********************************************************/
void Sparkle(void)
{
	/* 初始化 */
	if (DisplayData.InitFlag == TRUE)
	{
		DisplayData.InitFlag = FALSE;
		
		for (TempGrp = GRP_ONE; TempGrp <= GRP_SIX; TempGrp++)
		{
			ModeTime[TempGrp]	= 0;
			ModeStep[TempGrp]	= 0;
			ModeLed[TempGrp]	= 0;
			ModeColor[TempGrp]= 0;
		}
		
		for (TempGrp = GRP_ONE; TempGrp <= GRP_SIX; TempGrp++)
		{
			for (TempLed = 0; TempLed < 8; TempLed++)
			{
				srand(RndSeed++);
				LedNum[TempGrp][TempLed]	= (_Uint8)rand() % GRP_LED;
			}
		}
		
		
		for (TempGrp = GRP_ONE; TempGrp <= GRP_SIX; TempGrp++)
		{
			for (TempLed = 0; TempLed < GRP_LED; TempLed++)
			{
				TempColor = TempLed % ColorNum;
				ColorBuffer[TempGrp][TempLed].DutyR			= ColorData[TempColor][R];
				ColorBuffer[TempGrp][TempLed].DutyG		= ColorData[TempColor][G];
				ColorBuffer[TempGrp][TempLed].DutyB		= ColorData[TempColor][B];
				
				LedNum[TempGrp][TempLed]	= 0;
			}
		}
		
		return;
	}
	
	/* 时间控制 */
	if (ModeTime[0] < 4)
	{
		ModeTime[0]++;
		return;
	}
	ModeTime[0]	= 0;
	
	
	/* 模式控制 */
	switch (ColorNum)
	{
		/* 单色 */
		case 1:
			{
				FadeR	= ColorData[0][R] / 50;
				FadeG	= ColorData[0][G] / 50;
				FadeB	= ColorData[0][B]	/ 50;
				
				for (TempGrp = GRP_ONE; TempGrp <= GRP_SIX; TempGrp++)
				{
					for (TempLed = 0; TempLed < 8; TempLed++)
					{
						if (		(ColorBuffer[TempGrp][LedNum[TempGrp][TempLed]].DutyR 	== FadeR * 50)
								&& 	(ColorBuffer[TempGrp][LedNum[TempGrp][TempLed]].DutyG == FadeG * 50)
							  && 	(ColorBuffer[TempGrp][LedNum[TempGrp][TempLed]].DutyB	== FadeB * 50)
								)
						{
							ColorBuffer[TempGrp][LedNum[TempGrp][TempLed]].DutyR 		= FadeR * 15;
							ColorBuffer[TempGrp][LedNum[TempGrp][TempLed]].DutyG	= FadeG * 15;
							ColorBuffer[TempGrp][LedNum[TempGrp][TempLed]].DutyB		= FadeB	* 15;
						}
						else
						{
							ColorBuffer[TempGrp][LedNum[TempGrp][TempLed]].DutyR 		= FadeR * 50;
							ColorBuffer[TempGrp][LedNum[TempGrp][TempLed]].DutyG	= FadeG * 50;
							ColorBuffer[TempGrp][LedNum[TempGrp][TempLed]].DutyB		= FadeB	* 50;
						}
					}
				}
				
				for (TempGrp = GRP_ONE; TempGrp <= GRP_SIX; TempGrp++)
				{
					for (TempLed = 0; TempLed < 8; TempLed++)
					{
						srand(RndSeed++);
						LedNum[TempGrp][TempLed]	= (_Uint8)rand() % GRP_LED;
					}
				}
			} break;
		
		/* 多色 */
		default:
			{
				ModeColor[0]++;
				if (ModeColor[0] >= ColorNum)
				{
					ModeColor[0] = 0;
				}
				
				for (TempGrp = GRP_ONE; TempGrp <= GRP_SIX; TempGrp++)
				{
					for (TempLed = 0; TempLed < 8; TempLed++)
					{
						ColorBuffer[TempGrp][LedNum[TempGrp][TempLed]].DutyR 		= ColorData[ModeColor[0]][R];
						ColorBuffer[TempGrp][LedNum[TempGrp][TempLed]].DutyG	= ColorData[ModeColor[0]][G];
						ColorBuffer[TempGrp][LedNum[TempGrp][TempLed]].DutyB		= ColorData[ModeColor[0]][B];
					}
				}
				
				for (TempGrp = GRP_ONE; TempGrp <= GRP_SIX; TempGrp++)
				{
					for (TempLed = 0; TempLed < 8; TempLed++)
					{
						srand(RndSeed++);
						LedNum[TempGrp][TempLed]	= (_Uint8)rand() % GRP_LED;
					}
				}
			} break;
	}
	
	
}

/**********************************************************
	*
	* Function Name			: Instead()
	*
***********************************************************/
void Instead(void)
{
	/* 初始化 */
	if (DisplayData.InitFlag == TRUE)
	{
		DisplayData.InitFlag = FALSE;
		
		for (TempGrp = GRP_ONE; TempGrp <= GRP_SIX; TempGrp++)
		{
			ModeTime[TempGrp]	= 0;
			ModeStep[TempGrp]	= 0;
			ModeLed[TempGrp]	= 0;
			ModeColor[TempGrp]= 0;
			for (TempLed = 0; TempLed < GRP_LED; TempLed++)
			{
				LedNum[TempGrp][TempLed]	= 0;
			}
		}
		
		if (ModeSynFlag == FALSE)
		{
			for (TempGrp = GRP_ONE; TempGrp <= GRP_SIX; TempGrp++)
			{
				for (TempLed = 0; TempLed < GRP_LED; TempLed++)
				{
					ColorBuffer[TempGrp][TempLed].DutyR			= 0;
					ColorBuffer[TempGrp][TempLed].DutyG		= 0;
					ColorBuffer[TempGrp][TempLed].DutyB		= 0;
				}
			}
		}
		else
		{
			ModeSynFlag = FALSE;
		}
		
		FadeR	= ColorData[0][R] / 50;
		FadeG	= ColorData[0][G] / 50;
		FadeB	= ColorData[0][B] / 50;
		
		ModeStep[1] = 0;
		
		LedCnt = 0;
		
		return;
	}
	
	
	/* 速度控制 */
	if (ModeTime[0] < 8)
	{
		ModeTime[0]++;
		return;
	}
	ModeTime[0]	= 0;
	
	/* 模式控制 */
	switch (ColorNum)
	{
		
		/* 单色时 */
		case 1:
			{
				switch (ModeStep[1])
				{
					case 0:
					{
						/* 第一步,随机呈现 */
						if (ModeStep[0] < 6)
						{
							for (TempGrp = GRP_ONE; TempGrp <= GRP_SIX; TempGrp++)
							{
								if (ModeLed[TempGrp] < GRP_LED)
								{
									/* 随机选择一个灯 */
									while (1)
									{
										srand(RndSeed++);
										TempLed	= (_Uint8)rand() % GRP_LED;
										if (LedNum[TempGrp][TempLed] == 0)
										{
											ModeLed[TempGrp]++;
											ColorBuffer[TempGrp][TempLed].DutyR		= ColorData[0][R];
											ColorBuffer[TempGrp][TempLed].DutyG	= ColorData[0][G];
											ColorBuffer[TempGrp][TempLed].DutyB	= ColorData[0][B];
											LedNum[TempGrp][TempLed]	= 1;		//此灯已变色,置1
											break;														//退出循环
										}
										else
										{
											continue;													//进入下一个WHILE
										}
									}
								}
								
								else
								{
									ModeStep[0]++;
								}
							}
						}
						
						LedCnt++;
						if (LedCnt >= 50)
						{
							LedCnt = 0;
							ModeStep[1]++;
						}
					} break;
				
				
					/* fade out */
					default:
					{
						if ( (ColorBuffer[0][0].DutyR > 0) || (ColorBuffer[0][0].DutyG > 0) || (ColorBuffer[0][0].DutyB > 0))
						{
							for (TempGrp = GRP_ONE; TempGrp <= GRP_SIX; TempGrp++)
							{
								for (TempLed = 0; TempLed < GRP_LED; TempLed++)
								{
									ColorBuffer[TempGrp][TempLed].DutyR			-= FadeR;
									ColorBuffer[TempGrp][TempLed].DutyG		-= FadeG;
									ColorBuffer[TempGrp][TempLed].DutyB		-= FadeB;
								}
							}
						}
						else
						{
							for (TempGrp = GRP_ONE; TempGrp <= GRP_SIX; TempGrp++)
							{
								ModeLed[TempGrp]	= 0;
								ModeStep[TempGrp]	= 0;
								for (TempLed = 0; TempLed < GRP_LED; TempLed++)
								{
									LedNum[TempGrp][TempLed]	= 0;
								}
							}
						}
					} break;
				}
			} break;
			
			
			
			/* 多色时 */
		default:
			{
				/* 第一步,随机呈现 */
				if (ModeStep[0] < 6)
				{
					for (TempGrp = GRP_ONE; TempGrp <= GRP_SIX; TempGrp++)
					{
						if (ModeLed[TempGrp] < GRP_LED)
						{
							/* 随机选择一个灯 */
							while (1)
							{
								srand(RndSeed++);
								TempLed	= (_Uint8)rand() % GRP_LED;
								if (LedNum[TempGrp][TempLed] == 0)
								{
									ModeLed[TempGrp]++;
									ColorBuffer[TempGrp][TempLed].DutyR		= ColorData[ModeColor[0]][R];
									ColorBuffer[TempGrp][TempLed].DutyG	= ColorData[ModeColor[0]][G];
									ColorBuffer[TempGrp][TempLed].DutyB	= ColorData[ModeColor[0]][B];
									LedNum[TempGrp][TempLed]	= 1;		//此灯已变色,置1
									break;														//退出循环
								}
								else
								{
									continue;													//进入下一个WHILE
								}
							}
						}
						
						else
						{
							ModeStep[0]++;
						}
					}
				}
				
				
				/* 换色,清零 */
				else
				{
					ModeTime[1]++;
					if (ModeTime[1] > 50 - GRP_LED)
					{
						ModeTime[1] = 0;
						ModeColor[0]++;
						if (ModeColor[0] >= ColorNum)
						{
							ModeColor[0]	= 0;
						}
						
						
						for (TempGrp = GRP_ONE; TempGrp <= GRP_SIX; TempGrp++)
						{
							ModeLed[TempGrp]	= 0;
							ModeStep[TempGrp]	= 0;
							for (TempLed = 0; TempLed < GRP_LED; TempLed++)
							{
								LedNum[TempGrp][TempLed]	= 0;
							}
						}
					}
				}
			} break;
	}
}


/**********************************************************
	*
	* Function Name			: Sea_Wave()
	*
***********************************************************/
void Sea_Wave(void)
{
	/* 初始化 */
	if (DisplayData.InitFlag == TRUE)
	{
		DisplayData.InitFlag = FALSE;
		
		for (TempGrp = GRP_ONE; TempGrp <= GRP_SIX; TempGrp++)
		{
			ModeTime[TempGrp]	= 0;
			ModeStep[TempGrp]	= 0;
			ModeLed[TempGrp]	= 0;
			ModeColor[TempGrp]= 0;
		}
		
		for (TempGrp = GRP_ONE; TempGrp <= GRP_SIX; TempGrp++)
		{
			for (TempLed = 0; TempLed < GRP_LED; TempLed++)
			{
				ColorBuffer[TempGrp][TempLed].DutyR			= 0;
				ColorBuffer[TempGrp][TempLed].DutyG			= 0;
				ColorBuffer[TempGrp][TempLed].DutyB			= 0;
				
				LedNum[TempGrp][TempLed]	= 0;
			}
		}
		
		TempColor = 0;
		
		FadeR	= ColorData[0][R] / 50;
		FadeG	= ColorData[0][G] / 50;
		FadeB	= ColorData[0][B] / 50;
		
		TempR = 0;
		TempG = 0;
		TempB = 0;
		
		ModeSynFlag = FALSE;
		
		return;
	}
	
	/* 速度控制 */
	if (ModeTime[0] < 5)
	{
		ModeTime[0]++;
		return;
	}
	ModeTime[0]	= 0;
	
	
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
							if (TempColor >= ColorNum)		TempColor = 0;
							FadeR				= ColorData[TempColor][R] / FADE_LEVEL;
							FadeG				= ColorData[TempColor][G] / FADE_LEVEL;
							FadeB				= ColorData[TempColor][B] / FADE_LEVEL;
						}
		} break;
	}
	
	
	// Color Data Get
	for (TempGrp = GRP_ONE; TempGrp <= GRP_SIX; TempGrp++)
	{
		for (TempLed = 0; TempLed < GRP_LED; TempLed++)
		{
			ColorBuffer[TempGrp][TempLed].DutyR			= TempR;
			ColorBuffer[TempGrp][TempLed].DutyG		= TempG;
			ColorBuffer[TempGrp][TempLed].DutyB		= TempB;
		}
	}
}


/**********************************************************
	*
	* Function Name			: Roll()
	*
***********************************************************/
void Roll(void)
{
	/* 初始化 */
	if (DisplayData.InitFlag == TRUE)
	{
		DisplayData.InitFlag = FALSE;
		
		for (TempGrp = GRP_ONE; TempGrp <= GRP_SIX; TempGrp++)
		{
			ModeTime[TempGrp]	= 0;
			ModeStep[TempGrp]	= 0;
			ModeLed[TempGrp]	= 0;
			ModeColor[TempGrp]= 0;
		}
		
		for (TempGrp = GRP_ONE; TempGrp <= GRP_SIX; TempGrp++)
		{
			for (TempLed = 0; TempLed < GRP_LED; TempLed++)
			{
				ColorBuffer[TempGrp][TempLed].DutyR		= 0;
				ColorBuffer[TempGrp][TempLed].DutyG		= 0;
				ColorBuffer[TempGrp][TempLed].DutyB		= 0;
				
				LedNum[TempGrp][TempLed]	= 0;
			}
		}
		
		FadeR	= ColorData[0][R] / 50;
		FadeG	= ColorData[0][G] / 50;
		FadeB	= ColorData[0][B] / 50;
		
		ModeSynFlag = FALSE;
		
		return;
	}
	
	/* 速度控制 */
	if (ModeTime[0] < 5)
	{
		ModeTime[0]++;
		return;
	}
	ModeTime[0]	= 0;
	
	
	/* 模式控制 */
	switch (ColorNum)
	{
		/* 单色 */
		case 1:
			{
				switch (ModeStep[0])
				{
					case 0:		{	TempR	= FadeR * 50;	TempG	= FadeG * 50; TempB	= FadeB * 50;	ModeStep[0]++;}	 		break;
					case 1:		{	TempR	= FadeR * 43;	TempG	= FadeG * 43; TempB	= FadeB * 43;	ModeStep[0]++;}	 		break;
					case 2:		{	TempR	= FadeR * 36;	TempG	= FadeG * 36; TempB	= FadeB * 36;	ModeStep[0]++;}	 		break;
					case 3:		{	TempR	= FadeR * 29;	TempG	= FadeG * 29; TempB	= FadeB * 29;	ModeStep[0]++;}	 		break;
					case 4:		{	TempR	= FadeR * 22;	TempG	= FadeG * 22; TempB	= FadeB * 22;	ModeStep[0]++;}	 		break;
					case 5:		{	TempR	= FadeR * 15;	TempG	= FadeG * 15; TempB	= FadeB * 15;	ModeStep[0]++;}	 		break;
					case 6:		{	TempR	= FadeR * 8;	TempG	= FadeG * 8; TempB	= FadeB * 8;	ModeStep[0]++;}	 		break;
					case 7:		{	TempR	= FadeR * 1;	TempG	= FadeG * 1; TempB	= FadeB * 1;	ModeStep[0] = 0;}		break;	 	
				}
			} break;
			
			
		/* 多色 */
		default:
			{
				switch (ModeStep[0])
				{
					case 0:		{	TempR	= FadeR * 50;	TempG	= FadeG * 50; TempB	= FadeB * 50;	ModeStep[0]++;}	 		break;
					case 1:		{	TempR	= FadeR * 43;	TempG	= FadeG * 43; TempB	= FadeB * 43;	ModeStep[0]++;}	 		break;
					case 2:		{	TempR	= FadeR * 36;	TempG	= FadeG * 36; TempB	= FadeB * 36;	ModeStep[0]++;}	 		break;
					case 3:		{	TempR	= FadeR * 29;	TempG	= FadeG * 29; TempB	= FadeB * 29;	ModeStep[0]++;}	 		break;
					case 4:		{	TempR	= FadeR * 22;	TempG	= FadeG * 22; TempB	= FadeB * 22;	ModeStep[0]++;}	 		break;
					case 5:		{	TempR	= FadeR * 15;	TempG	= FadeG * 15; TempB	= FadeB * 15;	ModeStep[0]++;}	 		break;
					case 6:		{	TempR	= FadeR * 8;	TempG	= FadeG * 8; TempB	= FadeB * 8;	ModeStep[0]++;}	 		break;
					case 7:		{	TempR	= FadeR * 1;	TempG	= FadeG * 1; TempB	= FadeB * 1;	ModeStep[0] = 0;	 	
											ModeColor[0]++; 
											if (ModeColor[0] >= ColorNum)	
											{
												ModeColor[0] = 0;
											}
											
											FadeR	= ColorData[ModeColor[0]][R] / 50;
											FadeG	= ColorData[ModeColor[0]][G] / 50;
											FadeB	= ColorData[ModeColor[0]][B] / 50;
											
										}break;
				}
			} break;
		
	}
	
	for (TempGrp = GRP_ONE; TempGrp <= GRP_SIX; TempGrp++)
	{
			ColorBuffer[TempGrp][GRP_LED - 1].DutyR		= TempR;
			ColorBuffer[TempGrp][GRP_LED - 1].DutyG	= TempG;
			ColorBuffer[TempGrp][GRP_LED - 1].DutyB	= TempB;
	}	
	
	
	
	for (TempGrp = GRP_ONE; TempGrp <= GRP_SIX; TempGrp++)
	{
		for (TempLed = 0; TempLed < GRP_LED - 1; TempLed++)
		{
			ColorBuffer[TempGrp][TempLed].DutyR		= ColorBuffer[TempGrp][TempLed + 1].DutyR;
			ColorBuffer[TempGrp][TempLed].DutyG	= ColorBuffer[TempGrp][TempLed + 1].DutyG;
			ColorBuffer[TempGrp][TempLed].DutyB	= ColorBuffer[TempGrp][TempLed + 1].DutyB;
		}
	}
	
	
}


/**********************************************************
	*
	* Function Name			: Ripple()
	*
***********************************************************/
void Ripple(void)
{
	/* 初始化 */
	if (DisplayData.InitFlag == TRUE)
	{
		DisplayData.InitFlag = FALSE;
		
		for (TempGrp = GRP_ONE; TempGrp <= GRP_SIX; TempGrp++)
		{
			ModeTime[TempGrp]	= 0;
			ModeStep[TempGrp]	= 0;
			ModeLed[TempGrp]	= 0;
			ModeColor[TempGrp]= 0;
		}
		
		for (TempGrp = GRP_ONE; TempGrp <= GRP_SIX; TempGrp++)
		{
			for (TempLed = 0; TempLed < GRP_LED; TempLed++)
			{
				TempColor = TempLed % ColorNum;
				ColorBuffer[TempGrp][TempLed].DutyR			= 0;
				ColorBuffer[TempGrp][TempLed].DutyG		= 0;
				ColorBuffer[TempGrp][TempLed].DutyB		= 0;
			}
		}
		
		FadeR	= ColorData[0][R] / 25;
		FadeG	= ColorData[0][G] / 25;
		FadeB	= ColorData[0][B] / 25;
		
		TempR = 0;
		TempG = 0;
		TempB = 0;
		
		return;
	}
	
	
	/* 速度控制 */
	if (ModeTime[0] < 1)
	{
		ModeTime[0]++;
		return;
	}
	ModeTime[0]	= 0;
	
	/* 模式开始 */
	switch (ModeStep[0])
	{
		case 0:
		{
			if (TempR < ColorData[ModeColor[0]][R] || TempG < ColorData[ModeColor[0]][G] || TempB < ColorData[ModeColor[0]][B])
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
				ModeColor[0]++;
				if (ModeColor[0] >= ColorNum)
				{
					ModeColor[0] = 0;
				}
				
				FadeR	= ColorData[ModeColor[0]][R] / 25;
				FadeG = ColorData[ModeColor[0]][G] / 25;
				FadeB = ColorData[ModeColor[0]][B] / 25;
			}
		} break;
	}
	
	
	
	for (TempGrp = GRP_ONE; TempGrp <= GRP_SIX; TempGrp++)
	{
			ColorBuffer[TempGrp][GRP_LED - 1].DutyR		= TempR;
			ColorBuffer[TempGrp][GRP_LED - 1].DutyG	= TempG;
			ColorBuffer[TempGrp][GRP_LED - 1].DutyB	= TempB;
	}		
	
	for (TempGrp = GRP_ONE; TempGrp <= GRP_SIX; TempGrp++)
	{
		for (TempLed = 0; TempLed < GRP_LED - 1; TempLed++)
		{
			ColorBuffer[TempGrp][TempLed].DutyR		= ColorBuffer[TempGrp][TempLed + 1].DutyR;
			ColorBuffer[TempGrp][TempLed].DutyG	= ColorBuffer[TempGrp][TempLed + 1].DutyG;
			ColorBuffer[TempGrp][TempLed].DutyB	= ColorBuffer[TempGrp][TempLed + 1].DutyB;
		}
	}

}

/**********************************************************
	*
	* Function Name			: Flower_Bloom()
	*
***********************************************************/
void Flower_Bloom(void)
{
		/* 初始化 */
	if (DisplayData.InitFlag == TRUE)
	{
		DisplayData.InitFlag = FALSE;
		
		for (TempGrp = GRP_ONE; TempGrp <= GRP_SIX; TempGrp++)
		{
			ModeTime[TempGrp]	= 0;
			ModeStep[TempGrp]	= 0;
			ModeLed[TempGrp]	= 0;
			ModeColor[TempGrp]= 0;
		}
		
		for (TempGrp = GRP_ONE; TempGrp <= GRP_SIX; TempGrp++)
		{
			for (TempLed = 0; TempLed < GRP_LED; TempLed++)
			{
				ColorBuffer[TempGrp][TempLed].DutyR		= 0;
				ColorBuffer[TempGrp][TempLed].DutyG		= 0;
				ColorBuffer[TempGrp][TempLed].DutyB		= 0;
			}
		}
		
		FadeR = ColorData[0][R] / FADE_LEVEL;
		FadeG = ColorData[0][G] / FADE_LEVEL;
		FadeB = ColorData[0][B] / FADE_LEVEL;
		TempColor = 0;
		
		return;
	}
	
	
	/* 模式控制 */
	switch (ModeStep[0])
	{
		case 0:
			{
				if (ModeStep[1] >= GRP_LED)
				{
					ModeStep[1]	= 0;
					ModeStep[2]++;
				}
				TempLed 	= ModeStep[1]++;
				
				if (ModeStep[2] > GRP_SIX)
				{
					ModeStep[2] = 0;
					ModeStep[0]++;
					break;
				}
				TempGrp	= ModeStep[2];
				
				ColorBuffer[TempGrp][TempLed].DutyR		= ColorData[TempColor][R];
				ColorBuffer[TempGrp][TempLed].DutyG	= ColorData[TempColor][G];
				ColorBuffer[TempGrp][TempLed].DutyB	= ColorData[TempColor][B];
				
				FadeR	= ColorData[TempColor][R] / 50;
				FadeG = ColorData[TempColor][G] / 50;
				FadeB = ColorData[TempColor][B] / 50;
			} break;
			
		case 1:
			{
				if (ModeTime[1] < (GRP_LED * 5))
				{
					ModeTime[1]++;
				}
				
				for (TempLed = 0; TempLed < GRP_LED; TempLed++)
				{
					if (TempLed >= (GRP_LED - ModeTime[1] / 5))
					{
						if (ColorBuffer[0][TempLed].DutyR > 0 ||  ColorBuffer[0][TempLed].DutyG > 0 || ColorBuffer[0][TempLed].DutyB > 0)
						{
							for (TempGrp = GRP_ONE; TempGrp <= GRP_SIX; TempGrp++)
							{
								ColorBuffer[TempGrp][TempLed].DutyR	-= FadeR;
								ColorBuffer[TempGrp][TempLed].DutyG	-= FadeG;
								ColorBuffer[TempGrp][TempLed].DutyB	-= FadeB;
							}
						}
					}
				}
				
				if (ColorBuffer[0][0].DutyR == 0 &&  ColorBuffer[0][0].DutyG == 0 && ColorBuffer[0][0].DutyB == 0)
				{
					ModeStep[0]++;
					ModeStep[1]	= 0;
					ModeStep[2]	= 0;
					ModeTime[1] = 0;
				}
			} break;
			
		case 2:
		{
						TempColor++;
						if (TempColor > ColorNum)		TempColor = 0;
						ModeStep[0] = 0;
		} break;
	}
}


/**********************************************************
	*
	* Function Name			: Polar_Light()
	*
***********************************************************/
void Polar_Light(void)
{
	//--------------------------------------------------------
	/* 初始化 */
	if (DisplayData.InitFlag == TRUE)
	{
		DisplayData.InitFlag	= FALSE;
		
		ModeStep[0]	= 0;
		FadeR				= 0;
		FadeG				= 0;
		FadeB				= 0;
		ModeTime[0]	= 0;
		
		for (TempGrp = GRP_ONE; TempGrp <= GRP_SIX; TempGrp++)
		{
			for (TempLed = 0; TempLed < GRP_LED; TempLed++)
			{
				ColorBuffer[TempGrp][TempLed].DutyR		= 0;
				ColorBuffer[TempGrp][TempLed].DutyG	= 0;
				ColorBuffer[TempGrp][TempLed].DutyB	= 0;
			}
		}
		
		return;
	}
	
	//--------------------------------------------------------
	/* 速度控制 */
	if (ModeTime[0] < 5)
	{
		ModeTime[0]++;
		return;
	}
	ModeTime[0]	= 0;
	
	
	//--------------------------------------------------------
	/* 模式控制 */
	switch (ModeStep[0])
	{
		case 0:
			{
				if (FadeR < 255)				FadeR += 15;
				else										ModeStep[0]++;
			} break;
			
		case 1:
			{
				if (FadeG < 255)				FadeG += 15;
				else										ModeStep[0]++;
			} break;
			
		case 2:
			{
				if (FadeR > 0)					FadeR -= 15;
				else										ModeStep[0]++;
			} break;
		
		case 3:
			{
				if (FadeB < 255)				FadeB += 15;
				else										ModeStep[0]++;
			} break;
			
		case 4:
			{
				if (FadeG > 0)					FadeG -= 15;
				else										ModeStep[0]++;
			} break;
			
		case 5:
			{
				if (FadeR < 255)				FadeR += 15;
				else										ModeStep[0]++;
			} break;
			
		case 6:
			{
				if (FadeB > 0)					FadeB -= 15;
				else										ModeStep[0] = 1;
			} break;
	}
	
	for (TempGrp = GRP_ONE; TempGrp <= GRP_SIX; TempGrp++)
	{
		ColorBuffer[TempGrp][GRP_LED - 1].DutyR		= FadeR;
		ColorBuffer[TempGrp][GRP_LED - 1].DutyG	= FadeG;
		ColorBuffer[TempGrp][GRP_LED - 1].DutyB	= FadeB;
	}
	
	for (TempGrp = GRP_ONE; TempGrp <= GRP_SIX; TempGrp++)
	{
		for (TempLed = 0; TempLed < GRP_LED - 1; TempLed++)
		{
			ColorBuffer[TempGrp][TempLed].DutyR		= ColorBuffer[TempGrp][TempLed + 1].DutyR;
			ColorBuffer[TempGrp][TempLed].DutyG	= ColorBuffer[TempGrp][TempLed + 1].DutyG;
			ColorBuffer[TempGrp][TempLed].DutyB	= ColorBuffer[TempGrp][TempLed + 1].DutyB;
		}
	}
	
}


/**********************************************************
	*
	* Function Name			: Color_Show()
	*
***********************************************************/
void Color_Show(void)
{
	if (DisplayData.InitFlag == TRUE)
	{
		DisplayData.InitFlag = FALSE;
		
		ModeStep[0]	= 0;
		TempR				= 0;
		TempG				= 0;
		TempB				= 0;
		ModeTime[0]	= 0;
		ModeTime[1]	= 0;
		
		HorseCnt = 0;
		SynFlag = TRUE;
		
		for (TempGrp = GRP_ONE; TempGrp <= GRP_SIX; TempGrp++)
		{
			for (TempLed = 0; TempLed < GRP_LED; TempLed++)
			{
				ColorBuffer[TempGrp][TempLed].DutyR		= 0;
				ColorBuffer[TempGrp][TempLed].DutyG	= 0;
				ColorBuffer[TempGrp][TempLed].DutyB	= 0;
			}
		}
		
		return;
	}
	
	/* 速度控制 */
	ModeTime[0]++;
	if (ModeTime[0] >= 5)
	{
		ModeTime[0] = 0;
		
		ModeTime[1]++;
		if (ModeTime[1] >= 30)
		{
			ModeTime[1] = 0;
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
		
		
		for (TempGrp = GRP_ONE; TempGrp <= GRP_SIX; TempGrp++)
		{
			ColorBuffer[TempGrp][GRP_LED - 1].DutyR		= TempR;
			ColorBuffer[TempGrp][GRP_LED - 1].DutyG	= TempG;
			ColorBuffer[TempGrp][GRP_LED - 1].DutyB	= TempB;
		}
		
		for (TempGrp = GRP_ONE; TempGrp <= GRP_SIX; TempGrp++)
		{
			for (TempLed = 0; TempLed < GRP_LED - 1; TempLed++)
			{
				ColorBuffer[TempGrp][TempLed].DutyR		= ColorBuffer[TempGrp][TempLed + 1].DutyR;
				ColorBuffer[TempGrp][TempLed].DutyG	= ColorBuffer[TempGrp][TempLed + 1].DutyG;
				ColorBuffer[TempGrp][TempLed].DutyB	= ColorBuffer[TempGrp][TempLed + 1].DutyB;
			}
		}
	}
}

