#include "shell.h"
#include "keyboardControllor.h"
#include "console.h"
#include "utility2.h"
#include "mString.h"
#include "PCI.h"
#include "PIT.h"
#include "asmfunc2.h"
#include "mMemory.h"
#include "mList.h"
#include "mScheduler.h"

Command commands[] = {
		{"command", showCommandList},
		{"clear", clear},
		{"textcolor", setTextColor},
		{"pci", pciDevice},
		{"eflags", showEFLAGS},
		{"cr0", showCR0},
		{"memory", showMemory},
		{"task", showTask},
		{"kill", killTask},
		{"timer", showTimer},
		{"anim", animationTest},
};

int shellRun() {
	int commandLength = 0; //다음에 글자를 출력할 위치
	char commandBuffer[MAX_COMMAND_SIZE] = { 0, };
	int i;

	setTextColor("white");
	cPrintf("Shell Start...\n");
	cPrintf(PROMPT_STRING);
	g_KeyboardBuffer.front = 0;
	g_KeyboardBuffer.back = 0;

	while (1) {
		commandLength = keyboardBufferHandler(commandBuffer, commandLength);
	}
}

int keyboardBufferHandler(char* commandBuffer, int commandLength) {
	BYTE ch;
	BOOL scStatus;	//스케줄링을 일시정지할때 사용

	if (g_KeyboardBuffer.front == g_KeyboardBuffer.back)
		return commandLength;
	BYTE scancode = g_KeyboardBuffer.buffer[g_KeyboardBuffer.front];
	g_KeyboardBuffer.front = (g_KeyboardBuffer.front + 1) % KB_BUFFER_SIZE;

	switch (scancode) {
	case SCANCODE_BACKSPACE_DOWN: //백스페이스 처리
		if (commandLength >= 1) {
			removeCharacter();
			commandLength--;
			commandBuffer[commandLength] = ' ';
		}
		break;
	case SCANCODE_ENTER_DOWN: //엔터 처리
		cPrintf("\n");
		if (commandLength != 0) {
			//커맨드 처리
			CommandCompareAndExcute(commandBuffer, commandLength);
			//커맨드 초기화
			commandLength = 0;
			memSet(commandBuffer, 0, MAX_COMMAND_SIZE);
		}
		cPrintf(PROMPT_STRING);
		break;
	case SCANCODE_SHIFTLEFT_DOWN:
		g_KeyboardStatus.isLShiftPressed = TRUE;
		break;
	case SCANCODE_SHIFTLEFT_UP:
		g_KeyboardStatus.isLShiftPressed = FALSE;
		break;
	case SCANCODE_SHIFTRIGHT_DOWN:
		g_KeyboardStatus.isRShiftPressed = TRUE;
		break;
	case SCANCODE_SHIFTRIGHT_UP:
		g_KeyboardStatus.isRShiftPressed = FALSE;
		break;
	default: //그 외 문자 처리
		ch = convertScanCodeToASCIICode(scancode);
		if (ch != 128) {
			printChar(g_cursorOffset, g_consoleAttribute, ch);
			g_cursorOffset++;
			commandBuffer[commandLength] = ch;
			commandLength++;
			ch = 0;
		}
	}

	setCursor(g_cursorOffset);
	return commandLength;
}

void CommandCompareAndExcute(const char* command, int commandLength) {
	int i, spaceIndex;

	//명령어만 잘라냄
	for (spaceIndex = 0; spaceIndex < commandLength; spaceIndex++) {
		if (command[spaceIndex] == ' ') {
			break;
		}
	}

	//명령어 검색
	for (i = 0; i < sizeof(commands) / sizeof(Command); i++) {
		if (memCmp(command, commands[i].command, getStrLen(commands[i].command))
				== 0) {
			commands[i].handler(&(command[spaceIndex + 1]));
			break;
		}
	}
	if (i == sizeof(commands) / sizeof(Command)) {
		cPrintf("command not found.\n");
	}
	return;
}

//////////////////////////////////////////명령어 함수//////////////////////////////////////////////
int showCommandList(const char* args){
	int i;

	cPrintf("Command List:\n");
	for (i = 0; i < sizeof(commands) / sizeof(Command); i++){
		cPrintf("\t%s\n", commands[i].command);
	}
	return 0;
}

