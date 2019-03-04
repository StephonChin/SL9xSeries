/********************************************************************
	*
	* FILE NAME
	*									Show_2.c
	* DATE
	*									02 NOV. 2017
	* AUTHOR			
	*									DS.Chin
	* DESCRIPTION
	*									Display Show 2
	*
*********************************************************************/
#include "Display_Ctrl.h"


/**
	* FunctionName	Show_2
	*/
void Show_2(void)
{
	/* Initalize */
	if (DisplayData.InitFlag == TRUE)
	{
		DisplayData.InitFlag = FALSE;
				
		TimeLine = 0;
		ShowMode = 0;
#if _AL96_
		All_Color(0,0,0,0);
#else
		All_Color(0,0,0);
#endif
		
		return;
	}
	
	
	/* Mode Control */
	
	if (TimeLine == 0)									{ShowMode = 0;			ShowInit = TRUE;	}
	else if (TimeLine == 1640)					{ShowMode = 1;			ShowInit = TRUE;	}
	else if (TimeLine == 3410)					{ShowMode = 2;			ShowInit = TRUE;	}
	else if (TimeLine == 3950)					{ShowMode = 3;			ShowInit = TRUE;	}
	else if (TimeLine == 5010)					{ShowMode = 4;			ShowInit = TRUE;	}
	else if (TimeLine == 7000)					{TimeLine = 0;			DisplayData.InitFlag = TRUE; SynFlag = TRUE;}
  TimeLine++;
	switch (ShowMode)
	{
		case 0:			Show_2_1();		break;
		case 1:			Show_2_0();		break;
		case 2:			Show_2_2();		break;
		case 3:			Show_2_3();		break;
		case 4:			Show_2_4();		break;
	}
}


/*
 * FunctionName		Show_2_0
 * Duration				TimeLine += 1560
 */
void Show_2_0(void)
{
	if (ShowInit == TRUE)
	{
		ShowInit = FALSE;
		
#if _AL96_
		All_Color(0,0,0,0);
#else
		All_Color(0,0,0);
#endif
		
		TempColor		= 3;
		SpeedTime		= 0;
		TempStep		= 0;
		
		for (TempCnt = 0; TempCnt < 50; TempCnt++)
		{
			ModeLed[TempCnt] = 0;
		}
		
		RndCnt = 0;
		StepCnt = 0;
		return;
	}
	
	SpeedTime++;
	if (SpeedTime >= 4)
	{
		SpeedTime = 0;
		
		switch (TempStep)
		{
			case 0:
			{
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
						
						/* Snow */
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
							
							LedData.Buffer[ModeLed[0]].DutyR	= ColorData[TempColor][R];
							LedData.Buffer[ModeLed[0]].DutyG	= ColorData[TempColor][G];
							LedData.Buffer[ModeLed[0]].DutyB	= ColorData[TempColor][B];

							LedData.Buffer[ModeLed[1]].DutyR	= ColorData[TempColor][R];
							LedData.Buffer[ModeLed[1]].DutyG	= ColorData[TempColor][G];
							LedData.Buffer[ModeLed[1]].DutyB	= ColorData[TempColor][B];
							
							LedData.Buffer[ModeLed[2]].DutyR	= ColorData[TempColor][R];
							LedData.Buffer[ModeLed[2]].DutyG	= ColorData[TempColor][G];
							LedData.Buffer[ModeLed[2]].DutyB	= ColorData[TempColor][B];
						}
						
#elif _AL92A_
						/* Cane */
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
#elif _AL95_					
						/* Spot */
						if (RndCnt < 3)
						{
							LedData.Buffer[RndCnt].DutyR	= ColorData[TempColor][R];
							LedData.Buffer[RndCnt].DutyG	= ColorData[TempColor][G];
							LedData.Buffer[RndCnt].DutyB	= ColorData[TempColor][B];
							RndCnt++;
						}
#elif _AL96_
						/* Ball */
						DutyR = ColorData[TempColor][R];
						DutyG = ColorData[TempColor][G];
						DutyB = ColorData[TempColor][B];
						DutyW = ColorData[TempColor][W];
#endif
						
						StepCnt++;
						if (StepCnt >= RAND_END_TOTAL)
						{
							TempStep++;
							
							for (TempLed = 0; TempLed < 50; TempLed++)
							{
								RAND();
								HoldTime[TempLed] = (_Uint8)rand() % 20;
								ModeStep[TempLed] = 1;
								ModeTime[TempLed] = 0;
							}
							
							SteadyTime = 0;
							KeepTime = 0;
						}
			} break;
			
			
			case 1:
			{
#if _AL92C_
							/* Tree */
							for (TempLed = 0; TempLed < 3; TempLed++)
							{
								switch (ModeStep[TempLed])
								{
									case 0:
									{
										for (TempCnt = 0; TempCnt < 7; TempCnt++)
										{
											LedData.Buffer[TempLed * 7 + TempCnt].DutyR		= ColorData[TempColor][R];
											LedData.Buffer[TempLed * 7 + TempCnt].DutyG		= ColorData[TempColor][G];
											LedData.Buffer[TempLed * 7 + TempCnt].DutyB		= ColorData[TempColor][B];
										}
										ModeStep[TempLed] ++;
									} break;
									
									case 1:
									{
										ModeTime[TempLed]++;
										if (ModeTime[TempLed] > HoldTime[TempLed])
										{
											ModeTime[TempLed] = 0;
											RAND();
											HoldTime[TempLed] = (_Uint8)rand() % 20;
											ModeStep[TempLed]++;
										}
									} break;
									
									default:
									{
										for (TempCnt = 0; TempCnt < 7; TempCnt++)
										{
											LedData.Buffer[TempCnt + TempLed * 7].DutyR		/= 2;
											LedData.Buffer[TempCnt + TempLed * 7].DutyG		/= 2;
											LedData.Buffer[TempCnt + TempLed * 7].DutyB		/= 2;
										}
										ModeStep[TempLed] = 0;
									} break;
								}
							}
#elif _AL92B_
							/* Snow */
							for (TempLed = 0; TempLed < 3; TempLed++)
							{
								switch (ModeStep[TempLed])
								{
									case 0:
									{
										for (TempCnt = 0; TempCnt < 7; TempCnt++)
										{
											LedData.Buffer[TempCnt + TempLed * 7].DutyR		= ColorData[TempColor][R];
											LedData.Buffer[TempCnt + TempLed * 7].DutyG		= ColorData[TempColor][G];
											LedData.Buffer[TempCnt + TempLed * 7].DutyB		= ColorData[TempColor][B];
										}
										ModeStep[TempLed] ++;
									} break;
									
									case 1:
									{
										ModeTime[TempLed]++;
										if (ModeTime[TempLed] > HoldTime[TempLed])
										{
											ModeTime[TempLed] = 0;
											RAND();
											HoldTime[TempLed] = (_Uint8)rand() % 20;
											ModeStep[TempLed]++;
										}
									} break;
									
									default:
									{
										for (TempCnt = 0; TempCnt < 7; TempCnt++)
										{
											LedData.Buffer[TempCnt + TempLed * 7].DutyR		/= 2;
											LedData.Buffer[TempCnt + TempLed * 7].DutyG		/= 2;
											LedData.Buffer[TempCnt + TempLed * 7].DutyB		/= 2;
										}
										ModeStep[TempLed] = 0;
									} break;
								}
							}
#elif _AL92A_
							/* Cane */
							for (TempLed = 0; TempLed < 6; TempLed++)
							{
								switch (ModeStep[TempLed])
								{
									case 0:
									{
										for (TempCnt = 0; TempCnt < 5; TempCnt++)
										{
											LedData.Buffer[TempCnt + TempLed * 4].DutyR		= ColorData[TempColor][R];
											LedData.Buffer[TempCnt + TempLed * 4].DutyG		= ColorData[TempColor][G];
											LedData.Buffer[TempCnt + TempLed * 4].DutyB		= ColorData[TempColor][B];
										}
										ModeStep[TempLed] ++;
									} break;
									
									case 1:
									{
										ModeTime[TempLed]++;
										if (ModeTime[TempLed] > HoldTime[TempLed])
										{
											ModeTime[TempLed] = 0;
											RAND();
											HoldTime[TempLed] = (_Uint8)rand() % 20;
											ModeStep[TempLed]++;
										}
									} break;
									
									default:
									{
										for (TempCnt = 0; TempCnt < 4;TempCnt++)
										{
											LedData.Buffer[TempCnt + TempLed * 4].DutyR		/= 2;
											LedData.Buffer[TempCnt + TempLed * 4].DutyG		/= 2;
											LedData.Buffer[TempCnt + TempLed * 4].DutyB		/= 2;
										}
										ModeStep[TempLed] = 0;
									} break;
								}
							}
#elif _AL95_
							/* Spot */
							for (TempLed = 0; TempLed < 3; TempLed++)
							{
								switch (ModeStep[TempLed])
								{
									case 0:
									{
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
											RAND();
											HoldTime[TempLed] = (_Uint8)rand() % 20;
											ModeStep[TempLed]++;
										}
									} break;
									
									default:
									{
										LedData.Buffer[TempLed].DutyR		/= 2;
										LedData.Buffer[TempLed].DutyG		/= 2;
										LedData.Buffer[TempLed].DutyB		/= 2;
										ModeStep[TempLed] = 0;
									} break;
								}
							}
#elif _AL96_
							/* Ball */
							switch (ModeStep[0])
							{
								case 0:
								{
										DutyR		= ColorData[TempColor][R];
										DutyG		= ColorData[TempColor][G];
										DutyB		= ColorData[TempColor][B];
										DutyW		= ColorData[TempColor][W];
										ModeStep[0] ++;
								} break;
								
								case 1:
								{
									ModeTime[0]++;
									if (ModeTime[0] > HoldTime[0])
									{
										ModeTime[0] = 0;
										RAND();
										HoldTime[0] = (_Uint8)rand() % 20;
										ModeStep[0]++;
									}
								} break;
								
								default:
								{
										DutyR		/= 2;
										DutyG		/= 2;
										DutyB		/= 2;
										DutyW		/= 2;

									ModeStep[0] = 0;
								} break;
							}
#endif
							
							
							SteadyTime++;
							if (SteadyTime > 50)
							{
								SteadyTime 			= 0;
								TempStep			= 0;

								TempR	= ColorData[TempColor][R];
								TempG	= ColorData[TempColor][G];
								TempB = ColorData[TempColor][B];
#if _AL96_
								TempW = ColorData[TempColor][W];
								All_Color(TempR, TempG, TempB, TempW);
#else
								All_Color(TempR, TempG, TempB);
#endif
															
								
								TempColor++;
								if (TempColor > 5)	
								{
									TempStep		= 2;
								}
								
								for (TempCnt = 0; TempCnt < 50; TempCnt++)
								{
									ModeLed[TempCnt] = 0;
								}				

								RndCnt = 0;
								StepCnt = 0;
							}
			} break;
			
			default:
			{
#if _AL92C_
						/* Tree */
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
							
							TempColor = (RndCnt - 1) / 4;
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
#elif _AL92B_
						/* Snow */
						if (RndCnt < 12)
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
							
							TempColor = ModeLed[0] / 7;
							LedData.Buffer[ModeLed[0]].DutyR	= ColorData[TempColor][R];
							LedData.Buffer[ModeLed[0]].DutyG	= ColorData[TempColor][G];
							LedData.Buffer[ModeLed[0]].DutyB	= ColorData[TempColor][B];
							
							TempColor = ModeLed[1] / 7;
							LedData.Buffer[ModeLed[1]].DutyR	= ColorData[TempColor][R];
							LedData.Buffer[ModeLed[1]].DutyG	= ColorData[TempColor][G];
							LedData.Buffer[ModeLed[1]].DutyB	= ColorData[TempColor][B];
							
							TempColor = ModeLed[2] / 7;
							LedData.Buffer[ModeLed[2]].DutyR	= ColorData[TempColor][R];
							LedData.Buffer[ModeLed[2]].DutyG	= ColorData[TempColor][G];
							LedData.Buffer[ModeLed[2]].DutyB	= ColorData[TempColor][B];
						}
#elif _AL92A_
						/* Cane */
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
#elif _AL95_
						/* Spot */
						if (RndCnt < 3)
						{
							LedData.Buffer[RndCnt].DutyR	= ColorData[RndCnt][R];
							LedData.Buffer[RndCnt].DutyG	= ColorData[RndCnt][G];
							LedData.Buffer[RndCnt].DutyB	= ColorData[RndCnt][B];
							RndCnt++;
						}
#elif _AL96_
						/* Ball */
						DutyR = ColorData[1][R];
						DutyG = ColorData[1][G];
						DutyB = ColorData[1][B];
						DutyW = ColorData[1][W];
#endif
						
						StepCnt++;
						if (StepCnt >= 40)
						{
							TempStep = 0xFF;
						}
			} break;
		}
	}
}


