#include "Music.h"

//global argument
uint8   MusicMode;
_Flag   MusicEnFlag;
uint16  MusicEnTime;
_Flag   MusicTrigFlag;


//file argument
uint8   MusicModePre;
_Flag   MusicChgFlag;

#if AL96
uint8   DwnCnt;
uint8   DwnTime;
uint8   DwnLevel;
uint8   RptCnt;
#elif AL92 | AL91 | AL95 | AL94
sint8   MusicReal;
sint8   MusicRealPre;
_Flag   MusicInit;
uint8   MusicModeCrt;
uint8   UpLevel;
uint8   DwnLevel;


#endif

//const color table
uint8 const MUSIC_COLOR[][3]={
  250,0,0,
  250,25,0,
  250,50,0,
  250,75,0,
  250,100,0,
  250,150,0,
  250,200,0,
  250,250,0,
  200,250,0,
  150,250,0,
  100,250,0,
  50,250,0,
  0,250,0,
  0,250,25,
  0,250,50,
  0,250,75,
  0,250,100,
  0,250,150,
  0,250,200,
  0,250,250,
  0,200,250,
  0,150,250,
  0,100,250,
  0,50,250,
  0,0,250,
  50,0,250,
  100,0,250,
  125,0,250,
  150,0,250,
  175,0,250,
  200,0,250,
  250,0,250,
  250,0,200,
  250,0,150,
  250,0,100,
  250,0,75,
  250,0,50,
  250,0,25,
  250,0,25,
  250,0,25,
  250,0,25,
};



uint8 const MUSIC_COLOR_MUL[13][3]=
{
  250,0,0,      		//0:red
  0,250,0,      		//1:green
  0,0,250,      		//2:blue
  250,50,0,     		//3:orange
  250,50,100,   		//4:pink
  0,250,50,     		//5:spring green
  250,150,0,    		//6:gold
  250,0,50,     		//7:peach
  100,200,0,    		//8:lawn green
  250,0,250,    		//9:Cyan
  0,250,250,    		//a:sky blue
  250,250,0,    		//b:yellow
  100,0,250,     		//c:purple
};

/**
  * Music_Mode
  */
void Music_Mode(void)
{
    uint8   temp = 0;
  
  if (MusicEnFlag == FALSE)     return;
  MusicEnTime++;
  if (MusicEnTime >= 250){
    MusicEnFlag = FALSE;
    DisplayData.Mode = 0xA;
    DisplayData.InitFlag = TRUE;
  }
  
  
//**************************************************************************************
#if AL96
//**************************************************************************************
  //Initialize
  if (DisplayData.InitFlag == TRUE){
    DisplayData.InitFlag = FALSE;
    
    DutyR = 0;
    DutyG = 0;
    DutyB = 0;
    DutyW = 0;
  }
  
 
  
  //----------------------------------------------------------------------------------------------------------
  if (MusicModePre < MusicMode || ((DwnCnt + 10) < MusicMode && RptCnt < 1)){
    MusicChgFlag = TRUE;
    if (MusicModePre == MusicMode){
      RptCnt++;
    }
    else{
      RptCnt = 0;
    }
    
    MusicModePre = MusicMode;
    DwnLevel = MusicMode; 
    DwnTime = 0; 
    DwnCnt = DwnLevel;
    DutyR = MUSIC_COLOR[DwnCnt][R];
    DutyG = MUSIC_COLOR[DwnCnt][G];
    DutyB = MUSIC_COLOR[DwnCnt][B];
  }
  
  if (MusicChgFlag == TRUE){
    if (DwnTime < 19 - DwnLevel / 2){
      DwnTime++;
    }
    else{
      DwnTime = 0;
      MusicChgFlag = FALSE;
    }
  }
  
  else
  {
    DwnTime++;
    if (DwnTime >= 2){
      DwnTime = 0;
      if (DwnCnt > 0){
        DutyR = MUSIC_COLOR[DwnCnt][R];
        DutyG = MUSIC_COLOR[DwnCnt][G];
        DutyB = MUSIC_COLOR[DwnCnt][B];
        DwnCnt--;
      }
      else{
        MusicModePre = 0;
        MusicMode = 0;
      }
    }
  }
  
//**************************************************************************************
#elif AL92 | AL95 | AL91 | AL94
//**************************************************************************************
  //Initialize
  if (DisplayData.InitFlag == TRUE){
    DisplayData.InitFlag = FALSE;
    
    #if AL92 | AL95
    for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++){
      for (TempLed = 0; TempLed < LED_MAX; TempLed++){
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR = 0;
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG = 0;
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB = 0;
      }
    }
    #else
    for (TempLed = 0; TempLed < LED_TOTAL; TempLed++){
      LedData.Buffer[TempLed].DutyR = 0;
      LedData.Buffer[TempLed].DutyG = 0;
      LedData.Buffer[TempLed].DutyB = 0;
    }
    #endif
    
    for (TempLed = 0; TempLed < LED_TOTAL; TempLed++){
      ModeTime[TempLed] = 0;
      ModeStep[TempLed] = 0;
      ModeLed[TempLed] = 0;
      ModeColor[TempLed] = 0;
    }
    
    TempColor = 0xff;
    
    HoldTime[0] = 0;
  }
  
  //to check the music mode
  if (MusicTrigFlag == TRUE){
    MusicTrigFlag = FALSE;
    MusicReal = (sint8)(MusicMode / 5);
    if (MusicRealPre <= MusicReal || (MusicModePre == 0 && MusicModePre < MusicMode))
    {
      if ((MusicReal == 3 || MusicReal == 5) && MusicReal == MusicRealPre && MusicChgFlag == TRUE)
      {
        MusicInit = FALSE;
      }
      else
      {
        MusicInit = TRUE;
      }
      MusicChgFlag = TRUE;
      
      MusicRealPre = MusicReal;
      MusicModePre = MusicMode;
      MusicModeCrt = MusicMode;
    }
  }
  
  temp = MusicModeCrt / 5;
  switch (temp){
    case 0:     Music_DO();         break;
    case 1:     Music_RE();         break;
    case 2:     Music_MI();         break;
    case 3:     Music_FA();         break;
    case 4:     Music_SO();         break;
    case 5:     Music_LA();         break;
    default:     Music_XI();         break;
  }
  
  
  
  
  
  
  
//**************************************************************************************
#endif
//**************************************************************************************  
}




#if AL92 | AL91 | AL94 | AL95
/**
  * FunctionName    Music_RE
  */
