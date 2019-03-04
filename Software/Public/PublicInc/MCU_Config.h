/*******************************************************************************
	*
	* FILE NAME
	*						MCU_Config.h
	*
*******************************************************************************/
#ifndef __MCU_CONFIG_H__
#define __MCU_CONFIG_H__

/*<------------------Include Files--------------------> */
#include "Type_Def.h"

/*<-----------------Define-----------------------> */
#define		PLL_CLOCK					48000000

#define		PORT_RX						P12
#define		PORT_TX						P13

#if AL91 | AL92 | AL_CURTAIN
#define		PORT_BT_CE				P06
#define		PORT_BT_DT				P14
#define		PORT_COMM					P24

#elif AL94
#define		PORT_BT_CE				P06
#define		PORT_BT_DT				P07
#define		PORT_KEY					P15
#define		PORT_COMM					P24

#elif AL95
#define		PORT_BT_CE				P15
#define		PORT_BT_DT				P14
#define		PORT_COMM					P24

#elif AL96
#define		PORT_BT_CE				P14
#define		PORT_BT_DT				P25
#define		PORT_KEY					P15
#define		PORT_G						P07
#define		PORT_R						P06
#define		PORT_B						P05
#define		PORT_W						P04	

#elif AL99
#define		PORT_BT_CE				P35
#define		PORT_BT_DT				P34
#define		PORT_KEY					P15
#define		PORT_COMM_1				P04
#define		PORT_COMM_2				P05
#define 	PORT_COMM_3				P06
#define		PORT_COMM_4				P07
#define		PORT_COMM_5				P25
#define		PORT_COMM_6				P24
#define		PORT_COMM_7				P14

#endif



/*<-----------------File Functions--------------------> */
static void CLK_Init(void);
static void WDT_Init(void);
static void GPIO_Init(void);
static void UART_Init(void);
static void TIM_Init(void);
static void PWM_Init(void);


/*<-----------------Exported Function-----------------> */
void MCU_Config(void);


/*---------------------<Exported Paramters>----------------------*/
extern _Uint8	HseStatus;


#endif
