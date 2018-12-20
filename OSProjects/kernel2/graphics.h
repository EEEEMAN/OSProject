#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include "../kernel1/OSDefine.h"

#define MOUSE_CURSOR_WIDTH									20
#define MOUSE_CURSOR_HEIGHT									20

#define GRAPHICS_DEFAULT_BACKGROUND_COLOR					0x003F10

#pragma pack(push, 1)
typedef struct _VBEInfo{
	WORD modeAttr;			//모드의 속성
	BYTE winA;				//윈도우A속성
	BYTE winB;				//윈도우B속성
	WORD granulity;			//윈도우 가중치
	WORD winSize;
	WORD segmentA;			//윈도우A가 시작하는 세그먼트 주소
	WORD segmentB;			//윈도우B가 시작하는 세그먼트 주소
	DWORD funcPtr;			//윈도우 관련 함수의 포인터
	WORD bytesPerScanLine;	//화면 스캔 라인 당 바이트 수

	WORD resolutionX;
	WORD resolutionY;
	BYTE charX;
	BYTE charY;
	BYTE planeNum;
	BYTE bytePerPixel;
	BYTE bankNum;
	BYTE memoryModel;
	BYTE bankSize;
	BYTE imagePageNum;
	BYTE reserved1;

	BYTE redMaskSize;
	BYTE redFieldPos;
	BYTE greenMaskSize;
	BYTE greenFieldPos;
	BYTE blueMaskSize;
	BYTE blueFieldPos;
	BYTE reservedMaskSize;
	BYTE reservedFieldPos;
	BYTE directColorAttr;

	DWORD basePointer;
	DWORD reserved2;
	DWORD reserved3;

	WORD linearBytePerScanLine;
	BYTE linearImagePageNum;

	BYTE linearRedMaskSize;
	BYTE linearRedFieldPos;
	BYTE linearGreenMaskSize;
	BYTE linearGreenFieldPos;
	BYTE linearBlueMaskSize;
	BYTE linearBlueFieldPos;
	BYTE linearReservedMaskSize;
	BYTE linearReservedFieldPos;
	DWORD maxPixelClock;

	BYTE reserved4[189];
}VBEInfo;

typedef struct _VBE16BitsColor{
	unsigned char B : 5; //0~31
	unsigned char G : 6; //0~63
	unsigned char R : 5; //0~31
}VBE16BitsColor;

struct _GraphicsManager{
	VBE16BitsColor backGroundColor;
	WORD mousePosX;
	WORD mousePosY;
	BYTE mouseCenterX;		//0 ~ MOUSE_CURSOR_WIDTH
	BYTE mouseCenterY;		//0 ~ MOUSE_CURSOR_HEIGHT
}g_GraphicsManager;
#pragma pack(pop)

void initGraphicsPalette();
void drawPixel(int x, int y, VBE16BitsColor color);
void drawPixelwithColorCode(int x, int y, DWORD colorCode); //code:RRGGBB(0~1F, 0~3F, 0~1F)
void convertColorCode(DWORD colorCode, VBE16BitsColor* result);
void drawMouseCursor();
void drawFillRect(int x, int y, int width, int height, VBE16BitsColor color);
void drawFillRectwithColorCode(int x, int y, int width, int height, DWORD colorCode);

static BYTE g_MouseCursorImage[MOUSE_CURSOR_WIDTH * MOUSE_CURSOR_HEIGHT] = {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

#endif /*__GRAPHICS_H__*/
