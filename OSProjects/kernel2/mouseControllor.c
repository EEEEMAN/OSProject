#include "mouseControllor.h"
#include "asmfunc2.h"
#include "console.h"
#include "graphics.h"

BOOL mouseEnable() {
	BOOL intStat = getInterruptStatus();
	setInterruptStatus(FALSE);
	BOOL ack = FALSE;
	int i;

	if (writeKBCCommand(KB_CONTROL_ACTIVE_MOUSE) == FALSE) {
		setInterruptStatus(intStat);
		return FALSE;
	}
	for (i = 0; i < 100; i++) {
		if (writeKBCCommand(KB_CONTROL_MOUSE_CONTROL) == FALSE) {
			setInterruptStatus(intStat);
			return FALSE;
		}
		if (writeKBCBuffer(MOUSE_COMMANDL_ACTIVE_MOUSE) == FALSE) {
			setInterruptStatus(intStat);
			return FALSE;
		}
		ack = waitACK();
		if (ack == TRUE) break;
	}

	setInterruptStatus(intStat);
	return ack;
}

void mouseInterruptEnable() {
	BYTE commandByte;

	writeKBCCommand(KB_CONTROL_READCOMMANDBYTE);
	waitKBCOutBufferFull();
	commandByte = readKBCBuffer();

	//마우스인터럽트 비트를 활성화
	commandByte |= 0x02;
	writeKBCCommand(KB_CONTROL_WRITECOMMANDBYTE);
	writeKBCBuffer(commandByte);
}

BYTE mouseCheck() {
	int i;
	BYTE result;
	if (writeKBCCommand(KB_CONTROL_MOUSE_CONTROL) == FALSE) {
		return FALSE;
	}
	if (writeKBCBuffer(0xF2) == FALSE) {
		return FALSE;
	}
	for (i = 0; i < 100; i++){
		waitKBCOutBufferFull();
		if (isMouseData() == TRUE){
			result = readKBCBuffer();
			return result;
		}
		readKBCBuffer();
	}
	return 0xFF;
}

BOOL isMouseData(){
	if (in8bits(KBC_PORT_REGISTER) & 0x20){
		return TRUE;
	}
	return FALSE;
}

void mouseTest() {
	int readCount = 0;
	BYTE data;
	MousePacket mousePacket;
	int rX, rY;
	VBEInfo* vbeInfo = (VBEInfo*) VBE_INFO_ADDRESS;

	if (*((BYTE*) 0x8FFF) == 0x00) {
		while (1) {
			if (g_MouseBuffer.front == g_MouseBuffer.back)
				continue;
			data = g_MouseBuffer.buffer[g_MouseBuffer.front];
			g_MouseBuffer.front = (g_MouseBuffer.front + 1) % MOUSE_BUFFER_SIZE;

			//마우스 코드 조합
			switch (readCount) {
			case 0:
				mousePacket.status = data;
				readCount++;
				break;
			case 1:
				mousePacket.posX = data;
				readCount++;
				break;
			case 2:
				mousePacket.posY = data;
				readCount = 0;

				rX = mousePacket.posX & 0xFF;
				rY = mousePacket.posY & 0xFF;
				if ((mousePacket.status & MOUSE_PACKETFLAGS_SIGN_X) != 0) { //음수인경우
					rX |= (0xFFFFFF00);
				}
				if ((mousePacket.status & MOUSE_PACKETFLAGS_SIGN_Y) != 0) { //음수인경우
					rY |= (0xFFFFFF00);
				}
				rY = -rY;

				cPrintf("X:%d, Y:%d, L:%d, R:%d, C:%d\n",
						rX, rY,
						(mousePacket.status & MOUSE_PACKETFLAGS_BUTTON_L) == 0? 0:1,
						(mousePacket.status & MOUSE_PACKETFLAGS_BUTTON_R) == 0? 0:1,
						(mousePacket.status & MOUSE_PACKETFLAGS_BUTTON_C) == 0? 0:1);
				break;
			}
		}
	} else {
		while (1) {
			if (g_MouseBuffer.front == g_MouseBuffer.back)
				continue;
			data = g_MouseBuffer.buffer[g_MouseBuffer.front];
			g_MouseBuffer.front = (g_MouseBuffer.front + 1) % MOUSE_BUFFER_SIZE;

			//마우스 코드 조합
			switch (readCount) {
			case 0:
				mousePacket.status = data;
				readCount++;
				break;
			case 1:
				mousePacket.posX = data;
				readCount++;
				break;
			case 2:
				mousePacket.posY = data;
				readCount = 0;

				rX = mousePacket.posX & 0xFF;
				rY = mousePacket.posY & 0xFF;
				if ((mousePacket.status & MOUSE_PACKETFLAGS_SIGN_X) != 0) { //음수인경우
					rX |= (0xFFFFFF00);
				}
				if ((mousePacket.status & MOUSE_PACKETFLAGS_SIGN_Y) != 0) { //음수인경우
					rY |= (0xFFFFFF00);
				}
				rY = -rY;

				drawFillRect(
						g_GraphicsManager.mousePosX
								- g_GraphicsManager.mouseCenterX,
						g_GraphicsManager.mousePosY
								- g_GraphicsManager.mouseCenterY,
						MOUSE_CURSOR_WIDTH, MOUSE_CURSOR_HEIGHT,
						g_GraphicsManager.backGroundColor);

				if ((int) g_GraphicsManager.mousePosX + rX
						>= vbeInfo->resolutionX) {
					g_GraphicsManager.mousePosX = vbeInfo->resolutionX - 1;
				} else if ((int) g_GraphicsManager.mousePosX + rX < 0) {
					g_GraphicsManager.mousePosX = 0;
				} else {
					g_GraphicsManager.mousePosX += rX;
				}

				if ((int) g_GraphicsManager.mousePosY + rY
						>= vbeInfo->resolutionY) {
					g_GraphicsManager.mousePosY = vbeInfo->resolutionY - 1;
				} else if ((int) g_GraphicsManager.mousePosY + rY < 0) {
					g_GraphicsManager.mousePosY = 0;
				} else {
					g_GraphicsManager.mousePosY += rY;
				}

				drawMouseCursor();

				if ((mousePacket.status & MOUSE_PACKETFLAGS_BUTTON_L) != 0) {
					drawFillRectwithColorCode(
							g_GraphicsManager.mousePosX
									- g_GraphicsManager.mouseCenterX,
							g_GraphicsManager.mousePosY
									- g_GraphicsManager.mouseCenterY,
							MOUSE_CURSOR_WIDTH, MOUSE_CURSOR_HEIGHT, 0x1F0000);
				} else if ((mousePacket.status & MOUSE_PACKETFLAGS_BUTTON_R)
						!= 0) {
					drawFillRectwithColorCode(
							g_GraphicsManager.mousePosX
									- g_GraphicsManager.mouseCenterX,
							g_GraphicsManager.mousePosY
									- g_GraphicsManager.mouseCenterY,
							MOUSE_CURSOR_WIDTH, MOUSE_CURSOR_HEIGHT, 0x00001F);
				} else if ((mousePacket.status & MOUSE_PACKETFLAGS_BUTTON_C)
						!= 0) {
					drawFillRectwithColorCode(
							g_GraphicsManager.mousePosX
									- g_GraphicsManager.mouseCenterX,
							g_GraphicsManager.mousePosY
									- g_GraphicsManager.mouseCenterY,
							MOUSE_CURSOR_WIDTH, MOUSE_CURSOR_HEIGHT, 0x1F3F1F);
				}
				break;
			}
		}
	}
}