static void Music_RE(void)
{
  #if _AL92B_
  //---------------------------------------------------------------------------------------
  if (MusicInit == TRUE){
    MusicInit = FALSE;
    
    ModeTime[0] = 0;
    TempStep = 0;
  }
  
  
  if (MusicChgFlag == TRUE){
    ModeTime[0]++;
    if (ModeTime[0] >= 2){
      ModeTime[0] = 0;
      
      
      if (TempStep < 15){
        TempStep++;
        
        if (TempStep < 8){
          switch (TempStep)
          {
            case 1:		ModeLed[0] = 0;			ModeLed[1] = 7;			 ModeLed[2] = 14;	break;
            case 2:		ModeLed[0] = 1;			ModeLed[1] = 8;			 ModeLed[2] = 15;	break;
            case 3:		ModeLed[0] = 2;			ModeLed[1] = 9;			 ModeLed[2] = 16;	break;
            case 4:		ModeLed[0] = 3;			ModeLed[1] = 10;		 ModeLed[2] = 17;	break;
            case 5:		ModeLed[0] = 4;			ModeLed[1] = 11;		 ModeLed[2] = 18;	break;
            case 6:		ModeLed[0] = 5;			ModeLed[1] = 12;		 ModeLed[2] = 19;	break;
            case 7:		ModeLed[0] = 6;			ModeLed[1] = 13;		 ModeLed[2] = 20;	break;
          }
          
          for (TempLed = 0; TempLed < 3; TempLed++){
            LedData.Buffer[ModeLed[TempLed]].DutyR	= MUSIC_COLOR[MusicModeCrt][R];
            LedData.Buffer[ModeLed[TempLed]].DutyG	= MUSIC_COLOR[MusicModeCrt][G];
            LedData.Buffer[ModeLed[TempLed]].DutyB	= MUSIC_COLOR[MusicModeCrt][B];
          }
        }
      }
      
      else{
        TempStep = 0;
        MusicChgFlag = FALSE;
      }
    }
  }
  
  
  else{
    if (TempStep < 3){
      for (TempLed = 0; TempLed < LED_MAX; TempLed++){
        LedData.Buffer[TempStep * LED_MAX + TempLed].DutyR = 0;
        LedData.Buffer[TempStep * LED_MAX + TempLed].DutyG = 0;
        LedData.Buffer[TempStep * LED_MAX + TempLed].DutyB = 0;
      }
      TempStep++;
    }
    
    else{
      MusicModePre = 0;
      MusicMode = 0;
      MusicRealPre = -1;
      
    }
  }
  
  
  #elif _AL92C_
  //---------------------------------------------------------------------------------------
  if (MusicInit == TRUE){
    MusicInit = FALSE;
    
    ModeTime[0] = 0;
    TempStep = 0;
  }
  
  
  if (MusicChgFlag == TRUE){
    ModeTime[0]++;
    if (ModeTime[0] >= 1){
      ModeTime[0] = 0;
      
      
      if (TempStep < 15){
        TempStep++;
        if (TempStep < 13){
          switch (TempStep)
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
          
          for (TempLed = 0; TempLed < 2; TempLed++){
            LedData.Buffer[ModeLed[TempLed]].DutyR	= MUSIC_COLOR[MusicModeCrt][R];
            LedData.Buffer[ModeLed[TempLed]].DutyG	= MUSIC_COLOR[MusicModeCrt][G];
            LedData.Buffer[ModeLed[TempLed]].DutyB	= MUSIC_COLOR[MusicModeCrt][B];
          }
        }
      }
      
      else{
        TempStep = 0;
        MusicChgFlag = FALSE;
      }
    }
  }
  
  
  else{
    if (TempStep < 3){
      for (TempLed = 0; TempLed < LED_MAX; TempLed++){
        LedData.Buffer[TempStep * LED_MAX + TempLed].DutyR = 0;
        LedData.Buffer[TempStep * LED_MAX + TempLed].DutyG = 0;
        LedData.Buffer[TempStep * LED_MAX + TempLed].DutyB = 0;
      }
      TempStep++;
    }
    
    else{
      MusicModePre = 0;
      MusicMode = 0;
      MusicRealPre = -1;
      
    }
  }
  
  
  #elif _AL92A_
  //---------------------------------------------------------------------------------------
  if (MusicInit == TRUE){
    MusicInit = FALSE;
    
    ModeTime[0] = 0;
    TempStep = 0;
  }
  
  
  if (MusicChgFlag == TRUE){
    ModeTime[0]++;
    if (ModeTime[0] >= 2){
      ModeTime[0] = 0;
      
      
      if (TempStep < 15){
        TempStep++;
        if (TempStep < 7){
          
          for (TempLed = 0; TempLed < 4; TempLed++){
            LedData.Buffer[(TempStep - 1) * 4 + TempLed].DutyR	= MUSIC_COLOR[MusicModeCrt][R];
            LedData.Buffer[(TempStep - 1) * 4 + TempLed].DutyG	= MUSIC_COLOR[MusicModeCrt][G];
            LedData.Buffer[(TempStep - 1) * 4 + TempLed].DutyB	= MUSIC_COLOR[MusicModeCrt][B];
          }
        }
      }
      
      else{
        TempStep = 0;
        MusicChgFlag = FALSE;
      }
    }
  }
  
  
  else{
    if (TempStep < 6){
      for (TempLed = 0; TempLed < LED_MAX; TempLed++){
        LedData.Buffer[TempStep * LED_MAX + TempLed].DutyR = 0;
        LedData.Buffer[TempStep * LED_MAX + TempLed].DutyG = 0;
        LedData.Buffer[TempStep * LED_MAX + TempLed].DutyB = 0;
      }
      TempStep++;
    }
    
    else{
      MusicModePre = 0;
      MusicMode = 0;
      MusicRealPre = -1;
      
    }
  }
  
  
  #elif _AL95_
  //---------------------------------------------------------------------------------------
  if (MusicInit == TRUE){
    MusicInit = FALSE;
    
    ModeTime[0] = 0;
    TempStep = 0;
  }
  
  
  if (MusicChgFlag == TRUE){
    ModeTime[0]++;
    if (ModeTime[0] >= 2){
      ModeTime[0] = 0;
      
      
      if (TempStep < 8){
        TempStep++;
        if (TempStep < 4){
          LedData.Buffer[TempStep - 1].DutyR	= MUSIC_COLOR[MusicModeCrt][R];
          LedData.Buffer[TempStep - 1].DutyG	= MUSIC_COLOR[MusicModeCrt][G];
          LedData.Buffer[TempStep - 1].DutyB	= MUSIC_COLOR[MusicModeCrt][B];
        }
      }
      
      else {
        TempStep = 0;
        MusicChgFlag = FALSE;
      }
    }
  }
  
  
  else{
    if (TempStep < 3){
      LedData.Buffer[TempStep].DutyR = 0;
      LedData.Buffer[TempStep].DutyG = 0;
      LedData.Buffer[TempStep].DutyB = 0;
      TempStep++;
    }
    
    else{
      MusicModePre = 0;
      MusicMode = 0;
      MusicRealPre = -1;
      
    }
  }
  
  #elif AL91 | AL94 
  //-------------------------------------------------------------------------------
  if (MusicInit == TRUE){
    MusicInit = FALSE;
    
    ModeTime[0] = 0;
    TempStep = LED_TOTAL / 2;
    ModeColor[1]++;
    if (ModeColor[1] >= 0xC)    ModeColor[1] = 0;
    if (ModeColor[1] == TempColor){
      ModeColor[1]++;
      if (ModeColor[1] >= 0xC)    ModeColor[1] = 0;
    }
    TempColor = ModeColor[1];
  }
  
  
  if (MusicChgFlag == TRUE){
    ModeTime[0]++;
    if (ModeTime[0] >= 3){
      ModeTime[0] = 0;
      if (TempStep > 0){
        TempStep--;
        TempLed = TempStep;
        LedData.Buffer[TempLed].DutyR	= MUSIC_COLOR_MUL[TempColor][R];
        LedData.Buffer[TempLed].DutyG	= MUSIC_COLOR_MUL[TempColor][G];
        LedData.Buffer[TempLed].DutyB	= MUSIC_COLOR_MUL[TempColor][B];
        TempLed = LED_TOTAL - 1 - TempStep;
        LedData.Buffer[TempLed].DutyR	= MUSIC_COLOR_MUL[TempColor][R];
        LedData.Buffer[TempLed].DutyG	= MUSIC_COLOR_MUL[TempColor][G];
        LedData.Buffer[TempLed].DutyB	= MUSIC_COLOR_MUL[TempColor][B];
      }
      
      else {
        MusicChgFlag = FALSE;
        TempStep = LED_TOTAL / 2;
      }
    }
  }
  
  
  else{
    ModeTime[0]++;
    if (ModeTime[0] >= 2){
      ModeTime[0] = 0;
      if (TempStep > 0){
        TempStep--;
        TempLed = TempStep;
        LedData.Buffer[TempLed].DutyR	= 0;
        LedData.Buffer[TempLed].DutyG	= 0;
        LedData.Buffer[TempLed].DutyB	= 0;
        TempLed = LED_TOTAL - 1 - TempStep;
        LedData.Buffer[TempLed].DutyR	= 0;
        LedData.Buffer[TempLed].DutyG	= 0;
        LedData.Buffer[TempLed].DutyB	= 0;
        TempColor = 0xff;
      }
      
      else{
        MusicModePre = 0;
        MusicMode = 0;
        MusicRealPre = -1;
        
        
      }
    }
  }
  
  
  #endif
}


/**
  * FunctionName    Music_DO
  */
