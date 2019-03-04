/****************************************************************************
 *
 * FunctionName		Key.c
 *
 * Brief
 *								Get the key status
 *
*****************************************************************************/
#include "Key.h"


/*------------------------< Gloable Parameters >------------------------*/
_EnKey KeyStatus;

#if AL94

  #if _AL94_
  
    #define KEY_LONG_TIME       70
    
  #elif _AL94_24V3_ | _AL94_24V6_
  
    #define KEY_LONG_TIME       100
    #define KEY_LONG_LONG_TIME  250
    
  #else
  
    #error "AL94 type havn't defined!"
    
  #endif
  
#else

  #define KEY_LONG_TIME   70
  
#endif


/*
 * FunctionName		Key_Scan
 */
void Key_Scan(void)
{
  #if _AL94_24V3_ | _AL94_24V6_
  
	static _Flag			KeyLongDone;
  static _Flag      KeyLongLongDone;
	static _Uint8			KeyTime;
  
	if (PORT_KEY == RESET)
	{
		if (!(KeyLongDone && KeyLongLongDone))
		{
			KeyTime++;

      if (KeyTime > KEY_LONG_TIME && !KeyLongDone)
      {
        KeyLongDone = TRUE;
        KeyStatus = KEY_LONG;
      }
      
      if (KeyTime > KEY_LONG_LONG_TIME && !KeyLongLongDone)
      {
        KeyLongLongDone = TRUE;
        KeyStatus = KEY_LONG_LONG;
      }
		}
	}
	
	else
	{
		if (KeyLongDone == FALSE && KeyLongLongDone == FALSE && KeyTime > 1)
		{
			KeyStatus = KEY_SHORT;
		}
		KeyTime = 0;
		KeyLongDone = FALSE;
    KeyLongLongDone = FALSE;
	}
  //--------------------------------------------------------
  #else
    static _Flag			KeyDoneFlag;
    static _Uint8			KeyTime;
    
    if (PORT_KEY == RESET)
    {
      if (KeyDoneFlag == FALSE)
      {
        KeyTime++;
        
        if (KeyTime > KEY_LONG_TIME)
        {
          KeyDoneFlag = TRUE;
          KeyStatus = KEY_LONG;
        }
      }
    }
    
    else
    {
      if (KeyDoneFlag == FALSE && KeyTime > 1)
      {
        KeyStatus = KEY_SHORT;
      }
      KeyTime = 0;
      KeyDoneFlag = FALSE;
    }
  #endif
}
