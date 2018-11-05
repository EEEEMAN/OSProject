#include "utility2.h"

void* memcopy(void* des, const void* src, int size){
	int i;
	for (i = 0; i < size; i++){
		((char*)des)[i] = ((char*)src)[i];
	}
	return des;
}

void memSet(void* des, BYTE data, int size) {
	int i;
	for (i = 0; i < size; i++) {
		((char*) des)[i] = data;
	}
}

int memCmp(const void* addr1, const void* addr2, int size){
	int i;
	for (i = 0; i < size; i++){
		if (((char*)addr1)[i] > ((char*)addr2)[i]) return 1;
		else if (((char*)addr1)[i] < ((char*)addr2)[i]) return -1;
	}
	return 0;
}
