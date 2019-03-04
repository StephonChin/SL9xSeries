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
#if _AL96_	
		All_Color(0,0,0,0);
#else
		All_Color(0,0,0);
#endif
		
		return;
	}
	
	
	/* Mode Control */
	
	if (TimeLine == 0)									{ShowMode = 0;			ShowInit = TRUE;	}
	else if (TimeLine == 2660)					{ShowMode = 1;			ShowInit = TRUE;	}
	else if (TimeLine == 5350)					{ShowMode = 2;			ShowInit = TRUE;	}
	else if (TimeLine == 5700)					{ShowMode = 3;			ShowInit = TRUE;	}
	else if (TimeLine == 6606)					{ShowMode = 4;			ShowInit = TRUE;	}
	else if (TimeLine == 8500)					{TimeLine = 0;			DisplayData.InitFlag = TRUE; SynFlag = TRUE;}
  TimeLine++;
  
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
		
#if _AL96_	
		All_Color(0,0,0,0);
#else
		All_Color(0,0,0);
#endif
		
		TempStep 	= 0;
		TempColor	= 0;
		
		RndCnt = 0;
		ModeStep[0] = 0;
		
		KeepTime = 0;
		
		StepCnt = 0;
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
						

						
						KeepTime++;
						if (KeepTime >= 5)
						{
							KeepTime = 0;
#if _AL92C_
							/* Tree */
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
#elif _AL92B_
							
							/* Snow */
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
#elif _AL92A_
							
							/* Cane */
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
#elif _AL95_
							/* Spot */
							for (TempCnt = 2; TempCnt > 0; TempCnt--)
							{
								LedData.Buffer[TempCnt].DutyR = LedData.Buffer[TempCnt - 1].DutyR;
								LedData.Buffer[TempCnt].DutyG = LedData.Buffer[TempCnt - 1].DutyG;
								LedData.Buffer[TempCnt].DutyB = LedData.Buffer[TempCnt - 1].DutyB;
							}
							LedData.Buffer[0].DutyR = ColorData[TempColor][R];
							LedData.Buffer[0].DutyG = ColorData[TempColor][G];
							LedData.Buffer[0].DutyB = ColorData[TempColor][B];
#elif _AL96_		
							/* Ball */
							DutyR = ColorData[TempColor][R];
							DutyG = ColorData[TempColor][G];
							DutyB = ColorData[TempColor][B];
							DutyW = ColorData[TempColor][W];
#endif
						}
						
						
						StepCnt++;
						if (StepCnt >= RAND_END_TOTAL)
						{
							StepCnt = 0;
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
						
						
						KeepTime++;
						if (KeepTime >= 5)
						{
							KeepTime = 0;
							
#if _AL92C_
							/* Tree */
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
#elif _AL92B_
							/* Snow */
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
#elif _AL92A_
							/* Cane */
							for (TempCnt = 0; TempCnt < 5; TempCnt++)
							{
								for (TempLed = 0; TempLed < 5; TempLed++)
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
#elif _AL95_
							/* Spot */
							for (TempCnt = 0; TempCnt < 2; TempCnt++)
							{
								LedData.Buffer[TempCnt].DutyR = LedData.Buffer[TempCnt + 1].DutyR;
								LedData.Buffer[TempCnt].DutyG = LedData.Buffer[TempCnt + 1].DutyG;
								LedData.Buffer[TempCnt].DutyB = LedData.Buffer[TempCnt + 1].DutyB;
							}
							LedData.Buffer[2].DutyR = ColorData[TempColor][R];
							LedData.Buffer[2].DutyG = ColorData[TempColor][G];
							LedData.Buffer[2].DutyB = ColorData[TempColor][B];
#elif _AL96_	
							/* Ball */
							DutyR = ColorData[TempColor][R];
							DutyG = ColorData[TempColor][G];
							DutyB = ColorData[TempColor][B];
							DutyW = ColorData[TempColor][W];
#endif
						}
						
						StepCnt++;
						if (StepCnt >= 40)
						{
							StepCnt = 0;
							TempColor++;
							if (TempColor >= ColorNum)		TempColor = 0;

							TempStep = 0;
							ModeStep[0]++;
							if (ModeStep[0] > 2)
							{
								ModeStep[0] = 0;
								TempStep = 2;
								RndCnt = 0;
								StepCnt = 0;
								
								/* Tree */
#if _AL92C_
								for (TempCnt = 0; TempCnt < 3; TempCnt++)
								{
									for (TempLed = 0; TempLed < 7; TempLed++)
									{
										LedData.Buffer[TempCnt * 7 + TempLed].DutyR = 0;
										LedData.Buffer[TempCnt * 7 + TempLed].DutyG = 0;
										LedData.Buffer[TempCnt * 7 + TempLed].DutyB = 0;
									}
									ModeTime[TempCnt] = 0;
									ModeStep[TempCnt] = 0;
									ModeColor[TempCnt] = TempCnt;
								}
#elif _AL92B_
								/* Snow */
								for (TempCnt = 0; TempCnt < 3; TempCnt++)
								{
									for (TempLed = 0; TempLed < 7; TempLed++)
									{
										LedData.Buffer[TempCnt * 7 + TempLed].DutyR = 0;
										LedData.Buffer[TempCnt * 7 + TempLed].DutyG = 0;
										LedData.Buffer[TempCnt * 7 + TempLed].DutyB = 0;
									}
									ModeTime[TempCnt] = 0;
									ModeStep[TempCnt] = 0;
									ModeColor[TempCnt] = TempCnt;
								}
#elif _AL92A_
								/* Cane */
								for (TempCnt = 0; TempCnt < 6; TempCnt++)
								{
									for (TempLed = 0; TempLed < 4; TempLed++)
									{
										LedData.Buffer[TempCnt * 4 + TempLed].DutyR = 0;
										LedData.Buffer[TempCnt * 4 + TempLed].DutyG = 0;
										LedData.Buffer[TempCnt * 4 + TempLed].DutyB = 0;
									}
									ModeTime[TempCnt] = 0;
									ModeStep[TempCnt] = 0;
									ModeColor[TempCnt] = TempCnt;
								}
#elif _AL95_
								/* Spot */
								for (TempCnt = 0; TempCnt < 3; TempCnt++)
								{
									LedData.Buffer[TempCnt].DutyR = 0;
									LedData.Buffer[TempCnt].DutyG = 0;
									LedData.Buffer[TempCnt].DutyB = 0;
									ModeTime[TempCnt] = 0;
									ModeStep[TempCnt] = 0;
									ModeColor[TempCnt] = TempCnt;
								}
#elif _AL96_
								/* Ball */
								ModeTime[0] = 0;
								ModeStep[0] = 0;
								ModeColor[0] = 0;
								DutyR = 0;
								DutyG = 0;
								DutyB = 0;
								DutyW = 0;
#endif
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
						
#if _AL92C_
						
						/* Tree */
						for (TempCnt = 0; TempCnt < 3; TempCnt++)
						{
							ModeTime[TempCnt]++;
							if (ModeTime[TempCnt] >= TempCnt)
							{
								ModeTime[TempCnt] = 0;
								switch (ModeStep[TempCnt])
								{
									case 0:
									{
											if (LedData.Buffer[TempCnt * 7].DutyR < ColorData[ModeColor[TempCnt]][R]
												||LedData.Buffer[TempCnt * 7].DutyG < ColorData[ModeColor[TempCnt]][G]
												||LedData.Buffer[TempCnt * 7].DutyB < ColorData[ModeColor[TempCnt]][B])
											{
												FadeR = ColorData[ModeColor[TempCnt]][R] / 25;
												FadeG = ColorData[ModeColor[TempCnt]][G] / 25;
												FadeB = ColorData[ModeColor[TempCnt]][B] / 25;
												for (TempLed = 0; TempLed < 7; TempLed++)
												{
													LedData.Buffer[TempCnt * 7 + TempLed].DutyR += FadeR;
													LedData.Buffer[TempCnt * 7 + TempLed].DutyG += FadeG;
													LedData.Buffer[TempCnt * 7 + TempLed].DutyB += FadeB;
												}
											}
											else
											{
												ModeStep[TempCnt]++;
											}
									} break;
									
									case 1:
									{
												if (LedData.Buffer[TempCnt * 7].DutyR > 0
													 ||LedData.Buffer[TempCnt * 7].DutyG > 0
													 ||LedData.Buffer[TempCnt * 7].DutyB > 0)
												{
													FadeR = ColorData[ModeColor[TempCnt]][R] / 25;
													FadeG = ColorData[ModeColor[TempCnt]][G] / 25;
													FadeB = ColorData[ModeColor[TempCnt]][B] / 25;
													for (TempLed = 0; TempLed < 7; TempLed++)
													{
														LedData.Buffer[TempCnt * 7 + TempLed].DutyR -= FadeR;
														LedData.Buffer[TempCnt * 7 + TempLed].DutyG -= FadeG;
														LedData.Buffer[TempCnt * 7 + TempLed].DutyB -= FadeB;
													}
												}
												else
												{
													ModeStep[TempCnt] = 0;
													ModeColor[TempCnt]++;
													if (ModeColor[TempCnt] >= ColorNum)		ModeColor[TempCnt] = 0;
												}
									} break;
								}
							}
						}
#elif _AL92B_
						/* Snow */
						for (TempCnt = 0; TempCnt < 3; TempCnt++)
						{
							ModeTime[TempCnt]++;
							if (ModeTime[TempCnt] >= 2 - TempCnt)
							{
								ModeTime[TempCnt] = 0;
								switch (ModeStep[TempCnt])
								{
									case 0:
									{
											if (LedData.Buffer[TempCnt * 7].DutyR < ColorData[ModeColor[TempCnt]][R]
												||LedData.Buffer[TempCnt * 7].DutyG < ColorData[ModeColor[TempCnt]][G]
												||LedData.Buffer[TempCnt * 7].DutyB < ColorData[ModeColor[TempCnt]][B])
											{
												FadeR = ColorData[ModeColor[TempCnt]][R] / 25;
												FadeG = ColorData[ModeColor[TempCnt]][G] / 25;
												FadeB = ColorData[ModeColor[TempCnt]][B] / 25;
												for (TempLed = 0; TempLed < 7; TempLed++)
												{
													LedData.Buffer[TempCnt * 7 + TempLed].DutyR += FadeR;
													LedData.Buffer[TempCnt * 7 + TempLed].DutyG += FadeG;
													LedData.Buffer[TempCnt * 7 + TempLed].DutyB += FadeB;
												}
											}
											else
											{
												ModeStep[TempCnt]++;
											}
									} break;
									
									case 1:
									{
												if (LedData.Buffer[TempCnt * 7].DutyR > 0
													 ||LedData.Buffer[TempCnt * 7].DutyG > 0
													 ||LedData.Buffer[TempCnt * 7].DutyB > 0)
												{
													FadeR = ColorData[ModeColor[TempCnt]][R] / 25;
													FadeG = ColorData[ModeColor[TempCnt]][G] / 25;
													FadeB = ColorData[ModeColor[TempCnt]][B] / 25;
													for (TempLed = 0; TempLed < 7; TempLed++)
													{
														LedData.Buffer[TempCnt * 7 + TempLed].DutyR -= FadeR;
														LedData.Buffer[TempCnt * 7 + TempLed].DutyG -= FadeG;
														LedData.Buffer[TempCnt * 7 + TempLed].DutyB -= FadeB;
													}
												}
												else
												{
													ModeStep[TempCnt] = 0;
													ModeColor[TempCnt]++;
													if (ModeColor[TempCnt] >= ColorNum)		ModeColor[TempCnt] = 0;
												}
									} break;
								}
							}
						}
#elif _AL92A_
						/* Cane */
						for (TempCnt = 0; TempCnt < 6; TempCnt++)
						{
							ModeTime[TempCnt]++;
							if (ModeTime[TempCnt] >= TempCnt)
							{
								ModeTime[TempCnt] = 0;
								switch (ModeStep[TempCnt])
								{
									case 0:
									{
											if (LedData.Buffer[TempCnt * 4].DutyR < ColorData[ModeColor[TempCnt]][R]
												||LedData.Buffer[TempCnt * 4].DutyG < ColorData[ModeColor[TempCnt]][G]
												||LedData.Buffer[TempCnt * 4].DutyB < ColorData[ModeColor[TempCnt]][B])
											{
												FadeR = ColorData[ModeColor[TempCnt]][R] / 25;
												FadeG = ColorData[ModeColor[TempCnt]][G] / 25;
												FadeB = ColorData[ModeColor[TempCnt]][B] / 25;
												for (TempLed = 0; TempLed < 4; TempLed++)
												{
													LedData.Buffer[TempCnt * 4 + TempLed].DutyR += FadeR;
													LedData.Buffer[TempCnt * 4 + TempLed].DutyG += FadeG;
													LedData.Buffer[TempCnt * 4 + TempLed].DutyB += FadeB;
												}
											}
											else
											{
												ModeStep[TempCnt]++;
											}
									} break;
									
									case 1:
									{
												if (LedData.Buffer[TempCnt * 4].DutyR > 0
													 ||LedData.Buffer[TempCnt * 4].DutyG > 0
													 ||LedData.Buffer[TempCnt * 4].DutyB > 0)
												{
													FadeR = ColorData[ModeColor[TempCnt]][R] / 25;
													FadeG = ColorData[ModeColor[TempCnt]][G] / 25;
													FadeB = ColorData[ModeColor[TempCnt]][B] / 25;
													for (TempLed = 0; TempLed < 4; TempLed++)
													{
														LedData.Buffer[TempCnt * 4 + TempLed].DutyR -= FadeR;
														LedData.Buffer[TempCnt * 4 + TempLed].DutyG -= FadeG;
														LedData.Buffer[TempCnt * 4 + TempLed].DutyB -= FadeB;
													}
												}
												else
												{
													ModeStep[TempCnt] = 0;
													ModeColor[TempCnt]++;
													if (ModeColor[TempCnt] >= ColorNum)		ModeColor[TempCnt] = 0;
												}
									} break;
								}
							}
						}
						
#elif _AL95_
						/* Spot */
						for (TempCnt = 0; TempCnt < 3; TempCnt++)
						{
							ModeTime[TempCnt]++;
							if (ModeTime[TempCnt] >= TempCnt)
							{
								ModeTime[TempCnt] = 0;
								switch (ModeStep[TempCnt])
								{
									case 0:
									{
											if (LedData.Buffer[TempCnt].DutyR < ColorData[ModeColor[TempCnt]][R]
												||LedData.Buffer[TempCnt].DutyG < ColorData[ModeColor[TempCnt]][G]
												||LedData.Buffer[TempCnt].DutyB < ColorData[ModeColor[TempCnt]][B])
											{
												FadeR = ColorData[ModeColor[TempCnt]][R] / 25;
												FadeG = ColorData[ModeColor[TempCnt]][G] / 25;
												FadeB = ColorData[ModeColor[TempCnt]][B] / 25;
												LedData.Buffer[TempCnt].DutyR += FadeR;
												LedData.Buffer[TempCnt].DutyG += FadeG;
												LedData.Buffer[TempCnt].DutyB += FadeB;
											}
											else
											{
												ModeStep[TempCnt]++;
											}
									} break;
									
									case 1:
									{
												if (LedData.Buffer[TempCnt].DutyR > 0
													 ||LedData.Buffer[TempCnt].DutyG > 0
													 ||LedData.Buffer[TempCnt].DutyB > 0)
												{
													FadeR = ColorData[ModeColor[TempCnt]][R] / 25;
													FadeG = ColorData[ModeColor[TempCnt]][G] / 25;
													FadeB = ColorData[ModeColor[TempCnt]][B] / 25;
													LedData.Buffer[TempCnt].DutyR -= FadeR;
													LedData.Buffer[TempCnt].DutyG -= FadeG;
													LedData.Buffer[TempCnt].DutyB -= FadeB;
												}
												else
												{
													ModeStep[TempCnt] = 0;
													ModeColor[TempCnt]++;
													if (ModeColor[TempCnt] >= ColorNum)		ModeColor[TempCnt] = 0;
												}
									} break;
								}
							}
						}
#elif _AL96_
						/* Ball */
						ModeTime[0]++;
						if (ModeTime[0] >= 2)
						{
							ModeTime[0] = 0;
							switch (ModeStep[0])
							{
								case 0:
								{
										if (DutyR < ColorData[ModeColor[0]][R]
											||DutyG < ColorData[ModeColor[0]][G]
											||DutyB < ColorData[ModeColor[0]][B]
												|| DutyW < ColorData[ModeColor[0]][W])
										{
											FadeR = ColorData[ModeColor[0]][R] / 25;
											FadeG = ColorData[ModeColor[0]][G] / 25;
											FadeB = ColorData[ModeColor[0]][B] / 25;
											FadeW = ColorData[ModeColor[0]][W] / 25;
											DutyR += FadeR;
											DutyG += FadeG;
											DutyB += FadeB;
											DutyW += FadeW;
										}
										else
										{
											ModeStep[0]++;
										}
								} break;
								
								case 1:
								{
											if (DutyR > 0 || DutyG > 0 || DutyB > 0 || DutyW > 0)
											{
												FadeR = ColorData[ModeColor[0]][R] / 25;
												FadeG = ColorData[ModeColor[0]][G] / 25;
												FadeB = ColorData[ModeColor[0]][B] / 25;
												FadeW = ColorData[ModeColor[0]][W] / 25;
												DutyR -= FadeR;
												DutyG -= FadeG;
												DutyB -= FadeB;
												DutyW -= FadeW;
											}
											else
											{
												ModeStep[0] = 0;
												ModeColor[0]++;
												if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
											}
								} break;
							}
						}
#endif
						
						
						StepCnt++;
						if (StepCnt >= RAND_END_TOTAL)
						{
							StepCnt = 0;
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
						
#if _AL92C_				
						/* Tree */
						for (TempCnt = 0; TempCnt < 3; TempCnt++)
						{
							ModeTime[TempCnt]++;
							if (ModeTime[TempCnt] >= TempCnt)
							{
								ModeTime[TempCnt] = 0;
								switch (ModeStep[TempCnt])
								{
									case 0:
									{
											if (LedData.Buffer[TempCnt * 7].DutyR < ColorData[ModeColor[TempCnt]][R]
												||LedData.Buffer[TempCnt * 7].DutyG < ColorData[ModeColor[TempCnt]][G]
												||LedData.Buffer[TempCnt * 7].DutyB < ColorData[ModeColor[TempCnt]][B])
											{
												FadeR = ColorData[ModeColor[TempCnt]][R] / 25;
												FadeG = ColorData[ModeColor[TempCnt]][G] / 25;
												FadeB = ColorData[ModeColor[TempCnt]][B] / 25;
												for (TempLed = 0; TempLed < 7; TempLed++)
												{
													LedData.Buffer[TempCnt * 7 + TempLed].DutyR += FadeR;
													LedData.Buffer[TempCnt * 7 + TempLed].DutyG += FadeG;
													LedData.Buffer[TempCnt * 7 + TempLed].DutyB += FadeB;
												}
											}
											else
											{
												ModeStep[TempCnt]++;
											}
									} break;
									
									case 1:
									{
												if (LedData.Buffer[TempCnt * 7].DutyR > 0
													 ||LedData.Buffer[TempCnt * 7].DutyG > 0
													 ||LedData.Buffer[TempCnt * 7].DutyB > 0)
												{
													FadeR = ColorData[ModeColor[TempCnt]][R] / 25;
													FadeG = ColorData[ModeColor[TempCnt]][G] / 25;
													FadeB = ColorData[ModeColor[TempCnt]][B] / 25;
													for (TempLed = 0; TempLed < 7; TempLed++)
													{
														LedData.Buffer[TempCnt * 7 + TempLed].DutyR -= FadeR;
														LedData.Buffer[TempCnt * 7 + TempLed].DutyG -= FadeG;
														LedData.Buffer[TempCnt * 7 + TempLed].DutyB -= FadeB;
													}
												}
												else
												{
													ModeStep[TempCnt] = 0;
													ModeColor[TempCnt]++;
													if (ModeColor[TempCnt] >= ColorNum)		ModeColor[TempCnt] = 0;
												}
									} break;
								}
							}
						}
#elif _AL92B_
						/* Snow */
						for (TempCnt = 0; TempCnt < 3; TempCnt++)
						{
							ModeTime[TempCnt]++;
							if (ModeTime[TempCnt] >= 2 - TempCnt)
							{
								ModeTime[TempCnt] = 0;
								switch (ModeStep[TempCnt])
								{
									case 0:
									{
											if (LedData.Buffer[TempCnt * 7].DutyR < ColorData[ModeColor[TempCnt]][R]
												||LedData.Buffer[TempCnt * 7].DutyG < ColorData[ModeColor[TempCnt]][G]
												||LedData.Buffer[TempCnt * 7].DutyB < ColorData[ModeColor[TempCnt]][B])
											{
												FadeR = ColorData[ModeColor[TempCnt]][R] / 25;
												FadeG = ColorData[ModeColor[TempCnt]][G] / 25;
												FadeB = ColorData[ModeColor[TempCnt]][B] / 25;
												for (TempLed = 0; TempLed < 7; TempLed++)
												{
													LedData.Buffer[TempCnt * 7 + TempLed].DutyR += FadeR;
													LedData.Buffer[TempCnt * 7 + TempLed].DutyG += FadeG;
													LedData.Buffer[TempCnt * 7 + TempLed].DutyB += FadeB;
												}
											}
											else
											{
												ModeStep[TempCnt]++;
											}
									} break;
									
									case 1:
									{
												if (LedData.Buffer[TempCnt * 7].DutyR > 0
													 ||LedData.Buffer[TempCnt * 7].DutyG > 0
													 ||LedData.Buffer[TempCnt * 7].DutyB > 0)
												{
													FadeR = ColorData[ModeColor[TempCnt]][R] / 25;
													FadeG = ColorData[ModeColor[TempCnt]][G] / 25;
													FadeB = ColorData[ModeColor[TempCnt]][B] / 25;
													for (TempLed = 0; TempLed < 7; TempLed++)
													{
														LedData.Buffer[TempCnt * 7 + TempLed].DutyR -= FadeR;
														LedData.Buffer[TempCnt * 7 + TempLed].DutyG -= FadeG;
														LedData.Buffer[TempCnt * 7 + TempLed].DutyB -= FadeB;
													}
												}
												else
												{
													ModeStep[TempCnt] = 0;
													ModeColor[TempCnt]++;
													if (ModeColor[TempCnt] >= ColorNum)		ModeColor[TempCnt] = 0;
												}
									} break;
								}
							}
						}
#elif _AL92A_
						/* Cane */
						for (TempCnt = 0; TempCnt < 6; TempCnt++)
						{
							ModeTime[TempCnt]++;
							if (ModeTime[TempCnt] >= TempCnt)
							{
								ModeTime[TempCnt] = 0;
								switch (ModeStep[TempCnt])
								{
									case 0:
									{
											if (LedData.Buffer[TempCnt * 4].DutyR < ColorData[ModeColor[TempCnt]][R]
												||LedData.Buffer[TempCnt * 4].DutyG < ColorData[ModeColor[TempCnt]][G]
												||LedData.Buffer[TempCnt * 4].DutyB < ColorData[ModeColor[TempCnt]][B])
											{
												FadeR = ColorData[ModeColor[TempCnt]][R] / 25;
												FadeG = ColorData[ModeColor[TempCnt]][G] / 25;
												FadeB = ColorData[ModeColor[TempCnt]][B] / 25;
												for (TempLed = 0; TempLed < 4; TempLed++)
												{
													LedData.Buffer[TempCnt * 4 + TempLed].DutyR += FadeR;
													LedData.Buffer[TempCnt * 4 + TempLed].DutyG += FadeG;
													LedData.Buffer[TempCnt * 4 + TempLed].DutyB += FadeB;
												}
											}
											else
											{
												ModeStep[TempCnt]++;
											}
									} break;
									
									case 1:
									{
												if (LedData.Buffer[TempCnt * 4].DutyR > 0
													 ||LedData.Buffer[TempCnt * 4].DutyG > 0
													 ||LedData.Buffer[TempCnt * 4].DutyB > 0)
												{
													FadeR = ColorData[ModeColor[TempCnt]][R] / 25;
													FadeG = ColorData[ModeColor[TempCnt]][G] / 25;
													FadeB = ColorData[ModeColor[TempCnt]][B] / 25;
													for (TempLed = 0; TempLed < 4; TempLed++)
													{
														LedData.Buffer[TempCnt * 4 + TempLed].DutyR -= FadeR;
														LedData.Buffer[TempCnt * 4 + TempLed].DutyG -= FadeG;
														LedData.Buffer[TempCnt * 4 + TempLed].DutyB -= FadeB;
													}
												}
												else
												{
													ModeStep[TempCnt] = 0;
													ModeColor[TempCnt]++;
													if (ModeColor[TempCnt] >= ColorNum)		ModeColor[TempCnt] = 0;
												}
									} break;
								}
							}
						}
						
#elif _AL95_
						/* Spot */
						for (TempCnt = 0; TempCnt < 3; TempCnt++)
						{
							ModeTime[TempCnt]++;
							if (ModeTime[TempCnt] >= TempCnt)
							{
								ModeTime[TempCnt] = 0;
								switch (ModeStep[TempCnt])
								{
									case 0:
									{
											if (LedData.Buffer[TempCnt].DutyR < ColorData[ModeColor[TempCnt]][R]
												||LedData.Buffer[TempCnt].DutyG < ColorData[ModeColor[TempCnt]][G]
												||LedData.Buffer[TempCnt].DutyB < ColorData[ModeColor[TempCnt]][B])
											{
												FadeR = ColorData[ModeColor[TempCnt]][R] / 25;
												FadeG = ColorData[ModeColor[TempCnt]][G] / 25;
												FadeB = ColorData[ModeColor[TempCnt]][B] / 25;
												LedData.Buffer[TempCnt].DutyR += FadeR;
												LedData.Buffer[TempCnt].DutyG += FadeG;
												LedData.Buffer[TempCnt].DutyB += FadeB;
											}
											else
											{
												ModeStep[TempCnt]++;
											}
									} break;
									
									case 1:
									{
												if (LedData.Buffer[TempCnt].DutyR > 0
													 ||LedData.Buffer[TempCnt].DutyG > 0
													 ||LedData.Buffer[TempCnt].DutyB > 0)
												{
													FadeR = ColorData[ModeColor[TempCnt]][R] / 25;
													FadeG = ColorData[ModeColor[TempCnt]][G] / 25;
													FadeB = ColorData[ModeColor[TempCnt]][B] / 25;
													LedData.Buffer[TempCnt].DutyR -= FadeR;
													LedData.Buffer[TempCnt].DutyG -= FadeG;
													LedData.Buffer[TempCnt].DutyB -= FadeB;
												}
												else
												{
													ModeStep[TempCnt] = 0;
													ModeColor[TempCnt]++;
													if (ModeColor[TempCnt] >= ColorNum)		ModeColor[TempCnt] = 0;
												}
									} break;
								}
							}
						}
#elif _AL96_
						/* Ball */
						ModeTime[0]++;
						if (ModeTime[0] >= 2)
						{
							ModeTime[0] = 0;
							switch (ModeStep[0])
							{
								case 0:
								{
										if (DutyR < ColorData[ModeColor[0]][R]
											||DutyG < ColorData[ModeColor[0]][G]
											||DutyB < ColorData[ModeColor[0]][B]
												||DutyW < ColorData[ModeColor[0]][W])
										{
											FadeR = ColorData[ModeColor[0]][R] / 25;
											FadeG = ColorData[ModeColor[0]][G] / 25;
											FadeB = ColorData[ModeColor[0]][B] / 25;
											FadeW = ColorData[ModeColor[0]][W] / 25;
											DutyR += FadeR;
											DutyG += FadeG;
											DutyB += FadeB;
											DutyW += FadeW;
										}
										else
										{
											ModeStep[0]++;
										}
								} break;
								
								case 1:
								{
											if (DutyR > 0
												 ||DutyG > 0
												 ||DutyB > 0
													 || DutyW > 0)
											{
												FadeR = ColorData[ModeColor[0]][R] / 25;
												FadeG = ColorData[ModeColor[0]][G] / 25;
												FadeB = ColorData[ModeColor[0]][B] / 25;
												FadeW = ColorData[ModeColor[0]][W] / 25;

												DutyR -= FadeR;
												DutyG -= FadeG;
												DutyB -= FadeB;
												DutyW -= FadeW;
											}
											else
											{
												ModeStep[0] = 0;
												ModeColor[0]++;
												if (ModeColor[0] >= ColorNum)		ModeColor[0] = 0;
											}
								} break;
							}
						}
						
#endif
						
						StepCnt++;
						if (StepCnt >= RAND_END_TOTAL)
						{
							StepCnt = 0;
							TempStep = 2;
							RndCnt++;
							if (RndCnt > 2)
							{
								RndCnt = 0;
								TempStep = 4;
								
								for (TempCnt = 0; TempCnt < 50; TempCnt++)
								{
									ModeLed[TempCnt] = 0;
								}
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

							LedData.Buffer[ModeLed[0]].DutyR	= 0;
							LedData.Buffer[ModeLed[0]].DutyG	= 0;
							LedData.Buffer[ModeLed[0]].DutyB	= 0;
							LedData.Buffer[ModeLed[1]].DutyR	= 0;
							LedData.Buffer[ModeLed[1]].DutyG	= 0;
							LedData.Buffer[ModeLed[1]].DutyB	= 0;
						}
#elif _AL92B_
						/* Snow */
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
#elif _AL92A_
						/* Cane */
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
#elif _AL95_
						/* Spot */
						if (RndCnt < 3)
						{
							LedData.Buffer[RndCnt].DutyR	= 0;
							LedData.Buffer[RndCnt].DutyG	= 0;
							LedData.Buffer[RndCnt].DutyB	= 0;
							RndCnt++;
						}
#elif _AL96_
						/* Ball */
						DutyR = 0;
						DutyG = 0;
						DutyB = 0;
						DutyW = 0;
#endif
						StepCnt++;
						if (StepCnt >= RAND_END_TOTAL)
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
#if _AL96_
		All_Color(0,0,0,0);
		FadeW = ColorData[TempColor][W] / 50;
#else
		All_Color(0,0,0);
#endif
		
		TempStep 	= 0;
		TempColor	= 0;
		StepCnt = 0;
		SteadyTime = 0;
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
#if _AL96_
					TempW = FadeW * 10;
					All_Color(TempR, TempG, TempB, TempW);
#else
					All_Color(TempR, TempG, TempB);
#endif
					
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
#if _AL96_
					TempW += FadeW;
					All_Color(TempR, TempG, TempB, TempW);
#else
					All_Color(TempR, TempG, TempB);
#endif
					
					RndCnt++;
					if (RndCnt >= 20)
					{
						RndCnt = 0;
						TempStep++;
						
						
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
							if (ModeTime[0] >= 5)
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

						if (RndCnt >= RAND_END_TOTAL + 5)
						{
							StepCnt = 0;
							TempStep = 0;
							SpeedTime = 0;
							TempColor++;
							if (TempColor >= ColorNum)		TempColor = 0;
							FadeR = ColorData[TempColor][R] / 25;
							FadeG = ColorData[TempColor][G] / 25;
							FadeB = ColorData[TempColor][B] / 25;
#if _AL96_
							FadeW = ColorData[TempColor][W] / 25;
#endif
							RndCnt = 0;
							SpeedTime = 0;
							
							KeepTime++;
							if (KeepTime > 2)
							{
								KeepTime = 0;
								TempStep = 3;
								
								for (TempCnt = 0; TempCnt < 50; TempCnt++)
								{
									ModeLed[TempCnt] = 0;
								}
							}
						}
		} break;
		
		case 3:
		{
#if _AL92C_
					/* Tree */
					if (RndCnt < 3)
					{
						do
						{
							RAND();
							ModeStep[0] = (_Uint8)rand() % 3;
						} while(ModeLed[ModeStep[0]] == 1);
						ModeLed[ModeStep[0]] = 1;
						RndCnt++;
					}
					else
					{
						RndCnt = 4;
					}
#elif _AL92B_
					/* Snow */
					if (RndCnt < 3)
					{
						do
						{
							RAND();
							ModeStep[0] = (_Uint8)rand() % 3;
						} while(ModeLed[ModeStep[0]] == 1);
						ModeLed[ModeStep[0]] = 1;
						RndCnt++;
					}
					else
					{
						RndCnt = 4;
					}
#elif _AL95_
					/* Spot */
					if (RndCnt < 3)
					{
						do
						{
							RAND();
							ModeStep[0] = (_Uint8)rand() % 3;
						} while(ModeLed[ModeStep[0]] == 1);
						ModeLed[ModeStep[0]] = 1;
						RndCnt++;
					}
					else
					{
						RndCnt = 4;
					}
					
#elif _AL92A_
					/* Cane */
					if (RndCnt < 6)
					{
						do
						{
							RAND();
							ModeStep[0] = (_Uint8)rand() % 6;
						} while(ModeLed[ModeStep[0]] == 1);
						ModeLed[ModeStep[0]] = 1;
						RndCnt++;
					}
					else
					{
						RndCnt = 7;
					}
#endif
					TempStep++;
					KeepTime = 0;
					TempR = 0;
					TempG = 0;
					TempB = 0;
#if _AL96_
					TempW = 0;
					FadeW = ColorData[TempColor][W] / 50;
#endif
					FadeR = ColorData[TempColor][R] / 50;
					FadeG = ColorData[TempColor][G] / 50;
					FadeB = ColorData[TempColor][B] / 50;
					
					StepCnt++;
					if (StepCnt >= RAND_END_TOTAL)
					{
						TempStep = 5;
						StepCnt = 0;
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
#if _AL96_
					TempW += FadeW;
#endif
					
#if _AL92C_
					if (RndCnt <= 3)
					{
						for (TempCnt = 0; TempCnt < 7; TempCnt++)
						{
							LedData.Buffer[TempCnt + ModeStep[0] * 7].DutyR += FadeR;
							LedData.Buffer[TempCnt + ModeStep[0] * 7].DutyG += FadeG;
							LedData.Buffer[TempCnt + ModeStep[0] * 7].DutyB += FadeB;
						}
					}
#elif _AL92B_
					if (RndCnt <= 3)
					{
						for (TempCnt = 0; TempCnt < 7; TempCnt++)
						{
							LedData.Buffer[TempCnt + ModeStep[0] * 7].DutyR += FadeR;
							LedData.Buffer[TempCnt + ModeStep[0] * 7].DutyG += FadeG;
							LedData.Buffer[TempCnt + ModeStep[0] * 7].DutyB += FadeB;
						}
					}
#elif _AL92A_
					if (RndCnt <= 6)
					{
						for (TempCnt = 0; TempCnt < 4; TempCnt++)
						{
							LedData.Buffer[TempCnt + ModeStep[0] * 4].DutyR += FadeR;
							LedData.Buffer[TempCnt + ModeStep[0] * 4].DutyG += FadeG;
							LedData.Buffer[TempCnt + ModeStep[0] * 4].DutyB += FadeB;
						}
					}
					
#elif _AL95_
					if (RndCnt <= 3)
					{
						LedData.Buffer[ModeStep[0]].DutyR += FadeR;
						LedData.Buffer[ModeStep[0]].DutyG += FadeG;
						LedData.Buffer[ModeStep[0]].DutyB += FadeB;
					}
#elif _AL96_			
					if (RndCnt <= 1)
					{
						DutyR += FadeR;
						DutyG += FadeG;
						DutyB += FadeB;
						DutyW += FadeW;
					}
#endif
					
					
					KeepTime++;
					if (KeepTime >= 50)
					{
						TempStep = 3;
#if _AL96_
						RndCnt = 2;
#endif
						TempColor++;
						if (TempColor >= ColorNum)  TempColor = 0;
					}
		} break;
		
		case 5:
		{
#if _AL96_
					All_Color(0,0,0,0);
#else
					All_Color(0,0,0);
#endif
					TempStep++;
		} break;
		
		case 6:
		case 7:
		case 8:
		{
#if _AL92C_
					/* Tree */
					for (TempLed = 0; TempLed < 3; TempLed++)
					{
						if (TempLed % 3 == 1)
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
												if (LedData.Buffer[TempLed * 7].DutyR > 0
														|| LedData.Buffer[TempLed * 7].DutyG > 0
															|| LedData.Buffer[TempLed * 7].DutyB > 0)
												{
													for (TempCnt = 0; TempCnt < 7; TempCnt++)
													{
														LedData.Buffer[TempLed * 7 + TempCnt].DutyR -= FadeR;
														LedData.Buffer[TempLed * 7 + TempCnt].DutyG -= FadeG;
														LedData.Buffer[TempLed * 7 + TempCnt].DutyB -= FadeB;
													}
												}
												else
												{
													ModeStep[TempLed]++;
												}
									} break;
									
									default:
									{
												if (LedData.Buffer[TempLed * 7].DutyR < ColorData[TempColor][R]
														|| LedData.Buffer[TempLed * 7].DutyG < ColorData[TempColor][G]
															|| LedData.Buffer[TempLed * 7].DutyB < ColorData[TempColor][B])
												{
													for (TempCnt = 0; TempCnt < 7; TempCnt++)
													{
														LedData.Buffer[TempLed * 7 + TempCnt].DutyR += FadeR;
														LedData.Buffer[TempLed * 7 + TempCnt].DutyG += FadeG;
														LedData.Buffer[TempLed * 7 + TempCnt].DutyB += FadeB;
													}
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
												for (TempCnt = 0; TempCnt < 7; TempCnt++)
												{
													LedData.Buffer[TempLed * 7 + TempCnt].DutyR = ColorData[TempColor][R] / 2;
													LedData.Buffer[TempLed * 7 + TempCnt].DutyG = ColorData[TempColor][G] / 2;
													LedData.Buffer[TempLed * 7 + TempCnt].DutyB = ColorData[TempColor][B] / 2;
												}
												ModeStep[TempLed]++;
									} break;
									
									default:
									{
												for (TempCnt = 0; TempCnt < 7; TempCnt++)
												{
													LedData.Buffer[TempLed * 7 + TempCnt].DutyR = ColorData[TempColor][R];
													LedData.Buffer[TempLed * 7 + TempCnt].DutyG = ColorData[TempColor][G];
													LedData.Buffer[TempLed * 7 + TempCnt].DutyB = ColorData[TempColor][B];
												}
												ModeStep[TempLed] = 0;
									} break;
								}
							}
						}
					}
#elif _AL92B_
					/* Snow */
					for (TempLed = 0; TempLed < 3; TempLed++)
					{
						if (TempLed % 3 == 1)
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
												if (LedData.Buffer[TempLed * 7].DutyR > 0
														|| LedData.Buffer[TempLed * 7].DutyG > 0
															|| LedData.Buffer[TempLed * 7].DutyB > 0)
												{
													for (TempCnt = 0; TempCnt < 7; TempCnt++)
													{
														LedData.Buffer[TempLed * 7 + TempCnt].DutyR -= FadeR;
														LedData.Buffer[TempLed * 7 + TempCnt].DutyG -= FadeG;
														LedData.Buffer[TempLed * 7 + TempCnt].DutyB -= FadeB;
													}
												}
												else
												{
													ModeStep[TempLed]++;
												}
									} break;
									
									default:
									{
												if (LedData.Buffer[TempLed * 7].DutyR < ColorData[TempColor][R]
														|| LedData.Buffer[TempLed * 7].DutyG < ColorData[TempColor][G]
															|| LedData.Buffer[TempLed * 7].DutyB < ColorData[TempColor][B])
												{
													for (TempCnt = 0; TempCnt < 7; TempCnt++)
													{
														LedData.Buffer[TempLed * 7 + TempCnt].DutyR += FadeR;
														LedData.Buffer[TempLed * 7 + TempCnt].DutyG += FadeG;
														LedData.Buffer[TempLed * 7 + TempCnt].DutyB += FadeB;
													}
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
												for (TempCnt = 0; TempCnt < 7; TempCnt++)
												{
													LedData.Buffer[TempLed * 7 + TempCnt].DutyR = ColorData[TempColor][R] / 2;
													LedData.Buffer[TempLed * 7 + TempCnt].DutyG = ColorData[TempColor][G] / 2;
													LedData.Buffer[TempLed * 7 + TempCnt].DutyB = ColorData[TempColor][B] / 2;
												}
												ModeStep[TempLed]++;
									} break;
									
									default:
									{
												for (TempCnt = 0; TempCnt < 7; TempCnt++)
												{
													LedData.Buffer[TempLed * 7 + TempCnt].DutyR = ColorData[TempColor][R];
													LedData.Buffer[TempLed * 7 + TempCnt].DutyG = ColorData[TempColor][G];
													LedData.Buffer[TempLed * 7 + TempCnt].DutyB = ColorData[TempColor][B];
												}
												ModeStep[TempLed] = 0;
									} break;
								}
							}
						}
					}
#elif _AL92A_	
					/* Cane */
					for (TempLed = 0; TempLed < 6; TempLed++)
					{
						if (TempLed % 3 == 1)
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
												if (LedData.Buffer[TempLed * 4].DutyR > 0
														|| LedData.Buffer[TempLed * 4].DutyG > 0
															|| LedData.Buffer[TempLed * 4].DutyB > 0)
												{
													for (TempCnt = 0; TempCnt < 4; TempCnt++)
													{
														LedData.Buffer[TempLed * 4 + TempCnt].DutyR -= FadeR;
														LedData.Buffer[TempLed * 4 + TempCnt].DutyG -= FadeG;
														LedData.Buffer[TempLed * 4 + TempCnt].DutyB -= FadeB;
													}
												}
												else
												{
													ModeStep[TempLed]++;
												}
									} break;
									
									default:
									{
												if (LedData.Buffer[TempLed * 4].DutyR < ColorData[TempColor][R]
														|| LedData.Buffer[TempLed * 4].DutyG < ColorData[TempColor][G]
															|| LedData.Buffer[TempLed * 4].DutyB < ColorData[TempColor][B])
												{
													for (TempCnt = 0; TempCnt < 4; TempCnt++)
													{
														LedData.Buffer[TempLed * 4 + TempCnt].DutyR += FadeR;
														LedData.Buffer[TempLed * 4 + TempCnt].DutyG += FadeG;
														LedData.Buffer[TempLed * 4 + TempCnt].DutyB += FadeB;
													}
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
												for (TempCnt = 0; TempCnt < 4; TempCnt++)
												{
													LedData.Buffer[TempLed * 4 + TempCnt].DutyR = ColorData[TempColor][R] / 2;
													LedData.Buffer[TempLed * 4 + TempCnt].DutyG = ColorData[TempColor][G] / 2;
													LedData.Buffer[TempLed * 4 + TempCnt].DutyB = ColorData[TempColor][B] / 2;
												}
												ModeStep[TempLed]++;
									} break;
									
									default:
									{
												for (TempCnt = 0; TempCnt < 4; TempCnt++)
												{
													LedData.Buffer[TempLed * 4 + TempCnt].DutyR = ColorData[TempColor][R];
													LedData.Buffer[TempLed * 4 + TempCnt].DutyG = ColorData[TempColor][G];
													LedData.Buffer[TempLed * 4 + TempCnt].DutyB = ColorData[TempColor][B];
												}
												ModeStep[TempLed] = 0;
									} break;
								}
							}
						}
					}
