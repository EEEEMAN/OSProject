#include "Task.h"
#include "utility2.h"
#include "GDT.h"
#include "console.h"
#include "asmfunc2.h"
#include "mScheduler.h"

void initTSSDescriptors(DWORD GDTAddress, DWORD TSSAddress) {
	int i;
	GDescriptor* gd = (GDescriptor*) GDTAddress;

	//모든 TSS와 TSSDescriptor를 각각 매핑
	for (i = 0; i < TASK_COUNT_MAX; i++) {
		TSS* testTask = (TSS*) (TSS_START + sizeof(TSS) * i);
		setDescriptor(&(gd[i + 3]), (DWORD) testTask, 104, 0x89, 0);
	}

	//현재 실행중인 태스크 설정
	initTSS((TSS*)TSSAddress, 0, 0);
	loadTR(3 * 8);
}

void initTSS(TSS* tss, void* handlerAddress, void* stackAddress) {
	tss->preTaskLink = 0;
	tss->esp0 = 0;
	tss->ss0 = 0;
	tss->esp1 = 0;
	tss->ss1 = 0;
	tss->esp2 = 0;
	tss->ss2 = 0;
	tss->cr3 = 0x00200000;
	tss->eip = (DWORD) handlerAddress;
	tss->eflags = 0x00000202;
	tss->eax = 0;
	tss->ecx = 0;
	tss->edx = 0;
	tss->ebx = 0;
	tss->esp = (DWORD) stackAddress;
	tss->ebp = 0;
	tss->esi = 0;
	tss->edi = 0;
	tss->es = 2 * 8;
	tss->cs = 1 * 8;
	tss->ss = 2 * 8;
	tss->ds = 2 * 8;
	tss->fs = 2 * 8;
	tss->gs = 2 * 8;
	tss->LDTSelector = 0;
	tss->T_Flag = 0;
	tss->IOMapBaseAddress = 0x4000;
}
