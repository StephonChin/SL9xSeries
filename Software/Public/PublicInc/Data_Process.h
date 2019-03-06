/*******************************************************************************
	*
	* FILE NAME
	*							Data_Process.h
	*
*******************************************************************************/
#ifndef __DATA_PROCESS_H__
#define __DATA_PROCESS_H__

/*<---------------- Include Files --------------------> */
#include "Type_Def.h"
#include "Flash_Prgrm.h"
#include "CSR1010.h"
#include "Display_Ctrl.h"
#include "Timer_Ctrl.h"
#include "BT_Control.h"
#include "Music.h"

#if AL96
#include "Sleep.h"
#endif

#if AL99 | AL94 | AL96
 #include "Key.h"
#endif

/*<---------------- Define ---------------------------> */
#define     RED             				0x00
#define     GREEN           				0x01
#define     BLUE            				0x02
#define     ORANGE         					0x03
#define     PINK            				0x04
#define     SPRING_GREEN    				0x05
#define     GOLD            				0x06
#define     PEACH           				0x07
#define     LAWN_GREEN      				0x08
#define     CYAN            				0x09
#define     SKY_BLUE        				0x0a
#define     YELLOW          				0x0b
#define     PURPLE          				0x0c
#define     WHITE           				0x0d
#define		COLD_WHITE						0x0e
#define		WARM_WHITE						0x0f
#define 	DARK_GREEN 						0x10
#define		DARK_RED						0x11

#define		R								0
#define		G								1
#define		B								2
#define		W								3
#define		COLOR_MAX						0x1C

#define		MODE_MAX						0xD

#define		CUSTOM_MAX						20

//typedefine-------------------------------------
typedef struct CUSTOM_Type
{
	uint8_t EnFlag;
	uint8_t Mode;
	uint8_t Color;
}TypeCustomT;




/*<---------------- Exported Function-----------------> */
void User_Data_Init(void);
void Data_Process(void);

/*<---------------- File Functions -------------------> */
#if AL99 | AL94 | AL96
static void 						Key_Process(void);
#endif
static void 						Password_Process(void);
static void 						Syn_Process(void);
static void 						Count_Down_Process(void);
static void 						CSR1010_Process(void);
static void 						Color_Value_Get(_Uint8	ColorValBuf);
static _Uint16						CRC16_Cal(_Uint8 Buffer[]);
static _Uint8						Hex_To_Char(_Uint8);



/*<---------------- Exported Parameters --------------> */
extern _Flag						SynFlag;
extern _Uint8						ChkSumH;
extern _Uint8						ChkSumL;
extern _Uint8						ChkSumRst;
extern _Uint8						ChkSumRstSave;
extern _Uint8						PowerOnNum;
extern _Flag						WdtRstFlag;
extern TypeCustomT					CustomData[];




#endif
