#include "utility.h"

void* memcopy(void* des, const void* src, int size){
	int i = 0;
	for (i = 0; i < size; i++){
		((char*)des)[i] = ((char*)src)[i];
	}
	return des;
}
