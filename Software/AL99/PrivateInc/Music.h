#ifndef _MUSIC_H_
#define _MUSIC_H_

//include files
#include "Type_Def.h"
#include "Led_Class.h"
#include "Display_Ctrl.h"

//type redefine
typedef union{
  uint8 All;
  struct{
    uint8   High : 4;
    uint8   Low : 4;
  }Buf;
}_TypeUnMusic;

typedef struct MUSIC_MODE{
  uint8 TotalMode;
  uint8 TotalModePre;
  _TypeUnMusic Byte1;
  _TypeUnMusic Byte2;
  _TypeUnMusic Byte3;
}_TypeMusic;


//exported function
void Music_Mode(void);


//exported arguments
extern _TypeMusic   MusicMode;
extern _Flag   MusicEnFlag;
extern uint16  MusicEnTime;
extern _Flag   MusicTrigFlag;



#endif
