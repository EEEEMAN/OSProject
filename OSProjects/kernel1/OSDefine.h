#ifndef __OSDFINE_H__
#define __OSDFINE_H__

#define BYTE unsigned char
#define WORD unsigned short
#define DWORD unsigned int
#define QWORD unsigned long
#define BOOL unsigned char

#define IDT_START					0x500
#define GDT_START					0x10000
#define TSS_START					0x20000
#define MAIN_KERNEL_ENTRY			0x600000

#define TRUE 1
#define FALSE 0
#define NULL 0

#define VIDEO_MEM					0xB8000
#define VIDEO_WIDTH					80
#define VIDEO_HEIGHT				25
#define VIDEO_SIZE					(VIDEO_WIDTH * VIDEO_HEIGHT)

/////////////////////구조체 정의////////////////////////////////////
#pragma pack(push, 1)

typedef struct _SegmentDescriptor{
	WORD limit;
	WORD base_low;
	BYTE base_mid;
	BYTE attribute;
	BYTE attrAndLimit;
	BYTE base_high;
}SEGMENT_DESCRIPTOR;

#pragma pack(pop)

#endif /*__OSDFINE_H__*/
