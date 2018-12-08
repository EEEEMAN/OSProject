#include "graphics.h"
#include "asmfunc2.h"

void initGraphicsPalette(){
	int i;
	VBEInfo* vbeInfo = (VBEInfo*)VBE_INFO_ADDRESS;
	VBE16BitsColor* gMem = (VBE16BitsColor*)vbeInfo->basePointer;

	for (i = 0; i < vbeInfo->resolutionX * vbeInfo->resolutionY; i++){
		gMem[i].R = 31;
		gMem[i].G = 63;
		gMem[i].B = 31;
	}
}

void drawPixel(int x, int y, VBE16BitsColor color16){
	VBEInfo* vbeInfo = (VBEInfo*)VBE_INFO_ADDRESS;
	VBE16BitsColor* gMem = (VBE16BitsColor*)vbeInfo->basePointer;

	gMem[(vbeInfo->resolutionX * y) + x] = color16;
	//gMem[(GRAPHICS_VIDEO_WIDTH * y) + x] = color;
}
