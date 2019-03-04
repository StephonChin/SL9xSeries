#ifndef _MUSIC_H_
#define _MUSIC_H_

//include files
#include "Type_Def.h"
#include "Led_Class.h"
#include "Display_Ctrl.h"

//type redefine
#if AL99
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

extern _TypeMusic   MusicMode;

#else
extern uint8   MusicMode;

#endif



//exported function
void Music_Mode(void);


//exported arguments
extern _Flag   MusicEnFlag;
extern uint16  MusicEnTime;
extern _Flag   MusicTrigFlag;


//file function
#if AL92 | AL91 | AL95 | AL94
static void Music_DO(void);
static void Music_RE(void);
static void Music_MI(void);
static void Music_FA(void);
static void Music_SO(void);
static void Music_LA(void);
static void Music_XI(void);

#endif



#endif