/*
 * FunctionName		Show_2_1
 * Duration				TimeLine += 3200
 */
void Show_2_1(void)
{
	/* Initalize */
	if (ShowInit == TRUE)
	{
		ShowInit = FALSE;
		
		TempColor		= 0;
		SpeedTime		= 0;
		TempStep		= 0;
		
		
#if _AL92C_
		for (TempCnt = 0; TempCnt < 3; TempCnt++)
		{
			TempColor = TempCnt % ColorNum;
			for (TempLed = 0; TempLed < 7; TempLed++)
			{
				LedData.Buffer[TempCnt * 7 + TempLed].DutyR = ColorData[TempColor][R];
				LedData.Buffer[TempCnt * 7 + TempLed].DutyG = ColorData[TempColor][G];
				LedData.Buffer[TempCnt * 7 + TempLed].DutyB = ColorData[TempColor][B];
			}
		}
#elif _AL92B_
		for (TempCnt = 0; TempCnt < 3; TempCnt++)
		{
			TempColor = TempCnt % ColorNum;
			for (TempLed = 0; TempLed < 7; TempLed++)
			{
				LedData.Buffer[TempCnt * 7 + TempLed].DutyR = ColorData[TempColor][R];
				LedData.Buffer[TempCnt * 7 + TempLed].DutyG = ColorData[TempColor][G];
				LedData.Buffer[TempCnt * 7 + TempLed].DutyB = ColorData[TempColor][B];
			}
		}
#elif _AL92A_		
		for (TempCnt = 0; TempCnt < 6; TempCnt++)
		{
			TempColor = TempCnt % ColorNum;
			for (TempLed = 0; TempLed < 4; TempLed++)
			{
				LedData.Buffer[TempCnt * 4 + TempLed].DutyR = ColorData[TempColor][R];
				LedData.Buffer[TempCnt * 4 + TempLed].DutyG = ColorData[TempColor][G];
				LedData.Buffer[TempCnt * 4 + TempLed].DutyB = ColorData[TempColor][B];
			}
		}
#elif _AL95_		
		for (TempCnt = 0; TempCnt < 3; TempCnt++)
		{
			TempColor = TempCnt % ColorNum;
			LedData.Buffer[TempCnt].DutyR = ColorData[TempColor][R];
			LedData.Buffer[TempCnt].DutyG = ColorData[TempColor][G];
			LedData.Buffer[TempCnt].DutyB = ColorData[TempColor][B];
		}
#elif _AL96_	
			DutyR = ColorData[0][R];
			DutyG = ColorData[0][G];
			DutyB = ColorData[0][B];
			DutyW = ColorData[0][W];
#endif		
		
		SteadyTime		= 0;
		return;
	}
	
	
	switch (TempStep)
	{
		case 0:
		{
						SpeedTime++;
						if (SpeedTime >= 20)
						{
							SpeedTime = 0;
							
#if _AL92C_
							
							/* Tree */
							TempR = LedData.Buffer[0].DutyR;
							TempG = LedData.Buffer[0].DutyG;
							TempB = LedData.Buffer[0].DutyB;
							for (TempCnt = 0; TempCnt < 2; TempCnt++)
							{
								for (TempLed = 0; TempLed < 7; TempLed++)
								{
									LedData.Buffer[TempLed + TempCnt * 7].DutyR = LedData.Buffer[TempLed + TempCnt * 7 + 7].DutyR;
									LedData.Buffer[TempLed + TempCnt * 7].DutyG = LedData.Buffer[TempLed + TempCnt * 7 + 7].DutyG;
									LedData.Buffer[TempLed + TempCnt * 7].DutyB = LedData.Buffer[TempLed + TempCnt * 7 + 7].DutyB;
								}
							}
							for (TempLed = 0; TempLed < 7; TempLed++)
							{
								LedData.Buffer[TempLed + 14].DutyR = TempR;
								LedData.Buffer[TempLed + 14].DutyG = TempG;
								LedData.Buffer[TempLed + 14].DutyB = TempB;
							}
#elif _AL92B_
							/* Snow */
							TempR = LedData.Buffer[0].DutyR;
							TempG = LedData.Buffer[0].DutyG;
							TempB = LedData.Buffer[0].DutyB;
							for (TempCnt = 0; TempCnt < 2; TempCnt++)
							{
								for (TempLed = 0; TempLed < 7; TempLed++)
								{
									LedData.Buffer[TempLed + TempCnt * 7].DutyR = LedData.Buffer[TempLed + TempCnt * 7 + 7].DutyR;
									LedData.Buffer[TempLed + TempCnt * 7].DutyG = LedData.Buffer[TempLed + TempCnt * 7 + 7].DutyG;
									LedData.Buffer[TempLed + TempCnt * 7].DutyB = LedData.Buffer[TempLed + TempCnt * 7 + 7].DutyB;
								}
							}
							for (TempLed = 0; TempLed < 7; TempLed++)
							{
								LedData.Buffer[TempLed + 14].DutyR = TempR;
								LedData.Buffer[TempLed + 14].DutyG = TempG;
								LedData.Buffer[TempLed + 14].DutyB = TempB;
							}
#elif _AL95_
							/* Spot */
							TempR = LedData.Buffer[0].DutyR;
							TempG = LedData.Buffer[0].DutyG;
							TempB = LedData.Buffer[0].DutyB;
							for (TempCnt = 0; TempCnt < 2; TempCnt++)
							{
									LedData.Buffer[TempCnt].DutyR = LedData.Buffer[TempCnt + 1].DutyR;
									LedData.Buffer[TempCnt].DutyG = LedData.Buffer[TempCnt + 1].DutyG;
									LedData.Buffer[TempCnt].DutyB = LedData.Buffer[TempCnt + 1].DutyB;
							}
							LedData.Buffer[2].DutyR = TempR;
							LedData.Buffer[2].DutyG = TempG;
							LedData.Buffer[2].DutyB = TempB;
#elif _AL92A_
							/* Cane */
							TempR = LedData.Buffer[0].DutyR;
							TempG = LedData.Buffer[0].DutyG;
							TempB = LedData.Buffer[0].DutyB;
							for (TempCnt = 0; TempCnt < 6; TempCnt++)
							{
								for (TempLed = 0; TempLed < 4; TempLed++)
								{
									LedData.Buffer[TempLed + TempCnt * 4].DutyR = LedData.Buffer[TempLed + TempCnt * 4 + 4].DutyR;
									LedData.Buffer[TempLed + TempCnt * 4].DutyG = LedData.Buffer[TempLed + TempCnt * 4 + 4].DutyG;
									LedData.Buffer[TempLed + TempCnt * 4].DutyB = LedData.Buffer[TempLed + TempCnt * 4 + 4].DutyB;
								}
							}
							for (TempLed = 0; TempLed < 4; TempLed++)
							{
								LedData.Buffer[TempLed + 20].DutyR = TempR;
								LedData.Buffer[TempLed + 20].DutyG = TempG;
								LedData.Buffer[TempLed + 20].DutyB = TempB;
							}
#elif _AL96_
							/* Ball */
							DutyR = ColorData[TempColor][R];
							DutyG = ColorData[TempColor][G];
							DutyB = ColorData[TempColor][B];
							DutyW = ColorData[TempColor][W];
							TempColor++;
							if (TempColor >= ColorNum)	TempColor = 0;
#endif
							
							
							SteadyTime++;
							if (SteadyTime >= 20)
							{
								SteadyTime = 0;
								TempStep++;
								TempColor = 0;
								RndCnt = 0;
								
								ModeStep[0] 	= 0;
								ModeColor[0] 	= 0;
								ModeStep[0] 	= 0;
							}
						}		
		} break;
		
		
		case 1:
		{
						SpeedTime++;
						if (SpeedTime >= 10)
						{
							SpeedTime = 0;
							
#if _AL92C_
							
							/* Tree */
							switch (ModeStep[0])
							{
								case 0:
								{
											TempCnt = 0;
											for (TempLed = 0; TempLed < 7; TempLed++)
											{
												LedData.Buffer[TempLed + TempCnt * 7].DutyR = ColorData[ModeColor[0]][R];
												LedData.Buffer[TempLed + TempCnt * 7].DutyG = ColorData[ModeColor[0]][G];
												LedData.Buffer[TempLed + TempCnt * 7].DutyB = ColorData[ModeColor[0]][B];
											}
											ModeColor[0]++;
											if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
											ModeStep[0]++;
								} break;
								
								case 1:
								{
											TempCnt = 2;
											for (TempLed = 0; TempLed < 7; TempLed++)
											{
												LedData.Buffer[TempLed + TempCnt * 7].DutyR = ColorData[ModeColor[0]][R];
												LedData.Buffer[TempLed + TempCnt * 7].DutyG = ColorData[ModeColor[0]][G];
												LedData.Buffer[TempLed + TempCnt * 7].DutyB = ColorData[ModeColor[0]][B];
											}
											ModeColor[0]++;
											if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
											ModeStep[0]++;
								} break;
								
								case 2:
								{
											TempCnt = 1;
											for (TempLed = 0; TempLed < 7; TempLed++)
											{
												LedData.Buffer[TempLed + TempCnt * 7].DutyR = ColorData[ModeColor[0]][R];
												LedData.Buffer[TempLed + TempCnt * 7].DutyG = ColorData[ModeColor[0]][G];
												LedData.Buffer[TempLed + TempCnt * 7].DutyB = ColorData[ModeColor[0]][B];
											}
											ModeColor[0]++;
											if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
											ModeStep[0]++;
								} break;
								
								default:
								{
											for (TempCnt = 0; TempCnt < 3; TempCnt++)
											{
												for (TempLed = 0; TempLed < 7; TempLed++)
												{
													LedData.Buffer[TempCnt * 7 + TempLed].DutyR = ColorData[ModeColor[0]][R];
													LedData.Buffer[TempCnt * 7 + TempLed].DutyG = ColorData[ModeColor[0]][G];
													LedData.Buffer[TempCnt * 7 + TempLed].DutyB = ColorData[ModeColor[0]][B];
												}
											}
											ModeColor[0]++;
											if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
											ModeStep[0] = 0;
								} break;
							}
#elif _AL92B_
							/* Snow */
							switch (ModeStep[0])
							{
								case 0:
								{
											TempCnt = 2;
											for (TempLed = 0; TempLed < 7; TempLed++)
											{
												LedData.Buffer[TempCnt * 7 + TempLed].DutyR = ColorData[ModeColor[0]][R];
												LedData.Buffer[TempCnt * 7 + TempLed].DutyG = ColorData[ModeColor[0]][G];
												LedData.Buffer[TempCnt * 7 + TempLed].DutyB = ColorData[ModeColor[0]][B];
											}
											ModeColor[0]++;
											if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
											ModeStep[0]++;
								} break;
								
								case 1:
								{
											TempCnt = 0;
											for (TempLed = 0; TempLed < 7; TempLed++)
											{
												LedData.Buffer[TempCnt * 7 + TempLed].DutyR = ColorData[ModeColor[0]][R];
												LedData.Buffer[TempCnt * 7 + TempLed].DutyG = ColorData[ModeColor[0]][G];
												LedData.Buffer[TempCnt * 7 + TempLed].DutyB = ColorData[ModeColor[0]][B];
											}
											ModeColor[0]++;
											if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
											ModeStep[0]++;
								} break;
								
								case 2:
								{
											TempCnt = 1;
											for (TempLed = 0; TempLed < 7; TempLed++)
											{
												LedData.Buffer[TempCnt * 7 + TempLed].DutyR = ColorData[ModeColor[0]][R];
												LedData.Buffer[TempCnt * 7 + TempLed].DutyG = ColorData[ModeColor[0]][G];
												LedData.Buffer[TempCnt * 7 + TempLed].DutyB = ColorData[ModeColor[0]][B];
											}
											ModeColor[0]++;
											if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
											ModeStep[0]++;
								} break;
								
								default:
								{
											for (TempCnt = 0; TempCnt < 3; TempCnt++)
											{
												for (TempLed = 0; TempLed < 7; TempLed++)
												{
													LedData.Buffer[TempCnt * 7 + TempLed].DutyR = ColorData[ModeColor[0]][R];
													LedData.Buffer[TempCnt * 7 + TempLed].DutyG = ColorData[ModeColor[0]][G];
													LedData.Buffer[TempCnt * 7 + TempLed].DutyB = ColorData[ModeColor[0]][B];
												}
											}
											ModeColor[0]++;
											if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
											ModeStep[0] = 0;
								} break;
							}
#elif _AL95_
							/* Spot */
							switch (ModeStep[0])
							{
								case 0:
								{
											LedData.Buffer[0].DutyR = ColorData[ModeColor[0]][R];
											LedData.Buffer[0].DutyG = ColorData[ModeColor[0]][G];
											LedData.Buffer[0].DutyB = ColorData[ModeColor[0]][B];
											ModeColor[0]++;
											if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
											ModeStep[0]++;
								} break;
								
								case 1:
								{
											LedData.Buffer[2].DutyR = ColorData[ModeColor[0]][R];
											LedData.Buffer[2].DutyG = ColorData[ModeColor[0]][G];
											LedData.Buffer[2].DutyB = ColorData[ModeColor[0]][B];
											ModeColor[0]++;
											if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
											ModeStep[0]++;
								} break;
								
								case 2:
								{
											LedData.Buffer[1].DutyR = ColorData[ModeColor[0]][R];
											LedData.Buffer[1].DutyG = ColorData[ModeColor[0]][G];
											LedData.Buffer[1].DutyB = ColorData[ModeColor[0]][B];
											ModeColor[0]++;
											if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
											ModeStep[0]++;
								} break;
								
								default:
								{
											for (TempCnt = 0; TempCnt < 3; TempCnt++)
											{
												LedData.Buffer[TempCnt].DutyR = ColorData[ModeColor[0]][R];
												LedData.Buffer[TempCnt].DutyG = ColorData[ModeColor[0]][G];
												LedData.Buffer[TempCnt].DutyB = ColorData[ModeColor[0]][B];
											}
											ModeColor[0]++;
											if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
											ModeStep[0] = 0;
								} break;
							}
#elif _AL92A_
							/* Cane */
							switch (ModeStep[0])
							{
								case 0:
								{
											TempCnt = 0;
											for (TempLed = 0; TempLed < 4; TempLed++)
											{
												LedData.Buffer[TempCnt * 4 + TempLed].DutyR = ColorData[ModeColor[0]][R];
												LedData.Buffer[TempCnt * 4 + TempLed].DutyG = ColorData[ModeColor[0]][G];
												LedData.Buffer[TempCnt * 4 + TempLed].DutyB = ColorData[ModeColor[0]][B];
											}
											ModeColor[0]++;
											if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
											ModeStep[0]++;
								} break;
								
								case 1:
								{
											TempCnt = 2;
											for (TempLed = 0; TempLed < 4; TempLed++)
											{
												LedData.Buffer[TempCnt * 4 + TempLed].DutyR = ColorData[ModeColor[0]][R];
												LedData.Buffer[TempCnt * 4 + TempLed].DutyG = ColorData[ModeColor[0]][G];
												LedData.Buffer[TempCnt * 4 + TempLed].DutyB = ColorData[ModeColor[0]][B];
											}
											ModeColor[0]++;
											if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
											ModeStep[0]++;
								} break;
								
								case 2:
								{
											TempCnt = 1;
											for (TempLed = 0; TempLed < 4; TempLed++)
											{
												LedData.Buffer[TempCnt * 4 + TempLed].DutyR = ColorData[ModeColor[0]][R];
												LedData.Buffer[TempCnt * 4 + TempLed].DutyG = ColorData[ModeColor[0]][G];
												LedData.Buffer[TempCnt * 4 + TempLed].DutyB = ColorData[ModeColor[0]][B];
											}
											ModeColor[0]++;
											if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
											ModeStep[0]++;
								} break;
								
								case 3:
								{
											TempCnt = 5;
											for (TempLed = 0; TempLed < 4; TempLed++)
											{
												LedData.Buffer[TempCnt * 4 + TempLed].DutyR = ColorData[ModeColor[0]][R];
												LedData.Buffer[TempCnt * 4 + TempLed].DutyG = ColorData[ModeColor[0]][G];
												LedData.Buffer[TempCnt * 4 + TempLed].DutyB = ColorData[ModeColor[0]][B];
											}
											ModeColor[0]++;
											if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
											ModeStep[0]++;
								} break;
								
								case 4:
								{
											TempCnt = 3;
											for (TempLed = 0; TempLed < 4; TempLed++)
											{
												LedData.Buffer[TempCnt * 4 + TempLed].DutyR = ColorData[ModeColor[0]][R];
												LedData.Buffer[TempCnt * 4 + TempLed].DutyG = ColorData[ModeColor[0]][G];
												LedData.Buffer[TempCnt * 4 + TempLed].DutyB = ColorData[ModeColor[0]][B];
											}
											ModeColor[0]++;
											if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
											ModeStep[0]++;
								} break;
								
								case 5:
								{
											TempCnt = 4;
											for (TempLed = 0; TempLed < 4; TempLed++)
											{
												LedData.Buffer[TempCnt * 4 + TempLed].DutyR = ColorData[ModeColor[0]][R];
												LedData.Buffer[TempCnt * 4 + TempLed].DutyG = ColorData[ModeColor[0]][G];
												LedData.Buffer[TempCnt * 4 + TempLed].DutyB = ColorData[ModeColor[0]][B];
											}
											ModeColor[0]++;
											if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
											ModeStep[0]++;
								} break;
								
								default:
								{
											for (TempCnt = 0; TempCnt < 6; TempCnt++)
											{
												for (TempLed = 0; TempLed < 4; TempLed++)
												{
													LedData.Buffer[TempCnt * 4 + TempLed].DutyR = ColorData[ModeColor[0]][R];
													LedData.Buffer[TempCnt * 4 + TempLed].DutyG = ColorData[ModeColor[0]][G];
													LedData.Buffer[TempCnt * 4 + TempLed].DutyB = ColorData[ModeColor[0]][B];
												}
											}
											ModeColor[0]++;
											if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
											ModeStep[0] = 0;
								} break;
							}
#elif _AL96_
							/* Ball */
							switch (ModeStep[0])
							{
								case 0:
								case 2:
								{
											DutyR = ColorData[ModeColor[0]][R];
											DutyG = ColorData[ModeColor[0]][G];
											DutyB = ColorData[ModeColor[0]][B];
											DutyW = ColorData[ModeColor[0]][W];
											ModeStep[0]++;
								} break;
								
								case 1:
								case 3:
								{
											ModeColor[0]++;
											if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
											ModeStep[0]++;
								} break;
								
								case 4:
								case 5:
								case 6:
								{
											DutyR = ColorData[ModeColor[0]][R];
											DutyG = ColorData[ModeColor[0]][G];
											DutyB = ColorData[ModeColor[0]][B];
											DutyW = ColorData[ModeColor[0]][W];
											ModeStep[0]++;
								} break;
								

								default:
								{
											ModeColor[0]++;
											if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
											ModeStep[0] = 0;
								} break;
							}
#endif
							
							SteadyTime++;
							if (SteadyTime >= 100)
							{
								SteadyTime = 0;
								TempStep++;
							}
						}		
		} break;
		
		default:
		{
						SpeedTime++;
						if (SpeedTime >= 10)
						{
							SpeedTime = 0;
							
#if _AL92C_							
							/* Tree */
							switch (ModeStep[0])
							{
								case 0:
								{
											TempCnt = 0;
											for (TempLed = 0; TempLed < 7; TempLed++)
											{
												LedData.Buffer[TempLed + TempCnt * 7].DutyR = ColorData[ModeColor[0]][R];
												LedData.Buffer[TempLed + TempCnt * 7].DutyG = ColorData[ModeColor[0]][G];
												LedData.Buffer[TempLed + TempCnt * 7].DutyB = ColorData[ModeColor[0]][B];
											}
											ModeColor[0]++;
											if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
											ModeStep[0]++;
								} break;
								
								case 1:
								{
											TempCnt = 2;
											for (TempLed = 0; TempLed < 7; TempLed++)
											{
												LedData.Buffer[TempLed + TempCnt * 7].DutyR = ColorData[ModeColor[0]][R];
												LedData.Buffer[TempLed + TempCnt * 7].DutyG = ColorData[ModeColor[0]][G];
												LedData.Buffer[TempLed + TempCnt * 7].DutyB = ColorData[ModeColor[0]][B];
											}
											ModeColor[0]++;
											if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
											ModeStep[0]++;
								} break;
								
								case 2:
								{
											TempCnt = 1;
											for (TempLed = 0; TempLed < 7; TempLed++)
											{
												LedData.Buffer[TempLed + TempCnt * 7].DutyR = ColorData[ModeColor[0]][R];
												LedData.Buffer[TempLed + TempCnt * 7].DutyG = ColorData[ModeColor[0]][G];
												LedData.Buffer[TempLed + TempCnt * 7].DutyB = ColorData[ModeColor[0]][B];
											}
											ModeColor[0]++;
											if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
											ModeStep[0]++;
								} break;
								
								default:
								{
											for (TempCnt = 0; TempCnt < 3; TempCnt++)
											{
												for (TempLed = 0; TempLed < 7; TempLed++)
												{
													LedData.Buffer[TempCnt * 7 + TempLed].DutyR = ColorData[ModeColor[0]][R];
													LedData.Buffer[TempCnt * 7 + TempLed].DutyG = ColorData[ModeColor[0]][G];
													LedData.Buffer[TempCnt * 7 + TempLed].DutyB = ColorData[ModeColor[0]][B];
												}
											}
											ModeColor[0]++;
											if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
											ModeStep[0] = 0;
								} break;
							}
#elif _AL92B_
							/* Snow */
							switch (ModeStep[0])
							{
								case 0:
								{
											TempCnt = 2;
											for (TempLed = 0; TempLed < 7; TempLed++)
											{
												LedData.Buffer[TempCnt * 7 + TempLed].DutyR = ColorData[ModeColor[0]][R];
												LedData.Buffer[TempCnt * 7 + TempLed].DutyG = ColorData[ModeColor[0]][G];
												LedData.Buffer[TempCnt * 7 + TempLed].DutyB = ColorData[ModeColor[0]][B];
											}
											ModeColor[0]++;
											if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
											ModeStep[0]++;
								} break;
								
								case 1:
								{
											TempCnt = 0;
											for (TempLed = 0; TempLed < 7; TempLed++)
											{
												LedData.Buffer[TempCnt * 7 + TempLed].DutyR = ColorData[ModeColor[0]][R];
												LedData.Buffer[TempCnt * 7 + TempLed].DutyG = ColorData[ModeColor[0]][G];
												LedData.Buffer[TempCnt * 7 + TempLed].DutyB = ColorData[ModeColor[0]][B];
											}
											ModeColor[0]++;
											if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
											ModeStep[0]++;
								} break;
								
								case 2:
								{
											TempCnt = 1;
											for (TempLed = 0; TempLed < 7; TempLed++)
											{
												LedData.Buffer[TempCnt * 7 + TempLed].DutyR = ColorData[ModeColor[0]][R];
												LedData.Buffer[TempCnt * 7 + TempLed].DutyG = ColorData[ModeColor[0]][G];
												LedData.Buffer[TempCnt * 7 + TempLed].DutyB = ColorData[ModeColor[0]][B];
											}
											ModeColor[0]++;
											if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
											ModeStep[0]++;
								} break;
								
								default:
								{
											for (TempCnt = 0; TempCnt < 3; TempCnt++)
											{
												for (TempLed = 0; TempLed < 7; TempLed++)
												{
													LedData.Buffer[TempCnt * 7 + TempLed].DutyR = ColorData[ModeColor[0]][R];
													LedData.Buffer[TempCnt * 7 + TempLed].DutyG = ColorData[ModeColor[0]][G];
													LedData.Buffer[TempCnt * 7 + TempLed].DutyB = ColorData[ModeColor[0]][B];
												}
											}
											ModeColor[0]++;
											if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
											ModeStep[0] = 0;
								} break;
							}
#elif _AL95_
							/* Spot */
							switch (ModeStep[0])
							{
								case 0:
								{
											LedData.Buffer[0].DutyR = ColorData[ModeColor[0]][R];
											LedData.Buffer[0].DutyG = ColorData[ModeColor[0]][G];
											LedData.Buffer[0].DutyB = ColorData[ModeColor[0]][B];
											ModeColor[0]++;
											if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
											ModeStep[0]++;
								} break;
								
								case 1:
								{
											LedData.Buffer[2].DutyR = ColorData[ModeColor[0]][R];
											LedData.Buffer[2].DutyG = ColorData[ModeColor[0]][G];
											LedData.Buffer[2].DutyB = ColorData[ModeColor[0]][B];
											ModeColor[0]++;
											if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
											ModeStep[0]++;
								} break;
								
								case 2:
								{
											LedData.Buffer[1].DutyR = ColorData[ModeColor[0]][R];
											LedData.Buffer[1].DutyG = ColorData[ModeColor[0]][G];
											LedData.Buffer[1].DutyB = ColorData[ModeColor[0]][B];
											ModeColor[0]++;
											if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
											ModeStep[0]++;
								} break;
								
								default:
								{
											for (TempCnt = 0; TempCnt < 3; TempCnt++)
											{
												LedData.Buffer[TempCnt].DutyR = ColorData[ModeColor[0]][R];
												LedData.Buffer[TempCnt].DutyG = ColorData[ModeColor[0]][G];
												LedData.Buffer[TempCnt].DutyB = ColorData[ModeColor[0]][B];
											}
											ModeColor[0]++;
											if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
											ModeStep[0] = 0;
								} break;
							}
#elif _AL92A_
							/* Cane */
							switch (ModeStep[0])
							{
								case 0:
								{
											TempCnt = 0;
											for (TempLed = 0; TempLed < 4; TempLed++)
											{
												LedData.Buffer[TempCnt * 4 + TempLed].DutyR = ColorData[ModeColor[0]][R];
												LedData.Buffer[TempCnt * 4 + TempLed].DutyG = ColorData[ModeColor[0]][G];
												LedData.Buffer[TempCnt * 4 + TempLed].DutyB = ColorData[ModeColor[0]][B];
											}
											ModeColor[0]++;
											if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
											ModeStep[0]++;
								} break;
								
								case 1:
								{
											TempCnt = 2;
											for (TempLed = 0; TempLed < 4; TempLed++)
											{
												LedData.Buffer[TempCnt * 4 + TempLed].DutyR = ColorData[ModeColor[0]][R];
												LedData.Buffer[TempCnt * 4 + TempLed].DutyG = ColorData[ModeColor[0]][G];
												LedData.Buffer[TempCnt * 4 + TempLed].DutyB = ColorData[ModeColor[0]][B];
											}
											ModeColor[0]++;
											if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
											ModeStep[0]++;
								} break;
								
								case 2:
								{
											TempCnt = 1;
											for (TempLed = 0; TempLed < 4; TempLed++)
											{
												LedData.Buffer[TempCnt * 4 + TempLed].DutyR = ColorData[ModeColor[0]][R];
												LedData.Buffer[TempCnt * 4 + TempLed].DutyG = ColorData[ModeColor[0]][G];
												LedData.Buffer[TempCnt * 4 + TempLed].DutyB = ColorData[ModeColor[0]][B];
											}
											ModeColor[0]++;
											if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
											ModeStep[0]++;
								} break;
								
								case 3:
								{
											TempCnt = 5;
											for (TempLed = 0; TempLed < 4; TempLed++)
											{
												LedData.Buffer[TempCnt * 4 + TempLed].DutyR = ColorData[ModeColor[0]][R];
												LedData.Buffer[TempCnt * 4 + TempLed].DutyG = ColorData[ModeColor[0]][G];
												LedData.Buffer[TempCnt * 4 + TempLed].DutyB = ColorData[ModeColor[0]][B];
											}
											ModeColor[0]++;
											if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
											ModeStep[0]++;
								} break;
								
								case 4:
								{
											TempCnt = 3;
											for (TempLed = 0; TempLed < 4; TempLed++)
											{
												LedData.Buffer[TempCnt * 4 + TempLed].DutyR = ColorData[ModeColor[0]][R];
												LedData.Buffer[TempCnt * 4 + TempLed].DutyG = ColorData[ModeColor[0]][G];
												LedData.Buffer[TempCnt * 4 + TempLed].DutyB = ColorData[ModeColor[0]][B];
											}
											ModeColor[0]++;
											if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
											ModeStep[0]++;
								} break;
								
								case 5:
								{
											TempCnt = 4;
											for (TempLed = 0; TempLed < 4; TempLed++)
											{
												LedData.Buffer[TempCnt * 4 + TempLed].DutyR = ColorData[ModeColor[0]][R];
												LedData.Buffer[TempCnt * 4 + TempLed].DutyG = ColorData[ModeColor[0]][G];
												LedData.Buffer[TempCnt * 4 + TempLed].DutyB = ColorData[ModeColor[0]][B];
											}
											ModeColor[0]++;
											if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
											ModeStep[0]++;
								} break;
								
								default:
								{
											for (TempCnt = 0; TempCnt < 6; TempCnt++)
											{
												for (TempLed = 0; TempLed < 4; TempLed++)
												{
													LedData.Buffer[TempCnt * 4 + TempLed].DutyR = ColorData[ModeColor[0]][R];
													LedData.Buffer[TempCnt * 4 + TempLed].DutyG = ColorData[ModeColor[0]][G];
													LedData.Buffer[TempCnt * 4 + TempLed].DutyB = ColorData[ModeColor[0]][B];
												}
											}
											ModeColor[0]++;
											if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
											ModeStep[0] = 0;
								} break;
							}
#elif _AL96_
							/* Ball */
							switch (ModeStep[0])
							{
								case 0:
								case 2:
								{

											DutyR = ColorData[ModeColor[0]][R];
											DutyG = ColorData[ModeColor[0]][G];
											DutyB = ColorData[ModeColor[0]][B];
											DutyW = ColorData[ModeColor[0]][W];
											ModeStep[0]++;
								} break;
								
								case 1:
								case 3:
								{
											ModeColor[0]++;
											if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
											ModeStep[0]++;
								} break;
								
								case 4:
								case 5:
								case 6:
								{
											DutyR = ColorData[ModeColor[0]][R];
											DutyG = ColorData[ModeColor[0]][G];
											DutyB = ColorData[ModeColor[0]][B];
											DutyW = ColorData[ModeColor[0]][W];
											ModeStep[0]++;
								} break;

								default:
								{
											ModeColor[0]++;
											if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
											ModeStep[0] = 0;
								} break;
							}
#endif
						}
		} break;
	}
}



