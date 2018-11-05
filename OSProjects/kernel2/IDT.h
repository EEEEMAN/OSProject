#ifndef __IDT_H__
#define __IDT_H__

#include "../kernel1/OSDefine.h"

//인터럽트 디스크립터의 플래그 비트 값
#define IDT_FLAGS_P					0x80
#define IDT_FLAGS_DPT_KERNEL		0x00
#define IDT_FLAGS_D					0x08
#define IDT_FLAGS_LOW				0x06

//초기 설정값
#define IDT_FLAGS_DEFAULT		(IDT_FLAGS_P | IDT_FLAGS_D | IDT_FLAGS_LOW)
#define IDESCRIPTOR_MAX_COUNT		256

#pragma pack(push, 1)
//인터럽트 디스크립터 구조체(8바이트)
typedef struct _InterruptDescripter{
	WORD offset1;
	WORD codeSegmentSelector;
	BYTE none;
	BYTE flags;
	WORD offset2;
}IDescripter;
#pragma pack(pop)

//address부터 8 * 256바이트를 IDT영역으로 초기화
void initIDT(DWORD address);
void setIDTDescriptor(IDescripter* descriptor, void* handler, WORD CSSelector, BYTE flag);

#endif /*__IDT_H__*/