static void Music_DO(void)
{
  #if _AL92B_
  //-----------------------------------------------------------------------------------------
  
  if (MusicInit == TRUE){
    MusicInit = FALSE;
    
    UpLevel = MusicModeCrt;
    TempStep = 0;
    ModeTime[0] = 0;
  }
  
  
  
  if (MusicChgFlag == TRUE){
    if (TempStep < UpLevel){
      for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++){
        for (TempLed = 0; TempLed < LED_MAX; TempLed++){
          LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR = MUSIC_COLOR_[TempStep][R];
          LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG = MUSIC_COLOR[TempStep][G];
          LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB = MUSIC_COLOR[TempStep][B];
        }
      }
      TempStep++;
    }
    else{
      MusicChgFlag = FALSE;
      
      FadeR = MUSIC_COLOR[0][R] / 25;
      FadeG = MUSIC_COLOR[0][G] / 25;
      FadeB = MUSIC_COLOR[0][B] / 25;
    }
  }
  
  else{
    ModeTime[0]++;
    if (ModeTime[0] >= 1){
      ModeTime[0] = 0;
      
      if (TempStep > 0){
        TempStep--;
        for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++){
          for (TempLed = 0; TempLed < LED_MAX; TempLed++){
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR = MUSIC_COLOR[TempStep][R];
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG = MUSIC_COLOR[TempStep][G];
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB = MUSIC_COLOR[TempStep][B];
          }
        }
      }
      
      else if (LedData.Buffer[0].DutyR > 0 || LedData.Buffer[0].DutyG > 0 || LedData.Buffer[0].DutyB > 0){
        for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++){
          for (TempLed = 0; TempLed < LED_MAX; TempLed++){
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR -= FadeR;
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG -= FadeG;
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB -= FadeB;
          }
        }
      }
      
      else{
        MusicModePre = 0;
        MusicMode = 0;
        MusicRealPre = -1;
        
      }
    }
  }
  
  
  
  #elif _AL92C_
  //-----------------------------------------------------------------------------------------
  
  if (MusicInit == TRUE){
    MusicInit = FALSE;
    
    UpLevel = MusicModeCrt;
    TempStep = 0;
    ModeTime[0] = 0;
  }
  
  
  
  if (MusicChgFlag == TRUE){
    if (TempStep < UpLevel){
      for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++){
        for (TempLed = 0; TempLed < LED_MAX; TempLed++){
          LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR = MUSIC_COLOR[TempStep][R];
          LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG = MUSIC_COLOR[TempStep][G];
          LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB = MUSIC_COLOR[TempStep][B];
        }
      }
      TempStep++;
    }
    else{
      MusicChgFlag = FALSE;
      
      FadeR = MUSIC_COLOR[0][R] / 25;
      FadeG = MUSIC_COLOR[0][G] / 25;
      FadeB = MUSIC_COLOR[0][B] / 25;
    }
  }
  
  else{
    ModeTime[0]++;
    if (ModeTime[0] >= 2){
      ModeTime[0] = 0;
      
      if (TempStep > 0){
        TempStep--;
        for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++){
          for (TempLed = 0; TempLed < LED_MAX; TempLed++){
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR = MUSIC_COLOR[TempStep][R];
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG = MUSIC_COLOR[TempStep][G];
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB = MUSIC_COLOR[TempStep][B];
          }
        }
      }
      
      else if (LedData.Buffer[0].DutyR > 0 || LedData.Buffer[0].DutyG > 0 || LedData.Buffer[0].DutyB > 0){
        for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++){
          for (TempLed = 0; TempLed < LED_MAX; TempLed++){
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR -= FadeR;
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG -= FadeG;
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB -= FadeB;
          }
        }
      }
      
      else{
        MusicModePre = 0;
        MusicMode = 0;
        MusicRealPre = -1;
        
      }
    }
  }
  
  
  #elif _AL92A_
  //-----------------------------------------------------------------------------------------
  
  if (MusicInit == TRUE){
    MusicInit = FALSE;
    
    UpLevel = MusicModeCrt;
    TempStep = 0;
    ModeTime[0] = 0;
  }
  
  
  
  if (MusicChgFlag == TRUE){
    if (TempStep < UpLevel){
      for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++){
        for (TempLed = 0; TempLed < LED_MAX; TempLed++){
          LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR = MUSIC_COLOR[TempStep][R];
          LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG = MUSIC_COLOR[TempStep][G];
          LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB = MUSIC_COLOR[TempStep][B];
        }
      }
      TempStep++;
    }
    else{
      MusicChgFlag = FALSE;
      
      FadeR = MUSIC_COLOR[0][R] / 25;
      FadeG = MUSIC_COLOR[0][G] / 25;
      FadeB = MUSIC_COLOR[0][B] / 25;
    }
  }
  
  else{
    ModeTime[0]++;
    if (ModeTime[0] >= 2){
      ModeTime[0] = 0;
      
      if (TempStep > 0){
        TempStep--;
        for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++){
          for (TempLed = 0; TempLed < LED_MAX; TempLed++){
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR = MUSIC_COLOR[TempStep][R];
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG = MUSIC_COLOR[TempStep][G];
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB = MUSIC_COLOR[TempStep][B];
          }
        }
      }
      
      else if (LedData.Buffer[0].DutyR > 0 || LedData.Buffer[0].DutyG > 0 || LedData.Buffer[0].DutyB > 0){
        for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++){
          for (TempLed = 0; TempLed < LED_MAX; TempLed++){
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR -= FadeR;
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG -= FadeG;
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB -= FadeB;
          }
        }
      }
      
      else{
        MusicModePre = 0;
        MusicMode = 0;
        MusicRealPre = -1;
        
      }
    }
  }
  
  
  #elif _AL95_
  //-----------------------------------------------------------------------------------------
  
  if (MusicInit == TRUE){
    MusicInit = FALSE;
    
    UpLevel = MusicModeCrt;
    TempStep = 0;
    ModeTime[0] = 0;
  }
  
  
  
  if (MusicChgFlag == TRUE){
    if (TempStep < UpLevel){
      for (TempLed = 0; TempLed < GRP_MAX; TempLed++){
        LedData.Buffer[TempLed].DutyR = MUSIC_COLOR[TempStep][R];
        LedData.Buffer[TempLed].DutyG = MUSIC_COLOR[TempStep][G];
        LedData.Buffer[TempLed].DutyB = MUSIC_COLOR[TempStep][B];
      }
      TempStep++;
    }
    else{
      MusicChgFlag = FALSE;
      
      FadeR = MUSIC_COLOR[0][R] / 25;
      FadeG = MUSIC_COLOR[0][G] / 25;
      FadeB = MUSIC_COLOR[0][B] / 25;
    }
  }
  
  else{
    ModeTime[0]++;
    if (ModeTime[0] >= 2){
      ModeTime[0] = 0;
      
      if (TempStep > 0){
        TempStep--;
        for (TempLed = 0; TempLed < GRP_MAX; TempLed++){
          LedData.Buffer[TempLed].DutyR = MUSIC_COLOR[TempStep][R];
          LedData.Buffer[TempLed].DutyG = MUSIC_COLOR[TempStep][G];
          LedData.Buffer[TempLed].DutyB = MUSIC_COLOR[TempStep][B];
        }
      }
      
      else if (LedData.Buffer[0].DutyR > 0 || LedData.Buffer[0].DutyG > 0 || LedData.Buffer[0].DutyB > 0){
        for (TempLed = 0; TempLed < GRP_MAX; TempLed++){
          LedData.Buffer[TempLed].DutyR -= FadeR;
          LedData.Buffer[TempLed].DutyG -= FadeG;
          LedData.Buffer[TempLed].DutyB -= FadeB;
        }
      }
      
      else{
        MusicModePre = 0;
        MusicMode = 0;
        MusicRealPre = -1;
        
      }
    }
  }
	
	
	#elif AL91 | AL94
  //-----------------------------------------------------------------------------------------
  
  if (MusicInit == TRUE){
    MusicInit = FALSE;
    
    UpLevel = MusicModeCrt / 3;
    if (UpLevel > 13) UpLevel = 13;
    TempStep = 0;
    ModeTime[0] = 0;
    
    FadeR = MUSIC_COLOR_MUL[UpLevel][R] / 25;
    FadeG = MUSIC_COLOR_MUL[UpLevel][G] / 25;
    FadeB = MUSIC_COLOR_MUL[UpLevel][B] / 25;
  }
  
  
  
  if (MusicChgFlag == TRUE){
    ModeTime[0]++;
    if (ModeTime[0] >= 1){
      ModeTime[0] = 0;
      
      if (TempStep < 25){
        TempStep++;
        for (TempLed = 0; TempLed < LED_TOTAL; TempLed++){
          LedData.Buffer[TempLed].DutyR = TempStep * FadeR;
          LedData.Buffer[TempLed].DutyG = TempStep * FadeG;
          LedData.Buffer[TempLed].DutyB = TempStep * FadeB;
        }
      }
      else{
        MusicChgFlag = FALSE;
      }
    }
  }
  
  else{
    for (TempLed = 0; TempLed < LED_TOTAL; TempLed++){
      LedData.Buffer[TempLed].DutyR = 0;
      LedData.Buffer[TempLed].DutyG = 0;
      LedData.Buffer[TempLed].DutyB = 0;
    }
    MusicModePre = 0;
    MusicMode = 0;
    MusicRealPre = -1;
    
  }
  
  #endif
}


