/********************************************************************
	*
	* FILE NAME
	*									Show_3.c
	* DATE
	*									02 NOV. 2017
	* AUTHOR
	*									DS.Chin
	* DESCRIPTION
	*									Display Show 3
	*
*********************************************************************/
#include "Display_Ctrl.h"


/**
	* FunctionName	Show_3
	*/
void Show_3(void)
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

	if (TimeLine == 0)									{ShowMode = 0;			ShowInit = TRUE;	}
	else if (TimeLine == 2660)					{ShowMode = 1;			ShowInit = TRUE;	}
	else if (TimeLine == 5350)					{ShowMode = 2;			ShowInit = TRUE;	}
	else if (TimeLine == 5700)					{ShowMode = 3;			ShowInit = TRUE;	}
	else if (TimeLine == 6606)					{ShowMode = 4;			ShowInit = TRUE;	}

  TimeLine++;

	if (TimeLine == 8000)
	{
		TimeLine = 0;
		DisplayData.InitFlag = TRUE;
		SynFlag = TRUE;
	}

	switch (ShowMode)
	{
		case 0:			Show_3_0();		break;
		case 1:			Show_3_1();		break;
		case 2:			Show_3_2();		break;
		case 3:			Show_3_3();		break;
		case 4:			Show_3_4();		break;
	}
}


/*
 * FunctionName		Show_3_0
 * Duration				TimeLine += 1570
 */
void Show_3_0(void)
{
	/* Initalize */
	if (ShowInit == TRUE)
	{
		ShowInit = FALSE;

		All_Color(0,0,0);

		TempStep 	= 0;
		TempColor	= 0;

		RndCnt = 0;
		ModeStep[0] = 0;

		KeepTime = 0;
		SteadyTime = 0;
		return;
	}

	switch (TempStep)
	{
		case 0:
		{
					SpeedTime++;
					if (SpeedTime >= 6)
					{
						SpeedTime = 0;

						/* Roof10 */
						for (TempLed = RAND_TOTAL - 1; TempLed > 0; TempLed--)
						{
								LedData.Buffer[TempLed].DutyR = LedData.Buffer[TempLed  - 1].DutyR;
								LedData.Buffer[TempLed].DutyG = LedData.Buffer[TempLed  - 1].DutyG;
								LedData.Buffer[TempLed].DutyB = LedData.Buffer[TempLed  - 1].DutyB;
						}
						LedData.Buffer[0].DutyR = ColorData[TempColor][R];
						LedData.Buffer[0].DutyG = ColorData[TempColor][G];
						LedData.Buffer[0].DutyB = ColorData[TempColor][B];

						SteadyTime++;
						if (SteadyTime >= RAND_END_TOTAL)
						{
							SteadyTime = 0;
							TempStep++;
							TempColor++;
							if (TempColor >= ColorNum)		TempColor = 0;
						}
					}
		} break;

		case 1:
		{
					SpeedTime++;
					if (SpeedTime >= 6)
					{
						SpeedTime = 0;

						/* Roof10 */
						for (TempLed = 0; TempLed < RAND_TOTAL - 1; TempLed++)
						{
								LedData.Buffer[TempLed].DutyR = LedData.Buffer[TempLed + 1].DutyR;
								LedData.Buffer[TempLed].DutyG = LedData.Buffer[TempLed + 1].DutyG;
								LedData.Buffer[TempLed].DutyB = LedData.Buffer[TempLed + 1].DutyB;
						}

						LedData.Buffer[RAND_TOTAL - 1].DutyR = ColorData[TempColor][R];
						LedData.Buffer[RAND_TOTAL - 1].DutyG = ColorData[TempColor][G];
						LedData.Buffer[RAND_TOTAL - 1].DutyB = ColorData[TempColor][B];

						SteadyTime++;
						if (SteadyTime >= RAND_END_TOTAL)
						{
							SteadyTime = 0;
							TempColor++;
							if (TempColor >= ColorNum)		TempColor = 0;

							TempStep = 0;
							ModeStep[0]++;
							if (ModeStep[0] > 2)
							{
								ModeStep[0] = 0;
								TempStep = 2;
								RndCnt = 0;
							}
						}
					}
		} break;

		case 2:
		{
					SpeedTime++;
					if (SpeedTime >= 6)
					{
						SpeedTime = 0;

						/* Roof10 */
						for (TempLed = RAND_TOTAL - 1; TempLed > 0; TempLed--)
						{
							LedData.Buffer[TempLed].DutyR = LedData.Buffer[TempLed - 1].DutyR;
							LedData.Buffer[TempLed].DutyG = LedData.Buffer[TempLed - 1].DutyG;
							LedData.Buffer[TempLed].DutyB = LedData.Buffer[TempLed - 1].DutyB;
						}
						LedData.Buffer[0].DutyR = ColorData[TempColor][R];
						LedData.Buffer[0].DutyG = ColorData[TempColor][G];
						LedData.Buffer[0].DutyB = ColorData[TempColor][B];

						RndCnt++;
						if (RndCnt >= 6)
						{
							RndCnt = 0;
							TempColor++;
							if (TempColor >= ColorNum)		TempColor = 0;
						}

						SteadyTime++;
						if (SteadyTime >= RAND_END_TOTAL)
						{
							SteadyTime = 0;
							TempStep++;
						}
					}
		} break;

		case 3:
		{
					SpeedTime++;
					if (SpeedTime >= 6)
					{
						SpeedTime = 0;

						/* Roof10 */
						for (TempLed = 0; TempLed < RAND_TOTAL - 1; TempLed++)
						{
								LedData.Buffer[TempLed].DutyR = LedData.Buffer[TempLed + 1].DutyR;
								LedData.Buffer[TempLed].DutyG = LedData.Buffer[TempLed + 1].DutyG;
								LedData.Buffer[TempLed].DutyB = LedData.Buffer[TempLed + 1].DutyB;
						}
							LedData.Buffer[RAND_TOTAL - 1].DutyR = ColorData[TempColor][R];
							LedData.Buffer[RAND_TOTAL - 1].DutyG = ColorData[TempColor][G];
							LedData.Buffer[RAND_TOTAL - 1].DutyB = ColorData[TempColor][B];



						RndCnt++;
						if (RndCnt >= 6)
						{
							RndCnt = 0;
							TempColor++;
							if (TempColor >= ColorNum)		TempColor = 0;
						}

						SteadyTime++;
						if (SteadyTime >= RAND_END_TOTAL)
						{
							SteadyTime = 0;
							TempStep = 2;
							KeepTime++;
							if (KeepTime > 2)
							{
								TempStep = 4;

								for (TempCnt = 0; TempCnt < 50; TempCnt++)
								{
									ModeLed[TempCnt] = 0;
								}

								RndCnt = 0;
							}
						}
					}
		} break;

		case 4:
		{
					SpeedTime++;
					if (SpeedTime >= 6)
					{
						SpeedTime = 0;

						/* Icicle */
						if (RndCnt < RAND_TOTAL)
						{
							do
							{
								RAND();
								TempLed = (_Uint8)rand() % RAND_TOTAL;
							} while (ModeLed[TempLed] == 1);
							ModeLed[TempLed] = 1;

								LedData.Buffer[TempLed].DutyR	= 0;
								LedData.Buffer[TempLed].DutyG	= 0;
								LedData.Buffer[TempLed].DutyB	= 0;

							RndCnt++;
						}
						else
						{
							RndCnt++;
						}

						if (RndCnt >= RAND_END_TOTAL)
						{
							TempStep++;
						}
					}
		} break;

		default:
		{
					TempStep = 0xFF;
		} break;
	}
}


