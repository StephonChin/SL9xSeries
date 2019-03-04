/************************************************************************************************************
	*
	* FileName			Led_Class.c
	*
	* Description
	*								The protocol about communicate with LED, such as LED with KM5020, LED with UCS1903BC,
	*								LED drived by PWM, LED drived by general I/O or LED drived by custom protol.
	*
*************************************************************************************************************/
#include "Led_Class.h"

_Flag						DirectFlag;
  
/* Gloable Parameters */
#if AL91 | AL92 | AL94 | AL95
	_Type_Led 			LedData;
	
	#if AL91 | AL94
		_Uint8          LedTotal = LED_TOTAL;
		_Type_Led       LedDataBuf;
		static void Update_Send_Buffer(void);
		TypeHorseT	HorseInfo;
	#endif

#elif AL99
	_TypeLed_ST			ColorBuffer[GROUP_TOTAL][GROUP_CNT];

#endif


#if AL95
	_Uint8				RedEn = 0xFF;
	_Uint8				GrnEn = 0xFF;
	_Uint8				BleEn = 0xFF;
#endif



#if AL91 | AL94
/*
 * FUNCTION NAME  Update_Send_Buffer
 * BRIEF          Update the send buffer of AL91 & AL94 for different dirction
 */
static void Update_Send_Buffer(void)
{
	uint16 i = 0;
	uint16 j = 0;
  
    if (DirectFlag)
    {
      for (i = 0; i < LedTotal; i++)
      {
        LedDataBuf.Buffer[i].DutyR = LedData.Buffer[i].DutyR;
        LedDataBuf.Buffer[i].DutyG = LedData.Buffer[i].DutyG;
        LedDataBuf.Buffer[i].DutyB = LedData.Buffer[i].DutyB;
      }
    }
    else
    {
      for (i = 0; i < LedTotal; i++)
      {
        j = LedTotal - 1 - i;
        LedDataBuf.Buffer[i].DutyR = LedData.Buffer[j].DutyR;
        LedDataBuf.Buffer[i].DutyG = LedData.Buffer[j].DutyG;
        LedDataBuf.Buffer[i].DutyB = LedData.Buffer[j].DutyB;
      }
    }
}
#endif