/*
 * FunctionName	Show_2_2
 * TimeLine		+= 3720
 */
void Show_2_2(void)
{
	/* Initalize */
	if (ShowInit == TRUE)
	{
		ShowInit = FALSE;
		
		TempColor		= 0;
		SpeedTime		= 0;
		TempStep		= 0;
		SteadyTime		= 0;
		ModeStep[0] = 0;
		return;
	}
	
	
	switch (TempStep)
	{
		case 0:
		{
#if _AL92C_
						/* Tree */
						TempCnt = 0;
						for (TempLed = 0; TempLed < 7; TempLed++)
						{
							LedData.Buffer[TempCnt * 7 + TempLed].DutyR = ColorData[TempColor][R];
							LedData.Buffer[TempCnt * 7 + TempLed].DutyG = ColorData[TempColor][G];
							LedData.Buffer[TempCnt * 7 + TempLed].DutyB = ColorData[TempColor][B];
						}
#elif _AL92B_
						/* Snow */
						TempCnt = 0;
						for (TempLed = 0; TempLed < 7; TempLed++)
						{
							LedData.Buffer[TempCnt * 7 + TempLed].DutyR = ColorData[TempColor][R];
							LedData.Buffer[TempCnt * 7 + TempLed].DutyG = ColorData[TempColor][G];
							LedData.Buffer[TempCnt * 7 + TempLed].DutyB = ColorData[TempColor][B];
						}
#elif _AL95_					
						/* Spot */
						LedData.Buffer[0].DutyR = ColorData[TempColor][R];
						LedData.Buffer[0].DutyG = ColorData[TempColor][G];
						LedData.Buffer[0].DutyB = ColorData[TempColor][B];
#elif _AL92A_					
						/* Cane */
						TempCnt = 0;
						for (TempLed = 0; TempLed < 4; TempLed++)
						{
							LedData.Buffer[TempCnt * 4 + TempLed].DutyR = ColorData[TempColor][R];
							LedData.Buffer[TempCnt * 4 + TempLed].DutyG = ColorData[TempColor][G];
							LedData.Buffer[TempCnt * 4 + TempLed].DutyB = ColorData[TempColor][B];
						}
						TempCnt = 3;
						for (TempLed = 0; TempLed < 4; TempLed++)
						{
							LedData.Buffer[TempCnt * 4 + TempLed].DutyR = ColorData[TempColor][R];
							LedData.Buffer[TempCnt * 4 + TempLed].DutyG = ColorData[TempColor][G];
							LedData.Buffer[TempCnt * 4 + TempLed].DutyB = ColorData[TempColor][B];
						}
#elif _AL96_
						/* Ball */
						DutyR = ColorData[TempColor][R];
						DutyG = ColorData[TempColor][G];
						DutyB = ColorData[TempColor][B];
						DutyW = ColorData[TempColor][W];
#endif
						
						
						SteadyTime++;
						if (SteadyTime >= 20)
						{
							SteadyTime = 0;
							TempColor++;
							if (TempColor >= ColorNum)	TempColor = 0;
							TempStep++;
						}
		} break;
		
		
		case 1:
		{
#if _AL92C_
						/* Tree */
						TempCnt = 1;
						for (TempLed = 0; TempLed < 7; TempLed++)
						{
							LedData.Buffer[TempCnt * 7 + TempLed].DutyR = ColorData[TempColor][R];
							LedData.Buffer[TempCnt * 7 + TempLed].DutyG = ColorData[TempColor][G];
							LedData.Buffer[TempCnt * 7 + TempLed].DutyB = ColorData[TempColor][B];
						}
#elif _AL92B_		
						/* Snow */
						TempCnt = 1;
						for (TempLed = 0; TempLed < 7; TempLed++)
						{
							LedData.Buffer[TempCnt * 7 + TempLed].DutyR = ColorData[TempColor][R];
							LedData.Buffer[TempCnt * 7 + TempLed].DutyG = ColorData[TempColor][G];
							LedData.Buffer[TempCnt * 7 + TempLed].DutyB = ColorData[TempColor][B];
						}
#elif _AL95_
						/* Spot */
						LedData.Buffer[1].DutyR = ColorData[TempColor][R];
						LedData.Buffer[1].DutyG = ColorData[TempColor][G];
						LedData.Buffer[1].DutyB = ColorData[TempColor][B];
#elif _AL92A_	
						/* Cane */
						TempCnt = 1;
						for (TempLed = 0; TempLed < 4; TempLed++)
						{
							LedData.Buffer[TempCnt * 4 + TempLed].DutyR = ColorData[TempColor][R];
							LedData.Buffer[TempCnt * 4 + TempLed].DutyG = ColorData[TempColor][G];
							LedData.Buffer[TempCnt * 4 + TempLed].DutyB = ColorData[TempColor][B];
						}
						TempCnt = 4;
						for (TempLed = 0; TempLed < 4; TempLed++)
						{
							LedData.Buffer[TempCnt * 4 + TempLed].DutyR = ColorData[TempColor][R];
							LedData.Buffer[TempCnt * 4 + TempLed].DutyG = ColorData[TempColor][G];
							LedData.Buffer[TempCnt * 4 + TempLed].DutyB = ColorData[TempColor][B];
						}
#elif _AL96_	
						/* Ball */
						DutyR = ColorData[TempColor][R];
						DutyG = ColorData[TempColor][G];
						DutyB = ColorData[TempColor][B];
						DutyW = ColorData[TempColor][W];
#endif
						
						SteadyTime++;
						if (SteadyTime >= 20)
						{
							SteadyTime = 0;
							TempColor++;
							if (TempColor >= ColorNum)	TempColor = 0;
							TempStep++;
						}
		} break;
		
		case 2:
		{
#if _AL92C_
						
						/* Tree */
						TempCnt = 2;
						for (TempLed = 0; TempLed < 7; TempLed++)
						{
							LedData.Buffer[TempCnt * 7 + TempLed].DutyR = ColorData[TempColor][R];
							LedData.Buffer[TempCnt * 7 + TempLed].DutyG = ColorData[TempColor][G];
							LedData.Buffer[TempCnt * 7 + TempLed].DutyB = ColorData[TempColor][B];
						}
#elif _AL92B_	
						/* Snow */
						TempCnt = 2;
						for (TempLed = 0; TempLed < 7; TempLed++)
						{
							LedData.Buffer[TempCnt * 7 + TempLed].DutyR = ColorData[TempColor][R];
							LedData.Buffer[TempCnt * 7 + TempLed].DutyG = ColorData[TempColor][G];
							LedData.Buffer[TempCnt * 7 + TempLed].DutyB = ColorData[TempColor][B];
						}
#elif _AL95_
						/* Spot */
						LedData.Buffer[2].DutyR = ColorData[TempColor][R];
						LedData.Buffer[2].DutyG = ColorData[TempColor][G];
						LedData.Buffer[2].DutyB = ColorData[TempColor][B];
#elif _AL92A_
						/* Cane */
						TempCnt = 2;
						for (TempLed = 0; TempLed < 4; TempLed++)
						{
							LedData.Buffer[TempCnt * 4 + TempLed].DutyR = ColorData[TempColor][R];
							LedData.Buffer[TempCnt * 4 + TempLed].DutyG = ColorData[TempColor][G];
							LedData.Buffer[TempCnt * 4 + TempLed].DutyB = ColorData[TempColor][B];
						}
						TempCnt = 5;
						for (TempLed = 0; TempLed < 4; TempLed++)
						{
							LedData.Buffer[TempCnt * 4 + TempLed].DutyR = ColorData[TempColor][R];
							LedData.Buffer[TempCnt * 4 + TempLed].DutyG = ColorData[TempColor][G];
							LedData.Buffer[TempCnt * 4 + TempLed].DutyB = ColorData[TempColor][B];
						}
#elif _AL96_
						/* Ball */
						DutyR = ColorData[TempColor][R];
						DutyG = ColorData[TempColor][G];
						DutyB = ColorData[TempColor][B];
						DutyW = ColorData[TempColor][W];
#endif
						
						SteadyTime++;
						if (SteadyTime >= 20)
						{
							SteadyTime = 0;
							TempColor++;
							if (TempColor >= ColorNum)	TempColor = 0;
							TempStep++;
							RndCnt = 0;
						}
		} break;
		
		
		
		case 3:
		{	
						SpeedTime++;
						if (SpeedTime >= 2)
						{
							SpeedTime = 0;
							
#if _AL92C_
							TempCnt = 0;
							if (LedData.Buffer[0].DutyR > 0 || LedData.Buffer[0].DutyG > 0 || LedData.Buffer[0].DutyB > 0)
							{
								FadeR = ColorData[0 + ModeStep[0]][R] / 25;
								FadeG = ColorData[0 + ModeStep[0]][G] / 25;
								FadeB = ColorData[0 + ModeStep[0]][B] / 25;

								for (TempLed = 0; TempLed < 7; TempLed++)
								{
									LedData.Buffer[TempCnt * 7 + TempLed].DutyR -= FadeR;
									LedData.Buffer[TempCnt * 7 + TempLed].DutyG -= FadeG;
									LedData.Buffer[TempCnt * 7 + TempLed].DutyB -= FadeB;
								}
							}
#elif _AL92B_	
							/* Snow */
							TempCnt = 0;
							if (LedData.Buffer[0].DutyR > 0 || LedData.Buffer[0].DutyG > 0 || LedData.Buffer[0].DutyB > 0)
							{
								FadeR = ColorData[0 + ModeStep[0]][R] / 25;
								FadeG = ColorData[0 + ModeStep[0]][G] / 25;
								FadeB = ColorData[0 + ModeStep[0]][B] / 25;
								TempCnt = 0;
								for (TempLed = 0; TempLed < 7; TempLed++)
								{
									LedData.Buffer[TempCnt * 7 + TempLed].DutyR -= FadeR;
									LedData.Buffer[TempCnt * 7 + TempLed].DutyG -= FadeG;
									LedData.Buffer[TempCnt * 7 + TempLed].DutyB -= FadeB;
								}
							}
#elif _AL95_
								
							/* Spot */
							if (LedData.Buffer[0].DutyR > 0 || LedData.Buffer[0].DutyG > 0 || LedData.Buffer[0].DutyB > 0)
							{
								FadeR = ColorData[0 + ModeStep[0]][R] / 25;
								FadeG = ColorData[0 + ModeStep[0]][G] / 25;
								FadeB = ColorData[0 + ModeStep[0]][B] / 25;
								LedData.Buffer[0].DutyR -= FadeR;
								LedData.Buffer[0].DutyG -= FadeG;
								LedData.Buffer[0].DutyB -= FadeB;
							}
#elif _AL92A_
								/* Cane */
							if (LedData.Buffer[0].DutyR > 0 || LedData.Buffer[0].DutyG > 0 || LedData.Buffer[0].DutyB > 0)
							{
								FadeR = ColorData[0 + ModeStep[0]][R] / 25;
								FadeG = ColorData[0 + ModeStep[0]][G] / 25;
								FadeB = ColorData[0 + ModeStep[0]][B] / 25;
								TempCnt = 0;
								for (TempLed = 0; TempLed < 4; TempLed++)
								{
									LedData.Buffer[TempCnt * 4 + TempLed].DutyR -= FadeR;
									LedData.Buffer[TempCnt * 4 + TempLed].DutyG -= FadeG;
									LedData.Buffer[TempCnt * 4 + TempLed].DutyB -= FadeB;
								}
								TempCnt = 3;
								for (TempLed = 0; TempLed < 4; TempLed++)
								{
									LedData.Buffer[TempCnt * 4 + TempLed].DutyR -= FadeR;
									LedData.Buffer[TempCnt * 4 + TempLed].DutyG -= FadeG;
									LedData.Buffer[TempCnt * 4 + TempLed].DutyB -= FadeB;
								}
							}
#endif

							
							if (RndCnt >= 15)
							{
#if _AL92C_
									/* Tree */
								if (LedData.Buffer[7].DutyR > 0 || LedData.Buffer[7].DutyG > 0 || LedData.Buffer[7].DutyB > 0)
								{
									FadeR = ColorData[1 + ModeStep[0]][R] / 25;
									FadeG = ColorData[1 + ModeStep[0]][G] / 25;
									FadeB = ColorData[1 + ModeStep[0]][B] / 25;
									TempCnt = 1;
									for (TempLed = 0; TempLed < 7; TempLed++)
									{
										LedData.Buffer[TempCnt * 7 + TempLed].DutyR -= FadeR;
										LedData.Buffer[TempCnt * 7 + TempLed].DutyG -= FadeG;
										LedData.Buffer[TempCnt * 7 + TempLed].DutyB -= FadeB;
									}
								}
								
#elif _AL92B_
										
									/* Snow */
								if (LedData.Buffer[7].DutyR > 0 || LedData.Buffer[7].DutyG > 0 || LedData.Buffer[7].DutyB > 0)
								{
									FadeR = ColorData[1 + ModeStep[0]][R] / 25;
									FadeG = ColorData[1 + ModeStep[0]][G] / 25;
									FadeB = ColorData[1 + ModeStep[0]][B] / 25;
									TempCnt = 1;
									for (TempLed = 0; TempLed < 7; TempLed++)
									{
										LedData.Buffer[TempCnt * 7 + TempLed].DutyR -= FadeR;
										LedData.Buffer[TempCnt * 7 + TempLed].DutyG -= FadeG;
										LedData.Buffer[TempCnt * 7 + TempLed].DutyB -= FadeB;
									}
								}
								
#elif _AL95_
									
									/* Spot */
								if (LedData.Buffer[1].DutyR > 0 || LedData.Buffer[1].DutyG > 0 || LedData.Buffer[1].DutyB > 0)
								{
									FadeR = ColorData[1 + ModeStep[0]][R] / 25;
									FadeG = ColorData[1 + ModeStep[0]][G] / 25;
									FadeB = ColorData[1 + ModeStep[0]][B] / 25;
									LedData.Buffer[1].DutyR -= FadeR;
									LedData.Buffer[1].DutyG -= FadeG;
									LedData.Buffer[1].DutyB -= FadeB;
								}
#elif _AL92A_
									/* Cane */
								if (LedData.Buffer[4].DutyR > 0 || LedData.Buffer[4].DutyG > 0 || LedData.Buffer[4].DutyB > 0)
								{
									FadeR = ColorData[1 + ModeStep[0]][R] / 25;
									FadeG = ColorData[1 + ModeStep[0]][G] / 25;
									FadeB = ColorData[1 + ModeStep[0]][B] / 25;
									TempCnt = 1;
									for (TempLed = 0; TempLed < 4; TempLed++)
									{
										LedData.Buffer[TempCnt * 4 + TempLed].DutyR -= FadeR;
										LedData.Buffer[TempCnt * 4 + TempLed].DutyG -= FadeG;
										LedData.Buffer[TempCnt * 4 + TempLed].DutyB -= FadeB;
									}
									TempCnt = 4;
									for (TempLed = 0; TempLed < 4; TempLed++)
									{
										LedData.Buffer[TempCnt * 4 + TempLed].DutyR -= FadeR;
										LedData.Buffer[TempCnt * 4 + TempLed].DutyG -= FadeG;
										LedData.Buffer[TempCnt * 4 + TempLed].DutyB -= FadeB;
									}
								}
#endif
							}
							
							if (RndCnt >= 30)
							{
#if _AL92C_
									
									/* Tree */
								if (LedData.Buffer[14].DutyR > 0 || LedData.Buffer[14].DutyG > 0 || LedData.Buffer[14].DutyB > 0)
								{
									FadeR = ColorData[2 + ModeStep[0]][R] / 25;
									FadeG = ColorData[2 + ModeStep[0]][G] / 25;
									FadeB = ColorData[2 + ModeStep[0]][B] / 25;
									TempCnt = 2;
									for (TempLed = 0; TempLed < 7; TempLed++)
									{
										LedData.Buffer[TempCnt * 7 + TempLed].DutyR -= FadeR;
										LedData.Buffer[TempCnt * 7 + TempLed].DutyG -= FadeG;
										LedData.Buffer[TempCnt * 7 + TempLed].DutyB -= FadeB;
									}
								}
#elif _AL92B_
									
									/* Snow */
								if (LedData.Buffer[14].DutyR > 0 || LedData.Buffer[14].DutyG > 0 || LedData.Buffer[14].DutyB > 0)
								{
									FadeR = ColorData[2 + ModeStep[0]][R] / 25;
									FadeG = ColorData[2 + ModeStep[0]][G] / 25;
									FadeB = ColorData[2 + ModeStep[0]][B] / 25;
									TempCnt = 2;
									for (TempLed = 0; TempLed < 7; TempLed++)
									{
										LedData.Buffer[TempCnt * 7 + TempLed].DutyR -= FadeR;
										LedData.Buffer[TempCnt * 7 + TempLed].DutyG -= FadeG;
										LedData.Buffer[TempCnt * 7 + TempLed].DutyB -= FadeB;
									}
								}
								
#elif _AL95_
									
									/* Spot */
								if (LedData.Buffer[2].DutyR > 0 || LedData.Buffer[2].DutyG > 0 || LedData.Buffer[2].DutyB > 0)
								{
									FadeR = ColorData[2 + ModeStep[0]][R] / 25;
									FadeG = ColorData[2 + ModeStep[0]][G] / 25;
									FadeB = ColorData[2 + ModeStep[0]][B] / 25;
									LedData.Buffer[2].DutyR -= FadeR;
									LedData.Buffer[2].DutyG -= FadeG;
									LedData.Buffer[2].DutyB -= FadeB;
								}
#elif _AL92A_
									/* Cane */
								if (LedData.Buffer[8].DutyR > 0 || LedData.Buffer[8].DutyG > 0 || LedData.Buffer[8].DutyB > 0)
								{
									FadeR = ColorData[2 + ModeStep[0]][R] / 25;
									FadeG = ColorData[2 + ModeStep[0]][G] / 25;
									FadeB = ColorData[2 + ModeStep[0]][B] / 25;
									TempCnt = 2;
									for (TempLed = 0; TempLed < 4; TempLed++)
									{
										LedData.Buffer[TempCnt * 4 + TempLed].DutyR -= FadeR;
										LedData.Buffer[TempCnt * 4 + TempLed].DutyG -= FadeG;
										LedData.Buffer[TempCnt * 4 + TempLed].DutyB -= FadeB;
									}
									TempCnt = 5;
									for (TempLed = 0; TempLed < 4; TempLed++)
									{
										LedData.Buffer[TempCnt * 4 + TempLed].DutyR -= FadeR;
										LedData.Buffer[TempCnt * 4 + TempLed].DutyG -= FadeG;
										LedData.Buffer[TempCnt * 4 + TempLed].DutyB -= FadeB;
									}
								}
#elif _AL96_
									/* Ball */
								if (DutyR > 0 || DutyG > 0 || DutyB > 0 || DutyW > 0)
								{
									FadeR = ColorData[2 + ModeStep[0]][R] / 25;
									FadeG = ColorData[2 + ModeStep[0]][G] / 25;
									FadeB = ColorData[2 + ModeStep[0]][B] / 25;
									FadeW = ColorData[2 + ModeStep[0]][W] / 25;
									DutyR -= FadeR;
									DutyG -= FadeG;
									DutyB -= FadeB;
									DutyW -= FadeW;
								}
#endif
								else
								{
									TempStep = 0;
									ModeStep[0] += 3;
									if (ModeStep[0] >= 9)		TempStep = 4;
									RndCnt = 0;
								}
							}
							
							if (RndCnt < 31)		RndCnt++;
						}
		} break;
		
		default:
		{
						TempStep = 5;
		} break;
	}
}