/*
 * FunctionName		Show_3_1
 * Duration				TimeLine += 1830
 */
void Show_3_1(void)
{
	/* Initalize */
	if (ShowInit == TRUE)
	{
		ShowInit = FALSE;

		All_Color(0,0,0);

		TempStep 	= 0;
		TempColor	= 0;

		SpeedTime = 0;
		KeepTime	= 0;

		FadeR = ColorData[TempColor][R] / 50;
		FadeG = ColorData[TempColor][G] / 50;
		FadeB = ColorData[TempColor][B] / 50;
		return;
	}

	switch (TempStep)
	{
		case 0:
		{
					TempR = FadeR * 10;
					TempG = FadeG * 10;
					TempB = FadeB * 10;
					All_Color(TempR, TempG, TempB);

					SpeedTime++;
					if (SpeedTime >= 10)
					{
						SpeedTime = 0;
						TempStep++;
						RndCnt = 0;
					}
		} break;

		case 1:
		{
					TempR += FadeR;
					TempG += FadeG;
					TempB += FadeB;
					All_Color(TempR, TempG, TempB);

					RndCnt++;
					if (RndCnt >= 20)
					{
						RndCnt = 0;
						TempStep++;

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
							TempStep = 0;
							SpeedTime = 0;
							TempColor++;
							if (TempColor >= ColorNum)		TempColor = 0;
							FadeR = ColorData[TempColor][R] / 50;
							FadeG = ColorData[TempColor][G] / 50;
							FadeB = ColorData[TempColor][B] / 50;
							RndCnt 			= 0;
							SpeedTime 	= 0;

							KeepTime++;
							if (KeepTime > 2)
							{
								KeepTime = 0;
								TempStep = 3;
								RndCnt = 0;

								for (TempCnt = 0; TempCnt < 50; TempCnt++)
								{
									ModeLed[TempCnt] = 0;
								}
							}
						}
		} break;

		case 3:
		{
					if (RndCnt < RAND_TOTAL)
					{
						do
						{
							RAND();
							ModeStep[0] = (_Uint8)rand() % RAND_TOTAL;
						} while(ModeLed[ModeStep[0]] == 1);
						ModeLed[ModeStep[0]] = 1;
						RndCnt++;
					}
					else
					{
						RndCnt++;
					}

					TempStep++;
					KeepTime = 0;
					TempR = 0;
					TempG = 0;
					TempB = 0;
					FadeR = ColorData[TempColor][R] / 50;
					FadeG = ColorData[TempColor][G] / 50;
					FadeB = ColorData[TempColor][B] / 50;

					if (RndCnt >= RAND_END_TOTAL)
					{
						TempStep = 5;
						RndCnt = 0;

						for (TempLed = 0; TempLed < 50; TempLed++)
						{
							ModeLed[TempLed] = 0;
							RAND();
							HoldTime[TempLed] = (_Uint8)rand() % 20 + 10;
						}
					}
		} break;

		case 4:
		{
					TempR += FadeR;
					TempG += FadeG;
					TempB += FadeB;

					if (RndCnt <= RAND_TOTAL)
					{
						LedData.Buffer[ModeStep[0]].DutyR += FadeR;
						LedData.Buffer[ModeStep[0]].DutyG += FadeG;
						LedData.Buffer[ModeStep[0]].DutyB += FadeB;
					}

					KeepTime++;
					if (KeepTime >= 50)
					{
						TempStep = 3;
						TempColor++;
						if (TempColor >= ColorNum)  TempColor = 0;
					}
		} break;

		case 5:
		{
					All_Color(0,0,0);
					TempStep++;
		} break;

		case 6:
		case 7:
		case 8:
		{
					for (TempLed = 0; TempLed < RAND_TOTAL; TempLed++)
					{
						if (TempLed % 2 == 0)
						{
							ModeTime[TempLed]++;
							if (ModeTime[TempLed] >= 2)
							{
								ModeTime[TempLed] = 0;
								TempColor = TempLed % ColorNum;
								FadeR = ColorData[TempColor][R] / 25;
								FadeG = ColorData[TempColor][G] / 25;
								FadeB = ColorData[TempColor][B] / 25;

								switch (ModeStep[TempLed])
								{
									case 0:
									{
												if (LedData.Buffer[TempLed].DutyR > 0
														|| LedData.Buffer[TempLed].DutyG > 0
															|| LedData.Buffer[TempLed].DutyB > 0)
												{
														LedData.Buffer[TempLed].DutyR -= FadeR;
														LedData.Buffer[TempLed].DutyG -= FadeG;
														LedData.Buffer[TempLed].DutyB -= FadeB;
												}
												else
												{
													ModeStep[TempLed]++;
												}
									} break;

									default:
									{
												if (LedData.Buffer[TempLed].DutyR < ColorData[TempColor][R]
														|| LedData.Buffer[TempLed].DutyG < ColorData[TempColor][G]
															|| LedData.Buffer[TempLed].DutyB < ColorData[TempColor][B])
												{
														LedData.Buffer[TempLed].DutyR += FadeR;
														LedData.Buffer[TempLed].DutyG += FadeG;
														LedData.Buffer[TempLed].DutyB += FadeB;
												}
												else
												{
													ModeStep[TempLed] = 0;
												}
									} break;
								}
							}
						}

						else
						{
							ModeTime[TempLed]++;
							if (ModeTime[TempLed] > HoldTime[TempLed])
							{
								ModeTime[TempLed] = 0;
								TempColor = TempLed % ColorNum;

								switch (ModeStep[TempLed])
								{
									case 0:
									{
												LedData.Buffer[TempLed].DutyR = ColorData[TempColor][R] / 2;
												LedData.Buffer[TempLed].DutyG = ColorData[TempColor][G] / 2;
												LedData.Buffer[TempLed].DutyB = ColorData[TempColor][B] / 2;
												ModeStep[TempLed]++;
									} break;

									default:
									{
												LedData.Buffer[TempLed].DutyR = ColorData[TempColor][R];
												LedData.Buffer[TempLed].DutyG = ColorData[TempColor][G];
												LedData.Buffer[TempLed].DutyB = ColorData[TempColor][B];
												ModeStep[TempLed] = 0;
									} break;
								}
							}
						}
					}


					SpeedTime++;
					if (SpeedTime > 200)
					{
						SpeedTime = 0;
						TempStep++;
					}
		} break;

		default:
		{
					TempStep = 0xFF;
		} break;
	}
}



