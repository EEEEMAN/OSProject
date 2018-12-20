#ifndef __INTERRUPTHANDLER_H__
#define __INTERRUPTHANDLER_H__

#include "../kernel1/OSDefine.h"

void defaultHandler(BYTE intNum, BYTE errorCode);
void UnknownHandler();
void keyboardHandler();
void mouseHandler();
void testTimerHandler();

#endif /*__INTERRUPTHANDLER_H__*/
