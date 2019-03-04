#include "Music.h"

//global argument
_TypeMusic    MusicMode;
_Flag   MusicEnFlag;
uint16  MusicEnTime;
_Flag   MusicTrigFlag;

//file argument
_TypeMusic    MusicModePre;
_Flag         UpFlag[6];
uint8         UpStep[6];
uint8         ChgCnt[6];
uint8         DwnStep[6];
_Flag         DwnInit[6];
uint8         DwnTime[6];
uint8         DwnCnt[6];
_Flag         StarChgFlag;
uint8         StarStep;
uint8         StarCnt;
uint8         StarTime;
uint8         StarRptCnt;


//const color table
uint8 const MUSIC_COLOR[38][3]={
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
};

/**
  * Music_Mode
  */
void Music_Mode(void)
{
  uint8 temp = 0;
  
  
  if (MusicEnFlag == FALSE)     return;
  MusicEnTime++;
  if (MusicEnTime >= 250){
    MusicEnFlag = FALSE;
    DisplayData.Mode = 0xA;
    DisplayData.InitFlag = TRUE;
  }
  
  //Initialize
  if (DisplayData.InitFlag == TRUE){
    DisplayData.InitFlag = FALSE;
    
    for (TempGrp = 0; TempGrp < 6; TempGrp++){
      for (TempLed = 0; TempLed < 38; TempLed++){
        ColorBuffer[TempGrp][TempLed].DutyR = 0;
        ColorBuffer[TempGrp][TempLed].DutyG = 0;
        ColorBuffer[TempGrp][TempLed].DutyB = 0;
      }
    }
    
    
    for (TempGrp = 0; TempGrp < 6; TempGrp++){
      for (TempLed = 0; TempLed < 2; TempLed++){
        ColorBuffer[TempGrp][TempLed].DutyR = 250;
        ColorBuffer[TempGrp][TempLed].DutyG = 0;
        ColorBuffer[TempGrp][TempLed].DutyB = 0;
      }
    }
    
    for (TempLed = 0; TempLed < 6; TempLed++){
      ColorBuffer[GRP_SEVEN][TempLed].DutyR = 0;
      ColorBuffer[GRP_SEVEN][TempLed].DutyG = 0;
      ColorBuffer[GRP_SEVEN][TempLed].DutyB = 0;
      
    }
    
    for (temp = 0; temp < 6; temp++){
      UpStep[temp] = 0;
    }
  }
  
  
  //----------------------------------------------------------------------------------------------------------
  if (MusicModePre.TotalMode < MusicMode.TotalMode || (((StarCnt + 10) < MusicMode.TotalMode) && StarRptCnt < 2)){
    StarChgFlag = TRUE;
    if (MusicModePre.TotalMode == MusicMode.TotalMode){
      StarRptCnt++;
    }
    else{
      StarRptCnt = 0;
    }
    MusicModePre.TotalMode = MusicMode.TotalMode;
    StarStep = MusicMode.TotalMode; 
    StarTime = 0;
    
    for (TempLed = 0; TempLed < 6; TempLed++){
      ColorBuffer[GRP_SEVEN][TempLed].DutyR = MUSIC_COLOR[StarStep][B];
      ColorBuffer[GRP_SEVEN][TempLed].DutyG = MUSIC_COLOR[StarStep][R];
      ColorBuffer[GRP_SEVEN][TempLed].DutyB = MUSIC_COLOR[StarStep][G];
    }
    
    StarCnt = StarStep;
  }
  
  if (StarChgFlag == TRUE){
    if (StarTime < 19 - StarStep / 2){
      StarTime++;
    }
    else{
      StarChgFlag = FALSE;
    }
  }
  
  else
  {
    if (StarCnt > 0){
      for (TempLed = 0; TempLed < 6; TempLed++){
        ColorBuffer[GRP_SEVEN][TempLed].DutyR = MUSIC_COLOR[StarCnt][B];
        ColorBuffer[GRP_SEVEN][TempLed].DutyG = MUSIC_COLOR[StarCnt][R];
        ColorBuffer[GRP_SEVEN][TempLed].DutyB = MUSIC_COLOR[StarCnt][G];
      }
      StarCnt--;
    }
    else{
      MusicModePre.TotalMode = 0;
      MusicMode.TotalMode = 0;
      for (TempLed = 0; TempLed < 6; TempLed++){
        ColorBuffer[GRP_SEVEN][TempLed].DutyR = 0;
        ColorBuffer[GRP_SEVEN][TempLed].DutyG = 0;
        ColorBuffer[GRP_SEVEN][TempLed].DutyB = 0;
      }
    }
  }
  
  
  
  
  
  
  //----------------------------------------------------------------------------------------------------------
  
  //Start
  if ((MusicMode.Byte1.Buf.High > MusicModePre.Byte1.Buf.High) || (((UpStep[0] + 2) < MusicMode.Byte1.Buf.High) && ChgCnt[0] < 2)){
    UpFlag[0] = TRUE;
    if (MusicModePre.Byte1.Buf.High == MusicMode.Byte1.Buf.High){
      ChgCnt[0]++;
    }
    else{
      ChgCnt[0] = 0;
    }
    MusicModePre.Byte1.Buf.High = MusicMode.Byte1.Buf.High;
  }
  
  if (MusicMode.Byte1.Buf.Low > MusicModePre.Byte1.Buf.Low || (((UpStep[1] + 2) < MusicMode.Byte1.Buf.Low) && ChgCnt[1] < 2)){
    UpFlag[1] = TRUE;
    if (MusicModePre.Byte1.Buf.Low == MusicMode.Byte1.Buf.Low){
      ChgCnt[1]++;
    }
    else{
      ChgCnt[1] = 0;
    }
    
    MusicModePre.Byte1.Buf.Low = MusicMode.Byte1.Buf.Low;
  }
  
  if (MusicMode.Byte2.Buf.High > MusicModePre.Byte2.Buf.High || (((UpStep[2] + 2) < MusicMode.Byte2.Buf.High) && ChgCnt[2] < 2)){
    UpFlag[2] = TRUE;
    if (MusicModePre.Byte2.Buf.High == MusicMode.Byte2.Buf.High){
      ChgCnt[2]++;
    }
    else{
      ChgCnt[2] = 0;
    }
    MusicModePre.Byte2.Buf.High = MusicMode.Byte2.Buf.High;
  }
  
  if (MusicMode.Byte2.Buf.Low > MusicModePre.Byte2.Buf.Low || (((UpStep[3] + 2) < MusicMode.Byte2.Buf.Low) && ChgCnt[3] < 2)){
    UpFlag[3] = TRUE;
    if (MusicModePre.Byte2.Buf.Low == MusicMode.Byte2.Buf.Low){
      ChgCnt[3]++;
    }
    else{
      ChgCnt[3] = 0;
    }
    MusicModePre.Byte2.Buf.Low = MusicMode.Byte2.Buf.Low;
  }
  
  if (MusicMode.Byte3.Buf.High > MusicModePre.Byte3.Buf.High || (((UpStep[4] + 2) < MusicMode.Byte3.Buf.High) && ChgCnt[4] < 2)){
    UpFlag[4] = TRUE;
    if (MusicModePre.Byte3.Buf.High == MusicMode.Byte3.Buf.High){
      ChgCnt[4]++;
    }
    else{
      ChgCnt[4] = 0;
    }
    MusicModePre.Byte3.Buf.High = MusicMode.Byte3.Buf.High;
  }
  
  if (MusicMode.Byte3.Buf.Low > MusicModePre.Byte3.Buf.Low || (((UpStep[5] + 2) < MusicMode.Byte3.Buf.Low) && ChgCnt[5] < 2)){
    UpFlag[5] = TRUE;
    if (MusicModePre.Byte3.Buf.Low == MusicMode.Byte3.Buf.Low){
      ChgCnt[5]++;
    }
    else{
      ChgCnt[5] = 0;
    }
    MusicModePre.Byte3.Buf.Low = MusicMode.Byte3.Buf.Low;
  }
  
  
  //1
  if (UpFlag[0] == TRUE){
    if (UpStep[0] < MusicMode.Byte1.Buf.High){
      UpStep[0]++;
      temp = UpStep[0] * 2;
      ColorBuffer[GRP_ONE][temp].DutyR = MUSIC_COLOR[temp][R];
      ColorBuffer[GRP_ONE][temp].DutyG = MUSIC_COLOR[temp][G];
      ColorBuffer[GRP_ONE][temp].DutyB = MUSIC_COLOR[temp][B];
      
      temp = UpStep[0] * 2 + 1;
      ColorBuffer[GRP_ONE][temp].DutyR = MUSIC_COLOR[temp][R];
      ColorBuffer[GRP_ONE][temp].DutyG = MUSIC_COLOR[temp][G];
      ColorBuffer[GRP_ONE][temp].DutyB = MUSIC_COLOR[temp][B];
    }
    else{
      DwnStep[0] = UpStep[0] * 2 + 2;
      if (DwnCnt[0] < DwnStep[0]){
        ColorBuffer[GRP_ONE][DwnStep[0]].DutyR = MUSIC_COLOR[DwnStep[0]][R];
        ColorBuffer[GRP_ONE][DwnStep[0]].DutyG = MUSIC_COLOR[DwnStep[0]][G];
        ColorBuffer[GRP_ONE][DwnStep[0]].DutyB = MUSIC_COLOR[DwnStep[0]][B];
        DwnCnt[0] = DwnStep[0];
        DwnInit[0] = TRUE;
      }
      
      UpFlag[0] = 0;
    }
  }
  else{
    if (UpStep[0] > 0){
      temp = UpStep[0] * 2;
      ColorBuffer[GRP_ONE][temp].DutyR = 0;
      ColorBuffer[GRP_ONE][temp].DutyG = 0;
      ColorBuffer[GRP_ONE][temp].DutyB = 0;
      
      temp = UpStep[0] * 2 + 1;
      ColorBuffer[GRP_ONE][temp].DutyR = 0;
      ColorBuffer[GRP_ONE][temp].DutyG = 0;
      ColorBuffer[GRP_ONE][temp].DutyB = 0;
      UpStep[0]--;
    }
    else{
      MusicModePre.Byte1.Buf.High = 0;
      MusicMode.Byte1.Buf.High = 0;
    }
  }
  
  if (DwnInit[0] == TRUE){
    DwnInit[0] = FALSE;
    DwnTime[0] = 0;
  }
  else{
    DwnTime[0]++;
    if (DwnTime[0] >= 2){
      DwnTime[0] = 0;
      
      if (DwnCnt[0] > 0)      DwnCnt[0]--;

      if (UpFlag[0] == TRUE){
        for (temp = UpStep[0] * 2 + 2; temp < 37; temp++){
          ColorBuffer[GRP_ONE][temp].DutyR = ColorBuffer[GRP_ONE][temp + 1].DutyR;
          ColorBuffer[GRP_ONE][temp].DutyG = ColorBuffer[GRP_ONE][temp + 1].DutyG;
          ColorBuffer[GRP_ONE][temp].DutyB = ColorBuffer[GRP_ONE][temp + 1].DutyB;
        }
      }
      else{
        for (temp = UpStep[0] * 2 + 4; temp < 37; temp++){
          ColorBuffer[GRP_ONE][temp].DutyR = ColorBuffer[GRP_ONE][temp + 1].DutyR;
          ColorBuffer[GRP_ONE][temp].DutyG = ColorBuffer[GRP_ONE][temp + 1].DutyG;
          ColorBuffer[GRP_ONE][temp].DutyB = ColorBuffer[GRP_ONE][temp + 1].DutyB;
        }
      }
      ColorBuffer[GRP_ONE][37].DutyR = 0;
      ColorBuffer[GRP_ONE][37].DutyG = 0;
      ColorBuffer[GRP_ONE][37].DutyB = 0;
    }
  }
  
  
  
  //2
  if (UpFlag[1] == TRUE){
    if (UpStep[1] < MusicMode.Byte1.Buf.Low){
      UpStep[1]++;
      temp = UpStep[1] * 2;
      ColorBuffer[GRP_TWO][temp].DutyR = MUSIC_COLOR[temp][R];
      ColorBuffer[GRP_TWO][temp].DutyG = MUSIC_COLOR[temp][G];
      ColorBuffer[GRP_TWO][temp].DutyB = MUSIC_COLOR[temp][B];
      
      temp = UpStep[1] * 2 + 1;
      ColorBuffer[GRP_TWO][temp].DutyR = MUSIC_COLOR[temp][R];
      ColorBuffer[GRP_TWO][temp].DutyG = MUSIC_COLOR[temp][G];
      ColorBuffer[GRP_TWO][temp].DutyB = MUSIC_COLOR[temp][B];
    }
    else{
      DwnStep[1] = UpStep[1] * 2 + 2;
      if (DwnCnt[1] < DwnStep[1]){
        ColorBuffer[GRP_TWO][DwnStep[1]].DutyR = MUSIC_COLOR[DwnStep[1]][R];
        ColorBuffer[GRP_TWO][DwnStep[1]].DutyG = MUSIC_COLOR[DwnStep[1]][G];
        ColorBuffer[GRP_TWO][DwnStep[1]].DutyB = MUSIC_COLOR[DwnStep[1]][B];
        DwnCnt[1] = DwnStep[1];
        DwnInit[1] = TRUE;
      }
      UpFlag[1] = 0;
    }
  }
  else{
    if (UpStep[1] > 0){
      temp = UpStep[1] * 2;
      ColorBuffer[GRP_TWO][temp].DutyR = 0;
      ColorBuffer[GRP_TWO][temp].DutyG = 0;
      ColorBuffer[GRP_TWO][temp].DutyB = 0;
      
      temp = UpStep[1] * 2 + 1;
      ColorBuffer[GRP_TWO][temp].DutyR = 0;
      ColorBuffer[GRP_TWO][temp].DutyG = 0;
      ColorBuffer[GRP_TWO][temp].DutyB = 0;
      
      UpStep[1]--;
    }
    else{
      MusicModePre.Byte1.Buf.Low = 0;
      MusicMode.Byte1.Buf.Low = 0;
    }
  }
  if (DwnInit[1] == TRUE){
    DwnInit[1] = FALSE;
    DwnTime[1] = 0;
  }
  else{
    DwnTime[1]++;
    if (DwnTime[1] >= 2){
      DwnTime[1] = 0;
      
      if (DwnCnt[1] > 0)      DwnCnt[1]--;

      if (UpFlag[1] == TRUE){
        for (temp = UpStep[1] * 2 + 2; temp < 37; temp++){
          ColorBuffer[GRP_TWO][temp].DutyR = ColorBuffer[GRP_TWO][temp + 1].DutyR;
          ColorBuffer[GRP_TWO][temp].DutyG = ColorBuffer[GRP_TWO][temp + 1].DutyG;
          ColorBuffer[GRP_TWO][temp].DutyB = ColorBuffer[GRP_TWO][temp + 1].DutyB;
        }
      }
      else{
        for (temp = UpStep[1] * 2 + 4; temp < 37; temp++){
          ColorBuffer[GRP_TWO][temp].DutyR = ColorBuffer[GRP_TWO][temp + 1].DutyR;
          ColorBuffer[GRP_TWO][temp].DutyG = ColorBuffer[GRP_TWO][temp + 1].DutyG;
          ColorBuffer[GRP_TWO][temp].DutyB = ColorBuffer[GRP_TWO][temp + 1].DutyB;
        }
      }
      ColorBuffer[GRP_TWO][37].DutyR = 0;
      ColorBuffer[GRP_TWO][37].DutyG = 0;
      ColorBuffer[GRP_TWO][37].DutyB = 0;
    }
  }
  
  
  
  
  
  
  
  //3
  if (UpFlag[2] == TRUE){
    if (UpStep[2] < MusicMode.Byte2.Buf.High){
      UpStep[2]++;
      temp = UpStep[2] * 2;
      ColorBuffer[GRP_THREE][temp].DutyR = MUSIC_COLOR[temp][R];
      ColorBuffer[GRP_THREE][temp].DutyG = MUSIC_COLOR[temp][G];
      ColorBuffer[GRP_THREE][temp].DutyB = MUSIC_COLOR[temp][B];
      
      temp = UpStep[2] * 2 + 1;
      ColorBuffer[GRP_THREE][temp].DutyR = MUSIC_COLOR[temp][R];
      ColorBuffer[GRP_THREE][temp].DutyG = MUSIC_COLOR[temp][G];
      ColorBuffer[GRP_THREE][temp].DutyB = MUSIC_COLOR[temp][B];
    }
    else{
      DwnStep[2] = UpStep[2] * 2 + 2;
      if (DwnCnt[2] < DwnStep[2]){
        ColorBuffer[GRP_THREE][DwnStep[2]].DutyR = MUSIC_COLOR[DwnStep[2]][R];
        ColorBuffer[GRP_THREE][DwnStep[2]].DutyG = MUSIC_COLOR[DwnStep[2]][G];
        ColorBuffer[GRP_THREE][DwnStep[2]].DutyB = MUSIC_COLOR[DwnStep[2]][B];
        DwnCnt[2] = DwnStep[2];
        DwnInit[2] = TRUE;
      }
      UpFlag[2] = 0;
    }
  }
  else{
    if (UpStep[2] > 0){
      temp = UpStep[2] * 2;
      ColorBuffer[GRP_THREE][temp].DutyR = 0;
      ColorBuffer[GRP_THREE][temp].DutyG = 0;
      ColorBuffer[GRP_THREE][temp].DutyB = 0;
      
      temp = UpStep[2] * 2 + 1;
      ColorBuffer[GRP_THREE][temp].DutyR = 0;
      ColorBuffer[GRP_THREE][temp].DutyG = 0;
      ColorBuffer[GRP_THREE][temp].DutyB = 0;
      UpStep[2]--;
    }
    else{
      MusicModePre.Byte2.Buf.High = 0;
      MusicMode.Byte2.Buf.High = 0;
    }
  }
  if (DwnInit[2] == TRUE){
    DwnInit[2] = FALSE;
    DwnTime[2] = 0;
  }
  else{
    DwnTime[2]++;
    if (DwnTime[2] >= 2){
      DwnTime[2] = 0;
      
      if (DwnCnt[2] > 0)      DwnCnt[2]--;

      if (UpFlag[2] == TRUE){
        for (temp = UpStep[2] * 2 + 2; temp < 37; temp++){
          ColorBuffer[GRP_THREE][temp].DutyR = ColorBuffer[GRP_THREE][temp + 1].DutyR;
          ColorBuffer[GRP_THREE][temp].DutyG = ColorBuffer[GRP_THREE][temp + 1].DutyG;
          ColorBuffer[GRP_THREE][temp].DutyB = ColorBuffer[GRP_THREE][temp + 1].DutyB;
        }
      }
      else{
        for (temp = UpStep[2] * 2 + 4; temp < 37; temp++){
          ColorBuffer[GRP_THREE][temp].DutyR = ColorBuffer[GRP_THREE][temp + 1].DutyR;
          ColorBuffer[GRP_THREE][temp].DutyG = ColorBuffer[GRP_THREE][temp + 1].DutyG;
          ColorBuffer[GRP_THREE][temp].DutyB = ColorBuffer[GRP_THREE][temp + 1].DutyB;
        }
      }
      ColorBuffer[GRP_THREE][37].DutyR = 0;
      ColorBuffer[GRP_THREE][37].DutyG = 0;
      ColorBuffer[GRP_THREE][37].DutyB = 0;
    }
  }
  
  
  
  
  
  //4
  if (UpFlag[3] == TRUE){
    if (UpStep[3] < MusicMode.Byte2.Buf.Low){
      UpStep[3]++;
      temp = UpStep[3] * 2;
      ColorBuffer[GRP_FOUR][temp].DutyR = MUSIC_COLOR[temp][R];
      ColorBuffer[GRP_FOUR][temp].DutyG = MUSIC_COLOR[temp][G];
      ColorBuffer[GRP_FOUR][temp].DutyB = MUSIC_COLOR[temp][B];
      
      temp = UpStep[3] * 2 + 1;
      ColorBuffer[GRP_FOUR][temp].DutyR = MUSIC_COLOR[temp][R];
      ColorBuffer[GRP_FOUR][temp].DutyG = MUSIC_COLOR[temp][G];
      ColorBuffer[GRP_FOUR][temp].DutyB = MUSIC_COLOR[temp][B];
    }
    else{
      DwnStep[3] = UpStep[3] * 2 + 2;
      if (DwnCnt[3] < DwnStep[3]){
        ColorBuffer[GRP_FOUR][DwnStep[3]].DutyR = MUSIC_COLOR[DwnStep[3]][R];
        ColorBuffer[GRP_FOUR][DwnStep[3]].DutyG = MUSIC_COLOR[DwnStep[3]][G];
        ColorBuffer[GRP_FOUR][DwnStep[3]].DutyB = MUSIC_COLOR[DwnStep[3]][B];
        DwnCnt[3] = DwnStep[3];
        DwnInit[3] = TRUE;
      }
      UpFlag[3] = 0;
    }
  }
  else{
    if (UpStep[3] > 0){
      temp = UpStep[3] * 2;
      ColorBuffer[GRP_FOUR][temp].DutyR = 0;
      ColorBuffer[GRP_FOUR][temp].DutyG = 0;
      ColorBuffer[GRP_FOUR][temp].DutyB = 0;
      
      temp = UpStep[3] * 2 + 1;
      ColorBuffer[GRP_FOUR][temp].DutyR = 0;
      ColorBuffer[GRP_FOUR][temp].DutyG = 0;
      ColorBuffer[GRP_FOUR][temp].DutyB = 0;
      UpStep[3]--;
    }
    else{
      MusicModePre.Byte2.Buf.Low = 0;
      MusicMode.Byte2.Buf.Low = 0;
    }
  }
  if (DwnInit[3] == TRUE){
    DwnInit[3] = FALSE;
    DwnTime[3] = 0;
  }
  else{
    DwnTime[3]++;
    if (DwnTime[3] >= 2){
      DwnTime[3] = 0;
      
      if (DwnCnt[3] > 0)      DwnCnt[3]--;

      if (UpFlag[3] == TRUE){
        for (temp = UpStep[3] * 2 + 2; temp < 37; temp++){
          ColorBuffer[GRP_FOUR][temp].DutyR = ColorBuffer[GRP_FOUR][temp + 1].DutyR;
          ColorBuffer[GRP_FOUR][temp].DutyG = ColorBuffer[GRP_FOUR][temp + 1].DutyG;
          ColorBuffer[GRP_FOUR][temp].DutyB = ColorBuffer[GRP_FOUR][temp + 1].DutyB;
        }
      }
      else{
        for (temp = UpStep[3] * 2 + 4; temp < 37; temp++){
          ColorBuffer[GRP_FOUR][temp].DutyR = ColorBuffer[GRP_FOUR][temp + 1].DutyR;
          ColorBuffer[GRP_FOUR][temp].DutyG = ColorBuffer[GRP_FOUR][temp + 1].DutyG;
          ColorBuffer[GRP_FOUR][temp].DutyB = ColorBuffer[GRP_FOUR][temp + 1].DutyB;
        }
      }
      ColorBuffer[GRP_FOUR][37].DutyR = 0;
      ColorBuffer[GRP_FOUR][37].DutyG = 0;
      ColorBuffer[GRP_FOUR][37].DutyB = 0;
    }
  }
  
  
  
  
  
  //5
  if (UpFlag[4] == TRUE){
    if (UpStep[4] < MusicMode.Byte3.Buf.High){
      UpStep[4]++;
      temp = UpStep[4] * 2;
      ColorBuffer[GRP_FIVE][temp].DutyR = MUSIC_COLOR[temp][R];
      ColorBuffer[GRP_FIVE][temp].DutyG = MUSIC_COLOR[temp][G];
      ColorBuffer[GRP_FIVE][temp].DutyB = MUSIC_COLOR[temp][B];
      
      temp = UpStep[4] * 2 + 1;
      ColorBuffer[GRP_FIVE][temp].DutyR = MUSIC_COLOR[temp][R];
      ColorBuffer[GRP_FIVE][temp].DutyG = MUSIC_COLOR[temp][G];
      ColorBuffer[GRP_FIVE][temp].DutyB = MUSIC_COLOR[temp][B];
    }
    else{
      DwnStep[4] = UpStep[4] * 2 + 2;
      if (DwnCnt[4] < DwnStep[4]){
        ColorBuffer[GRP_FIVE][DwnStep[4]].DutyR = MUSIC_COLOR[DwnStep[4]][R];
        ColorBuffer[GRP_FIVE][DwnStep[4]].DutyG = MUSIC_COLOR[DwnStep[4]][G];
        ColorBuffer[GRP_FIVE][DwnStep[4]].DutyB = MUSIC_COLOR[DwnStep[4]][B];
        DwnCnt[4] = DwnStep[4];
        DwnInit[4] = TRUE;
      }
      UpFlag[4] = 0;
    }
  }
  else{
    if (UpStep[4] > 0){
      temp = UpStep[4] * 2;
      ColorBuffer[GRP_FIVE][temp].DutyR = 0;
      ColorBuffer[GRP_FIVE][temp].DutyG = 0;
      ColorBuffer[GRP_FIVE][temp].DutyB = 0;
      
      temp = UpStep[4] * 2 + 1;
      ColorBuffer[GRP_FIVE][temp].DutyR = 0;
      ColorBuffer[GRP_FIVE][temp].DutyG = 0;
      ColorBuffer[GRP_FIVE][temp].DutyB = 0;
      UpStep[4]--;
    }
    else{
      MusicModePre.Byte3.Buf.High = 0;
      MusicMode.Byte3.Buf.High = 0;
    }
  }
  if (DwnInit[4] == TRUE){
    DwnInit[4] = FALSE;
    DwnTime[4] = 0;
  }
  else{
    DwnTime[4]++;
    if (DwnTime[4] >= 2){
      DwnTime[4] = 0;
      
      if (DwnCnt[4] > 0)      DwnCnt[4]--;

      if (UpFlag[4] == TRUE){
        for (temp = UpStep[4] * 2 + 2; temp < 37; temp++){
          ColorBuffer[GRP_FIVE][temp].DutyR = ColorBuffer[GRP_FIVE][temp + 1].DutyR;
          ColorBuffer[GRP_FIVE][temp].DutyG = ColorBuffer[GRP_FIVE][temp + 1].DutyG;
          ColorBuffer[GRP_FIVE][temp].DutyB = ColorBuffer[GRP_FIVE][temp + 1].DutyB;
        }
      }
      else{
        for (temp = UpStep[4] * 2 + 4; temp < 37; temp++){
          ColorBuffer[GRP_FIVE][temp].DutyR = ColorBuffer[GRP_FIVE][temp + 1].DutyR;
          ColorBuffer[GRP_FIVE][temp].DutyG = ColorBuffer[GRP_FIVE][temp + 1].DutyG;
          ColorBuffer[GRP_FIVE][temp].DutyB = ColorBuffer[GRP_FIVE][temp + 1].DutyB;
        }
      }
      ColorBuffer[GRP_FIVE][37].DutyR = 0;
      ColorBuffer[GRP_FIVE][37].DutyG = 0;
      ColorBuffer[GRP_FIVE][37].DutyB = 0;
    }
  }
  
  
  
  
  
  
  //6
  if (UpFlag[5] == TRUE){
    if (UpStep[5] < MusicMode.Byte3.Buf.Low){
      UpStep[5]++;
      temp = UpStep[5] * 2;
      ColorBuffer[GRP_SIX][temp].DutyR = MUSIC_COLOR[temp][R];
      ColorBuffer[GRP_SIX][temp].DutyG = MUSIC_COLOR[temp][G];
      ColorBuffer[GRP_SIX][temp].DutyB = MUSIC_COLOR[temp][B];
      
      temp = UpStep[5] * 2 + 1;
      ColorBuffer[GRP_SIX][temp].DutyR = MUSIC_COLOR[temp][R];
      ColorBuffer[GRP_SIX][temp].DutyG = MUSIC_COLOR[temp][G];
      ColorBuffer[GRP_SIX][temp].DutyB = MUSIC_COLOR[temp][B];
    }
    else{
      DwnStep[5] = UpStep[5] * 2 + 2;
      if (DwnCnt[5] < DwnStep[5]){
        ColorBuffer[GRP_SIX][DwnStep[5]].DutyR = MUSIC_COLOR[DwnStep[5]][R];
        ColorBuffer[GRP_SIX][DwnStep[5]].DutyG = MUSIC_COLOR[DwnStep[5]][G];
        ColorBuffer[GRP_SIX][DwnStep[5]].DutyB = MUSIC_COLOR[DwnStep[5]][B];
        DwnCnt[5] = DwnStep[5];
        DwnInit[5] = TRUE;
      }
      UpFlag[5] = 0;
    }
  }
  else{
    if (UpStep[5] > 0){
      temp = UpStep[5] * 2;
      ColorBuffer[GRP_SIX][temp].DutyR = 0;
      ColorBuffer[GRP_SIX][temp].DutyG = 0;
      ColorBuffer[GRP_SIX][temp].DutyB = 0;
      
      temp = UpStep[5] * 2 + 1;
      ColorBuffer[GRP_SIX][temp].DutyR = 0;
      ColorBuffer[GRP_SIX][temp].DutyG = 0;
      ColorBuffer[GRP_SIX][temp].DutyB = 0;
      UpStep[5]--;
    }
    else{
      MusicModePre.Byte3.Buf.Low = 0;
      MusicMode.Byte3.Buf.Low = 0;
    }
  }
  if (DwnInit[5] == TRUE){
    DwnInit[5] = FALSE;
    DwnTime[5] = 0;
  }
  else{
    DwnTime[5]++;
    if (DwnTime[5] >= 2){
      DwnTime[5] = 0;
      
      if (DwnCnt[5] > 0)      DwnCnt[5]--;

      if (UpFlag[5] == TRUE){
        for (temp = UpStep[5] * 2 + 2; temp < 37; temp++){
          ColorBuffer[GRP_SIX][temp].DutyR = ColorBuffer[GRP_SIX][temp + 1].DutyR;
          ColorBuffer[GRP_SIX][temp].DutyG = ColorBuffer[GRP_SIX][temp + 1].DutyG;
          ColorBuffer[GRP_SIX][temp].DutyB = ColorBuffer[GRP_SIX][temp + 1].DutyB;
        }
      }
      else{
        for (temp = UpStep[5] * 2 + 4; temp < 37; temp++){
          ColorBuffer[GRP_SIX][temp].DutyR = ColorBuffer[GRP_SIX][temp + 1].DutyR;
          ColorBuffer[GRP_SIX][temp].DutyG = ColorBuffer[GRP_SIX][temp + 1].DutyG;
          ColorBuffer[GRP_SIX][temp].DutyB = ColorBuffer[GRP_SIX][temp + 1].DutyB;
        }
      }
      ColorBuffer[GRP_SIX][37].DutyR = 0;
      ColorBuffer[GRP_SIX][37].DutyG = 0;
      ColorBuffer[GRP_SIX][37].DutyB = 0;
    }
  }
}

