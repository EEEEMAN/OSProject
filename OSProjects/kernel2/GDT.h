#ifndef __GDT_H__
#define __GDT_H__

#include "../kernel1/OSDefine.h"

#define GDT_KERNELCODESEGMENT			(1 * 8)
#define GDT_KERNELDATASEGMENT			(2 * 8)

#define GDT_FLAGS1_P					0x80
#define GDT_FLAGS1_S					0x10
#define GDT_FLAGS2_G					0x80
#define GST_FLAGS2_32BITS				0x40

#define GDT_DESCRIPTOR_COUNT			3

#pragma pack(push, 1)
typedef struct _GlobalDescriptor{
	WORD limitLow;
	WORD baseLow;
	BYTE baseMid;
	BYTE flags1;
	BYTE flags2AndLimitHigh;
	BYTE baseHigh;
}GDescriptor;

typedef struct _GlobalDescriptorTable{
	WORD size;
	GDescriptor* address;
}GDT;
#pragma pack(pop)

void initGDT(DWORD address);
void setDescriptor(GDescriptor* descriptor, DWORD baseAddress, DWORD limit,
		BYTE flags1, BYTE flags2);
#endif /*__GDT_H__*/
