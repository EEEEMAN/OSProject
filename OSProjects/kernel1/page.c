#include "page.h"
#include "asmfunc.h"

void initPage(){
	DWORD* pageDirectory;
	int i;
	pageDirectory = (void*)0x200000;
	for(i = 0; i < 1024; i++){
		pageDirectory[i] = (i << 22) | 0x83;
	}
	setCR3Register(0x200000);
	activePaging();
}
