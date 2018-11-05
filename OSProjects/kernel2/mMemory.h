#ifndef __MMEMORY_H__
#define __MMEMORY_H__

#include "../kernel1/OSDefine.h"

#define EFLAGS_AC						0x00040000
#define CR0_DISABLE_CACHE				0x60000000
#define MEMORY_FREESPACE_MAX_COUNT		1000
#define MEMORY_HEAP_SIZE				0xbf8fffff

#pragma pack(push, 1)

typedef struct _FreeMemorySpace{
	DWORD addr;
	unsigned int size;
}FreeMemorySpace;

struct MemoryManager{
	int freeSpaceCount;
	FreeMemorySpace freeSpace[MEMORY_FREESPACE_MAX_COUNT];
} g_memoryManager;

#pragma pack(pop)

DWORD checkMemory(DWORD start, DWORD end); //메모리 크기 체크
DWORD initMemoryManager();  //메모리 관리자를 초기화하고 사용 가능한 메모리 크기를 반환
void* mMalloc(DWORD size);
int mFree(void* address, DWORD size);

#endif /*__MMEMORY_H__*/