/**
  * FunctionName    Music_MT
  */
static void Music_MI(void)
{
  #if _AL92B_
  //--------------------------------------------------------------------------
  if (MusicInit == TRUE){
    MusicInit = FALSE;
    
    TempStep = 0;
    ModeTime[0] = 0;
    UpLevel = MusicModeCrt;
  }
  
  
  
  if (MusicChgFlag == TRUE){
    
    ModeTime[0]++;
    if (ModeTime[0] >= 15){
      ModeTime[0] = 0;
      if (TempStep < 3){
        TempStep++;
      }
      else{
        MusicChgFlag = FALSE;
      }
    }
    
    switch (TempStep){
      case 0:
      case 2:{
        for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++){
          for (TempLed = 0; TempLed < LED_MAX; TempLed++){
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR = MUSIC_COLOR[UpLevel][R];
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG = MUSIC_COLOR[UpLevel][G];
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB = MUSIC_COLOR[UpLevel][B];
          }
        }
      } break;
      
      case 1:
      case 3:{
        for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++){
          for (TempLed = 0; TempLed < LED_MAX; TempLed++){
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR = 0;
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG = 0;
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB = 0;
          }
        }
      } break;
    }
  }
  
  else{
    for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++){
      for (TempLed = 0; TempLed < LED_MAX; TempLed++){
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR = 0;
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG = 0;
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB = 0;
      }
    }
    MusicModePre = 0;
    MusicMode = 0;
    MusicRealPre = -1;
    
  }
  
  
  #elif _AL92C_
  //--------------------------------------------------------------------------
  if (MusicInit == TRUE){
    MusicInit = FALSE;
    
    TempStep = 0;
    ModeTime[0] = 0;
    UpLevel = MusicModeCrt;
  }
  
  
  
  if (MusicChgFlag == TRUE){
    
    ModeTime[0]++;
    if (ModeTime[0] >= 15){
      ModeTime[0] = 0;
      if (TempStep < 3){
        TempStep++;
      }
      else{
        MusicChgFlag = FALSE;
      }
    }
    
    switch (TempStep){
      case 0:
      case 2:{
        for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++){
          for (TempLed = 0; TempLed < LED_MAX; TempLed++){
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR = MUSIC_COLOR[UpLevel][R];
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG = MUSIC_COLOR[UpLevel][G];
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB = MUSIC_COLOR[UpLevel][B];
          }
        }
      } break;
      
      case 1:
      case 3:{
        for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++){
          for (TempLed = 0; TempLed < LED_MAX; TempLed++){
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR = 0;
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG = 0;
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB = 0;
          }
        }
      } break;
    }
  }
  
  else{
    for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++){
      for (TempLed = 0; TempLed < LED_MAX; TempLed++){
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR = 0;
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG = 0;
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB = 0;
      }
    }
    MusicModePre = 0;
    MusicMode = 0;
    MusicRealPre = -1;
    
  }
  
  
  #elif _AL92A_
  //--------------------------------------------------------------------------
  if (MusicInit == TRUE){
    MusicInit = FALSE;
    
    TempStep = 0;
    ModeTime[0] = 0;
    UpLevel = MusicModeCrt;
  }
  
  
  
  if (MusicChgFlag == TRUE){
    
    ModeTime[0]++;
    if (ModeTime[0] >= 15){
      ModeTime[0] = 0;
      if (TempStep < 3){
        TempStep++;
      }
      else{
        MusicChgFlag = FALSE;
      }
    }
    
    switch (TempStep){
      case 0:
      case 2:{
        for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++){
          for (TempLed = 0; TempLed < LED_MAX; TempLed++){
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR = MUSIC_COLOR[UpLevel][R];
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG = MUSIC_COLOR[UpLevel][G];
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB = MUSIC_COLOR[UpLevel][B];
          }
        }
      } break;
      
      case 1:
      case 3:{
        for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++){
          for (TempLed = 0; TempLed < LED_MAX; TempLed++){
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR = 0;
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG = 0;
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB = 0;
          }
        }
      } break;
    }
  }
  
  else{
    for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++){
      for (TempLed = 0; TempLed < LED_MAX; TempLed++){
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR = 0;
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG = 0;
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB = 0;
      }
    }
    MusicModePre = 0;
    MusicMode = 0;
    MusicRealPre = -1;
    
  }
  
  
  #elif _AL95_
  //--------------------------------------------------------------------------
  if (MusicInit == TRUE){
    MusicInit = FALSE;
    
    TempStep = 0;
    ModeTime[0] = 0;
    UpLevel = MusicModeCrt;
  }
  
  
  
  if (MusicChgFlag == TRUE){
    
    ModeTime[0]++;
    if (ModeTime[0] >= 15){
      ModeTime[0] = 0;
      if (TempStep < 3){
        TempStep++;
      }
      else{
        MusicChgFlag = FALSE;
      }
    }
    
    switch (TempStep){
      case 0:
      case 2:{
        for (TempLed = 0; TempLed < GRP_MAX; TempLed++){
          LedData.Buffer[TempLed].DutyR = MUSIC_COLOR[UpLevel][R];
          LedData.Buffer[TempLed].DutyG = MUSIC_COLOR[UpLevel][G];
          LedData.Buffer[TempLed].DutyB = MUSIC_COLOR[UpLevel][B];
        }
      } break;
      
      case 1:
      case 3:{
        for (TempLed = 0; TempLed < GRP_MAX; TempLed++){
          LedData.Buffer[TempLed].DutyR = 0;
          LedData.Buffer[TempLed].DutyG = 0;
          LedData.Buffer[TempLed].DutyB = 0;
        }
      } break;
    }
  }
  
  else{
    for (TempLed = 0; TempLed < GRP_MAX; TempLed++){
      LedData.Buffer[TempLed].DutyR = 0;
      LedData.Buffer[TempLed].DutyG = 0;
      LedData.Buffer[TempLed].DutyB = 0;
    }
    MusicModePre = 0;
    MusicMode = 0;
    MusicRealPre = -1;
    
  }
	
	
	#elif AL91 | AL94
  //--------------------------------------------------------------------------
  if (MusicInit == TRUE){
    MusicInit = FALSE;
    
    TempStep = 0;
    ModeTime[0] = 0;
    UpLevel = MusicModeCrt;
    ModeColor[2]++;
    if (ModeColor[2] >= 0xC)    ModeColor[2] = 0;
    if (ModeColor[2] == TempColor){
      ModeColor[2]++;
      if (ModeColor[2] >= 0xC)    ModeColor[2] = 0;
    }
    TempColor = ModeColor[2];
  }
  
  
  
  if (MusicChgFlag == TRUE){
    
    ModeTime[0]++;
    if (ModeTime[0] >= 15){
      ModeTime[0] = 0;
      MusicChgFlag = FALSE;
      TempStep = 0;
    }
    
    for (TempLed = 0; TempLed < LED_TOTAL; TempLed++){
      LedData.Buffer[TempLed].DutyR = MUSIC_COLOR_MUL[TempColor][R];
      LedData.Buffer[TempLed].DutyG = MUSIC_COLOR_MUL[TempColor][G];
      LedData.Buffer[TempLed].DutyB = MUSIC_COLOR_MUL[TempColor][B];
    }
  }
  
  else{
    for (TempLed = 0; TempLed < LED_TOTAL; TempLed++){
      LedData.Buffer[TempLed].DutyR = 0;
      LedData.Buffer[TempLed].DutyG = 0;
      LedData.Buffer[TempLed].DutyB = 0;
    }
    TempColor = 0xff;
    MusicModePre = 0;
    MusicMode = 0;
    MusicRealPre = -1;
    
  }
  
  #endif
}


/**
  * FunctionName    Music_FA
  */
