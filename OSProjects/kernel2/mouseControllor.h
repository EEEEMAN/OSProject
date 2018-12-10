#ifndef __MOUSECONTROLLOR_H__
#define __MOUSECONTROLLOR_H__

#include "../kernel1/OSDefine.h"
#include "keyboardControllor.h"

#define MOUSE_COMMANDL_ACTIVE_MOUSE		0xF4

BOOL mouseEnable();
void mouseInterruptEnable();

#endif /*__MOUSECONTROLLOR_H__*/
