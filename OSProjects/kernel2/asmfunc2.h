#ifndef __ASNFUNC_H__
#define __ASNFUNC_H__

#include "../kernel1/OSDefine.h"
#include "Task.h"

BYTE in8bits(WORD port);
void out8bits(WORD port, BYTE data);
DWORD in32bits(WORD port);
void out32bits(WORD port, DWORD data);

void loadIDT(WORD size, void* address);
void loadGDT(WORD size, void* address);

void enableInterrupt();
void disableInterrupt();
void hltCall();

void loadTR(int offset);
void taskswitch(int eip, int cs);

DWORD getEFLAGS();
void setEFLAGS(DWORD eflags);
BOOL getInterruptStatus();
void setInterruptStatus(BOOL status);
DWORD getCR0Register();
void setCR0Register(DWORD CR0);

DWORD memoryTest(DWORD start, DWORD end);

#endif /*__ASNFUNC_H__*/
