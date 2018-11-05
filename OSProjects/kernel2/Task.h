#ifndef __TASK_H__
#define __TASK_H__

#include "../kernel1/OSDefine.h"

//TaskStateSegment (104Byte)
#pragma pack(push, 1)
typedef struct _TSS{
	DWORD preTaskLink, esp0, ss0, esp1, ss1, esp2, ss2;
	DWORD cr3, eip, eflags, eax, ecx, edx, ebx, esp, ebp, esi, edi;
	DWORD es, cs, ss, ds, fs, gs;
	DWORD LDTSelector;
	WORD T_Flag, IOMapBaseAddress;
}TSS;
#pragma pack(pop)

void initTSSDescriptors(DWORD GDTAddress, DWORD TSSAddress);
void initTSS(TSS* tss, void* handlerAddress, void* stackAddress);

#endif /*__TASK_H__*/
