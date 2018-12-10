#include "PIC.h"
#include "asmfunc2.h"

void initPIC(){
	//maskPIC(0xFd); //타이머, 키보드빼고는 마스크
	WORD mask;

	//마스터 PIC를 초기화
	out8bits(PIC_PORT_MASTER1, ICW1);
	out8bits(PIC_PORT_MASTER2, ICW2_MASTER); //IRQ 0 ~ 7
	out8bits(PIC_PORT_MASTER2, ICW3_MASTER);
	out8bits(PIC_PORT_MASTER2, ICW4);

	//슬레이브 PIC를 초기화
	out8bits(PIC_PORT_SLAVE1, ICW1);
	out8bits(PIC_PORT_SLAVE2, ICW2_MASTER + 8); //IRQ 8 ~ 15
	out8bits(PIC_PORT_SLAVE2, ICW3_SLAVE);
	out8bits(PIC_PORT_SLAVE2, ICW4);

	//타이머, 키보드, 슬레이브PIC빼고는 마스크
	mask = 0;
	mask |= PIC_IMR_MASK_IRQ0;
	mask |= PIC_IMR_MASK_IRQ1;
	mask |= PIC_IMR_MASK_IRQ2;
	mask |= PIC_IMR_MASK_IRQ12;
	mask = ~mask;
	maskPIC(mask);
}

void maskPIC(WORD mask){
	out8bits(PIC_PORT_MASTER2, (BYTE)mask);
	out8bits(PIC_PORT_SLAVE2, (BYTE)(mask >> 8));
}

BYTE getIMR(BOOL isMaster){
	BYTE mask;
	if (isMaster == TRUE){
		mask = in8bits(PIC_PORT_MASTER2);
	}else{
		mask = in8bits(PIC_PORT_SLAVE2);
	}
	return mask;
}

void sendEOI(int IRQNum){
	out8bits(PIC_PORT_MASTER1, 0x20);
	if (IRQNum > 8){
		out8bits(PIC_PORT_SLAVE1, 0x20);
	}
}