static void Music_FA(void)
{
  #if _AL92B_
  //---------------------------------------------------------------------------------
  if (MusicInit == TRUE){
    MusicInit = FALSE;
    
    TempStep = 0;
    ModeTime[0] = 0;
    UpLevel = MusicModeCrt;
  }
  
  
  
  if (MusicChgFlag == TRUE){
    
    ModeTime[0]++;
    if (ModeTime[0] >= 5){
      ModeTime[0] = 0;
      
      if (TempStep < 6){
        TempStep++;
      }
    }
    
    if (TempStep < 3){
      TempGrp = TempStep;
      for (TempLed = 0; TempLed < LED_MAX; TempLed++){
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR = MUSIC_COLOR[UpLevel][R];
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG = MUSIC_COLOR[UpLevel][G];
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB = MUSIC_COLOR[UpLevel][B];
      }
    }
    
    else if (TempStep < 6){
      TempGrp = TempStep - 3;
      for (TempLed = 0; TempLed < LED_MAX; TempLed++){
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR = 0;
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG = 0;
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB = 0;
      }
    }
    else{
      MusicModePre = 0;
      MusicMode = 0;
      MusicRealPre = -1;
      
      MusicChgFlag = FALSE;
    }
  }
  
  
  #elif _AL92C_
  //---------------------------------------------------------------------------------
  if (MusicInit == TRUE){
    MusicInit = FALSE;
    
    TempStep = 0;
    ModeTime[0] = 0;
    UpLevel = MusicModeCrt;
  }
  
  
  
  if (MusicChgFlag == TRUE){
    
    ModeTime[0]++;
    if (ModeTime[0] >= 5){
      ModeTime[0] = 0;
      
      if (TempStep < 6){
        TempStep++;
      }
    }
    
    if (TempStep < 3){
      TempGrp = TempStep;
      for (TempLed = 0; TempLed < LED_MAX; TempLed++){
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR = MUSIC_COLOR[UpLevel][R];
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG = MUSIC_COLOR[UpLevel][G];
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB = MUSIC_COLOR[UpLevel][B];
      }
    }
    
    else if (TempStep < 6){
      TempGrp = TempStep - 3;
      for (TempLed = 0; TempLed < LED_MAX; TempLed++){
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR = 0;
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG = 0;
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB = 0;
      }
    }
    else{
      MusicModePre = 0;
      MusicMode = 0;
      MusicRealPre = -1;
      
      MusicChgFlag = FALSE;
    }
  }
  
  
  #elif _AL92A_
  //---------------------------------------------------------------------------------
  if (MusicInit == TRUE){
    MusicInit = FALSE;
    
    TempStep = 0;
    ModeTime[0] = 0;
    UpLevel = MusicModeCrt;
  }
  
  
  
  if (MusicChgFlag == TRUE){
    
    ModeTime[0]++;
    if (ModeTime[0] >= 2){
      ModeTime[0] = 0;
      
      if (TempStep < 12){
        TempStep++;
      }
    }
    
    if (TempStep < 6){
      TempGrp = TempStep;
      for (TempLed = 0; TempLed < LED_MAX; TempLed++){
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR = MUSIC_COLOR[UpLevel][R];
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG = MUSIC_COLOR[UpLevel][G];
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB = MUSIC_COLOR[UpLevel][B];
      }
    }
    
    else if (TempStep < 12){
      TempGrp = TempStep - 6;
      for (TempLed = 0; TempLed < LED_MAX; TempLed++){
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR = 0;
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG = 0;
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB = 0;
      }
    }
    else{
      MusicModePre = 0;
      MusicMode = 0;
      MusicRealPre = -1;
      
      MusicChgFlag = FALSE;
    }
  }
  
  #elif _AL95_
  //---------------------------------------------------------------------------------
  if (MusicInit == TRUE){
    MusicInit = FALSE;
    
    TempStep = 0;
    ModeTime[0] = 0;
    UpLevel = MusicModeCrt;
  }
  
  
  
  if (MusicChgFlag == TRUE){
    
    ModeTime[0]++;
    if (ModeTime[0] >= 2){
      ModeTime[0] = 0;
      
      if (TempStep < 6){
        TempStep++;
      }
    }
    
    if (TempStep < 3){
      TempLed = TempStep;
      LedData.Buffer[TempLed].DutyR = MUSIC_COLOR[UpLevel][R];
      LedData.Buffer[TempLed].DutyG = MUSIC_COLOR[UpLevel][G];
      LedData.Buffer[TempLed].DutyB = MUSIC_COLOR[UpLevel][B];
    }
    
    else if (TempStep < 6){
      TempLed = TempStep - 3;
      LedData.Buffer[TempLed].DutyR = 0;
      LedData.Buffer[TempLed].DutyG = 0;
      LedData.Buffer[TempLed].DutyB = 0;
    }
    else{
      MusicModePre = 0;
      MusicMode = 0;
      MusicRealPre = -1;
      
      MusicChgFlag = FALSE;
    }
  }
	
	
	#elif AL91 | AL94
  //---------------------------------------------------------------------------------
  if (MusicInit == TRUE){
    MusicInit = FALSE;
    
    TempStep = 0;
    ModeTime[0] = 0;
    UpLevel = MusicModeCrt;
    ModeStep[0] = 0;
    ModeColor[3]++;
    if (ModeColor[3] >= 0xC)    ModeColor[3] = 0;
  }
  
  
  
  if (MusicChgFlag == TRUE){ 
		ModeTime[0]++;
		if (ModeTime[0] >= 4){
			ModeTime[0] = 0;
			
			if (TempStep < 12){
				if (TempStep < 6){
					TempGrp = TempStep;
					for (TempLed = 0; TempLed < LED_TOTAL; TempLed++){
						if ((TempLed % 6) == TempGrp){
							LedData.Buffer[TempLed].DutyR = MUSIC_COLOR_MUL[ModeColor[3]][R];
							LedData.Buffer[TempLed].DutyG = MUSIC_COLOR_MUL[ModeColor[3]][G];
							LedData.Buffer[TempLed].DutyB = MUSIC_COLOR_MUL[ModeColor[3]][B];
						}
					}
				}
				
				else if (TempStep < 12){
					TempGrp = TempStep - 6;
					for (TempLed = 0; TempLed < LED_TOTAL; TempLed++){
						if ((TempLed % 6) == TempGrp){
							LedData.Buffer[TempLed].DutyR = 0;
							LedData.Buffer[TempLed].DutyG = 0;
							LedData.Buffer[TempLed].DutyB = 0;
						}
					}
				}
				TempStep++;
			}
			
			else{
        for (TempLed = 0; TempLed < LED_TOTAL; TempLed++){
          LedData.Buffer[TempLed].DutyR = 0;
          LedData.Buffer[TempLed].DutyG = 0;
          LedData.Buffer[TempLed].DutyB = 0;
        }
        MusicChgFlag = FALSE;
      }
		}
  }
  else{
    MusicModePre = 0;
    MusicMode = 0;
    MusicRealPre = -1;
    
  }
  
  
  
  #endif
}


/**
  * FunctionName    Music_SO
  */
