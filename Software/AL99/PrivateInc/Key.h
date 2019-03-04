#ifndef _KEY_H__
#define _KEY_H__

#include "Type_Def.h"
#include "MCU_Config.h"

typedef enum KEY_TYPE
{
	KEY_IDLE,
	KEY_SHORT,
	KEY_LONG
}_EnKey;

void Key_Scan(void);
extern _EnKey			KeyStatus;

#endif
