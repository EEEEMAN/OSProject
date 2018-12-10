#include "console.h"
#include "mainKernel.h"
#include "GDT.h"
#include "IDT.h"
#include "PIC.h"
#include "PIT.h"
#include "asmfunc2.h"
#include "keyboardControllor.h"
#include "mString.h"
#include "utility2.h"
#include "shell.h"
#include "mMemory.h"
#include "mList.h"
#include "mScheduler.h"
#include "task.h"
#include "HDControllor.h"
#include "graphics.h"

void _entry() {
	//모니터화면 초기화
	initVideoMemory();
	cPrintf("kernel2 start...");
	//커널 사이즈(섹터단위)를 가져옴
	BYTE subKernelSize = (*(BYTE*) (0x7c00 + 2));
	BYTE mainKernelSize = (*(BYTE*) (0x7c00 + 3));
	cPrintf("Main Kernel Start...\n");
	cPrintf("subkernel size:%dbyte\n", subKernelSize * 512);
	cPrintf("mainkernel size:%dbyte\n", mainKernelSize * 512);

	//메인커널을 임시로 저장해뒀던 공간을 비움
	memSet((void*) 0x30000, 0, mainKernelSize * 512);

	//GDT초기화
	initGDT(GDT_START);
	cPrintf("GDT initialization completed.\n");
	//IDT초기화
	initIDT(IDT_START);
	cPrintf("IDT initialization completed.\n");
	//PIT초기화
	initPIT(MSTOCOUNT(1), TRUE);
	cPrintf("PIT initialization completed.\n");
	//메모리 체크
	cPrintf("memory initializing...");
	DWORD mem = initMemoryManager();
	cPrintf("%dMB available.\n", mem / 1024 / 1024);

	//키보드 활성화
	if (activeKBC() == TRUE) {
		cPrintf("KBC enabled.\n");
		if (activeKeyboard() == 1) {
			cPrintf("keyboard enabled.\n");

//			//ps2키보드일경우 에코테스트, 스캔코드셋 확인
//			if (KBCechoTest() == TRUE)
//				cPrintf("keyboard echo test passed\n");
//			else
//				cPrintf("keyboard echo test fail\n");
//
//			BYTE k = getScancodeType();
//			if (k == SCANCODE_TYPE1)
//				cPrintf("scancode type:1\n");
//			else if (k == SCANCODE_TYPE2)
//				cPrintf("scancode type:2\n");
//			else if (k == SCANCODE_TYPE3)
//				cPrintf("scancode type:3\n");
//			else
//				cPrintf("scancode:0x%x\n", k);
//			while (isOutBufferFull() == TRUE) {
//				k = readKBCBuffer();
//				cPrintf("buffer:0x%x\n", k);
//			}
		}
	} else {
		cPrintf("KBC activation failed.\n");
	}
	clearKBCBuffer(); //키보드 컨트롤러 버퍼를 비움

	//PIC초기화하고 인터럽트 활성화
	initPIC();
	cPrintf("PIC initialization completed.\n");
	enableInterrupt();
	cPrintf("Interrupt enabled.\n");

//	//타이머 테스트
//	cPrintf("Timer Test");
//	while (g_timerCount < 1000) {
//		printChar(g_cursorOffset + (g_timerCount / 200), g_consoleAttribute,
//				'.');
//	}
//	cPrintf(".....Passed\n");

	//TSS 초기화
	initTSSDescriptors(GDT_START, TSS_START);
	cPrintf("TSS initialization completed.\n");

	//태스크 풀 초기화
	initTaskPool(TASKPOOL_ADDRESS);

	if (mouseEnable() == TRUE){
		cPrintf("mouse enabled\n");
		mouseInterruptEnable();
	}

	cPrintf("MasterIMR:0x%x\n", getIMR(TRUE));
	cPrintf("SlaveIMR:0x%x\n", getIMR(FALSE));

	//셸 실행
	if (*((BYTE*)0x8FFF) == 0x00){
		shellRun();
	}else if (*((BYTE*)0x8FFF) == 0x01){
		VBEInfo* vbeInfo = (VBEInfo*)0x8E00;
		initGraphicsPalette();
		VBE16BitsColor col;
		col.R = 31;
		drawPixel(500, 300, col);
	}

	while(1);
}
