#ifndef __KEYBOARDCONTROLLOR_H__
#define __KEYBOARDCONTROLLOR_H__

#include "../kernel1/OSDefine.h"

#define KBC_PORT_REGISTER				0x64
#define KBC_PORT_BUFFER					0x60

#define KBC_CONTROL_ACTIVE_KB			0xAE
#define KBC_CONTROL_DISABLE_KB			0xAD
#define KB_CONTROL_ACTIVE_KB			0xF4

#define KB_RETRY_COUNT					0xFFFF

#define SCANCODE_TYPE1					0x43
#define SCANCODE_TYPE2					0x41
#define SCANCODE_TYPE3					0x3F

#define KB_BUFFER_SIZE					128

#define SCANCODE_BACKSPACE_DOWN			0x0E
#define SCANCODE_ENTER_DOWN				0x1C
#define SCANCODE_SHIFTLEFT_DOWN			0x2A
#define SCANCODE_SHIFTLEFT_UP			0xAA
#define SCANCODE_SHIFTRIGHT_DOWN		0x36
#define SCANCODE_SHIFTRIGHT_UP			0xB6

#pragma pack(push, 1)
typedef struct _KeyMap{
	BYTE normalASCIICode;
	BYTE combinedASCIICode;
}KeyMap;

struct _KEYBOARDSTATUS{
	BOOL isLShiftPressed;
	BOOL isRShiftPressed;
	BOOL isCapsLockOn;
	BOOL isNumLockOn;
} g_KeyboardStatus;

struct _KEYBOARDBUFFER{
	BYTE buffer[KB_BUFFER_SIZE]; //버퍼
	int front; //다음에 꺼낼 위치를 가리킴, front == back이면 빈 상태
	int back; //다음에 집어넣을 위치를 가리킴
} g_KeyboardBuffer;
#pragma pack(pop)

BOOL isOutBufferFull();
BOOL isInBufferFull();
BOOL activeKBC(); //TRUE를 반환하면 활성화 성공
int activeKeyboard(); //1을 반환하면 활성화 성공, -1은 실패, 0은 재시도요청
void clearKBCBuffer(); //키보드버퍼를 비움
BOOL writeKBCCommand(BYTE command);
BYTE readKBCStatus();
BOOL writeKBCBuffer(BYTE data);
BYTE readKBCBuffer();
BOOL waitKBCOutBufferFull();
BOOL KBCechoTest();
BYTE convertScanCodeToASCIICode(BYTE scanCode);
BYTE getScancodeType(); //0x43, 0x41, 0x3F, 0x00중 하나를 반환. 0일 경우 에러를 뜻함
BOOL waitACK(); //ACK(0xFA)가 전송될 때까지 대기

static KeyMap g_keyMappingList[89] = {
/* 0 */{ 128, 128 },
/* 1 */{ 128, 128 },
/* 2 */{ '1', '!' },
/* 3 */{ '2', '@' },
/* 4 */{ '3', '#' },
/* 5 */{ '4', '$' },
/* 6 */{ '5', '%' },
/* 7 */{ '6', '^' },
/* 8 */{ '7', '&' },
/* 9 */{ '8', '*' },
/* 10 */{ '9', '(' },
/* 11 */{ '0', ')' },
/* 12 */{ '-', '_' },
/* 13 */{ '=', '+' },
/* 14 */{ 128, 128 },
/* 15 */{ 128, 128 },
/* 16 */{ 'q', 'Q' },
/* 17 */{ 'w', 'W' },
/* 18 */{ 'e', 'E' },
/* 19 */{ 'r', 'R' },
/* 20 */{ 't', 'T' },
/* 21 */{ 'y', 'Y' },
/* 22 */{ 'u', 'U' },
/* 23 */{ 'i', 'I' },
/* 24 */{ 'o', 'O' },
/* 25 */{ 'p', 'P' },
/* 26 */{ '[', '{' },
/* 27 */{ ']', '}' },
/* 28 */{ 128, 128 },
/* 29 */{ 128, 128 },
/* 30 */{ 'a', 'A' },
/* 31 */{ 's', 'S' },
/* 32 */{ 'd', 'D' },
/* 33 */{ 'f', 'F' },
/* 34 */{ 'g', 'G' },
/* 35 */{ 'h', 'H' },
/* 36 */{ 'j', 'J' },
/* 37 */{ 'k', 'K' },
/* 38 */{ 'l', 'L' },
/* 39 */{ ';', ':' },
/* 40 */{ '\'', '\"' },
/* 41 */{ '`', '~' },
/* 42 */{ 128, 128 },
/* 43 */{ '\\', '|' },
/* 44 */{ 'z', 'Z' },
/* 45 */{ 'x', 'X' },
/* 46 */{ 'c', 'C' },
/* 47 */{ 'v', 'V' },
/* 48 */{ 'b', 'B' },
/* 49 */{ 'n', 'N' },
/* 50 */{ 'm', 'M' },
/* 51 */{ ',', '<' },
/* 52 */{ '.', '>' },
/* 53 */{ '/', '?' },
/* 54 */{ 128, 128 },
/* 55 */{ '*', '*' },
/* 56 */{ 128, 128 },
/* 57 */{ ' ', ' ' },
/* 58 */{ 128, 128 },
/* 59 */{ 128, 128 },
/* 60 */{ 128, 128 },
/* 61 */{ 128, 128 },
/* 62 */{ 128, 128 },
/* 63 */{ 128, 128 },
/* 64 */{ 128, 128 },
/* 65 */{ 128, 128 },
/* 66 */{ 128, 128 },
/* 67 */{ 128, 128 },
/* 68 */{ 128, 128 },
/* 69 */{ 128, 128 },
/* 70 */{ 128, 128 },

/* 71 */{ 128, '7' },
/* 72 */{ 128, '8' },
/* 73 */{ 128, '9' },
/* 74 */{ '-', '-' },
/* 75 */{ 128, '4' },
/* 76 */{ 128, '5' },
/* 77 */{ 128, '6' },
/* 78 */{ '+', '+' },
/* 79 */{ 128, '1' },
/* 80 */{ 128, '2' },
/* 81 */{ 128, '3' },
/* 82 */{ 128, '0' },
/* 83 */{ 128, '.' },
/* 84 */{ 128, 128 },
/* 85 */{ 128, 128 },
/* 86 */{ 128, 128 },
/* 87 */{ 128, 128 },
/* 88 */{ 128, 128 } };

#endif/*__KEYBOARDCONTROLLOR_H__*/