/**************************************************************************************
	*
	* FunctionName		Led_Update
	* 
	*	Brief
	*									Include KM5020's LED driver protocol
 	*									Include UCS1903BC's Led driver protocol
	*									Include MCU PWM driver
	*									Include custom protocol
	*
***************************************************************************************/
void Led_Update(void)
{
//UCS1903BC---------------------------------AL94--------------------------------
#if AL94
	_Uint16	TempCnt 		= 0;
  _Uint8  TempBit  		= 0;
	_Uint8	*DataBufAdd	= 0;
	_Uint8  DataBuf 		= 0;
  _Uint16 ColorTotal  = 0;
  

   ColorTotal = (_Uint16)LedTotal * 3;

  
  Update_Send_Buffer();
	
	/* run from the header to tail */
	DataBufAdd = LedDataBuf.SndByte;																	
  for (TempCnt = 0; TempCnt < ColorTotal; TempCnt++)			/* Circle count caculated													*/
  {
    DataBuf = *DataBufAdd++;
    DataBuf /= BRIGHT_LEVEL;
  
    /* Address increase																*/
    for (TempBit = 0; TempBit < 8; TempBit++)							/* Send the bit data one bye one									*/
    {
      if ((DataBuf & 0x80) == 0x80)												/* Bit 1 data send																*/
      {
        PORT_COMM = SET;
        __asm("nop");__asm("nop");__asm("nop");__asm("nop");	
        __asm("nop");__asm("nop");__asm("nop");__asm("nop");	
        __asm("nop");__asm("nop");__asm("nop");__asm("nop");
        __asm("nop");__asm("nop");__asm("nop");__asm("nop");
        __asm("nop");__asm("nop");__asm("nop");__asm("nop");
        __asm("nop");__asm("nop");__asm("nop");__asm("nop");
        __asm("nop");__asm("nop");__asm("nop");__asm("nop");
        __asm("nop");__asm("nop");__asm("nop");__asm("nop");
        __asm("nop");__asm("nop");__asm("nop");__asm("nop");
        __asm("nop");__asm("nop");__asm("nop");__asm("nop");
        __asm("nop");__asm("nop");
        PORT_COMM = RESET;
        __asm("nop");__asm("nop");__asm("nop");__asm("nop");
        __asm("nop");__asm("nop");__asm("nop");__asm("nop");
        __asm("nop");__asm("nop");__asm("nop");__asm("nop");
        __asm("nop");__asm("nop");__asm("nop");__asm("nop");
      }
      else																								/* Bit0 data send																	*/
      {
        PORT_COMM = SET;
        __asm("nop");__asm("nop");__asm("nop");__asm("nop");
        __asm("nop");__asm("nop");
        PORT_COMM = RESET;
        __asm("nop");__asm("nop");__asm("nop");__asm("nop");
        __asm("nop");__asm("nop");__asm("nop");__asm("nop");
        __asm("nop");__asm("nop");__asm("nop");__asm("nop");
        __asm("nop");__asm("nop");__asm("nop");__asm("nop");
        __asm("nop");__asm("nop");__asm("nop");__asm("nop");
        __asm("nop");__asm("nop");__asm("nop");__asm("nop");
        __asm("nop");__asm("nop");__asm("nop");__asm("nop");
        __asm("nop");__asm("nop");__asm("nop");__asm("nop");
        __asm("nop");__asm("nop");__asm("nop");__asm("nop");
        __asm("nop");__asm("nop");__asm("nop");__asm("nop");
      }
      DataBuf <<= 1;																			/* move one bit to the left 											*/					
    }
	}
	
	PORT_COMM = RESET;
	DataBufAdd = 0;
	

	
//KM5020-----------------------------------------AL91 AL92----------------------------
#elif	AL91 | AL92
	_Uint16		ColorTemp		= 0;
  _Uint8  	BitTemp  		= 0;
  _Uint8		*DataBufAdd	= 0;
  _Uint8  	DataBuf 		= 0;
  _Uint8		TimeTemp		= 0;
	static 	_Uint8		BitCnt			= 0;
  
  
  #if AL91 
  Update_Send_Buffer();
  DataBufAdd = &LedDataBuf.SndByte;
  #else
  DataBufAdd = &LedData.SndByte;
  #endif
	
	/* <-- Get the color buffers' header address --> */
	BitCnt = 0;
	
	
	DataBuf=0x55;
  for(BitTemp=0;BitTemp<8;BitTemp++)
  {
    PORT_COMM = SET;
    if((DataBuf&0x80)!=0x80)  
    for(TimeTemp = 0; TimeTemp < BIT0_DELAY; TimeTemp++);  // BIT0     
    else               
    for(TimeTemp = 0; TimeTemp < BIT1_DELAY; TimeTemp++);  // BIT1
    PORT_COMM = RESET;
    for (TimeTemp = 0; TimeTemp < HIGH_DELAY; TimeTemp++);
    DataBuf <<= 1;
  }
//-----------------------------------------------Seacond  Head Send-----------------------------//		
  /*Second Frame 0xA 4BIT  0110 ??? 1010??? */
  DataBuf=0xAA;
  for(BitTemp=0;BitTemp<4;BitTemp++)
  {
    PORT_COMM = SET;
    if(!(DataBuf&0x80))   for (TimeTemp = 0; TimeTemp < BIT0_DELAY; TimeTemp++);   // BIT0
    else                  for (TimeTemp = 0; TimeTemp < BIT1_DELAY; TimeTemp++);   // BIT1
    PORT_COMM = RESET;
    for (TimeTemp = 0; TimeTemp < HIGH_DELAY; TimeTemp++);
    DataBuf <<=  1;
  }
//-----------------------------------------------Data Send-----------------------------//	
	for(ColorTemp = 0; ColorTemp < COLOR_TOTAL; ColorTemp++)
	{
	  DataBuf= *DataBufAdd++;
		for(BitTemp=0;BitTemp<8;BitTemp++)
		{
     PORT_COMM = SET;
     if(!(DataBuf & 0x80))   for (TimeTemp = 0; TimeTemp < BIT0_DELAY; TimeTemp++);   // BIT0
     else                    for (TimeTemp = 0; TimeTemp < BIT1_DELAY; TimeTemp++);   // BIT1
     PORT_COMM = RESET;
     for (TimeTemp = 0; TimeTemp < HIGH_DELAY; TimeTemp++);
     DataBuf <<=  1;
		}		
		BitCnt++;
		if(BitCnt==3)
		{
				PORT_COMM = SET;
				for (TimeTemp = 0; TimeTemp < BIT0_DELAY; TimeTemp++);		 // bit0
				PORT_COMM = RESET;
				for (TimeTemp = 0; TimeTemp < HIGH_DELAY; TimeTemp++);
				BitCnt = 0;	
		}
	}
  DataBufAdd = 0;
	
	
	
	
//---------------------AL95---------------------------------------------
#elif	AL95
	_Uint8	TempCnt 		= 0;
	_Uint8	TempColor		= 0;
  _Uint8  DataBuf 		= 0;
  _Uint8  TempBit  		= 0;
	_Uint8	*DataBufAdd	= 0;
	
    
	for (TempCnt = 1; TempCnt < LED_TOTAL; TempCnt++)			/* Circle count caculated													*/
	{
		DataBufAdd = &LedData.Buffer[TempCnt].DutyR;
		
		for (TempColor = 0; TempColor < 3; TempColor++)
		{
			DataBuf = *DataBufAdd++;
			/* Address increase																*/
			for (TempBit = 0; TempBit < 8; TempBit++)							/* Send the bit data one bye one									*/
		{
			if ((DataBuf & 0x80) != 0x80)												/* Bit 1 data send																*/
			{
				PORT_COMM = SET;
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");	
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");	
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");
				PORT_COMM = RESET;
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
			}
			else																								/* Bit0 data send																	*/
			{
				PORT_COMM = SET;
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");
				PORT_COMM = RESET;
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
			}
			DataBuf <<= 1;		 											
		}
		}
	}
	DataBuf = 0;
	
	
	if (LedData.Buffer[0].DutyG == 0)
	{
		if (GrnEn != 0x0)
		{
			GrnEn = 0x0;
			PWM->PHCHG &= ~(BIT13 | BIT5);
		}
	}
	else
	{
		if (GrnEn != 0x1)
		{
			GrnEn = 0x1;
			PWM->PHCHG |= BIT13;
		}
		PWM->CMPDAT5 	= LedData.Buffer[0].DutyG;
	}
	
	
	if (LedData.Buffer[0].DutyR == 0)
	{
		if (RedEn != 0x0)
		{
			RedEn = 0x0;
			PWM->PHCHG &= ~(BIT9 | BIT1);
		}
	}
	else
	{
		if (RedEn != 0x1)
		{
			RedEn = 0x1;
			PWM->PHCHG |= BIT9;
		}
		PWM->CMPDAT1 	= LedData.Buffer[0].DutyR;
	}
	
	
	
	if (LedData.Buffer[0].DutyB == 0)
	{
		if (BleEn != 0x0)
		{
			BleEn = 0x0;
			PWM->PHCHG &= ~(BIT12 | BIT4);
		}
	}
	else
	{
		if (BleEn != 0x1)
		{
			BleEn = 0x1;
			PWM->PHCHG |= BIT12;
		}
		PWM->CMPDAT4 	= LedData.Buffer[0].DutyB;
	}
	
	
// ------------------------------------AL99-------------------------------------------------
#elif AL99
	_Uint8	ColorTemp		= 0;
  _Uint8  TempBit  		= 0;
	_Uint8	*DataBufAdd	= 0;
	_Uint8  DataBuf 		= 0;
	_Uint8	TimeTemp		= 0;
	
	
	DataBufAdd = (_Uint8 *)ColorBuffer[0];	
	
	TimeTemp = 100;
	while(TimeTemp--);
	
	/* Group 1 */
	/* 按地址加1的方式发送一组灯的所有颜色数据 */
	for (ColorTemp = 0; ColorTemp < GROUP_COLOR_TOTAL; ColorTemp++)			//select LED
	{
		DataBuf = *DataBufAdd++;
		DataBuf /= LIGHT_LEVEL;
					
		for (TempBit = 0; TempBit < 8; TempBit++)							/* Send the bit data one bye one									*/
		{
			if ((DataBuf & 0x80) == 0x80)												/* Bit 1 data send																*/
			{
				PORT_COMM_1 = SET;
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");	
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");	
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");
				PORT_COMM_1 = RESET;
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
			}
			else																								/* Bit0 data send																	*/
			{
				PORT_COMM_1 = SET;
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");
				PORT_COMM_1 = RESET;
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
			}
			DataBuf <<= 1;																			/* move one bit to the left 											*/					
		}
	}
	
	
	
	/* Group 2 */
	TimeTemp = 100;
	while(TimeTemp--);
	
	/* 按地址加1的方式发送一组灯的所有颜色数据 */
	for (ColorTemp = 0; ColorTemp < GROUP_COLOR_TOTAL; ColorTemp++)			//select LED
	{
		DataBuf = *DataBufAdd++;
		DataBuf /= LIGHT_LEVEL;
					
		for (TempBit = 0; TempBit < 8; TempBit++)							/* Send the bit data one bye one									*/
		{
			if ((DataBuf & 0x80) == 0x80)												/* Bit 1 data send																*/
			{
				PORT_COMM_2 = SET;
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");	
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");	
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");
				PORT_COMM_2 = RESET;
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
			}
			else																								/* Bit0 data send																	*/
			{
				PORT_COMM_2 = SET;
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");
				PORT_COMM_2 = RESET;
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
			}
			DataBuf <<= 1;																			/* move one bit to the left 											*/					
		}
	}
	
	
	
	/* Group 3 */	
	TimeTemp = 100;
	while(TimeTemp--);
	
	/* 按地址加1的方式发送一组灯的所有颜色数据 */
	for (ColorTemp = 0; ColorTemp < GROUP_COLOR_TOTAL; ColorTemp++)			//select LED
	{
		DataBuf = *DataBufAdd++;
		DataBuf /= LIGHT_LEVEL;
					
		for (TempBit = 0; TempBit < 8; TempBit++)							/* Send the bit data one bye one									*/
		{
			if ((DataBuf & 0x80) == 0x80)												/* Bit 1 data send																*/
			{
				PORT_COMM_3 = SET;
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");	
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");	
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");
				PORT_COMM_3 = RESET;
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
			}
			else																								/* Bit0 data send																	*/
			{
				PORT_COMM_3 = SET;
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");
				PORT_COMM_3 = RESET;
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
			}
			DataBuf <<= 1;																			/* move one bit to the left 											*/					
		}
	}
	
	
	
	/* Group 4 */
	TimeTemp = 100;
	while(TimeTemp--);
	
	/* 按地址加1的方式发送一组灯的所有颜色数据 */
	for (ColorTemp = 0; ColorTemp < GROUP_COLOR_TOTAL; ColorTemp++)			//select LED
	{
		DataBuf = *DataBufAdd++;
		DataBuf /= LIGHT_LEVEL;
					
		for (TempBit = 0; TempBit < 8; TempBit++)							/* Send the bit data one bye one									*/
		{
			if ((DataBuf & 0x80) == 0x80)												/* Bit 1 data send																*/
			{
				PORT_COMM_4 = SET;
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");	
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");	
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");
				PORT_COMM_4 = RESET;
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
			}
			else																								/* Bit0 data send																	*/
			{
				PORT_COMM_4 = SET;
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");
				PORT_COMM_4 = RESET;
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
			}
			DataBuf <<= 1;																			/* move one bit to the left 											*/					
		}
	}
	
	
	/* Group 5 */
	/* 按地址加1的方式发送一组灯的所有颜色数据 */
	for (ColorTemp = 0; ColorTemp < GROUP_COLOR_TOTAL; ColorTemp++)			//select LED
	{
		DataBuf = *DataBufAdd++;
		DataBuf /= LIGHT_LEVEL;
					
		for (TempBit = 0; TempBit < 8; TempBit++)							/* Send the bit data one bye one									*/
		{
			if ((DataBuf & 0x80) == 0x80)												/* Bit 1 data send																*/
			{
				PORT_COMM_5 = SET;
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");	
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");	
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");
				PORT_COMM_5 = RESET;
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
			}
			else																								/* Bit0 data send																	*/
			{
				PORT_COMM_5 = SET;
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");
				PORT_COMM_5 = RESET;
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
			}
			DataBuf <<= 1;																			/* move one bit to the left 											*/					
		}
	}
	
	
	
	/* Group 6 */
	TimeTemp = 100;
	while(TimeTemp--);
	
	/* 按地址加1的方式发送一组灯的所有颜色数据 */
	for (ColorTemp = 0; ColorTemp < GROUP_COLOR_TOTAL; ColorTemp++)			//select LED
	{
		DataBuf = *DataBufAdd++;
		DataBuf /= LIGHT_LEVEL;
					
		for (TempBit = 0; TempBit < 8; TempBit++)							/* Send the bit data one bye one									*/
		{
			if ((DataBuf & 0x80) == 0x80)												/* Bit 1 data send																*/
			{
				PORT_COMM_6 = SET;
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");	
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");	
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");
				PORT_COMM_6 = RESET;
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
			}
			else																								/* Bit0 data send																	*/
			{
				PORT_COMM_6 = SET;
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");
				PORT_COMM_6 = RESET;
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
			}
			DataBuf <<= 1;																			/* move one bit to the left 											*/					
		}
	}
	
	/* Group 7 */
	TimeTemp = 100;
	while(TimeTemp--);
	
	/* 按地址加1的方式发送一组灯的所有颜色数据 */
	for (ColorTemp = 0; ColorTemp < 18; ColorTemp++)			//select LED
	{
		DataBuf = *DataBufAdd++;
					
		for (TempBit = 0; TempBit < 8; TempBit++)							/* Send the bit data one bye one									*/
		{
			if ((DataBuf & 0x80) == 0x80)												/* Bit 1 data send																*/
			{
				PORT_COMM_7 = SET;
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");	
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");	
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");
				PORT_COMM_7 = RESET;
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
			}
			else																								/* Bit0 data send																	*/
			{
				PORT_COMM_7 = SET;
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");
				PORT_COMM_7 = RESET;
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
				__asm("nop");__asm("nop");__asm("nop");__asm("nop");
			}
			DataBuf <<= 1;		 											
		}
	}
	
	DataBufAdd = 0;

#endif
}