/*
 * FunctionName	Show_3_2
 * TimeLine		+= 1410
 */
void Show_3_2(void)
{
	/* Initalize */
	if (ShowInit == TRUE)
	{
		ShowInit = FALSE;

		TempStep 	= 0;
		SpeedTime = 0;
		TempR			= 255;
		TempG			= 0;
		TempB			= 0;
		KeepTime	= 0;

		for (TempCnt = 0; TempCnt < 50; TempCnt++)
		{
			ModeLed[TempCnt] = 0;
		}

		RndCnt = 0;
		return;
	}

	switch (TempStep)
	{
		case 0:
		{
				SpeedTime++;
				if (SpeedTime >= 6)
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

						LedData.Buffer[TempLed].DutyR	= TempR;
						LedData.Buffer[TempLed].DutyG	= TempG;
						LedData.Buffer[TempLed].DutyB	= TempB;
						RndCnt++;
					}
					else
					{
						RndCnt++;
					}


					if (RndCnt >= RAND_END_TOTAL)
					{
						TempStep++;
					}
				}
		} break;

		case 1:
		{
					if (TempG < 255)			TempG += 15;
					else									TempStep++;

					All_Color(TempR, TempG, TempB);
		} break;

		case 2:
		{
					if (TempR > 0)				TempR -= 15;
					else									TempStep++;

					All_Color(TempR, TempG, TempB);
		} break;

		case 3:
		{
					if (TempB < 255)			TempB += 15;
					else									TempStep++;

					All_Color(TempR, TempG, TempB);
		} break;

		case 4:
		{
					if (TempG > 0)				TempG -= 15;
					else									TempStep++;

					All_Color(TempR, TempG, TempB);
		} break;

		case 5:
		{
					if (TempR < 255)			TempR += 15;
					else									TempStep++;

					All_Color(TempR, TempG, TempB);
		} break;

		default:
		{
					TempStep = 0xFF;
		} break;
	}
}

