#ifndef __PIT_H__
#define __PIT_H__

#include"../kernel1/OSDefine.h"

#define	PIT_PORT_COUNTER0	0x40
#define	PIT_PORT_COUNTER1	0x41
#define	PIT_PORT_COUNTER2	0x42
#define	PIT_PORT_CONTROL	0x43

#define	PIT_COUNT_PER_SECOND			1193182
#define MSTOCOUNT(x)					(PIT_COUNT_PER_SECOND * (x) / 1000) //x의 단위:ms

#define PIT_MODE_TIMER					0x00		//모드0, 한번만
#define PIT_MODE_ONESHOTTIMER			0x02
#define PIT_MODE_PULSE_GEN				0x04		//모드2, 반복
#define PIT_MODE_WAVE_GEN				0x06
#define PIT_MODE_SOFTWARE_TRIGGER		0x08
#define PIT_MODE_HARDWARE_TRIGGER		0x0A

#define PIT_COUNT_BINARY				0x00		//바이너리형식으로 카운트. 범위:0x0000~0xffff
#define PIT_COUNT_BCD					0x01		//2진화10진법으로카운트. 범위:0~9999

#define PIT_RW_LATCH					0x00
#define PIT_RW_LSBMSBRW					0x30 		//LSB->MSB순으로 읽기/쓰기를함

#define PIT_SC_COUNTER0					0x00
#define PIT_SC_COUNTER1					0x40
#define PIT_SC_COUNTER2					0x80

#define PIT_CONTROL_COUNTER0_ONCE		(PIT_SC_COUNTER0 | PIT_RW_LSBMSBRW \
										| PIT_MODE_TIMER | PIT_COUNT_BINARY)
#define PIT_CONTROL_COUNTER0_PERIODIC	(PIT_SC_COUNTER0 | PIT_RW_LSBMSBRW \
										| PIT_MODE_PULSE_GEN | PIT_COUNT_BINARY)


unsigned int g_timerCount;
void initPIT(WORD count, BOOL isPeriodic);
void mSleep(unsigned int time);

#endif /*__PIT_H__*/