#elif _AL95_
					/* Spot */
					for (TempLed = 0; TempLed < 3; TempLed++)
					{
						if (TempLed % 3 == 1)
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
#elif _AL96_
					/* Ball */
					ModeTime[0]++;
					if (ModeTime[0] >= 2)
					{
						ModeTime[0] = 0;
						FadeR = ColorData[0][R] / 25;
						FadeG = ColorData[0][G] / 25;
						FadeB = ColorData[0][B] / 25;
						FadeW = ColorData[0][W] / 25;
						
						switch (ModeStep[0])
						{
							case 0:
							{
										if (DutyR > 0
												|| DutyG > 0
													|| DutyB > 0
														|| DutyW > 0)
										{
											DutyR -= FadeR;
											DutyG -= FadeG;
											DutyB -= FadeB;
											DutyW -= FadeW;
										}
										else
										{
											ModeStep[0]++;
										}
							} break;
							
							default:
							{
										if (DutyR < ColorData[0][R]
												|| DutyG < ColorData[0][G]
													|| DutyB < ColorData[0][B]
														|| DutyW < ColorData[0][W])
										{
											DutyR += FadeR;
											DutyG += FadeG;
											DutyB += FadeB;
											DutyW += FadeW;
										}
										else
										{
											ModeStep[0] = 0;
										}
							} break;
						}
					}
#endif
					
					
					
					
					SpeedTime++;
					if (SpeedTime >= 200)
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
		StepCnt = 0;
		TempR			= 255;
		TempG			= 0;
		TempB			= 0;
#if _AL96_
		TempW = 0;
#endif
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
	
						LedData.Buffer[ModeLed[0]].DutyR	= TempR;
						LedData.Buffer[ModeLed[0]].DutyG	= TempG;
						LedData.Buffer[ModeLed[0]].DutyB	= TempB;
						LedData.Buffer[ModeLed[1]].DutyR	= TempR;
						LedData.Buffer[ModeLed[1]].DutyG	= TempG;
						LedData.Buffer[ModeLed[1]].DutyB	= TempB;
					}