int setTextColor(const char* args) {
	Character* vim = (Character*) VIDEO_MEM;
	int i, argLength, loopCount;
	BYTE color;
	struct ColorSet {
		char* name;
		BYTE colorCode;
	} colorSet[] = {
			{"red", CONSOLE_COLOR_BRIGHTRED },
			{"blue", CONSOLE_COLOR_BRIGHTBLUE },
			{"cyan", CONSOLE_COLOR_BRIGHTCYAN },
			{"green", CONSOLE_COLOR_BRIGHTGREEN },
			{"magenta", CONSOLE_COLOR_BRIGHTMAGENTA },
			{"brown", CONSOLE_COLOR_BROWN},
			{"yellow", CONSOLE_COLOR_YELLOW},
			{"white", CONSOLE_COLOR_WHITE}
	};

	//인수가 없으면 종료
	argLength = getStrLen(args);
	loopCount = sizeof(colorSet) / sizeof(struct ColorSet);
	if (argLength == 0) {
		cPrintf("choose one of");
		for (i = 0; i < loopCount; i++) {
			cPrintf(" %s", colorSet[i].name);
			if (i != loopCount - 1) {
				cPrintf(",");
			}
		}
		cPrintf(".\n");
		return -1;
	}
	//색 지정
	for (i = 0; i < loopCount; i++) {
		if (memCmp(args, colorSet[i].name, getStrLen(colorSet[i].name)) == 0) {
			color = colorSet[i].colorCode;
			break;
		}
	}
	//색을 못찾았을 경우
	if (i == loopCount) {
		cPrintf("choose one of");
		for (i = 0; i < loopCount; i++){
			cPrintf(" %s", colorSet[i].name);
			if (i != loopCount - 1){
				cPrintf(",");
			}
		}
		cPrintf(".\n");
		return -1;
	}
	//문제없으면 바꿈
	g_consoleAttribute = g_consoleAttribute & 0xF0;
	g_consoleAttribute = g_consoleAttribute | (color & 0xF);
	//커서보다 아래는 모두 적용
	for (i = g_cursorOffset; i < VIDEO_SIZE; i++) {
		vim[i].attribute = g_consoleAttribute;
	}
	return 0;
}

int clear(const char* args) {
	clearScreen();
	return 0;
}

int pciDevice(const char* args) {
	int busNum, devNum;
	int count = 0;

	for (busNum = 0; busNum < 256; busNum++) {
		for (devNum = 0; devNum < 32; devNum++) {
			DWORD reg;
			reg = getPCICSData(0, 0, devNum, busNum);
			if ((reg & 0xFFFF) == 0xFFFF)
				continue; //venderID가 무효한 경우 넘어감
			cPrintf("venderID:%x, DeviceID:%x\n", (reg & 0xFFFF),
					((reg >> 16) & 0xFFFF));
			count++;
		}
	}
	if (count == 0)
		cPrintf("PCI Device not found.\n");
	return 0;
}

int showEFLAGS(const char* args) {
	cPrintf("EFLAGS:0x%x\n", getEFLAGS());
	return 0;
}

int showCR0(const char* args) {
	cPrintf("CR0 register:0x%x\n", getCR0Register());
	return 0;
}

int showMemory(const char* args) {
	int i;
	cPrintf("FreeMemorySpaceList:\n");
	for (i = 0; i < g_memoryManager.freeSpaceCount; i++) {
		cPrintf("Address:0x%x, Size:%dKB\n", g_memoryManager.freeSpace[i].addr,
				g_memoryManager.freeSpace[i].size / 1024);
	}
	return 0;
}

int showTask(const char* args) {
	int i;
	Task* tasks = (Task*) TASKPOOL_ADDRESS;

	cPrintf("Task List:\n");
	for (i = 0; i < TASK_COUNT_MAX; i++) {
		if ((tasks[i].flags & TASK_FLAGS_RUN) == 0)
			continue;
		cPrintf("Task ID:%d, size:%dByte\n", tasks[i].taskID,
				tasks[i].stackSize);
	}
	return 0;
}

int killTask(const char* args) {
	WORD taskID;
	int i;

	if (memCmp(args, "all", sizeof("all")) == 0){
		for (i = 4; i < TASK_COUNT_MAX; i++){
			deleteTask(i);
		}
		return 0;
	}
	taskID = (WORD) mAtoi(args);
	if (taskID > TASK_COUNT_MAX || taskID <= 3) {
		cPrintf("Invalid taskID.\n");
		return -1;
	}
	if (deleteTask(taskID) == -1) {
		cPrintf("task not found.\n");
		return -1;
	}
	return 0;

}

