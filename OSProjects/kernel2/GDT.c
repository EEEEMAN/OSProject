#include "GDT.h"
#include "Task.h"
#include "asmfunc2.h"

void setDescriptor(GDescriptor* descriptor, DWORD baseAddress, DWORD limit,
		BYTE flags1, BYTE flags2){
	descriptor->limitLow = limit & 0xFFFF;
	descriptor->baseLow = baseAddress & 0xFFFF;
	descriptor->baseMid = (baseAddress & 0x00FF0000) >> 16;
	descriptor->flags1 = flags1;
	descriptor->flags2AndLimitHigh =  flags2 | ((limit & 0xFF0000) >> 16);
	descriptor->baseHigh = (baseAddress & 0xFF000000) >> 24;
}

void initGDT(DWORD address){
	GDescriptor* gd = (GDescriptor*)address;

	//initTSS();
	setDescriptor(&(gd[0]), 0, 0, 0, 0); //Null Descriptor
	setDescriptor(&(gd[1]), 0x00000000, 0xFFFFFFFF, 0x9A, 0xC0); //Kernel Code Descriptor
	setDescriptor(&(gd[2]), 0x00000000, 0xFFFFFFFF, 0x92, 0xC0); //Kernel Data Descriptor
	//setDescriptor(&(gd[3]), 0x20000, 104, 0x89, 0);
	//setDescriptor(&(gd[4]), 0x20000 + sizeof(TSS), 104, 0x89, 0);

	//loadGDT(GDT_DESCRIPTOR_COUNT * sizeof(GDescriptor), gd);
	loadGDT(0xFFFF, gd);
	//loadTR(0x18);
}