#elif _AL92B_
					/* Snow */
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
						
						LedData.Buffer[ModeLed[0]].DutyR	= TempR;
						LedData.Buffer[ModeLed[0]].DutyG	= TempG;
						LedData.Buffer[ModeLed[0]].DutyB	= TempB;

						LedData.Buffer[ModeLed[1]].DutyR	= TempR;
						LedData.Buffer[ModeLed[1]].DutyG	= TempG;
						LedData.Buffer[ModeLed[1]].DutyB	= TempB;
						
						LedData.Buffer[ModeLed[2]].DutyR	= TempR;
						LedData.Buffer[ModeLed[2]].DutyG	= TempG;
						LedData.Buffer[ModeLed[2]].DutyB	= TempB;
					}
#elif _AL92A_
					/* Cane */
					if (RndCnt < 6)
					{
						for (TempCnt = 0; TempCnt < 4; TempCnt++)
						{
							LedData.Buffer[RndCnt * 4 + TempCnt].DutyR	= TempR;
							LedData.Buffer[RndCnt * 4 + TempCnt].DutyG	= TempG;
							LedData.Buffer[RndCnt * 4 + TempCnt].DutyB	= TempB;
						}
						
						RndCnt++;
					}
#elif _AL95_
					/* Spot */
					if (RndCnt < 3)
					{
						LedData.Buffer[RndCnt].DutyR	= TempR;
						LedData.Buffer[RndCnt].DutyG	= TempG;
						LedData.Buffer[RndCnt].DutyB	= TempB;
						RndCnt++;
					}
