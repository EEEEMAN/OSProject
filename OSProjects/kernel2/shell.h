#ifndef __SHELL_H__
#define __SHELL_H__

#include "console.h"
#include <stdarg.h>

#define PROMPT_STRING			"shell>"
#define MAX_COMMAND_SIZE		256
#define VIDEO_LAYER_MAX			2

#pragma pack(push, 1)
typedef struct _Command{
	char* command;		//명령어
	int (*handler)(const char*);		//실행될 함수
}Command;
#pragma pack(pop)

int shellRun();
int keyboardBufferHandler(char* commandBuffer, int commandLength);
void CommandCompareAndExcute(const char* command, int commandLength);

/*-----------------------------명령어 함수------------------------------------------*/
//명령어 목록을 출력
int showCommandList(const char* args);
//글자 색 변경
int setTextColor(const char* args);
//화면 지움
int clear(const char* args);
//pci 장치 표시
int pciDevice(const char* args);
//EFLAGS의 상태를 출력
int showEFLAGS(const char* args);
//CR0레지스터의 상태를 출력
int showCR0(const char* args);
//메모리 상태를 출력
int showMemory(const char* args);
//현재 실행중인 태스크를 출력
int showTask(const char* args);
//태스크를 종료시킴
int killTask(const char* args);
//타이머를 표시
int showTimer(const char* args);
//스케줄링 태스트를 위한 애니메이션을 보여주는 함수
int animationTest(const char* args);

#endif /*__SHELL_H__*/
