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

#define	PIC_IMR_MASK_IRQ0			0x01
#define	PIC_IMR_MASK_IRQ1			0x02
#define	PIC_IMR_MASK_IRQ2			0x04
#define	PIC_IMR_MASK_IRQ3			0x08
#define	PIC_IMR_MASK_IRQ4			0x10
#define	PIC_IMR_MASK_IRQ5			0x20
#define	PIC_IMR_MASK_IRQ6			0x40
#define	PIC_IMR_MASK_IRQ7			0x80
#define	PIC_IMR_MASK_IRQ_ALL		0xFF

void initPIC();
void maskPIC(WORD mask);
void sendEOI(int IRQNum);

#endif /*__PIC_H__*/
