#include "PCI.h"
#include "asmfunc2.h"

DWORD getPCICSData(int reg, int func, int devNum, int busNum){
	DWORD configAddressRegister;

	//유효비트를 1로
	configAddressRegister = (DWORD)1 << 31;
	//레지스터 설정
	configAddressRegister |= reg & 0xFF;
	//함수번호 설정
	configAddressRegister |= (func & 0xF) << 8;
	//디바이스번호 설정
	configAddressRegister |= (devNum & 0xFF) << 11;
	//버스번호 설정
	configAddressRegister |= (busNum & 0xFF) << 16;
	out32bits(PCI_CONFIG_ADDRESS_PORT, configAddressRegister);

	return in32bits(PCI_CONFIG_DATA_PORT);
}
