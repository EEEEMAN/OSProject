#include "mString.h"
#include "console.h"
#include "utility2.h"

int getStrLen(const char* str) {
	int i;

	for (i = 0;; i++) {
		if (str[i] == '\0') {
			break;
		}
	}
	return i;
}

//buffer에 formatString을 해석한 내용을 담음
int makeStrByVaList(char* buffer, const char* formatString, va_list ap) {
	QWORD i;
	int bufferLength = 0; //반환 문자열 길이
	int formatStrLength = getStrLen(formatString);

	int intValue; //%d처리시 사용
	QWORD qwValue; //%x처리시 사용
	char* strValue; //%s처리시 사용
	int strValueLength; //%s처리시 사용

	for (i = 0; i < formatStrLength; i++) {
		if (formatString[i] == '%') {
			i++;
			switch (formatString[i]) {
			case 'd':
				intValue = (int) (va_arg(ap, int));
				bufferLength += itoa(intValue, buffer + bufferLength);
				break;
			case 'x':
			case 'X':
				qwValue = (QWORD) (va_arg(ap, QWORD));
				bufferLength += itoa16(qwValue, buffer + bufferLength);
				break;
			case 's':
				strValue = (char*) (va_arg(ap, char*));
				strValueLength = getStrLen(strValue);
				memcopy(buffer + bufferLength, strValue, strValueLength);
				bufferLength += strValueLength;
				break;
			}
		} else {
			buffer[bufferLength] = formatString[i];
			bufferLength++;
		}
	}
	buffer[bufferLength] = '\0';
	return bufferLength;
}

int itoa(int val, char* buffer) {
	int length;

	if (val == 0) {
		buffer[0] = '0';
		buffer[1] = '\0';
		return 1;
	}
	if (val < 0) {
		length = 1;
		buffer[0] = '-';
		val = -val;
	} else {
		length = 0;
	}

	for (; val > 0; length++) {
		buffer[length] = '0' + val % 10;
		val = val / 10;
	}
	buffer[length] = '\0';
	if (buffer[0] == '-')
		reverseStr(&buffer[1]);
	else
		reverseStr(buffer);
	return length;
}

int itoa16(QWORD val, char* buffer) {
	QWORD length = 0;
	QWORD curVal;

	if (val == 0) {
		buffer[0] = '0';
		buffer[1] = '\0';
		return 1;
	}

	for (length = 0; val > 0; length++) {
		curVal = val % 16;
		if (curVal >= 10) {
			buffer[length] = 'A' + (curVal - 10);
		} else {
			buffer[length] = '0' + curVal;
		}
		val = val / 16;
	}
	buffer[length] = '\0';
	reverseStr(buffer);
	return length;
}

int mAtoi(const char* str) {
	int len = getStrLen(str);
	int i;
	int result = 0;

	for (i = 0; i < len; i++) {
		int num = str[i] - '0';
		int j;
		for (j = 0; j < len - i - 1; j++) {
			num *= 10;
		}
		result += num;
	}
	return result;
}

void reverseStr(char* buffer) {
	int length = getStrLen(buffer);
	char temp;
	int i;

	for (i = 0; i < length / 2; i++) {
		temp = buffer[i];
		buffer[i] = buffer[length - (i + 1)];
		buffer[length - (i + 1)] = temp;
	}
}

void csPrintf(char* buffer, const char* formatString, ...) {
	va_list va;

	va_start(va, formatString);
	makeStrByVaList(buffer, formatString, va);
	va_end(va);

}
