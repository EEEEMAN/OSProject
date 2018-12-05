#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <stdarg.h>
#include "../kernel1/OSDefine.h"

#define SCROLL_BUFFER_HEIGHT			50 //화면 스크롤 버퍼 세로 최대 길이
#define SCROLL_BUFFER_SIZE				(VIDEO_WIDTH * SCROLL_BUFFER_HEIGHT)
#define CURSOR_X						(g_cursorOffset % VIDEO_WIDTH)
#define CURSOR_Y						(g_cursorOffset / VIDEO_WIDTH)

#define CONSOLE_COLOR_BLACK				0x0
#define CONSOLE_COLOR_BLUE				0x1
#define CONSOLE_COLOR_GREEN				0x2
#define CONSOLE_COLOR_CYAN				0x3
#define CONSOLE_COLOR_RED				0x4
#define CONSOLE_COLOR_MAGENTA			0x5
#define CONSOLE_COLOR_BROWN				0x6
#define CONSOLE_COLOR_LIGHTGRAY			0x7
#define CONSOLE_COLOR_DARTGRAY			0x8
#define CONSOLE_COLOR_BRIGHTBLUE		0x9
#define CONSOLE_COLOR_BRIGHTGREEN		0xA
#define CONSOLE_COLOR_BRIGHTCYAN		0xB
#define CONSOLE_COLOR_BRIGHTRED			0xC
#define CONSOLE_COLOR_BRIGHTMAGENTA		0xD
#define CONSOLE_COLOR_YELLOW			0xE
#define CONSOLE_COLOR_WHITE				0xF
#define CONSOLE_DEFAULT_ATTRIBUTE		((CONSOLE_COLOR_BLACK << 4) | CONSOLE_COLOR_BRIGHTBLUE)
#define MAX_STRING_LENGTH				128

#define CRTC_ADDRESS_REGISTER_PORT		0x3D4
#define CRTC_DATA_REGISTER_PORT			0x3D5
#define CRTC_CURSOR_UPPER				0x0E
#define CRTC_CURSOR_LOWER				0x0F

#pragma pack(push, 1)
typedef struct _VideoModeCharacters{
	unsigned char Character;
	unsigned char attribute;
}Character;

typedef struct _VideoBuffer{
	Character buffer[VIDEO_SIZE];
	int cursorOffset;
}VideoBuffer;
#pragma pack(pop)

int g_cursorOffset; //커서 위치 (y * width + x)
BYTE g_consoleAttribute; //화면 글자 속성

void initVideoMemory();
void clearScreen();
void printString(int offset, BYTE attribute, const char* buffer); //화면에 문자열 출력
void printStringWhereCursor(BYTE attribute, const char* buffer); //커서가 있는곳에 문자열 출력
void printChar(int offset, BYTE attribute, const char ch); //화면에 한 글자 출력
void setCursor(int curOffset); //커서 위치를 지정
void cPrintf(const char* formatString, ...); //문자열 인수 처리후 커서를 이용하여 출력
void removeCharacter(); //커서가 있는곳에서 글자를 하나 지움(backspace)

void bClearScreen(VideoBuffer* buffer, int size); //버퍼를 지움
void bPrintString(VideoBuffer* buffer, int offset, BYTE attribute, const char* str); //버퍼에 문자열
void bPrintChar(VideoBuffer* buffer, int offset, BYTE attribute, const char ch); //버퍼에 글자
void bPrintf(VideoBuffer* buffer, BYTE attribute, const char* formatString, ...); //문자열포맷 해석 후 버퍼에 씀
void bRemoveCharacter(VideoBuffer* buffer); //커서가 있는곳에서 글자를 하나 지움(backspace)

#endif /*__CONSOLE_H__*/