/*
 * FunctionName		Show_3_3
 * Duration				TimeLine += 900
 */
void Show_3_3(void)
{
	/* Initalize */
	if (ShowInit == TRUE)
	{
		ShowInit = FALSE;

		TempStep 	= 0;
		TempColor	= 0;
		SpeedTime = 0;
		KeepTime	= 0;
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

					KeepTime++;
					if (KeepTime >= 50)
					{
						KeepTime = 0;
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

					KeepTime++;
					if (KeepTime >= 50)
					{
						KeepTime = 0;
						TempColor++;
						if (TempColor >= ColorNum)	TempColor = 0;
						TempStep++;
					}
		} break;

		case 2:
		{
					for (TempLed = 0; TempLed < LED_TOTAL; TempLed++)
					{
						if (TempLed % 3 == 2)
						{
							LedData.Buffer[TempLed].DutyR = ColorData[TempColor][R];
							LedData.Buffer[TempLed].DutyG = ColorData[TempColor][G];
							LedData.Buffer[TempLed].DutyB = ColorData[TempColor][B];
						}
					}


					KeepTime++;
					if (KeepTime >= 50)
					{
						KeepTime = 0;
						TempColor++;
						if (TempColor >= ColorNum)	TempColor = 0;
						TempStep++;
					}
		} break;

		case 3:
		{
					TempR = ColorData[TempColor][R];
					TempG = ColorData[TempColor][G];
					TempB = ColorData[TempColor][B];
					All_Color(TempR, TempG, TempB);

					KeepTime++;
					if (KeepTime >= 50)
					{
						KeepTime = 0;
						FadeR = ColorData[TempColor][R] / 50;
						FadeG = ColorData[TempColor][G] / 50;
						FadeB = ColorData[TempColor][B] / 50;
						TempStep++;
						RndCnt = 0;
					}
		} break;

		case 4:
		{
					TempR -= FadeR;
					TempG -= FadeG;
					TempB -= FadeB;
					All_Color(TempR, TempG, TempB);
					RndCnt++;
					if (RndCnt >= 50)
					{
						RndCnt = 0;
						TempStep = 0;
						TempColor++;
						if (TempColor >= ColorNum)  TempColor = 0;
						SpeedTime++;
						if (SpeedTime > 3)
						{
							TempStep = 5;
						}
					}
		} break;

		default:
		{
					TempStep = 0xFF;
		} break;
	}
}


