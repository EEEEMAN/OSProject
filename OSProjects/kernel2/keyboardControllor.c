#include "keyboardControllor.h"
#include "asmfunc2.h"

BOOL isOutBufferFull() {
	BYTE statusRegister;
	statusRegister = in8bits(KBC_PORT_REGISTER);

	if (statusRegister & 0x01)
		return TRUE;
	return FALSE;
}

BOOL isInBufferFull() {
	BYTE statusRegister;
	statusRegister = in8bits(KBC_PORT_REGISTER);

	if (statusRegister & 0x02)
		return TRUE;
	return FALSE;
}

BOOL activeKBC() {
	return writeKBCCommand(KBC_CONTROL_ACTIVE_KB);
}

int activeKeyboard() {
	int i, j;
	writeKBCBuffer(0xF4);
	for (i = 0; i < 100; i++) {
		if (waitKBCOutBufferFull() == TRUE) {
			BYTE k = readKBCBuffer();
			if (k == 0xFA) {
				return 1;
			} else if (k == 0xFE) {
				return 0;
			}
		}
	}
	return -1;
}

void clearKBCBuffer() {
	while (isOutBufferFull() == TRUE) {
		readKBCBuffer();
	}
}

BOOL writeKBCCommand(BYTE command) {
	int i;
	for (i = 0; i < KB_RETRY_COUNT; i++) {
		if (isInBufferFull() == FALSE) {
			out8bits(KBC_PORT_REGISTER, command);
			return TRUE;
		}
	}
	return FALSE;
}

BYTE readKBCStatus() {
	return in8bits(KBC_PORT_REGISTER);
}

BOOL writeKBCBuffer(BYTE data) {
	int i;
	for (i = 0; i < KB_RETRY_COUNT; i++) {
		if (isInBufferFull() == FALSE) {
			out8bits(KBC_PORT_BUFFER, data);
			return TRUE;
		}
	}
	return FALSE;
}

BYTE readKBCBuffer() {
	return in8bits(KBC_PORT_BUFFER);
}

BOOL KBCechoTest() {
	BYTE status;
	if (writeKBCBuffer(0xEE) == TRUE)
		if (waitKBCOutBufferFull() == TRUE) {
			status = readKBCBuffer();
			if (status == 0xEE)
				return TRUE;
		}
	return FALSE;
}

BOOL waitKBCOutBufferFull() {
	int i;
	for (i = 0; i < KB_RETRY_COUNT; i++) {
		if (isOutBufferFull() == TRUE) {
			return TRUE;
		}
	}
	return FALSE;
}

BYTE convertScanCodeToASCIICode(BYTE scanCode) {
	if (scanCode >= 0x81) {
		return 128;
	}
	if (g_KeyboardStatus.isLShiftPressed == TRUE){
		return g_keyMappingList[scanCode].combinedASCIICode;
	}
	return g_keyMappingList[scanCode].normalASCIICode;
}

BOOL waitACK() {
	int i, j;
	for (i = 0; i < 100; i++) {
		if (waitKBCOutBufferFull() == TRUE) {
			BYTE k = readKBCBuffer();
			if (k == 0xFA) {
				return 1;
			} else if (k == 0xFE) {
				return 0;
			}
		}
	}
	return FALSE;
}

BYTE getScancodeType() {
	int i = 0;
	if (writeKBCBuffer(0xF0) == TRUE) {
		if (waitACK() == TRUE) {
			if (writeKBCBuffer(0x00) == TRUE) {
				if (waitKBCOutBufferFull() == TRUE) {
					BYTE k = readKBCBuffer();
					return k;
				}
			}
		}
	}
	return 0;
}