/*
 * FunctionName		Show_2_3
 * Duration				TimeLine += 1030 
 */
void Show_2_3(void)
{
	/* Initalize */
	if (ShowInit == TRUE)
	{
		ShowInit = FALSE;
				
		TempColor		= 0;
		SpeedTime		= 0;
		TempStep		= 0;
		RndCnt			= 0;
		KeepTime		= 0;	
		StepCnt = 0;
		
#if _AL96_
		All_Color(0,0,0,0);
		TempR = 0;
		TempG = 0;
		TempB = 0;
		TempW = 0;
		FadeR = ColorData[TempColor][R] / 50;
		FadeG = ColorData[TempColor][G] / 50;
		FadeB = ColorData[TempColor][B] / 50;
		FadeW = ColorData[TempColor][W] / 50;
#else
		All_Color(0,0,0);
		TempR = 0;
		TempG = 0;
		TempB = 0;
		FadeR = ColorData[TempColor][R] / 50;
		FadeG = ColorData[TempColor][G] / 50;
		FadeB = ColorData[TempColor][B] / 50;
#endif
		
		
		return;
	}
	
	
	switch (TempStep)
	{
		case 0:
		{
						TempR += FadeR;
						TempG += FadeG;
						TempB += FadeB;
#if _AL96_
						TempW += FadeW;
						All_Color(TempR, TempG, TempB, TempW);
#else
						All_Color(TempR, TempG, TempB);
#endif
						StepCnt++;
						if (StepCnt >= 50)  
						{
							TempStep++;
							FadeR = ColorData[TempColor][R] / 50;
							FadeG = ColorData[TempColor][G] / 50;
							FadeB = ColorData[TempColor][B] / 50;
#if _AL96_
							FadeW = ColorData[TempColor][W] / 50;
#endif

							RndCnt = 0;
							StepCnt = 0;
							
							for (TempLed = 0; TempLed < 50; TempLed++)
							{
								ModeLed[TempLed] = 0;
								RAND();
								HoldTime[TempLed] = (_Uint8)rand() % 5 + 5;
							}
						}
		} break;
		
		
		case 1:
		{
#if _AL92C_
						/* Tree */
						if (RndCnt < 3)
						{
							for (TempLed = 0; TempLed < 3; TempLed++)
							{
								if (ModeLed[TempLed] == 1) continue;
								
								ModeTime[TempLed]++;
								if (ModeTime[TempLed] >= HoldTime[TempLed])
								{
									ModeTime[TempLed] = 0;
									for (TempCnt = 0; TempCnt < 7; TempCnt++)
									{
										LedData.Buffer[TempCnt + TempLed * 7].DutyR -= FadeR;
										LedData.Buffer[TempCnt + TempLed * 7].DutyG -= FadeG;
										LedData.Buffer[TempCnt + TempLed * 7].DutyB -= FadeB;
									}
								}
								
								if (LedData.Buffer[TempLed * 7].DutyR == 0 && LedData.Buffer[TempLed * 7].DutyG == 0 && LedData.Buffer[TempLed * 7].DutyB == 0)
								{
									RndCnt++;
									ModeLed[TempLed] = 1;
								}
							}
						}
						else
						{
							RndCnt++;
						}
#elif _AL92B_
						/* Snow */
						if (RndCnt < 3)
						{
							for (TempLed = 0; TempLed < 3; TempLed++)
							{
								if (ModeLed[TempLed] == 1) continue;
								
								ModeTime[TempLed]++;
								if (ModeTime[TempLed] >= HoldTime[TempLed])
								{
									ModeTime[TempLed] = 0;
									for (TempCnt = 0; TempCnt < 7; TempCnt++)
									{
										LedData.Buffer[TempLed * 7 + TempCnt].DutyR -= FadeR;
										LedData.Buffer[TempLed * 7 + TempCnt].DutyG -= FadeG;
										LedData.Buffer[TempLed * 7 + TempCnt].DutyB -= FadeB;
									}
								}
								
								if (LedData.Buffer[TempLed * 7].DutyR == 0 && LedData.Buffer[TempLed * 7].DutyG == 0 && LedData.Buffer[TempLed * 7].DutyB == 0)
								{
									RndCnt++;
									ModeLed[TempLed] = 1;
								}
							}
						}
						else
						{
							RndCnt++;
						}
#elif _AL95_
						/* Spot */
						if (RndCnt < 3)
						{
							for (TempLed = 0; TempLed < 3; TempLed++)
							{
								if (ModeLed[TempLed] == 1) continue;
								
								ModeTime[TempLed]++;
								if (ModeTime[TempLed] >= HoldTime[TempLed])
								{
									ModeTime[TempLed] = 0;
									LedData.Buffer[TempLed].DutyR -= FadeR;
									LedData.Buffer[TempLed].DutyG -= FadeG;
									LedData.Buffer[TempLed].DutyB -= FadeB;
								}
								
								if (LedData.Buffer[TempLed].DutyR == 0 && LedData.Buffer[TempLed].DutyG == 0 && LedData.Buffer[TempLed].DutyB == 0)
								{
									RndCnt++;
									ModeLed[TempLed] = 1;
								}
							}
						}
						else
						{
							RndCnt++;
						}
#elif _AL92A_
						/* Cane */
						if (RndCnt < 6)
						{
							for (TempLed = 0; TempLed < 6; TempLed++)
							{
								if (ModeLed[TempLed] == 1) continue;
								
								ModeTime[TempLed]++;
								if (ModeTime[TempLed] >= HoldTime[TempLed])
								{
									ModeTime[TempLed] = 0;
									for (TempCnt = 0; TempCnt < 4; TempCnt++)
									{
										LedData.Buffer[TempCnt + TempLed * 4].DutyR -= FadeR;
										LedData.Buffer[TempCnt + TempLed * 4].DutyG -= FadeG;
										LedData.Buffer[TempCnt + TempLed * 4].DutyB -= FadeB;
									}
								}
								
								if (LedData.Buffer[TempLed * 4].DutyR == 0 && LedData.Buffer[TempLed * 4].DutyG == 0 && LedData.Buffer[TempLed * 4].DutyB == 0)
								{
									RndCnt++;
									ModeLed[TempLed] = 1;
								}
							}
						}
						else
						{
							RndCnt++;
						}
#elif _AL96_
						/* Ball */
						if (DutyR > 0 || DutyG > 0 || DutyB > 0 || DutyW > 0)
						{
							ModeTime[0]++;
							if (ModeTime[0] >= 8)
							{
								ModeTime[0] = 0;
								DutyR -= FadeR;
								DutyG -= FadeG;
								DutyB -= FadeB;
								DutyW -= FadeW;
							}
						}
						else
						{
							RndCnt++;
						}
#endif
						
						if (RndCnt >= RAND_END_TOTAL+5)
						{
							RndCnt = 0;
							TempStep++;
							TempColor++;
							if (TempColor >= ColorNum)		TempColor = 0;
							FadeR = ColorData[TempColor][R] / 50;
							FadeG = ColorData[TempColor][G] / 50;
							FadeB = ColorData[TempColor][B] / 50;
#if _AL96_
							FadeW = ColorData[TempColor][W] / 50;
#endif

							RndCnt = 0;
							
							for (TempLed = 0; TempLed < 50; TempLed++)
							{
								ModeLed[TempLed] = 0;
								RAND();
								HoldTime[TempLed] = (_Uint8)rand() % 5 + 5;
							}
						}
		} break;
		
		case 2:
		{
#if _AL92C_
						
						/* Tree */
						if (RndCnt < 3)
						{
							for (TempLed = 0; TempLed < 3; TempLed++)
							{
								if (ModeLed[TempLed] == 1) continue;
								
								ModeTime[TempLed]++;
								if (ModeTime[TempLed] >= HoldTime[TempLed])
								{
									ModeTime[TempLed] = 0;
									for (TempCnt = 0; TempCnt < 7; TempCnt++)
									{
										LedData.Buffer[TempCnt + TempLed * 7].DutyR += FadeR;
										LedData.Buffer[TempCnt + TempLed * 7].DutyG += FadeG;
										LedData.Buffer[TempCnt + TempLed * 7].DutyB += FadeB;
									}
								}
								
								if (LedData.Buffer[TempLed * 7].DutyR == ColorData[TempColor][R] && LedData.Buffer[TempLed * 7].DutyG == ColorData[TempColor][G] && LedData.Buffer[TempLed * 7].DutyB == ColorData[TempColor][B])
								{
									RndCnt++;
									ModeLed[TempLed] = 1;
								}
							}
						}
						else
						{
							RndCnt++;
						}
#elif _AL92B_
						
						/* Snow */
						if (RndCnt < 3)
						{
							for (TempLed = 0; TempLed < 3; TempLed++)
							{
								if (ModeLed[TempLed] == 1) continue;
								
								ModeTime[TempLed]++;
								if (ModeTime[TempLed] >= HoldTime[TempLed])
								{
									ModeTime[TempLed] = 0;
									for (TempCnt = 0; TempCnt < 7; TempCnt++)
									{
										LedData.Buffer[TempLed * 7 + TempCnt].DutyR += FadeR;
										LedData.Buffer[TempLed * 7 + TempCnt].DutyG += FadeG;
										LedData.Buffer[TempLed * 7 + TempCnt].DutyB += FadeB;
									}
								}
								
								if (LedData.Buffer[TempLed * 7].DutyR == ColorData[TempColor][R] && LedData.Buffer[TempLed * 7].DutyG == ColorData[TempColor][G] && LedData.Buffer[TempLed * 7].DutyB == ColorData[TempColor][B])
								{
									RndCnt++;
									ModeLed[TempLed] = 1;
								}
							}
						}
						else
						{
							RndCnt++;
						}
#elif _AL95_
						/* Spot */
						if (RndCnt < 3)
						{
							for (TempLed = 0; TempLed < 3; TempLed++)
							{
								if (ModeLed[TempLed] == 1) continue;
								
								ModeTime[TempLed]++;
								if (ModeTime[TempLed] >= HoldTime[TempLed])
								{
									ModeTime[TempLed] = 0;
									LedData.Buffer[TempLed].DutyR += FadeR;
									LedData.Buffer[TempLed].DutyG += FadeG;
									LedData.Buffer[TempLed].DutyB += FadeB;
								}
								
								if (LedData.Buffer[TempLed].DutyR == ColorData[TempColor][R] && LedData.Buffer[TempLed].DutyG == ColorData[TempColor][G] && LedData.Buffer[TempLed].DutyB == ColorData[TempColor][B])
								{
									RndCnt++;
									ModeLed[TempLed] = 1;
								}
							}
						}
						else
						{
							RndCnt++;
						}
#elif _AL92A_
						/* Cane */
						if (RndCnt < 6)
						{
							for (TempLed = 0; TempLed < 6; TempLed++)
							{
								if (ModeLed[TempLed] == 1) continue;
								
								ModeTime[TempLed]++;
								if (ModeTime[TempLed] >= HoldTime[TempLed])
								{
									ModeTime[TempLed] = 0;
									for (TempCnt = 0; TempCnt < 4; TempCnt++)
									{
										LedData.Buffer[TempLed * 4 + TempCnt].DutyR += FadeR;
										LedData.Buffer[TempLed * 4 + TempCnt].DutyG += FadeG;
										LedData.Buffer[TempLed * 4 + TempCnt].DutyB += FadeB;
									}
								}
								
								if (LedData.Buffer[TempLed * 4].DutyR == ColorData[TempColor][R] && LedData.Buffer[TempLed * 4].DutyG == ColorData[TempColor][G] && LedData.Buffer[TempLed * 4].DutyB == ColorData[TempColor][B])
								{
									RndCnt++;
									ModeLed[TempLed] = 1;
								}
							}
						}
						
						else
						{
							RndCnt++;
						}
#elif _AL96_
						/* Ball */
						if (DutyR < ColorData[TempColor][R] || DutyG < ColorData[TempColor][G] || DutyB < ColorData[TempColor][B] || DutyW < ColorData[TempColor][W])
						{
							ModeTime[0]++;
							if (ModeTime[0] >= 8)
							{
								ModeTime[0] = 0;
								DutyR += FadeR;
								DutyG += FadeG;
								DutyB += FadeB;
								DutyW += FadeW;
							}
						}
						else
						{
							RndCnt++;
						}
#endif
						
						
						
						if (RndCnt >= RAND_END_TOTAL+5)
						{
							RndCnt = 0;
							TempStep++;
							FadeR = ColorData[TempColor][R] / 50;
							FadeG = ColorData[TempColor][G] / 50;
							FadeB = ColorData[TempColor][B] / 50;
#if _AL96_
							FadeW = ColorData[TempColor][W] / 50;
							TempW = ColorData[TempColor][W];
#endif
							RndCnt = 0;
							TempR = ColorData[TempColor][R];
							TempG = ColorData[TempColor][G];
							TempB = ColorData[TempColor][B];
						}
		} break;
		
		
		
		case 3:
		{	
						TempR -= FadeR;
						TempG -= FadeG;
						TempB -= FadeB;
#if _AL96_
						TempW -= FadeW;
						All_Color(TempR, TempG, TempB, TempW);
#else
						All_Color(TempR, TempG, TempB);
#endif
						StepCnt++;
						if (StepCnt >= 50)  
						{
							StepCnt = 0;
							
							TempColor++;
							if (TempColor >= ColorNum) TempColor = 0;
							
							FadeR = ColorData[TempColor][R] / 50;
							FadeG = ColorData[TempColor][G] / 50;
							FadeB = ColorData[TempColor][B] / 50;
							TempR = 0;
							TempG = 0;
							TempB = 0;
#if _AL96_
							TempW = 0;
							FadeW = ColorData[TempColor][W] / 50;
#endif
							TempStep = 0;
							
							KeepTime++;
							if (KeepTime >= 2)		TempStep = 4;
						}
		} break;
		
		default:
		{
						TempStep = 4;
		} break;
	}
}