void showTimer_sub() {
	unsigned int count = 0;
	while (1) {
		char str[10];
		csPrintf(str, "Timer:%d", count);
		printString(VIDEO_WIDTH * 2 - 9, g_consoleAttribute, str);
		count++;
		mSleep(1000);
	}
}
int showTimer(const char* args) {
	return createTask(showTimer_sub, mMalloc(1024) + 1024, 1024);
}

void cursorAnimation_sub() {
	int animCount = 0;
	char frame[4] = { '-', '\\', '|', '/' };
	while (1) {
		animCount = (animCount + 1) % 4;
		printChar(g_cursorOffset + 1, g_consoleAttribute, frame[animCount]);
		mSleep(30);
	}
}
void lineAnimationR_sub(){
	Character* vim = (Character*) VIDEO_MEM;
	Character oldLine[VIDEO_HEIGHT];		//이전에 그렸던 선을 지울 때 사용
	int i;
	int animOffset = 0;
	int beforeOffset = VIDEO_WIDTH - 1;

	for (i = 0; i < VIDEO_HEIGHT; i++) {
		oldLine[i] = vim[VIDEO_WIDTH * i + beforeOffset];
	}

	while (1) {
		for (i = 0; i < VIDEO_HEIGHT; i++) {
			//이전에 그렸던 선을 지운다.
			printChar(
			VIDEO_WIDTH * i + beforeOffset, oldLine[i].attribute,
					oldLine[i].Character);
			//선을 그리기 전에 이전 정보를 저장해둔다.
			oldLine[i] = vim[VIDEO_WIDTH * i + animOffset];
			//선을 그린다.
			printChar(VIDEO_WIDTH * i + animOffset,
					((CONSOLE_COLOR_BLACK << 4) | CONSOLE_COLOR_RED), '*');
		}
		animOffset = (animOffset + 1) % (VIDEO_WIDTH);
		beforeOffset = (beforeOffset + 1) % (VIDEO_WIDTH);
		mSleep(10);
	}
}
void lineAnimationL_sub() {
	Character* vim = (Character*) VIDEO_MEM;
	Character oldLine[VIDEO_HEIGHT];		//이전에 그렸던 선을 지울 때 사용
	int i;
	int animOffset = VIDEO_WIDTH - 1;
	int beforeOffset = 0;

	for (i = 0; i < VIDEO_HEIGHT; i++) {
		oldLine[i] = vim[VIDEO_WIDTH * i + animOffset];
	}

	while (1) {
		for (i = 0; i < VIDEO_HEIGHT; i++) {
			//이전에 그렸던 선을 지운다.
			printChar(
			VIDEO_WIDTH * i + beforeOffset, oldLine[i].attribute,
					oldLine[i].Character);
			//선을 그리기 전에 이전 정보를 저장해둔다.
			oldLine[i] = vim[VIDEO_WIDTH * i + animOffset];
			//선을 그린다.
			printChar(VIDEO_WIDTH * i + animOffset,
					((CONSOLE_COLOR_BLACK << 4) | CONSOLE_COLOR_MAGENTA), '*');
		}
		animOffset = (animOffset + VIDEO_WIDTH - 1) % (VIDEO_WIDTH);
		beforeOffset = (beforeOffset + VIDEO_WIDTH - 1) % (VIDEO_WIDTH);
		mSleep(10);
	}
}
int animationTest(const char* args){
	if (memCmp(args, "c", 1) == 0){
		return createTask(cursorAnimation_sub, mMalloc(1024) + 1024, 1024);
	}
	else if (memCmp(args, "r", 1) == 0){
		return createTask(lineAnimationR_sub, mMalloc(1024) + 1024, 1024);
	}
	else if (memCmp(args, "l", 1) == 0){
		return createTask(lineAnimationL_sub, mMalloc(1024) + 1024, 1024);
	}
	else if(memCmp(args, "help", getStrLen("help")) == 0){
		cPrintf("animation list:\n");
		cPrintf("\tc:cursorAnimation.\n");
		cPrintf("\tr:the line move to right.\n");
		cPrintf("\tl:the line move to left.\n");
		cPrintf("ex)anim c\n");
	}
	else{
		cPrintf("unknown option.\n");
	}
	return 0;
}