static void Music_SO(void)
{
  #if _AL92B_
  //-------------------------------------------------------------------------------
  if (MusicChgFlag == TRUE){
    
    ModeTime[0]++;
    if (ModeTime[0] >= 5){
      ModeTime[0] = 0;
      
      if (TempStep < 6){
        TempStep++;
      }
    }
    
    if (TempStep < 3){
      TempGrp = 2 - TempStep;
      for (TempLed = 0; TempLed < LED_MAX; TempLed++){
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR = MUSIC_COLOR[UpLevel][R];
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG = MUSIC_COLOR[UpLevel][G];
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB = MUSIC_COLOR[UpLevel][B];
      }
    }
    
    else if (TempStep < 6){
      TempGrp = 5 - TempStep;
      for (TempLed = 0; TempLed < LED_MAX; TempLed++){
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR = 0;
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG = 0;
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB = 0;
      }
    }
    else{
      MusicModePre = 0;
      MusicMode = 0;
      MusicRealPre = -1;
      
      MusicChgFlag = FALSE;
    }
  }
  
  
  #elif _AL92C_
  //-------------------------------------------------------------------------------
  if (MusicChgFlag == TRUE){
    
    ModeTime[0]++;
    if (ModeTime[0] >= 5){
      ModeTime[0] = 0;
      
      if (TempStep < 6){
        TempStep++;
      }
    }
    
    if (TempStep < 3){
      TempGrp = 2 - TempStep;
      for (TempLed = 0; TempLed < LED_MAX; TempLed++){
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR = MUSIC_COLOR[UpLevel][R];
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG = MUSIC_COLOR[UpLevel][G];
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB = MUSIC_COLOR[UpLevel][B];
      }
    }
    
    else if (TempStep < 6){
      TempGrp = 5 - TempStep;
      for (TempLed = 0; TempLed < LED_MAX; TempLed++){
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR = 0;
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG = 0;
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB = 0;
      }
    }
    else{
      MusicModePre = 0;
      MusicMode = 0;
      MusicRealPre = -1;
      
      MusicChgFlag = FALSE;
    }
  }
  
  
  #elif _AL92A_
  //-------------------------------------------------------------------------------
  if (MusicChgFlag == TRUE){
    
    ModeTime[0]++;
    if (ModeTime[0] >= 2){
      ModeTime[0] = 0;
      
      if (TempStep < 12){
        TempStep++;
      }
    }
    
    if (TempStep < 6){
      TempGrp = 5 - TempStep;
      for (TempLed = 0; TempLed < LED_MAX; TempLed++){
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR = MUSIC_COLOR[UpLevel][R];
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG = MUSIC_COLOR[UpLevel][G];
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB = MUSIC_COLOR[UpLevel][B];
      }
    }
    
    else if (TempStep < 12){
      TempGrp = 11 - TempStep;
      for (TempLed = 0; TempLed < LED_MAX; TempLed++){
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR = 0;
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG = 0;
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB = 0;
      }
    }
    else{
      MusicModePre = 0;
      MusicMode = 0;
      MusicRealPre = -1;
      
      MusicChgFlag = FALSE;
    }
  }
  
  
  #elif _AL95_
  //-------------------------------------------------------------------------------
  if (MusicChgFlag == TRUE){
    
    ModeTime[0]++;
    if (ModeTime[0] >= 5){
      ModeTime[0] = 0;
      
      if (TempStep < 6){
        TempStep++;
      }
    }
    
    if (TempStep < 3){
      TempLed = 2 - TempStep;
      LedData.Buffer[TempLed].DutyR = MUSIC_COLOR[UpLevel][R];
      LedData.Buffer[TempLed].DutyG = MUSIC_COLOR[UpLevel][G];
      LedData.Buffer[TempLed].DutyB = MUSIC_COLOR[UpLevel][B];
    }
    
    else if (TempStep < 6){
      TempLed = 5 - TempStep;
      LedData.Buffer[TempLed].DutyR = 0;
      LedData.Buffer[TempLed].DutyG = 0;
      LedData.Buffer[TempLed].DutyB = 0;
    }
    else{
      MusicModePre = 0;
      MusicMode = 0;
      MusicRealPre = -1;
      
      MusicChgFlag = FALSE;
    }
  }
  
	
	#elif AL91 | AL94
  //---------------------------------------------------------------------------------
  if (MusicInit == TRUE){
    MusicInit = FALSE;
    
    TempStep = 0;
    ModeTime[0] = 0;
    UpLevel = MusicModeCrt;
    ModeColor[4]++;
    if (ModeColor[4] >= 0xC)    ModeColor[4] = 0;
  }
  
  
  
  if (MusicChgFlag == TRUE){ 
    switch (TempStep){
      case 0:{
        for (TempLed = 0; TempLed < LED_TOTAL; TempLed++){
          if ((TempLed % 2) == 0){
            LedData.Buffer[TempLed].DutyR = MUSIC_COLOR_MUL[ModeColor[4]][R];
            LedData.Buffer[TempLed].DutyG = MUSIC_COLOR_MUL[ModeColor[4]][G];
            LedData.Buffer[TempLed].DutyB = MUSIC_COLOR_MUL[ModeColor[4]][B];
          }
        }
        
        ModeTime[0]++;
        if (ModeTime[0] >= 12){
          ModeTime[0] = 0;
          TempStep++;
          ModeColor[4]++;
          if (ModeColor[4] >= 0xC)    ModeColor[4] = 0;
          TempColor = ModeColor[4];
        }
      } break;
    
      case 1:{
        for (TempLed = 0; TempLed < LED_TOTAL; TempLed++){
          if ((TempLed % 2) == 1){
            LedData.Buffer[TempLed].DutyR = MUSIC_COLOR_MUL[ModeColor[4]][R];
            LedData.Buffer[TempLed].DutyG = MUSIC_COLOR_MUL[ModeColor[4]][G];
            LedData.Buffer[TempLed].DutyB = MUSIC_COLOR_MUL[ModeColor[4]][B];
          }
        }
        
        ModeTime[0]++;
        if (ModeTime[0] >= 8){
          ModeTime[0] = 16;
          TempStep++;
          ModeColor[4]++;
          if (ModeColor[4] >= 0xC)    ModeColor[4] = 0;
          TempColor = ModeColor[4];
        }
      } break;
      
      case 2:{
        for (TempLed = 0; TempLed < LED_TOTAL; TempLed++){
          LedData.Buffer[TempLed].DutyR = MUSIC_COLOR_MUL[ModeColor[4]][R];
          LedData.Buffer[TempLed].DutyG = MUSIC_COLOR_MUL[ModeColor[4]][G];
          LedData.Buffer[TempLed].DutyB = MUSIC_COLOR_MUL[ModeColor[4]][B];
        }
        
        ModeTime[0]++;
        if (ModeTime[0] >= 8){
          ModeTime[0] = 16;
          TempStep++;
          FadeR = MUSIC_COLOR_MUL[ModeColor[4]][R] / 25;
          FadeG = MUSIC_COLOR_MUL[ModeColor[4]][G] / 25;
          FadeB = MUSIC_COLOR_MUL[ModeColor[4]][B] / 25;
        }
      } break;
      
      default:{
        if (LedData.Buffer[0].DutyR > 0 || LedData.Buffer[0].DutyG > 0 || LedData.Buffer[0].DutyB > 0){
          for (TempLed = 0; TempLed < LED_TOTAL; TempLed++){
            LedData.Buffer[TempLed].DutyR -= FadeR;
            LedData.Buffer[TempLed].DutyG -= FadeG;
            LedData.Buffer[TempLed].DutyB -= FadeB;
          }
        }
        
        if (LedData.Buffer[0].DutyR > 0 || LedData.Buffer[0].DutyG > 0 || LedData.Buffer[0].DutyB > 0){
          for (TempLed = 0; TempLed < LED_TOTAL; TempLed++){
            LedData.Buffer[TempLed].DutyR -= FadeR;
            LedData.Buffer[TempLed].DutyG -= FadeG;
            LedData.Buffer[TempLed].DutyB -= FadeB;
          }
        }
        
        if (LedData.Buffer[0].DutyR == 0 && LedData.Buffer[0].DutyG == 0 && LedData.Buffer[0].DutyB == 0){
          MusicModePre = 0;
          MusicMode = 0;
          MusicRealPre = -1;
          
          TempColor = 0xff;
        }
      } break;
    }
  }
  
  
  #endif
}


/**
  * FunctionName    Music_LA
  */
