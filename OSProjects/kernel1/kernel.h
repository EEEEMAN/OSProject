#ifndef __KERNEL_H__
#define __KERNEL_H__

#include "OSDefine.h"

#define CONFIG_ADDRESS_PORT			0xcf8
#define	CONFIG_DATA_PORT			0xcfc

/*
DWORD getConfigData(BYTE bus, BYTE device, BYTE func, BYTE addr);
WORD getVenderID(BYTE bus, BYTE device, BYTE func);
WORD getDeviceID(BYTE bus, BYTE device, BYTE func);
WORD getClassCode(BYTE bus, BYTE device, BYTE func);
BYTE getHeaderType(BYTE bus, BYTE device, BYTE func);
*/

#endif /*__KERNEL_H__*/
