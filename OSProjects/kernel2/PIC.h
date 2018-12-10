#ifndef __PIC_H__
#define __PIC_H__

#include "../kernel1/OSDefine.h"

#define PIC_PORT_MASTER1			0x20
#define PIC_PORT_MASTER2			0x21
#define PIC_PORT_SLAVE1				0xA0
#define PIC_PORT_SLAVE2				0xA1

#define ICW1						0x11
#define ICW2_MASTER					0x20
#define ICW3_MASTER					0x04
#define ICW3_SLAVE					0x02
#define ICW4						0x01

#define	PIC_IMR_MASK_IRQ0			0x0001
#define	PIC_IMR_MASK_IRQ1			0x0002
#define	PIC_IMR_MASK_IRQ2			0x0004
#define	PIC_IMR_MASK_IRQ3			0x0008
#define	PIC_IMR_MASK_IRQ4			0x0010
#define	PIC_IMR_MASK_IRQ5			0x0020
#define	PIC_IMR_MASK_IRQ6			0x0040
#define	PIC_IMR_MASK_IRQ7			0x0080
#define	PIC_IMR_MASK_IRQ8			0x0100
#define	PIC_IMR_MASK_IRQ9			0x0200
#define	PIC_IMR_MASK_IRQ10			0x0400
#define	PIC_IMR_MASK_IRQ11			0x0800
#define	PIC_IMR_MASK_IRQ12			0x1000
#define	PIC_IMR_MASK_IRQ13			0x2000
#define	PIC_IMR_MASK_IRQ14			0x4000
#define	PIC_IMR_MASK_IRQ15			0x8000
#define	PIC_IMR_MASK_IRQ_ALL		0xFFFF

void initPIC();
void maskPIC(WORD mask);
BYTE getIMR(BOOL isMaster);
void sendEOI(int IRQNum);

#endif /*__PIC_H__*/
