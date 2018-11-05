#ifndef __MSTRING_H__
#define __MSTRING_H__

#include <stdarg.h>
#include "../kernel1/OSDefine.h"

int getStrLen(const char* str);
int makeStrByVaList(char* buffer, const char* formatString, va_list ap);
int itoa(int val, char* buffer);
int itoa16(QWORD val, char* buffer);
int mAtoi(const char* str);
void reverseStr(char* buffer);
void csPrintf(char* buffer, const char* formatString, ...);

#endif /*__MSTRING_H__*/