#elif _AL96_
					/* Ball */
					DutyR = TempR;
					DutyG = TempG;
					DutyB = TempB;
					DutyW = TempW;
#endif
					StepCnt++;
					if (StepCnt >= RAND_END_TOTAL)
					{
						StepCnt = 0;
						TempStep++;
					}
				}
		} break;
		
		case 1:
		{
					if (TempG < 255)			TempG += 15;
					else									TempStep++;
#if _AL96_
					All_Color(TempR, TempG, TempB, 0);
#else
					All_Color(TempR, TempG, TempB);
#endif
		} break;
		
		case 2:
		{
					if (TempR > 0)				TempR -= 15;
					else									TempStep++;
					
#if _AL96_
					All_Color(TempR, TempG, TempB, 0);
#else
					All_Color(TempR, TempG, TempB);
#endif
		} break;
		
		case 3:
		{
					if (TempB < 255)			TempB += 15;
					else									TempStep++;
					
#if _AL96_
					All_Color(TempR, TempG, TempB, 0);
#else
					All_Color(TempR, TempG, TempB);
#endif
		} break;
		
		case 4:
		{
					if (TempG > 0)				TempG -= 15;
					else									TempStep++;
					
#if _AL96_
					All_Color(TempR, TempG, TempB, 0);
#else
					All_Color(TempR, TempG, TempB);
#endif
		} break;
		
		case 5:
		{
					if (TempR < 255)			TempR += 15;
					else									TempStep++;
					
#if _AL96_
					All_Color(TempR, TempG, TempB, 0);
#else
					All_Color(TempR, TempG, TempB);
#endif
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
#elif _AL95_	
					/* Spot */
					LedData.Buffer[0].DutyR = ColorData[TempColor][R];
					LedData.Buffer[0].DutyG = ColorData[TempColor][G];
					LedData.Buffer[0].DutyB = ColorData[TempColor][B];
#elif _AL96_				
					/* Ball */
					DutyR = ColorData[TempColor][R];
					DutyG = ColorData[TempColor][G];
					DutyB = ColorData[TempColor][B];
					DutyW = ColorData[TempColor][W];
#endif
					
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
#elif _AL95_
					/* Spot */
					LedData.Buffer[1].DutyR = ColorData[TempColor][R];
					LedData.Buffer[1].DutyG = ColorData[TempColor][G];
					LedData.Buffer[1].DutyB = ColorData[TempColor][B];
#elif _AL96_
					/* Ball */
					DutyR = ColorData[TempColor][R];
					DutyG = ColorData[TempColor][G];
					DutyB = ColorData[TempColor][B];
					DutyW = ColorData[TempColor][W];
#endif
					
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
#elif _AL95_
					/* Spot */
					LedData.Buffer[2].DutyR = ColorData[TempColor][R];
					LedData.Buffer[2].DutyG = ColorData[TempColor][G];
					LedData.Buffer[2].DutyB = ColorData[TempColor][B];
#elif _AL96_
					/* Ball */
					DutyR = ColorData[TempColor][R];
					DutyG = ColorData[TempColor][G];
					DutyB = ColorData[TempColor][B];
					DutyW = ColorData[TempColor][W];
#endif

					
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
#if _AL96_
					TempW = ColorData[TempColor][W];
					All_Color(TempR, TempG, TempB, TempW);
#else
					All_Color(TempR, TempG, TempB);
#endif
					
					KeepTime++;
					if (KeepTime >= 50)
					{
						KeepTime = 0;
						FadeR = ColorData[TempColor][R] / 50;
						FadeG = ColorData[TempColor][G] / 50;
						FadeB = ColorData[TempColor][B] / 50;
#if _AL96_
						FadeW = ColorData[TempColor][W] / 50;
#endif
						TempStep++;
						RndCnt = 0;
					}
		} break;
		
		case 4:
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
#if _AL96_
		TempW = 0;
