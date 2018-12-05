#include "HDControllor.h"
#include "asmfunc2.h"

BOOL readHDDInfo(BOOL isFirstHDD, BOOL isMaster, HDDInfo* hddInfo){
	WORD DHRPort = 0;
	BYTE flags = 0;

	//드라이브_헤드_레지스터 설정
	if (isFirstHDD == TRUE){
		DHRPort = HDC_PORT_DRIVE_HEAD_REGISTER1;
	}else{
		DHRPort = HDC_PORT_DRIVE_HEAD_REGISTER2;
	}
	flags = HDC_DRIVE_HEAD_MODE_LBA;
	if (isMaster == FALSE){
		flags |= HDC_DRIVE_HEAD_SLAVE;
	}
	out8bits(DHRPort, flags);


}

void changeHDDInterruptStatus(BOOL isFirst, BOOL isDisable){
	BYTE disable;

	if (isDisable == TRUE){
		disable = HDC_DIGITAL_OUTPUT_N_IEN;
	}else{
		disable = 0;
	}

	if (isFirst == TRUE){
		out8bits(HDC_PORT_DIGITAL_OUTPUT_REGISTER1, disable);
	}else{
		out8bits(HDC_PORT_DIGITAL_OUTPUT_REGISTER2, disable);
	}
}
