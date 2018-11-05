#include "PIT.h"
#include "asmfunc2.h"

void initPIT(WORD count, BOOL isPeriodic) {
	g_timerCount = 0;
	g_timerCount2 = 0;
	out8bits(PIT_PORT_CONTROL, PIT_CONTROL_COUNTER0_ONCE);
	if (isPeriodic == TRUE) {
		out8bits(PIT_PORT_CONTROL, PIT_CONTROL_COUNTER0_PERIODIC);
	}
	out8bits(PIT_PORT_COUNTER0, count);
	out8bits(PIT_PORT_COUNTER0, count >> 8);
}

void mSleep(unsigned int time) {
	unsigned int oldtime = g_timerCount;
	unsigned int sleepTime = 0;
	while (1) {
		if (g_timerCount < oldtime) {
			sleepTime += 0xFFFFFFFF - oldtime;
			sleepTime += g_timerCount;
			oldtime = g_timerCount;
		} else if (g_timerCount > oldtime) {
			sleepTime += g_timerCount - oldtime;
			oldtime = g_timerCount;
		}
		if (sleepTime >= time) break;
	}
}
