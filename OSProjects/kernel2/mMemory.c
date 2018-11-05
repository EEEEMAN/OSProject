#include "mMemory.h"
#include "asmfunc2.h"
#include "console.h"

DWORD checkMemory(DWORD start, DWORD end) {
	DWORD result;
	BOOL is486;

	//486CPU인지 검사
	DWORD eflags = getEFLAGS();
	eflags |= EFLAGS_AC;
	setEFLAGS(eflags);
	//ac가 0이면 386, 1이면 486
	eflags = getEFLAGS();
	if ((eflags & EFLAGS_AC) == 0) {
		is486 = FALSE;
	} else {
		is486 = TRUE;
		eflags = getEFLAGS();
		eflags &= ~EFLAGS_AC;
		setEFLAGS(eflags);
	}

	//486CPU면 캐시기능을 잠시 꺼둔다
	if (is486 == TRUE) {
		DWORD cr0 = getCR0Register();
		cr0 |= CR0_DISABLE_CACHE;
		setCR0Register(cr0);
	}

	result = memoryTest(start, end);

	//486CPU면 캐시기능을 다시 킨다
	if (is486 == TRUE) {
		DWORD cr0 = getCR0Register();
		cr0 &= ~CR0_DISABLE_CACHE;
		setCR0Register(cr0);
	}

	return result;
}

DWORD initMemoryManager(){
	g_memoryManager.freeSpaceCount = 1;
	DWORD memsize = checkMemory(0x700000, 0x700000 + MEMORY_HEAP_SIZE);
	g_memoryManager.freeSpace[0].addr = 0x700000;
	g_memoryManager.freeSpace[0].size = memsize;
	return memsize;
}

void* mMalloc(DWORD size){
	int i;
	DWORD addr;

	for (i = 0; i < g_memoryManager.freeSpaceCount; i++){
		if (g_memoryManager.freeSpace[i].size >= size){
			addr = g_memoryManager.freeSpace[i].addr;
			g_memoryManager.freeSpace[i].addr += size;
			g_memoryManager.freeSpace[i].size -= size;
			//공간을 다 쓰면 리스트에서 지움
			if (g_memoryManager.freeSpace[i].size == 0){
				g_memoryManager.freeSpaceCount--;
				//앞으로 하나씩 당김
				for (; i < g_memoryManager.freeSpaceCount; i++){
					g_memoryManager.freeSpace[i] = g_memoryManager.freeSpace[i + 1];
				}
			}
			return (void*)addr;
		}
	}
	return 0;
}

int mFree(void* address, DWORD size){
	int i, j;
	DWORD addr = (DWORD)address;
	//cPrintf("delete address:0x%x, size:%d\n", address, size);

	//해제한 메모리를 리스트의 어디에 넣을 건지를 정함
	for (i = 0; i < g_memoryManager.freeSpaceCount; i++){
		if (g_memoryManager.freeSpace[i].addr > addr){
			break;
		}
	}

	/* freeSpace[i - 1].addr < addr < freeSpace[i].addr */
	if (i > 0){
		if (g_memoryManager.freeSpace[i - 1].addr +
				g_memoryManager.freeSpace[i - 1].size == addr){

			g_memoryManager.freeSpace[i - 1].size += size;

			if (i < g_memoryManager.freeSpaceCount){
				if (addr + size == g_memoryManager.freeSpace[i].addr){
					g_memoryManager.freeSpace[i - 1].size += g_memoryManager.freeSpace[i].size;
					g_memoryManager.freeSpaceCount--;
					for (; i < g_memoryManager.freeSpaceCount; i++){
						g_memoryManager.freeSpace[i] = g_memoryManager.freeSpace[i + 1];
					}
				}
			}
			return 0;
		}
	}
	if (i < g_memoryManager.freeSpaceCount){
		if (addr + size == g_memoryManager.freeSpace[i].addr){
			g_memoryManager.freeSpace[i].addr = addr;
			g_memoryManager.freeSpace[i].size += size;
			return 0;
		}
	}
	if (g_memoryManager.freeSpaceCount < MEMORY_FREESPACE_MAX_COUNT){
		for (j = g_memoryManager.freeSpaceCount; j > i; j--){
			g_memoryManager.freeSpace[j] = g_memoryManager.freeSpace[j - 1];
		}
		g_memoryManager.freeSpaceCount++;

		g_memoryManager.freeSpace[i].addr = addr;
		g_memoryManager.freeSpace[i].size = size;
		return 0;
	}
	return -1;
}
