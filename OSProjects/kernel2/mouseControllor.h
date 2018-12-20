#ifndef __MOUSECONTROLLOR_H__
#define __MOUSECONTROLLOR_H__

#include "../kernel1/OSDefine.h"
#include "keyboardControllor.h"

#define MOUSE_COMMANDL_ACTIVE_MOUSE		0xF4

#define MOUSE_PACKETFLAGS_BUTTON_L		0x01
#define MOUSE_PACKETFLAGS_BUTTON_R		0x02
#define MOUSE_PACKETFLAGS_BUTTON_C		0x04
#define MOUSE_PACKETFLAGS_SIGN_X		0x10
#define MOUSE_PACKETFLAGS_SIGN_Y		0x20
#define MOUSE_PACKETFLAGS_OVERFLOW_X	0x40
#define MOUSE_PACKETFLAGS_OVERFLOW_Y	0x80

#define MOUSE_BUFFER_SIZE				256

#pragma pack(push, 1)
struct _MOUSEBUFFER{
	BYTE buffer[MOUSE_BUFFER_SIZE]; //버퍼
	int front; //다음에 꺼낼 위치를 가리킴, front == back이면 빈 상태
	int back; //다음에 집어넣을 위치를 가리킴
} g_MouseBuffer;

typedef struct _MousePacket{
	BYTE status;
	BYTE posX;
	BYTE posY;
}MousePacket;
#pragma pack(pop)

BOOL mouseEnable();
void mouseInterruptEnable();
BYTE mouseCheck();
BOOL isMouseData();
void mouseTest();

#endif /*__MOUSECONTROLLOR_H__*/
