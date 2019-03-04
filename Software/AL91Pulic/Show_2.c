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

		All_Color(0,0,0);

		SynFlag = FALSE;
		return;
	}


	/* Mode Control */

	if (TimeLine == 0)									{ShowMode = 0;			ShowInit = TRUE;	}
	else if (TimeLine == 1640)					{ShowMode = 1;			ShowInit = TRUE;	}
	else if (TimeLine == 3410)					{ShowMode = 2;			ShowInit = TRUE;	}
	else if (TimeLine == 3950)					{ShowMode = 3;			ShowInit = TRUE;	}
	else if (TimeLine == 5010)					{ShowMode = 4;			ShowInit = TRUE;	}

  TimeLine++;

	if (TimeLine == 7000)
	{
		TimeLine = 0;
		DisplayData.InitFlag = TRUE;
		SynFlag = TRUE;
	}
	
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

		All_Color(0,0,0);

		TempColor		= 3;
		SpeedTime		= 0;
		TempStep		= 0;

		for (TempCnt = 0; TempCnt < 50; TempCnt++)
		{
			ModeLed[TempCnt] = 0;
		}

		RndCnt = 0;
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
						/* Icicle */
						if (RndCnt < RAND_TOTAL)
						{
							do
							{
								RAND();
								TempLed = (_Uint8)rand() % RAND_TOTAL;
							} while (ModeLed[TempLed] == 1);
							ModeLed[TempLed] = 1;
							LedData.Buffer[TempLed].DutyR	= ColorData[TempColor][R];
							LedData.Buffer[TempLed].DutyG	= ColorData[TempColor][G];
							LedData.Buffer[TempLed].DutyB	= ColorData[TempColor][B];
							RndCnt++;
						}
						else
						{
							RndCnt++;
						}

						if (RndCnt >= RAND_END_TOTAL)
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
							/* Roof10 */
							for (TempLed = 0; TempLed < RAND_TOTAL; TempLed++)
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



							SteadyTime++;
							if (SteadyTime > 50)
							{
								SteadyTime 		= 0;
								TempStep			= 0;

								TempR	= ColorData[TempColor][R];
								TempG	= ColorData[TempColor][G];
								TempB = ColorData[TempColor][B];
								All_Color(TempR, TempG, TempB);



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
							} while (ModeLed[TempLed] == 1);
							ModeLed[TempLed] = 1;

							TempColor = TempLed % ColorNum;
							LedData.Buffer[TempLed].DutyR	= ColorData[TempColor][R];
							LedData.Buffer[TempLed].DutyG	= ColorData[TempColor][G];
							LedData.Buffer[TempLed].DutyB	= ColorData[TempColor][B];
							RndCnt++;
						}
						else
						{
							RndCnt++;
						}

						if (RndCnt >= RAND_END_TOTAL)
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

		for (TempLed = 0; TempLed < LED_TOTAL; TempLed++)
		{
			TempColor = TempLed % ColorNum;
			LedData.Buffer[TempLed].DutyR = ColorData[TempColor][R];
			LedData.Buffer[TempLed].DutyG = ColorData[TempColor][G];
			LedData.Buffer[TempLed].DutyB = ColorData[TempColor][B];
		}

		TempColor		= 0;
		SpeedTime		= 0;
		TempStep		= 0;

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

							TempR = LedData.Buffer[0].DutyR;
							TempG = LedData.Buffer[0].DutyG;
							TempB = LedData.Buffer[0].DutyB;
							for (TempLed = 0; TempLed < LED_TOTAL; TempLed++)
							{
								LedData.Buffer[TempLed].DutyR = LedData.Buffer[TempLed + 1].DutyR;
								LedData.Buffer[TempLed].DutyG = LedData.Buffer[TempLed + 1].DutyG;
								LedData.Buffer[TempLed].DutyB = LedData.Buffer[TempLed + 1].DutyB;
							}
							LedData.Buffer[LED_TOTAL - 1].DutyR = TempR;
							LedData.Buffer[LED_TOTAL - 1].DutyG = TempG;
							LedData.Buffer[LED_TOTAL - 1].DutyB = TempB;


							SteadyTime++;
							if (SteadyTime >= 20)
							{
								SteadyTime = 0;
								TempStep++;
								TempColor = 0;
								RndCnt = 0;
							}
						}
		} break;


		case 1:
		{
						SpeedTime++;
						if (SpeedTime >= 10)
						{
							SpeedTime = 0;

							/* Roof10 */
							TempR = ColorData[TempColor][R];
							TempG = ColorData[TempColor][G];
							TempB = ColorData[TempColor][B];
							for (TempLed = LED_TOTAL - 1; TempLed > 0; TempLed--)
							{
								LedData.Buffer[TempLed].DutyR = LedData.Buffer[TempLed - 1].DutyR;
								LedData.Buffer[TempLed].DutyG = LedData.Buffer[TempLed - 1].DutyG;
								LedData.Buffer[TempLed].DutyB = LedData.Buffer[TempLed - 1].DutyB;
							}
							LedData.Buffer[0].DutyR = TempR;
							LedData.Buffer[0].DutyG = TempG;
							LedData.Buffer[0].DutyB = TempB;

							RndCnt++;
							if(RndCnt > 5)
							{
								RndCnt = 0;
								TempColor++;
								if (TempColor >= ColorNum)		TempColor = 0;
							}

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

							/* Roof10 */
							TempR = ColorData[TempColor][R];
							TempG = ColorData[TempColor][G];
							TempB = ColorData[TempColor][B];
							for (TempLed = LED_TOTAL - 1; TempLed > 0; TempLed--)
							{
								LedData.Buffer[TempLed].DutyR = LedData.Buffer[TempLed - 1].DutyR;
								LedData.Buffer[TempLed].DutyG = LedData.Buffer[TempLed - 1].DutyG;
								LedData.Buffer[TempLed].DutyB = LedData.Buffer[TempLed - 1].DutyB;
							}
							LedData.Buffer[0].DutyR = TempR;
							LedData.Buffer[0].DutyG = TempG;
							LedData.Buffer[0].DutyB = TempB;

							RndCnt++;
							if(RndCnt > 12)
							{
								RndCnt = 0;
								TempColor++;
								if (TempColor >= ColorNum)		TempColor = 0;
							}
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
						for (TempLed = 0; TempLed < LED_TOTAL; TempLed++)
						{
							if (TempLed % 3 == 0)
							{
								LedData.Buffer[TempLed].DutyR = ColorData[TempColor][R];
								LedData.Buffer[TempLed].DutyG = ColorData[TempColor][G];
								LedData.Buffer[TempLed].DutyB = ColorData[TempColor][B];
							}
						}

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
						for (TempLed = 0; TempLed < LED_TOTAL; TempLed++)
						{
							if (TempLed % 3 == 1)
							{
								LedData.Buffer[TempLed].DutyR = ColorData[TempColor][R];
								LedData.Buffer[TempLed].DutyG = ColorData[TempColor][G];
								LedData.Buffer[TempLed].DutyB = ColorData[TempColor][B];
							}
						}

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
						/* Roof10 */
						for (TempLed = 0; TempLed < LED_TOTAL; TempLed++)
						{
							if (TempLed % 3 == 2)
							{
								LedData.Buffer[TempLed].DutyR = ColorData[TempColor][R];
								LedData.Buffer[TempLed].DutyG = ColorData[TempColor][G];
								LedData.Buffer[TempLed].DutyB = ColorData[TempColor][B];
							}
						}

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

							if (LedData.Buffer[0].DutyR > 0 || LedData.Buffer[0].DutyG > 0 || LedData.Buffer[0].DutyB > 0)
							{
								FadeR = ColorData[0 + ModeStep[0]][R] / 25;
								FadeG = ColorData[0 + ModeStep[0]][G] / 25;
								FadeB = ColorData[0 + ModeStep[0]][B] / 25;

								for (TempLed = 0; TempLed < LED_TOTAL; TempLed++)
								{
									if (TempLed % 3 == 0)
									{
										LedData.Buffer[TempLed].DutyR -= FadeR;
										LedData.Buffer[TempLed].DutyG -= FadeG;
										LedData.Buffer[TempLed].DutyB -= FadeB;
									}
								}
							}

							if (RndCnt >= 15)
							{
								if (LedData.Buffer[1].DutyR > 0 || LedData.Buffer[1].DutyG > 0 || LedData.Buffer[1].DutyB > 0)
								{
									FadeR = ColorData[1 + ModeStep[0]][R] / 25;
									FadeG = ColorData[1 + ModeStep[0]][G] / 25;
									FadeB = ColorData[1 + ModeStep[0]][B] / 25;
									for (TempLed = 0; TempLed < LED_TOTAL; TempLed++)
									{
										if (TempLed % 3 == 1)
										{
											LedData.Buffer[TempLed].DutyR -= FadeR;
											LedData.Buffer[TempLed].DutyG -= FadeG;
											LedData.Buffer[TempLed].DutyB -= FadeB;
										}
									}
								}
							}

							if (RndCnt >= 30)
							{
								if (LedData.Buffer[2].DutyR > 0 || LedData.Buffer[2].DutyG > 0 || LedData.Buffer[2].DutyB > 0)
								{
									FadeR = ColorData[2 + ModeStep[0]][R] / 25;
									FadeG = ColorData[2 + ModeStep[0]][G] / 25;
									FadeB = ColorData[2 + ModeStep[0]][B] / 25;
									for (TempLed = 0; TempLed < LED_TOTAL; TempLed++)
									{
										if (TempLed % 3 == 2)
										{
											LedData.Buffer[TempLed].DutyR -= FadeR;
											LedData.Buffer[TempLed].DutyG -= FadeG;
											LedData.Buffer[TempLed].DutyB -= FadeB;
										}
									}
								}
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

		All_Color(0,0,0);

		TempColor		= 0;
		SpeedTime		= 0;
		TempStep		= 0;
		RndCnt		= 0;
		KeepTime		= 0;

		TempR = 0;
		TempG = 0;
		TempB = 0;

		FadeR = ColorData[TempColor][R] / 50;
		FadeG = ColorData[TempColor][G] / 50;
		FadeB = ColorData[TempColor][B] / 50;

		KeepTime = 0;
		return;
	}


	switch (TempStep)
	{
		case 0:
		{
						TempR += FadeR;
						TempG += FadeG;
						TempB += FadeB;
						All_Color(TempR, TempG, TempB);
						RndCnt++;
						if (RndCnt >= 50)
						{
							TempStep++;
							FadeR = ColorData[TempColor][R] / 50;
							FadeG = ColorData[TempColor][G] / 50;
							FadeB = ColorData[TempColor][B] / 50;
							RndCnt = 0;

							for (TempLed = 0; TempLed < 50; TempLed++)
							{
								ModeLed[TempLed] = 0;
								RAND();
								HoldTime[TempLed] = (_Uint8)rand() % 10;
							}
						}
		} break;


		case 1:
		{
						if (RndCnt < RAND_TOTAL)
						{
							for (TempLed = 0; TempLed < RAND_TOTAL; TempLed++)
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


						if (RndCnt >= RAND_END_TOTAL)
						{
							TempStep++;
							TempColor++;
							if (TempColor >= ColorNum)		TempColor = 0;
							FadeR = ColorData[TempColor][R] / 50;
							FadeG = ColorData[TempColor][G] / 50;
							FadeB = ColorData[TempColor][B] / 50;
							RndCnt = 0;

							for (TempLed = 0; TempLed < 50; TempLed++)
							{
								ModeLed[TempLed] = 0;
								RAND();
								HoldTime[TempLed] = (_Uint8)rand() % 10;
							}
						}
		} break;

		case 2:
		{
						if (RndCnt < RAND_TOTAL)
						{
							for (TempLed = 0; TempLed < RAND_TOTAL; TempLed++)
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

						if (RndCnt >= RAND_END_TOTAL)
						{
							TempStep++;
							FadeR = ColorData[TempColor][R] / 50;
							FadeG = ColorData[TempColor][G] / 50;
							FadeB = ColorData[TempColor][B] / 50;
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
						All_Color(TempR, TempG, TempB);
						RndCnt++;
						if (RndCnt >= 50)
						{
							RndCnt = 0;
							TempR = 0;
							TempG = 0;
							TempB = 0;
							TempStep = 0;
							TempColor++;
							if (TempColor >= ColorNum) TempColor = 0;

							FadeR = ColorData[TempColor][R] / 50;
							FadeG = ColorData[TempColor][G] / 50;
							FadeB = ColorData[TempColor][B] / 50;

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

		All_Color(0,0,0);

		TempColor		= 0;
		SpeedTime		= 0;
		TempStep		= 0;
		KeepTime		= 0;

		TempR = 0;
		TempG = 0;
		TempB = 0;
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