static void Music_LA(void)
{
  #if _AL92B_
  //------------------------------------------------------------------------
  if (MusicInit == TRUE){
    MusicInit = FALSE;
    
    UpLevel = MusicModeCrt;
    TempStep = 0;
    ModeTime[0] = 0;
    ModeStep[0] = 0;
  }
  
  
  
  if (MusicChgFlag == TRUE){
    ModeTime[0]++;
    if (ModeTime[0] >= 2){
      ModeTime[0] = 0;
      if (TempStep < UpLevel){
        for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++){
          for (TempLed = 0; TempLed < LED_MAX; TempLed++){
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR = MUSIC_COLOR[TempStep][R];
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG = MUSIC_COLOR[TempStep][G];
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB = MUSIC_COLOR[TempStep][B];
          }
        }
        TempStep++;
      }
      else{
        MusicChgFlag = FALSE;
        TempStep = 0;
      }
    }
  }
  
  else{
    ModeTime[0]++;
    if (ModeTime[0] >= 1){
      ModeTime[0] = 0;
      
      if (TempStep < 7){
        TempStep++;
          switch (TempStep)
          {
            case 1:		ModeLed[0] = 0;			ModeLed[1] = 7;			 ModeLed[2] = 14;	break;
            case 2:		ModeLed[0] = 1;			ModeLed[1] = 8;			 ModeLed[2] = 15;	break;
            case 3:		ModeLed[0] = 2;			ModeLed[1] = 9;			 ModeLed[2] = 16;	break;
            case 4:		ModeLed[0] = 3;			ModeLed[1] = 10;		 ModeLed[2] = 17;	break;
            case 5:		ModeLed[0] = 4;			ModeLed[1] = 11;		 ModeLed[2] = 18;	break;
            case 6:		ModeLed[0] = 5;			ModeLed[1] = 12;		 ModeLed[2] = 19;	break;
            case 7:		ModeLed[0] = 6;			ModeLed[1] = 13;		 ModeLed[2] = 20;	break;
          }
          
          LedData.Buffer[ModeLed[ModeStep[0]]].DutyR	= 0;
          LedData.Buffer[ModeLed[ModeStep[0]]].DutyG	= 0;
          LedData.Buffer[ModeLed[ModeStep[0]]].DutyB	= 0;
      }
      
      else{
        if (ModeStep[0] < 2){
          ModeStep[0]++;
          TempStep = 0;
        }
        else{
          MusicMode = 0;
          MusicModePre = 0;
          MusicRealPre = -1;
          
        }
      }
    }
  }
  
  
  #elif _AL92C_
  //------------------------------------------------------------------------
  if (MusicInit == TRUE){
    MusicInit = FALSE;
    
    UpLevel = MusicModeCrt;
    TempStep = 0;
    ModeTime[0] = 0;
    ModeStep[0] = 0;
  }
  
  
  
  if (MusicChgFlag == TRUE){
    ModeTime[0]++;
    if (ModeTime[0] >= 2){
      ModeTime[0] = 0;
      if (TempStep < UpLevel){
        for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++){
          for (TempLed = 0; TempLed < LED_MAX; TempLed++){
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR = MUSIC_COLOR[TempStep][R];
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG = MUSIC_COLOR[TempStep][G];
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB = MUSIC_COLOR[TempStep][B];
          }
        }
        TempStep++;
      }
      else{
        MusicChgFlag = FALSE;
        TempStep = 0;
      }
    }
  }
  
  else{
    ModeTime[0]++;
    if (ModeTime[0] >= 1){
      ModeTime[0] = 0;
      
      if (TempStep < 15){
        TempStep++;
        if (TempStep < 13){
          switch (TempStep)
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
          
          LedData.Buffer[ModeLed[0]].DutyR = 0;
          LedData.Buffer[ModeLed[0]].DutyG = 0;
          LedData.Buffer[ModeLed[0]].DutyB = 0;
          
          LedData.Buffer[ModeLed[1]].DutyR = 0;
          LedData.Buffer[ModeLed[1]].DutyG = 0;
          LedData.Buffer[ModeLed[1]].DutyB = 0;
        }
      }
      
      else{
        MusicMode = 0;
        MusicModePre = 0;
        MusicRealPre = -1;
        
      }
    }
  }
  
	#elif _AL92A_
  //------------------------------------------------------------------------
  if (MusicInit == TRUE){
    MusicInit = FALSE;
    
    UpLevel = MusicModeCrt;
    TempStep = 0;
    ModeTime[0] = 0;
    ModeStep[0] = 0;
  }
  
  if (MusicChgFlag == TRUE){
    ModeTime[0]++;
    if (ModeTime[0] >= 2){
      ModeTime[0] = 0;
      if (TempStep < UpLevel){
        for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++){
          for (TempLed = 0; TempLed < LED_MAX; TempLed++){
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR = MUSIC_COLOR[TempStep][R];
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG = MUSIC_COLOR[TempStep][G];
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB = MUSIC_COLOR[TempStep][B];
          }
        }
        TempStep++;
      }
      else{
        MusicChgFlag = FALSE;
        TempStep = 0;
      }
    }
  }
  
  else{
    ModeTime[0]++;
    if (ModeTime[0] >= 1){
      ModeTime[0] = 0;
      
      if (TempStep < 4){
        TempLed = ModeStep[0] * LED_MAX + 3 - TempStep;  
        LedData.Buffer[TempLed].DutyR	= 0;
        LedData.Buffer[TempLed].DutyG	= 0;
        LedData.Buffer[TempLed].DutyB	= 0;
        TempStep++;
      }
      
      else{
        if (ModeStep[0] < 5){
          ModeStep[0]++;
          TempStep = 0;
        }
        else{
          MusicMode = 0;
          MusicModePre = 0;
          MusicRealPre = -1;
          
        }
      }
    }
  }
  
  
  #elif _AL95_
	//------------------------------------------------------------------------
	if (MusicInit == TRUE){
    MusicInit = FALSE;
    
    UpLevel = MusicModeCrt;
    TempStep = 0;
    ModeTime[0] = 0;
    ModeStep[0] = 0;
  }
	
  if (MusicChgFlag == TRUE){
    ModeTime[0]++;
    if (ModeTime[0] >= 2){
      ModeTime[0] = 0;
      if (TempStep < UpLevel){
        for (TempLed = 0; TempLed < GRP_MAX; TempLed++){
          LedData.Buffer[TempLed].DutyR = MUSIC_COLOR[TempStep][R];
          LedData.Buffer[TempLed].DutyG = MUSIC_COLOR[TempStep][G];
          LedData.Buffer[TempLed].DutyB = MUSIC_COLOR[TempStep][B];
        }
        TempStep++;
      }
      else{
        MusicChgFlag = FALSE;
        TempStep = 0;
      }
    }
  }
  
  else{
    ModeTime[0]++;
    if (ModeTime[0] >= 2){
      ModeTime[0] = 0;
      
      if (TempStep < 3){
        LedData.Buffer[TempStep].DutyR	= 0;
        LedData.Buffer[TempStep].DutyG	= 0;
        LedData.Buffer[TempStep].DutyB	= 0;
        TempStep++;
      }
      
      else{
        MusicMode = 0;
        MusicModePre = 0;
        MusicRealPre = -1;
        
      }
    }
  }
	
	
	#elif AL91 | AL94
	//-----------------------------------------------------------------------------
	if (MusicInit == TRUE){
    MusicInit = FALSE;
    
    UpLevel = MusicModeCrt;
    TempStep = 0;
    ModeTime[1] = 0;
    ModeStep[0] = 0;
  }
	
  if (MusicChgFlag == TRUE){
		if (TempStep < UpLevel){
			for (TempLed = 0; TempLed < LED_TOTAL; TempLed++){
				LedData.Buffer[TempLed].DutyR = MUSIC_COLOR[TempStep][R];
				LedData.Buffer[TempLed].DutyG = MUSIC_COLOR[TempStep][G];
				LedData.Buffer[TempLed].DutyB = MUSIC_COLOR[TempStep][B];
			}
			TempStep++;
		}
		else{
			MusicChgFlag = FALSE;
			TempStep = 0;
		}
  }
  
  else{
    
    ModeTime[0]++;
    if (ModeTime[0] >= 2){
      ModeTime[0] = 0;
      switch (TempStep){
        case 0:			ModeStep[0] = 1; 		TempStep++;		break;
        case 1:			ModeStep[0] = 7; 		TempStep++;		break;
        case 2:			ModeStep[0] = 4; 		TempStep++;		break;
        case 3:			ModeStep[0] = 6; 		TempStep++;		break;
        case 4:			ModeStep[0] = 2; 		TempStep++;		break;
        case 5:			ModeStep[0] = 3; 	TempStep++;		break;
        case 6:			ModeStep[0] = 5; 		TempStep++;		break;
        case 7:			ModeStep[0] = 0; 		TempStep++;		break;
        default:{
          for (TempLed = 0; TempLed < LED_TOTAL; TempLed++){
            LedData.Buffer[TempLed].DutyR = 0;
            LedData.Buffer[TempLed].DutyG = 0;
            LedData.Buffer[TempLed].DutyB = 0;
          }
          MusicMode = 0;
          MusicModePre = 0;
          MusicRealPre = -1;
          
        }break;
      }
      
      
      for (TempLed = 0; TempLed < LED_TOTAL; TempLed++){
        if ((TempLed % 8) == ModeStep[0]){
          LedData.Buffer[TempLed].DutyR = 0;
          LedData.Buffer[TempLed].DutyG = 0;
          LedData.Buffer[TempLed].DutyB = 0;
        }
      }
    }
  }
  
  
  #endif
}


/**
  * FunctionName    Music_XI
  */