#endif
		
		for (TempCnt = 0; TempCnt < 50; TempCnt++)
		{
			ModeLed[TempCnt] = 0;
		}
		
		RndCnt = 0;
		StepCnt = 0;
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
#if _AL92C_
						
						/* Tree */
						if (RndCnt < 12)
						{
							RndCnt++;
							switch (RndCnt)
							{
								case 1:			ModeLed[0] = 0;			ModeLed[1] = 6;		 	break;
								case 2:			ModeLed[0] = 1;			ModeLed[1] = 5;	  	break;
								case 3:			ModeLed[0] = 2;			ModeLed[1] = 6;	   	break;
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
		
							LedData.Buffer[ModeLed[0]].DutyR	= TempR;
							LedData.Buffer[ModeLed[0]].DutyG	= TempG;
							LedData.Buffer[ModeLed[0]].DutyB	= TempB;
							LedData.Buffer[ModeLed[1]].DutyR	= TempR;
							LedData.Buffer[ModeLed[1]].DutyG	= TempG;
							LedData.Buffer[ModeLed[1]].DutyB	= TempB;
						}
#elif _AL92B_				
						/* Snow */
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
							
							LedData.Buffer[ModeLed[0]].DutyR	= TempR;
							LedData.Buffer[ModeLed[0]].DutyG	= TempG;
							LedData.Buffer[ModeLed[0]].DutyB	= TempB;

							LedData.Buffer[ModeLed[1]].DutyR	= TempR;
							LedData.Buffer[ModeLed[1]].DutyG	= TempG;
							LedData.Buffer[ModeLed[1]].DutyB	= TempB;
							
							LedData.Buffer[ModeLed[2]].DutyR	= TempR;
							LedData.Buffer[ModeLed[2]].DutyG	= TempG;
							LedData.Buffer[ModeLed[2]].DutyB	= TempB;
						}