/**
 * FunctionName  Show_3_4
 * TimeLine
 */
void Show_3_4(void)
{
	/* Initalize */
	if (ShowInit == TRUE)
	{
		ShowInit = FALSE;



		TempStep 	= 0;
		TempColor	= 0;
		SpeedTime = 0;
		KeepTime	= 0;

		TempR = 255;
		TempG = 0;
		TempB = 0;

		for (TempCnt = 0; TempCnt < 50; TempCnt++)
		{
			ModeLed[TempCnt] = 0;
		}

		RndCnt = 0;
		return;
	}

	switch (TempStep)
	{
		case 0:
		{
					SpeedTime++;
					if (SpeedTime >= 6)
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

							LedData.Buffer[TempLed].DutyR	= TempR;
							LedData.Buffer[TempLed].DutyG	= TempG;
							LedData.Buffer[TempLed].DutyB	= TempB;

							RndCnt++;
						}
						else
						{
							RndCnt++;
						}


						if (RndCnt >= RAND_END_TOTAL)
						{
							TempStep++;
							TempColor = 1;
							ModeColor[0] = 0;
							ModeColor[1] = 1;
							for (TempCnt = 0;TempCnt < 8; TempCnt++)
							{
								ModeLed[TempCnt] = 0;
							}
							KeepTime = 0;
						}
					}
		} break;

		case 1:
		{
					SpeedTime++;
					if (SpeedTime >= 6)
					{
						SpeedTime = 0;


						TempR = ColorData[ModeColor[0]][R];
						TempG = ColorData[ModeColor[0]][G];
						TempB = ColorData[ModeColor[0]][B];
						All_Color(TempR, TempG, TempB);
						for (TempLed = 0; TempLed < 8; TempLed++)
						{
							if (ModeLed[TempLed] < RAND_TOTAL)
							{
								LedData.Buffer[ModeLed[TempLed]].DutyR = ColorData[ModeColor[1]][R];
								LedData.Buffer[ModeLed[TempLed]].DutyG = ColorData[ModeColor[1]][G];
								LedData.Buffer[ModeLed[TempLed]].DutyB = ColorData[ModeColor[1]][B];
							}
						}


						ModeLed[0]++;
						if (ModeLed[0] > RAND_END_TOTAL)		ModeLed[0] = RAND_END_TOTAL + 1;
						for (TempLed = 7; TempLed > 0; TempLed--)
						{
							ModeLed[TempLed] = ModeLed[TempLed - 1];
						}


						if (ModeLed[7] > RAND_END_TOTAL)
						{
							ModeColor[1]++;
							if (ModeColor[1] >= ColorNum)  ModeColor[1] = 1;
							for (TempLed = 0; TempLed < 8; TempLed++)
							{
								ModeLed[TempLed] = 0;
							}
							KeepTime++;
							if (KeepTime >= 3)
							{
								KeepTime = 0;
								TempStep++;
								ModeColor[0] = ModeColor[1];
								ModeColor[1]++;
								if (ModeColor[1] >= ColorNum)  ModeColor[1] = 1;
							}
						}
					}
		} break;


		case 2:
		{
					SpeedTime++;
					if (SpeedTime >= 6)
					{
						SpeedTime = 0;

						for (TempLed = 0; TempLed < 8; TempLed++)
						{
							if (ModeLed[TempLed] < RAND_TOTAL)
							{
								LedData.Buffer[ModeLed[TempLed]].DutyR = ColorData[ModeColor[1]][R];
								LedData.Buffer[ModeLed[TempLed]].DutyG = ColorData[ModeColor[1]][G];
								LedData.Buffer[ModeLed[TempLed]].DutyB = ColorData[ModeColor[1]][B];
							}
						}


						ModeLed[0]++;
						if (ModeLed[0] > RAND_END_TOTAL)		ModeLed[0] = RAND_END_TOTAL + 1;
						for (TempLed = 7; TempLed > 0; TempLed--)
						{
							ModeLed[TempLed] = ModeLed[TempLed - 1];
						}


						if (ModeLed[7] > RAND_END_TOTAL)
						{
							ModeColor[1]++;
							if (ModeColor[1] >= ColorNum)  ModeColor[1] = 1;
							for (TempLed = 0; TempLed < 8; TempLed++)
							{
								ModeLed[TempLed] = 0;
							}

							TempStep = 1;
						}
					}

		} break;

		default:
		{
					TempStep = 0xFF;
		} break;
	}
}
