#ifndef __MSCHEDULER_H__
#define __MSCHEDULER_H__

#include "../kernel1/OSDefine.h"
#include "Task.h"
#include "mList.h"

#define TASK_COUNT_MAX					512
#define TASK_RUNNINGTIME_MAX			20
#define TASKPOOL_ADDRESS				0x2d000

#define TASK_FLAGS_RUN					0x0001	//실행중인 태스크
#define TASK_FLAGS_END					0x0002	//종료 대기중인 태스크

#pragma pack(push, 1)
typedef struct _Task{
	WORD taskID;		//3~515
	WORD flags;			//실행중 또는 준비큐에 들어있으면 1, 사용중이 아니면 0
	TSS* tss;
	void* stackAddress; //스택 주소
	int stackSize;		//스택 크기
}Task;

struct _TaskManager{
	Task* currentTask;
	int runningTime;	//태스크가 실행되고 경과한 시간
	mLList readyTasks;  //data:Task*
} g_taskManager;

#pragma pack(pop)

BOOL setEnableScheduler(BOOL enabled);
void initTaskPool(DWORD address);
void schedule();
int createTask(void* handlerAddress, void* stackAddress, int stackSize); //생성한 태스크 ID를 반환. 실패 시 -1를 반환
int deleteTask(WORD taskID);

#endif /*__MSCHEDULER_H__*/
