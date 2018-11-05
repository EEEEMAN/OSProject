#include "kernel.h"
#include "asmfunc.h"
#include "utility.h"
#include "page.h"

void _entry() {
	BYTE mainKernelSize = (*(BYTE*)(0x7c00 + 3));
	memcopy((void*)0x600000, (void*)0x30000, mainKernelSize * 512);
	initPage();
	jumpToMainKernel();
	while(1){};
}
