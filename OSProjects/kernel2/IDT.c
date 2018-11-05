#include "IDT.h"
#include "ISR.h"
#include "asmfunc2.h"

void initIDT(DWORD address) {
	IDescripter* ptIdt = (IDescripter*) address;
	int i;

	setIDTDescriptor(&(ptIdt[0]), isrDivideZero, 0x08, IDT_FLAGS_DEFAULT);
	setIDTDescriptor(&(ptIdt[1]), isrDebugMode, 0x08, IDT_FLAGS_DEFAULT);
	setIDTDescriptor(&(ptIdt[2]), isrNMI, 0x08, IDT_FLAGS_DEFAULT);
	setIDTDescriptor(&(ptIdt[3]), isrINT3, 0x08, IDT_FLAGS_DEFAULT);
	setIDTDescriptor(&(ptIdt[4]), isrOverflow, 0x08, IDT_FLAGS_DEFAULT);
	setIDTDescriptor(&(ptIdt[5]), isrOverAddress, 0x08, IDT_FLAGS_DEFAULT);
	setIDTDescriptor(&(ptIdt[6]), isrNonExistCommand, 0x08, IDT_FLAGS_DEFAULT);
	setIDTDescriptor(&(ptIdt[7]), isrNonExistDevice, 0x08, IDT_FLAGS_DEFAULT);
	setIDTDescriptor(&(ptIdt[8]), isrContinuousException, 0x08,
	IDT_FLAGS_DEFAULT);
	setIDTDescriptor(&(ptIdt[9]), isrCoprocessorError, 0x08, IDT_FLAGS_DEFAULT);
	setIDTDescriptor(&(ptIdt[10]), isrTSSError, 0x08, IDT_FLAGS_DEFAULT);
	setIDTDescriptor(&(ptIdt[11]), isrOverSegment, 0x08, IDT_FLAGS_DEFAULT);
	setIDTDescriptor(&(ptIdt[12]), isrStackSegmentError, 0x08,
	IDT_FLAGS_DEFAULT);
	setIDTDescriptor(&(ptIdt[13]), isrViolidProtectRule, 0x08,
	IDT_FLAGS_DEFAULT);
	setIDTDescriptor(&(ptIdt[14]), isrPageFault, 0x08, IDT_FLAGS_DEFAULT);
	setIDTDescriptor(&(ptIdt[15]), isrNonDefiled, 0x08, IDT_FLAGS_DEFAULT);
	setIDTDescriptor(&(ptIdt[16]), isrFloatingError, 0x08, IDT_FLAGS_DEFAULT);
	setIDTDescriptor(&(ptIdt[17]), isrAligndError, 0x08, IDT_FLAGS_DEFAULT);
	setIDTDescriptor(&(ptIdt[18]), isrMachineCheckError, 0x08,
	IDT_FLAGS_DEFAULT);
	setIDTDescriptor(&(ptIdt[19]), isrSIMDError, 0x08, IDT_FLAGS_DEFAULT);
	setIDTDescriptor(&(ptIdt[20]), isrVirtualizationError, 0x08,
			IDT_FLAGS_DEFAULT);

//	for (i = 21; i < 30; i++) {
//		ptIdt[i].offset1 = ((DWORD) funcAddress & 0xFFFF);
//		ptIdt[i].codeSegmentSelector = 0x08;
//		ptIdt[i].none = 0;
//		ptIdt[i].flags = IDT_FLAGS_DEFAULT;
//		ptIdt[i].offset2 = ((DWORD) funcAddress >> 16);
//	}
	setIDTDescriptor(&(ptIdt[21]), isrControlProtectionException, 0x08, IDT_FLAGS_DEFAULT);
	setIDTDescriptor(&(ptIdt[22]), isrDefault22, 0x08, IDT_FLAGS_DEFAULT);
	setIDTDescriptor(&(ptIdt[23]), isrDefault23, 0x08, IDT_FLAGS_DEFAULT);
	setIDTDescriptor(&(ptIdt[24]), isrDefault24, 0x08, IDT_FLAGS_DEFAULT);
	setIDTDescriptor(&(ptIdt[25]), isrDefault25, 0x08, IDT_FLAGS_DEFAULT);
	setIDTDescriptor(&(ptIdt[26]), isrDefault26, 0x08, IDT_FLAGS_DEFAULT);
	setIDTDescriptor(&(ptIdt[27]), isrDefault27, 0x08, IDT_FLAGS_DEFAULT);
	setIDTDescriptor(&(ptIdt[28]), isrDefault28, 0x08, IDT_FLAGS_DEFAULT);
	setIDTDescriptor(&(ptIdt[29]), isrDefault29, 0x08, IDT_FLAGS_DEFAULT);

	setIDTDescriptor(&(ptIdt[30]), isrSecurityError, 0x08, IDT_FLAGS_DEFAULT);
	setIDTDescriptor(&(ptIdt[31]), isrDefault31, 0x08, IDT_FLAGS_DEFAULT);
	setIDTDescriptor(&(ptIdt[32]), isrTimerInterrupt, 0x08, IDT_FLAGS_DEFAULT);
	setIDTDescriptor(&(ptIdt[33]), isrKeyboardInterrupt, 0x08,
			IDT_FLAGS_DEFAULT);
	for (i = 34; i < IDESCRIPTOR_MAX_COUNT; i++) {
		ptIdt[i].offset1 = ((DWORD) isrDefault & 0xFFFF);
		ptIdt[i].codeSegmentSelector = 0x08;
		ptIdt[i].none = 0;
		ptIdt[i].flags = IDT_FLAGS_DEFAULT;
		ptIdt[i].offset2 = ((DWORD) isrDefault >> 16);
	}

	loadIDT(IDESCRIPTOR_MAX_COUNT * sizeof(IDescripter), ptIdt);
}

void setIDTDescriptor(IDescripter* descriptor, void* handler, WORD CSSelector,
BYTE flag) {
	descriptor->offset1 = ((DWORD) handler & 0xFFFF);
	descriptor->codeSegmentSelector = CSSelector;
	descriptor->none = 0;
	descriptor->flags = flag;
	descriptor->offset2 = ((DWORD) handler >> 16);
}
