#include "mouseControllor.h"
#include "asmfunc2.h"

BOOL mouseEnable(){
	BOOL intStat = getInterruptStatus();
	setInterruptStatus(FALSE);

	if (writeKBCCommand(KB_CONTROL_ACTIVE_MOUSE) == FALSE){
		return FALSE;
	}
	if (writeKBCCommand(KB_CONTROL_MOUSE_CONTROL) == FALSE){
		return FALSE;
	}
	if (writeKBCBuffer(MOUSE_COMMANDL_ACTIVE_MOUSE) == FALSE){
		return FALSE;
	}

	setInterruptStatus(intStat);
	return waitACK();
}

void mouseInterruptEnable(){
	BYTE commandByte;

	writeKBCCommand(KB_CONTROL_READCOMMANDBYTE);
	waitKBCOutBufferFull();
	commandByte = readKBCBuffer();

	//마우스인터럽트 비트를 활성화
	commandByte |= 0x02;
	writeKBCCommand(KB_CONTROL_WRITECOMMANDBYTE);
	writeKBCBuffer(commandByte);
}