/*
 * FunctionName	Show_2_4
 * TimeLint
 */
void Show_2_4(void)
{
	if (ShowInit == TRUE)
	{
		ShowInit= FALSE;
#if _AL96_
		All_Color(0,0,0,0);
		TempW = 0;
#else
		All_Color(0,0,0);
#endif
		
		TempColor		= 0;
		SpeedTime		= 0;
		TempStep		= 0;
		KeepTime		= 0;
		
		TempR = 0;
		TempG = 0;
		TempB = 0;
		
		ModeStep[0] = 0;
	}
	
	SpeedTime++;
	if (SpeedTime > 3)
	{
		SpeedTime = 0;
		
		KeepTime++;
		if (KeepTime > 40)
		{
			KeepTime = 0;
			TempStep++;
			if (TempStep > 5)	
			{
				TempStep = 0;
			}
		}
		
			
		switch (TempStep)
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
#if _AL92C_
		
		/* Tree */
		switch (ModeStep[0])
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
						ModeStep[0]++;
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
						ModeStep[0]++;
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
						ModeStep[0]++;
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
						ModeStep[0] = 0;
			} break;
		}
#elif _AL92B_
		
		/* Snow */
		switch (ModeStep[0])
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
						ModeStep[0]++;
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
						ModeStep[0]++;
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
						ModeStep[0]++;
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
						ModeStep[0] = 0;
			} break;
		}
