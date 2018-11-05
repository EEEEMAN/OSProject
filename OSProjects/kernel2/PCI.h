#ifndef __PCI_H__
#define __PCI_H__

#include "../kernel1/OSDefine.h"

#define PCI_CONFIG_ADDRESS_PORT					0xCF8
#define PCI_CONFIG_DATA_PORT					0xCFC

//#pragma pack(push, 1)
//typedef struct _PCIConfigurationSpace{
//	WORD venderID;
//	WORD deviceID;
//	WORD command;
//	WORD status;
//	BYTE revisionID;
//	BYTE interface;
//	BYTE subClass;
//	BYTE baseClass;
//	BYTE cacheLineSize;
//	BYTE masterLatencyTimer;
//	BYTE headerType;
//	BYTE BIST;
//	DWORD baseAddressRegister0;
//	DWORD baseAddressRegister1;
//	DWORD buff1[7];
//	BYTE capabilitiesPointer;
//	BYTE buff2[3];
//	DWORD buff3[2];
//}PCICS;
//#pragma pack(pop)

DWORD getPCICSData(int reg, int func, int devNum, int busNum);

#endif /*__PCI_H__*/
