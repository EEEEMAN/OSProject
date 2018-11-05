#ifndef __UTILITY_H__
#define __UTILITY_H__

#include "../kernel1/OSDefine.h"

void* memcopy(void* des, const void* src, int size);
void memSet(void* des, BYTE data, int size);
int memCmp(const void* addr1, const void* addr2, int size);

#endif /*__UTILITY_H__*/
