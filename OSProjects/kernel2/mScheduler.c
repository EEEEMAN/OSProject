#include "mScheduler.h"
#include "asmfunc2.h"
#include "console.h"
#include "mMemory.h"

BOOL g_scheduleEnable;

BOOL setEnableScheduler(BOOL enabled) {
	BOOL stat = g_scheduleEnable;
	g_scheduleEnable = enabled;
	return stat;
}

void initTaskPool(DWORD address) {
	int i;

	//태스크풀 생성 후 초기화
	Task* tasks = (Task*) address;
	for (i = 0; i < TASK_COUNT_MAX; i++) {
		tasks[i].flags = 0;
		tasks[i].taskID = i + 3;
		tasks[i].tss = (TSS*) (TSS_START + (sizeof(TSS) * i));
	}
	tasks[0].flags = TASK_FLAGS_RUN;
	tasks[0].stackAddress = (void*) 0x1FFFFC;
	tasks[0].stackSize = 0xFFFFC;

	//태스크매니저에 현재 태스크를 적용
	g_taskManager.currentTask = tasks;
	g_taskManager.runningTime = 0;
	initList(&g_taskManager.readyTasks);

	//스케줄링 활성화
	g_scheduleEnable = TRUE;
}

void schedule() {
	Task* nextTask;		//다음 태스크
	int i;

	if (g_scheduleEnable == FALSE)
		return;

	g_taskManager.runningTime++;
	if (g_taskManager.runningTime < TASK_RUNNINGTIME_MAX) {
		return;
	}
	//준비중인 태스크가 없으면 종료
	if (g_taskManager.readyTasks.nodeCount == 0) {
		return;
	}
	//종료 대기중인 태스크를 지움
	//다음 태스크 가져오기
	int loopCount = g_taskManager.readyTasks.nodeCount;
	for (i = 0; i < loopCount; i++) {
		nextTask = (Task*) popItem(&g_taskManager.readyTasks);
		//Task* tsk = (Task*)getItem(&g_taskManager.readyTasks, i);
		if ((nextTask->flags & TASK_FLAGS_END) == 0) {
			break;
		} else {
			nextTask->flags = 0;
			mFree((void*) (nextTask->stackAddress - nextTask->stackSize),
					nextTask->stackSize);
		}
	}
	if ((nextTask->flags & TASK_FLAGS_RUN) == 0 && g_taskManager.readyTasks.nodeCount == 0){
		return;
	}
	//현재 태스크를 준비 큐에 추가
	insertItemBack(&g_taskManager.readyTasks,
			(DWORD) g_taskManager.currentTask);
	//다음 태스크를 현재 태스크로 설정
	g_taskManager.currentTask = nextTask;
	g_taskManager.runningTime = 0;
	//태스크스위칭
	taskswitch(0, nextTask->taskID * 8);
}

int createTask(void* handlerAddress, void* stackAddress, int stackSize) {
	int i;
	Task* taskpool = (Task*) TASKPOOL_ADDRESS;
	//사용중이 아닌 태스크를 검색
	for (i = 0; i < TASK_COUNT_MAX; i++) {
		if ((taskpool[i].flags & TASK_FLAGS_RUN) == 0) {
			break;
		}
	}
	if (i == TASK_COUNT_MAX) {
		return -1;
	}

	//태스크, TSS 초기화
	taskpool[i].stackAddress = stackAddress;
	taskpool[i].stackSize = stackSize;
	initTSS(taskpool[i].tss, handlerAddress, stackAddress);

	//태스크를 사용중으로 바꾸고 준비 큐에 넣는다.
	taskpool[i].flags |= TASK_FLAGS_RUN;
	insertItemBack(&g_taskManager.readyTasks, (DWORD) &(taskpool[i]));

	return taskpool[i].taskID;
}

int deleteTask(WORD taskID) {
	//스케줄링을 일시정지시키고 원래의 상태를 저장
	BOOL scheduleState = setEnableScheduler(FALSE);
	int i;
	Task* tsk = (Task*) TASKPOOL_ADDRESS;

	//태스크를 찾는다.
	for (i = 0; i < TASK_COUNT_MAX; i++) {
		if (tsk[i].taskID == taskID && (tsk[i].flags & TASK_FLAGS_RUN) != 0
				&& (tsk[i].flags & TASK_FLAGS_END) == 0) {
			break;
		}
	}
	//못찾았을경우
	if (i == TASK_COUNT_MAX) {
		setEnableScheduler(scheduleState);
		return -1;
	}

	tsk[i].flags |= TASK_FLAGS_END;

	setEnableScheduler(scheduleState);
	return 0;
}