#elif _AL95_
		/* Spot */
		switch (ModeStep[0])
		{
			case 0:
			{
						LedData.Buffer[0].DutyR = TempR;
						LedData.Buffer[0].DutyG = TempG;
						LedData.Buffer[0].DutyB = TempB;
						ModeStep[0]++;
			} break;
			
			case 1:
			{
						LedData.Buffer[2].DutyR = TempR;
						LedData.Buffer[2].DutyG = TempG;
						LedData.Buffer[2].DutyB = TempB;
						ModeStep[0]++;
			} break;
			
			case 2:
			{
						LedData.Buffer[1].DutyR = TempR;
						LedData.Buffer[1].DutyG = TempG;
						LedData.Buffer[1].DutyB = TempB;
						ModeStep[0]++;
			} break;
			
			default:
			{
						for (TempCnt = 0; TempCnt < 3; TempCnt++)
						{
							LedData.Buffer[TempCnt].DutyR = TempR;
							LedData.Buffer[TempCnt].DutyG = TempG;
							LedData.Buffer[TempCnt].DutyB = TempB;
						}
						ModeStep[0] = 0;
			} break;
		}
#elif _AL92A_
		/* Cane */
		switch (ModeStep[0])
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
						ModeStep[0]++;
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
						ModeStep[0]++;
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
						ModeStep[0]++;
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
						ModeStep[0]++;
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
						ModeStep[0]++;
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
						ModeStep[0]++;
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
						ModeStep[0] = 0;
			} break;
		}
#elif _AL96_
		/* Ball */
		switch (ModeStep[0])
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
						ModeStep[0] = 0;
			} break;


			default:
			{
						ModeStep[0]++;
			} break;
		}
#endif
	}
}










