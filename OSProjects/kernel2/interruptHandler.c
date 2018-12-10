#include "interruptHandler.h"
#include "console.h"
#include "keyboardControllor.h"
#include "asmfunc2.h"
#include "PIC.h"
#include "PIT.h"
#include "mString.h"
#include "mScheduler.h"
#include "task.h"

void defaultHandler(BYTE intNum, BYTE errorCode) {
	cPrintf("Interrupt Occur(%d), ErrorCode:0x%x\n", intNum, errorCode);
	hltCall();
}

void UnknownHandler() {
	cPrintf("Unknown Exception.\n");
	hltCall();
}

void keyboardHandler() {
	BYTE scancode;
	scancode = readKBCBuffer();
	//키보드 버퍼에 스캔코드를 넣는다.
	if ((g_KeyboardBuffer.back + 1) % KB_BUFFER_SIZE
			!= g_KeyboardBuffer.front) {
		g_KeyboardBuffer.buffer[g_KeyboardBuffer.back] = scancode;
		g_KeyboardBuffer.back = (g_KeyboardBuffer.back + 1) % KB_BUFFER_SIZE;
	} else {
		cPrintf("keyboard bufer is full\n");
	}
	sendEOI(1);
}

void testTimerHandler() {
	g_timerCount++;
	sendEOI(0);
	schedule();
}
