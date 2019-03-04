/*******************************************************************************
	*
	* FILE NAME
	*						 	LedClass.h
	* BRIEF
	*							Communicate with LED
	*
*******************************************************************************/
#ifndef __LED_CLASS_H__
#define __LED_CLASS_H__

/* < -----------------Include Files --------------------> */
#include "Type_Def.h"
#include "MCU_Config.h"

/* < ---------------Data Type Redefine -----------------> */
#if AL94
  typedef union _LED_DATA_TYPE
	{
		_Uint8	SndByte[COLOR_TOTAL  * LENGTHEN_TOTAL];
		struct _COLOR_TYPE
		{
			_Uint8	DutyR;
			_Uint8	DutyB;
			_Uint8	DutyG;
		}Buffer[LED_TOTAL * LENGTHEN_TOTAL];
	} _Type_Led;
	
	typedef struct Horse_Type
	{
		uint8_t		Grp;
		uint8_t 	LenPre;
		uint8_t		Len;
		uint16_t 	AllLedCnt;
		uint16_t	PreLedCnt;
	}TypeHorseT;
#elif AL95
	typedef union _LED_DATA_TYPE
	{
		_Uint8	SndByte[COLOR_TOTAL];
		struct _COLOR_TYPE
		{
			_Uint8	DutyR;
			_Uint8	DutyG;
			_Uint8	DutyB;
		}Buffer[LED_TOTAL];
	} _Type_Led;

#elif AL91 | AL92
  typedef union _LED_DATA_TYPE
	{
		_Uint8	SndByte;
		struct _COLOR_TYPE
		{
			_Uint8	DutyR;
			_Uint8	DutyG;
			_Uint8	DutyB;
		}Buffer[LED_TOTAL];
	} _Type_Led;
	
	typedef struct Horse_Type
	{
		uint8_t		Grp;
		uint8_t 	LenPre;
		uint8_t		Len;
		uint16_t 	AllLedCnt;
		uint16_t	PreLedCnt;
	}TypeHorseT;
	
  #define		BIT0_DELAY			15
  #define 		BIT1_DELAY			30
  #define 		HIGH_DELAY			100
  
	
#elif AL99
	#define				GROUP_TOTAL					(_Uint8)7					/* GROUP数量		*/
	#define				GROUP_CNT					(_Uint8)38				/* GROUP灯数量	*/
	#define				GRP_LED_TOTAL				(_Uint8)228				/* LED总数量 		= GROUP_TOTAL * GROUP_CNT*/
	#define				COLOR_CNT					(_Uint8)3					/* 每灯颜色总数 */
	#define				GROUP_COLOR_TOTAL			(_Uint8)114				/* 每组颜色总数 = GROUP_CNT * COLOR_CNT*/

	#define				LIGHT_LEVEL							3

	#define				BIT0_H								1
	#define				BIT0_L								3
	#define				BIT1_H								3
	#define				BIT1_L								1

	/* Type Redefine */
	typedef 	struct		LED_TYPE
	{
		_Uint8		DutyG;
		_Uint8		DutyR;
		_Uint8		DutyB;
	} _TypeLed_ST;

#endif

/* < -------------Exported Parameters ------------------> */
extern _Flag					DirectFlag;
	
#if AL91 | AL92 | AL94 | AL95
	extern _Type_Led 			LedData;
  
	#if AL91 | AL94
	extern _Uint8          LedTotal;
	extern TypeHorseT	HorseInfo;
	#endif
  

#elif AL99
	extern _TypeLed_ST			ColorBuffer[GROUP_TOTAL][GROUP_CNT];

#endif

/*<---------------- Exported Function ------------------> */
void Led_Update(void);



#endif
