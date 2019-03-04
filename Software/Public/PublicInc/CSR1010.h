/**************************************************************************************
	*
	* FileName	Csr1010.h
	* 
***************************************************************************************/
#ifndef __CSR1010_H__
#define __CSR1010_H__

/*<---------------------Include Files---------------------------> */
#include "Type_Def.h"

/* <------------------------define------------------------------> */
#define 	RCV_BYTE_MAX									((_Uint8)20)
#define 	RCV_IDLE											((_Uint8)0)
#define		RCV_END												((_Uint8)1)
#define		RCV_ERR												((_Uint8)2)


/* <--------------------------Type Define-----------------------> */
typedef struct RCV_DATA_TYPE
{
	_Uint8 		DataBuf[6];
}_TypeStructRcv;


typedef struct SND_DATA_TYPE
{
	enum SND_STATUS
	{
		SND_IDLE,	
		SND_TYPE,	
		SND_NORMAL, 
		SND_HORSE,
		SND_SYN
	}SndStatus;
	_Uint8 		DataBuf[8];
}_TypeStructSnd;


/***
	* @Brief Exported Functions
	*/
void Uart_Clear_Buf(void);
void Csr1010_Rcv_Data(void);
void Csr1010_Snd_Data(void);
	

/***
	* @Brief File Functions
	*/
static void Csr1010_Rcv_Byte(void);
static void Csr1010_Snd_Byte(_Uint8);


/***
	* @Brief Exported Variables
	*/
extern _TypeStructRcv 		RcvData;
extern _TypeStructSnd 		SndData;
extern _Flag							RcvFlag;
extern _Uint8							SynData[5];
extern _Uint8							ChkSumReply[4];

#endif
