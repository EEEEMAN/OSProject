#include "console.h"
#include "mString.h"
#include "utility2.h"
#include "asmfunc2.h"

void initVideoMemory() {
	g_consoleAttribute = CONSOLE_DEFAULT_ATTRIBUTE;
	clearScreen();
}

void clearScreen() {
	Character* vim = (Character*) VIDEO_MEM;
	int i;

	g_cursorOffset = 0;
	for (i = 0; i < VIDEO_SIZE; i++) {
		vim[i].Character = ' ';
		vim[i].attribute = g_consoleAttribute;
	}
	setCursor(0);
}

void printString(int offset, BYTE attribute, const char* buffer) {

	Character* vim = (Character*) VIDEO_MEM;
	int strLength = getStrLen(buffer);
	int i;
	for (i = 0; i < strLength; i++) {
		vim[offset + i].Character = buffer[i];
		vim[offset + i].attribute = attribute;
	}

}

void printStringWhereCursor(BYTE attribute, const char* buffer) {

	Character* vim = (Character*) VIDEO_MEM;
	int strLength = getStrLen(buffer);
	int i, j;

	for (i = 0; i < strLength; i++) {
		if (buffer[i] == '\n') {
			g_cursorOffset += (VIDEO_WIDTH - (g_cursorOffset % VIDEO_WIDTH));
		} else if (buffer[i] == '\t') {
			g_cursorOffset += (8 - (g_cursorOffset % 8));
		} else {
			printChar(g_cursorOffset, attribute, buffer[i]);
			g_cursorOffset = g_cursorOffset + 1;
		}
		//화면이 꽉 차기 한 줄 전에 한 줄씩 위로 올림
		if (g_cursorOffset + VIDEO_WIDTH >= VIDEO_SIZE) {
			//한 줄씩 위로 올림
			memcopy(&(vim[0]), &(vim[VIDEO_WIDTH]),
					(VIDEO_SIZE - (VIDEO_WIDTH * 2)) * sizeof(Character));
			//맨 아래, 아래에서 두번째 줄을 비움
			for (j = VIDEO_SIZE - (VIDEO_WIDTH * 2); j < VIDEO_SIZE; j++) {
				vim[j].Character = ' ';
				vim[j].attribute = g_consoleAttribute;
			}
			//커서를 한 줄 위로 올림
			g_cursorOffset -= VIDEO_WIDTH;
		}
	}
	setCursor(g_cursorOffset);

}

void printChar(int offset, BYTE attribute, const char ch) {

	Character* vim = (Character*) VIDEO_MEM;

	vim[offset].Character = ch;
	vim[offset].attribute = attribute;

}

void setCursor(int curOffset) {
	//상위 1비트 전송
	out8bits(CRTC_ADDRESS_REGISTER_PORT, CRTC_CURSOR_UPPER);
	out8bits(CRTC_DATA_REGISTER_PORT, curOffset >> 8);
	//하위 1비트 전송
	out8bits(CRTC_ADDRESS_REGISTER_PORT, CRTC_CURSOR_LOWER);
	out8bits(CRTC_DATA_REGISTER_PORT, curOffset & 0xFF);
	g_cursorOffset = curOffset;
}

void cPrintf(const char* formatString, ...) {

	char buffer[MAX_STRING_LENGTH];
	va_list va;

	va_start(va, formatString);
	makeStrByVaList(buffer, formatString, va);
	va_end(va);

	printStringWhereCursor(g_consoleAttribute, buffer);

}

void removeCharacter() {

	Character* vim = (Character*) VIDEO_MEM;
	g_cursorOffset--;
	vim[g_cursorOffset].Character = ' ';
	vim[g_cursorOffset].attribute = g_consoleAttribute;
	setCursor(g_cursorOffset);

}

void bClearScreen(VideoBuffer* buffer, int size) {
	int i;
	for (i = 0; i < size; i++) {
		buffer->buffer[i].attribute = g_consoleAttribute;
		buffer->buffer[i].Character = ' ';
	}
	buffer->cursorOffset = 0;
}

void bPrintString(VideoBuffer* buffer, int offset, BYTE attribute,
		const char* str) {
	int i;
	int steLen = getStrLen(str);
	for (i = offset; i < offset + steLen; i++) {
		buffer->buffer[i].attribute = attribute;
		buffer->buffer[i].Character = str[i - offset];
	}
}

void bPrintChar(VideoBuffer* buffer, int offset, BYTE attribute, const char ch) {
	buffer->buffer[offset].Character = ch;
	buffer->buffer[offset].attribute = attribute;
}

void bPrintf(VideoBuffer* buffer, BYTE attribute, const char* formatString, ...) {
	char str[MAX_STRING_LENGTH];
	va_list va;

	va_start(va, formatString);
	makeStrByVaList(str, formatString, va);
	va_end(va);

	bPrintString(buffer, buffer->cursorOffset, attribute, str);
}

void bRemoveCharacter(VideoBuffer* buffer) {
	buffer->cursorOffset--;
	buffer->buffer[buffer->cursorOffset].Character = ' ';
	buffer->buffer[buffer->cursorOffset].attribute = g_consoleAttribute;
}