static void Music_XI(void)
{
  #if _AL92B_
  //------------------------------------------------------------------------
  if (MusicInit == TRUE){
    MusicInit = FALSE;
    
    UpLevel = MusicModeCrt;
    TempStep = 0;
    ModeTime[0] = 0;
    ModeStep[0] = 0;
    
    FadeR = MUSIC_COLOR[MusicModeCrt][R] / 25;
    FadeG = MUSIC_COLOR[MusicModeCrt][G] / 25;
    FadeB = MUSIC_COLOR[MusicModeCrt][B] / 25;
    
    for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++){
      for (TempLed = 0; TempLed < LED_MAX; TempLed++){
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR = FadeR;
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG = FadeG;
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB = FadeB;
      }
    }
  }
  
  
  
  if (MusicChgFlag == TRUE){
    
    if (TempStep < 25){
      TempStep++;
      for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++){
        for (TempLed = 0; TempLed < LED_MAX; TempLed++){
          LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR = FadeR * TempStep;
          LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG = FadeG * TempStep;
          LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB = FadeB * TempStep;
        }
      }
    }
    else{
      MusicChgFlag = FALSE;
      TempStep = MusicModeCrt;
    }
  }
  
  else{
    ModeTime[0]++;
    if (ModeTime[0] >= 2){
      ModeTime[0] = 0;
      
      if (TempStep > 0){
        TempStep--;
        for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++){
          for (TempLed = 0; TempLed < LED_MAX; TempLed++){
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR = MUSIC_COLOR[TempStep][R];
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG = MUSIC_COLOR[TempStep][G];
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB = MUSIC_COLOR[TempStep][B];
          }
        }
      }
      
      else{
        MusicMode = 0;
        MusicModePre = 0;
        MusicRealPre = -1;
        
      }
    }
  }
  
  
  #elif _AL92C_
  //------------------------------------------------------------------------
  if (MusicInit == TRUE){
    MusicInit = FALSE;
    
    UpLevel = MusicModeCrt;
    TempStep = 0;
    ModeTime[0] = 0;
    ModeStep[0] = 0;
    
    
    FadeR = MUSIC_COLOR[MusicModeCrt][R] / 25;
    FadeG = MUSIC_COLOR[MusicModeCrt][G] / 25;
    FadeB = MUSIC_COLOR[MusicModeCrt][B] / 25;
    
    for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++){
      for (TempLed = 0; TempLed < LED_MAX; TempLed++){
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR = FadeR;
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG = FadeG;
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB = FadeB;
      }
    }
    
    
  }
  
  
  
  if (MusicChgFlag == TRUE){
    
    if (TempStep < 25){
      TempStep++;
      for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++){
        for (TempLed = 0; TempLed < LED_MAX; TempLed++){
          LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR = FadeR * TempStep;
          LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG = FadeG * TempStep;
          LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB = FadeB * TempStep;
        }
      }
    }
    else{
      MusicChgFlag = FALSE;
      TempStep = MusicModeCrt;
    }
  }
  
  else{
    ModeTime[0]++;
    if (ModeTime[0] >= 1){
      ModeTime[0] = 0;
      
      if (TempStep > 0){
        TempStep--;
        for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++){
          for (TempLed = 0; TempLed < LED_MAX; TempLed++){
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR = MUSIC_COLOR[TempStep][R];
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG = MUSIC_COLOR[TempStep][G];
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB = MUSIC_COLOR[TempStep][B];
          }
        }
      }
      
      else{
        MusicMode = 0;
        MusicModePre = 0;
        MusicRealPre = -1;
        
      }
    }
  }
  
  
  #elif _AL92A_
  //------------------------------------------------------------------------
  if (MusicInit == TRUE){
    MusicInit = FALSE;
    
    UpLevel = MusicModeCrt;
    TempStep = 0;
    ModeTime[0] = 0;
    ModeStep[0] = 0;
    
    
    FadeR = MUSIC_COLOR[MusicModeCrt][R] / 25;
    FadeG = MUSIC_COLOR[MusicModeCrt][G] / 25;
    FadeB = MUSIC_COLOR[MusicModeCrt][B] / 25;
    
    for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++){
      for (TempLed = 0; TempLed < LED_MAX; TempLed++){
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR = FadeR;
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG = FadeG;
        LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB = FadeB;
      }
    }
    
    
  }
  
  
  
  if (MusicChgFlag == TRUE){
    
    if (TempStep < 25){
      TempStep++;
      for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++){
        for (TempLed = 0; TempLed < LED_MAX; TempLed++){
          LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR = FadeR * TempStep;
          LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG = FadeG * TempStep;
          LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB = FadeB * TempStep;
        }
      }
    }
    else{
      MusicChgFlag = FALSE;
      TempStep = MusicModeCrt;
    }
  }
  
  else{
    ModeTime[0]++;
    if (ModeTime[0] >= 1){
      ModeTime[0] = 0;
      
      if (TempStep > 0){
        TempStep--;
        for (TempGrp = 0; TempGrp < GRP_MAX; TempGrp++){
          for (TempLed = 0; TempLed < LED_MAX; TempLed++){
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyR = MUSIC_COLOR[TempStep][R];
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyG = MUSIC_COLOR[TempStep][G];
            LedData.Buffer[TempGrp * LED_MAX + TempLed].DutyB = MUSIC_COLOR[TempStep][B];
          }
        }
      }
      
      else{
        MusicMode = 0;
        MusicModePre = 0;
        MusicRealPre = -1;
        
      }
    }
  }
  
  
  #elif _AL95_
  //------------------------------------------------------------------------
  if (MusicInit == TRUE){
    MusicInit = FALSE;
    
    UpLevel = MusicModeCrt;
    TempStep = 0;
    ModeTime[0] = 0;
    ModeStep[0] = 0;
    
    
    FadeR = MUSIC_COLOR[MusicModeCrt][R] / 25;
    FadeG = MUSIC_COLOR[MusicModeCrt][G] / 25;
    FadeB = MUSIC_COLOR[MusicModeCrt][B] / 25;
    
    for (TempLed = 0; TempLed < LED_MAX; TempLed++){
      LedData.Buffer[TempLed].DutyR = FadeR;
      LedData.Buffer[TempLed].DutyG = FadeG;
      LedData.Buffer[TempLed].DutyB = FadeB;
    }
    
    
  }
  
  
  
  if (MusicChgFlag == TRUE){
    
    if (TempStep < 25){
      TempStep++;
      for (TempLed = 0; TempLed < GRP_MAX; TempLed++){
        LedData.Buffer[TempLed].DutyR = FadeR * TempStep;
        LedData.Buffer[TempLed].DutyG = FadeG * TempStep;
        LedData.Buffer[TempLed].DutyB = FadeB * TempStep;
      }
    }
    else{
      MusicChgFlag = FALSE;
      TempStep = MusicModeCrt;
    }
  }
  
  else{
    ModeTime[0]++;
    if (ModeTime[0] >= 1){
      ModeTime[0] = 0;
      
      if (TempStep > 0){
        TempStep--;
        for (TempLed = 0; TempLed < GRP_MAX; TempLed++){
          LedData.Buffer[TempLed].DutyR = MUSIC_COLOR[TempStep][R];
          LedData.Buffer[TempLed].DutyG = MUSIC_COLOR[TempStep][G];
          LedData.Buffer[TempLed].DutyB = MUSIC_COLOR[TempStep][B];
        }
      }
      
      else{
        MusicMode = 0;
        MusicModePre = 0;
        MusicRealPre = -1;
        
      }
    }
  }
	
	#elif AL91 | AL94
  //------------------------------------------------------------------------
  if (MusicInit == TRUE){
    MusicInit = FALSE;
    
    UpLevel = MusicModeCrt;
    TempStep = 0;
    ModeTime[0] = MusicModeCrt - 30 + 1;
    ModeStep[0] = 0;
    
    
    FadeR = MUSIC_COLOR[MusicModeCrt][R] / 25;
    FadeG = MUSIC_COLOR[MusicModeCrt][G] / 25;
    FadeB = MUSIC_COLOR[MusicModeCrt][B] / 25;
  }
  
  
  
  if (MusicChgFlag == TRUE){
    ModeTime[0]++;
    if (ModeTime[0] >= 2){
      ModeTime[0] = 0;
      if (TempStep < 25){
        TempStep++;
        for (TempLed = 0; TempLed < LED_TOTAL; TempLed++){
          LedData.Buffer[TempLed].DutyR = FadeR * TempStep;
          LedData.Buffer[TempLed].DutyG = FadeG * TempStep;
          LedData.Buffer[TempLed].DutyB = FadeB * TempStep;
        }
      }
      else{
        MusicChgFlag = FALSE;
        TempStep = MusicModeCrt;
      }
    }
  }
  
  else{
    ModeTime[0]++;
    if (ModeTime[0] >= 1){
      ModeTime[0] = 0;
      
      if (TempStep > HoldTime[0]){
        TempStep--;
        for (TempLed = 0; TempLed < LED_TOTAL; TempLed++){
          LedData.Buffer[TempLed].DutyR = MUSIC_COLOR[TempStep][R];
          LedData.Buffer[TempLed].DutyG = MUSIC_COLOR[TempStep][G];
          LedData.Buffer[TempLed].DutyB = MUSIC_COLOR[TempStep][B];
        }
      }
      
      else{
        MusicMode = 0;
        MusicModePre = 0;
        MusicRealPre = -1;
        
      }
    }
  }
  
  #endif
}

#endif