#elif _AL92A_		
						/* Cane */
						if (RndCnt < 6)
						{
							for (TempCnt = 0; TempCnt < 4; TempCnt++)
							{
								LedData.Buffer[RndCnt * 4 + TempCnt].DutyR	= TempR;
								LedData.Buffer[RndCnt * 4 + TempCnt].DutyG	= TempG;
								LedData.Buffer[RndCnt * 4 + TempCnt].DutyB	= TempB;
							}
							
							RndCnt++;
						}
#elif _AL95_
						/* Spot */
						if (RndCnt < 3)
						{
							LedData.Buffer[RndCnt].DutyR	= TempR;
							LedData.Buffer[RndCnt].DutyG	= TempG;
							LedData.Buffer[RndCnt].DutyB	= TempB;
							RndCnt++;
						}
#elif _AL96_
						/* Ball */
						DutyR = TempR;
						DutyG = TempG;
						DutyB = TempB;
						DutyW = TempW;
#endif

						StepCnt++;
						if (StepCnt >= RAND_END_TOTAL)
						{
							StepCnt = 0;
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
#if _AL96_
						TempW = ColorData[ModeColor[0]][W];
						All_Color(TempR, TempG, TempB, TempW);
#else
						All_Color(TempR, TempG, TempB);
#endif
						for (TempLed = 0; TempLed < 8; TempLed++)
						{
#if _AL92C_
							/* Tree */
							if (ModeLed[TempLed] < 3)
							{
								for (TempCnt = 0; TempCnt < 7; TempCnt++)
								{
									LedData.Buffer[ModeLed[TempLed] * 7 + TempCnt].DutyR = ColorData[ModeColor[1]][R];
									LedData.Buffer[ModeLed[TempLed] * 7 + TempCnt].DutyG = ColorData[ModeColor[1]][G];
									LedData.Buffer[ModeLed[TempLed] * 7 + TempCnt].DutyB = ColorData[ModeColor[1]][B];
								}
							}
#elif _AL92B_
							/* Snow */
							if (ModeLed[TempLed] < 3)
							{
								for (TempCnt = 0; TempCnt < 9; TempCnt++)
								{
									LedData.Buffer[ModeLed[TempLed] * 7 + TempCnt].DutyR = ColorData[ModeColor[1]][R];
									LedData.Buffer[ModeLed[TempLed] * 7 + TempCnt].DutyG = ColorData[ModeColor[1]][G];
									LedData.Buffer[ModeLed[TempLed] * 7 + TempCnt].DutyB = ColorData[ModeColor[1]][B];
								}
							}
#elif _AL92A_
							/* Cane */
							if (ModeLed[TempLed] < 6)
							{
								for (TempCnt = 0; TempCnt < 4; TempCnt++)
								{
									LedData.Buffer[ModeLed[TempLed] * 4 + TempCnt].DutyR = ColorData[ModeColor[1]][R];
									LedData.Buffer[ModeLed[TempLed] * 4 + TempCnt].DutyG = ColorData[ModeColor[1]][G];
									LedData.Buffer[ModeLed[TempLed] * 4 + TempCnt].DutyB = ColorData[ModeColor[1]][B];
								}
							}
#elif _AL95_
							/* Spot */
							if (ModeLed[TempLed] < 3)
							{
								LedData.Buffer[ModeLed[TempLed]].DutyR = ColorData[ModeColor[1]][R];
								LedData.Buffer[ModeLed[TempLed]].DutyG = ColorData[ModeColor[1]][G];
								LedData.Buffer[ModeLed[TempLed]].DutyB = ColorData[ModeColor[1]][B];
							}
#elif _AL96_	
							/* Ball */
							if (ModeLed[TempLed] < 10)
							{
								DutyR = ColorData[ModeColor[1]][R];
								DutyG = ColorData[ModeColor[1]][G];
								DutyB = ColorData[ModeColor[1]][B];
								DutyW = ColorData[ModeColor[1]][W];
							}
#endif
						}
						
						ModeLed[0]++;
						if (ModeLed[0] >= 41)		ModeLed[0] = 41;
						for (TempLed = 7; TempLed > 0; TempLed--)
						{
							ModeLed[TempLed] = ModeLed[TempLed - 1];
						}

						
						if (ModeLed[7] >= 41)
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
							
#if _AL92C_
							/* Tree */
							if (ModeLed[TempLed] < 3)
							{
								for (TempCnt = 0; TempCnt < 7; TempCnt++)
								{
									LedData.Buffer[ModeLed[TempLed] * 7 + TempCnt].DutyR = ColorData[ModeColor[1]][R];
									LedData.Buffer[ModeLed[TempLed] * 7 + TempCnt].DutyG = ColorData[ModeColor[1]][G];
									LedData.Buffer[ModeLed[TempLed] * 7 + TempCnt].DutyB = ColorData[ModeColor[1]][B];
								}
							}
#elif _AL92B_
							/* Snow */
							if (ModeLed[TempLed] < 3)
							{
								for (TempCnt = 0; TempCnt < 7; TempCnt++)
								{
									LedData.Buffer[ModeLed[TempLed] * 7 + TempCnt].DutyR = ColorData[ModeColor[1]][R];
									LedData.Buffer[ModeLed[TempLed] * 7 + TempCnt].DutyG = ColorData[ModeColor[1]][G];
									LedData.Buffer[ModeLed[TempLed] * 7 + TempCnt].DutyB = ColorData[ModeColor[1]][B];
								}
							}
#elif _AL92A_
							/* Cane */
							if (ModeLed[TempLed] < 6)
							{
								for (TempCnt = 0; TempCnt < 4; TempCnt++)
								{
									LedData.Buffer[ModeLed[TempLed] * 4 + TempCnt].DutyR = ColorData[ModeColor[1]][R];
									LedData.Buffer[ModeLed[TempLed] * 4 + TempCnt].DutyG = ColorData[ModeColor[1]][G];
									LedData.Buffer[ModeLed[TempLed] * 4 + TempCnt].DutyB = ColorData[ModeColor[1]][B];
								}
							}
#elif _AL95_
							/* Spot */
							if (ModeLed[TempLed] < 3)
							{
								LedData.Buffer[ModeLed[TempLed]].DutyR = ColorData[ModeColor[1]][R];
								LedData.Buffer[ModeLed[TempLed]].DutyG = ColorData[ModeColor[1]][G];
								LedData.Buffer[ModeLed[TempLed]].DutyB = ColorData[ModeColor[1]][B];
							}
#elif _AL96_
							/* Ball */
							if (ModeLed[TempLed] < 10)
							{
								DutyR = ColorData[ModeColor[1]][R];
								DutyG = ColorData[ModeColor[1]][G];
								DutyB = ColorData[ModeColor[1]][B];
								DutyW = ColorData[ModeColor[1]][W];
							}
#endif
						}
						
						
						ModeLed[0]++;
						if (ModeLed[0] >= 41)		ModeLed[0] = 41;
						for (TempLed = 7; TempLed > 0; TempLed--)
						{
							ModeLed[TempLed] = ModeLed[TempLed - 1];
						}

						
						if (ModeLed[7] >= 41)
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








