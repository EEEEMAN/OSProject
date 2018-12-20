#include "graphics.h"
#include "asmfunc2.h"

void initGraphicsPalette() {
	int i;
	VBEInfo* vbeInfo = (VBEInfo*) VBE_INFO_ADDRESS;
	VBE16BitsColor* gMem = (VBE16BitsColor*) vbeInfo->basePointer;
	VBE16BitsColor color16;

	convertColorCode(GRAPHICS_DEFAULT_BACKGROUND_COLOR, &color16);

	g_GraphicsManager.backGroundColor = color16;
	g_GraphicsManager.mousePosX = vbeInfo->resolutionX / 2;
	g_GraphicsManager.mousePosY = vbeInfo->resolutionY / 2;
	g_GraphicsManager.mouseCenterX = MOUSE_CURSOR_WIDTH / 2;
	g_GraphicsManager.mouseCenterY = MOUSE_CURSOR_HEIGHT / 2;

	for (i = 0; i < vbeInfo->resolutionX * vbeInfo->resolutionY; i++) {
		gMem[i] = g_GraphicsManager.backGroundColor;
	}
}

void drawPixel(int x, int y, VBE16BitsColor color16) {
	VBEInfo* vbeInfo = (VBEInfo*) VBE_INFO_ADDRESS;
	VBE16BitsColor* gMem = (VBE16BitsColor*) vbeInfo->basePointer;

	if (x >= vbeInfo->resolutionX || x < 0) return;
	if (y >= vbeInfo->resolutionY || y < 0) return;

	gMem[(vbeInfo->resolutionX * y) + x] = color16;
}

void drawPixelwithColorCode(int x, int y, DWORD colorCode) {
	VBE16BitsColor color16;

	convertColorCode(colorCode, &color16);
	drawPixel(x, y, color16);
}

void convertColorCode(DWORD colorCode, VBE16BitsColor* result) {
	VBEInfo* vbeInfo = (VBEInfo*) VBE_INFO_ADDRESS;
	result->B = ((colorCode >> 0) & 0x1F);			//B
	result->G = ((colorCode >> 8) & 0x3F);			//G
	result->R = ((colorCode >> 16) & 0x1F);			//R
}

void drawMouseCursor() {
	int i, j;
	VBEInfo* vbeInfo = (VBEInfo*) VBE_INFO_ADDRESS;

	for (j = 0; j < MOUSE_CURSOR_HEIGHT; j++) {
		for (i = 0; i < MOUSE_CURSOR_WIDTH; i++) {
			switch (g_MouseCursorImage[(MOUSE_CURSOR_WIDTH * j) + i]) {
			case 0:
				break;
			case 1:
				drawPixelwithColorCode(
						g_GraphicsManager.mousePosX + i
								- g_GraphicsManager.mouseCenterX,
						g_GraphicsManager.mousePosY + j
								- g_GraphicsManager.mouseCenterY, 0x000000);
				break;
			default:
				break;
			}
		}
	}

}

void drawFillRect(int x, int y, int width, int height, VBE16BitsColor color) {
	int i, j;

	//기존 위치를 지움
	for (j = y; j < y + height; j++) {
		for (i = x; i < x + width; i++) {
			drawPixel(i, j, color);
		}
	}
}

void drawFillRectwithColorCode(int x, int y, int width, int height,
DWORD colorCode) {
	int i, j;
	VBE16BitsColor color;

	convertColorCode(colorCode, &color);

	//기존 위치를 지움
	for (j = y; j < y + height; j++) {
		for (i = x; i < x + width; i++) {
			drawPixel(i, j, color);
		}
	}
}
