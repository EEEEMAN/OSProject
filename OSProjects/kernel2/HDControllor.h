#ifndef __HDCONTROLLOR_H__
#define __HDCONTROLLOR_H__

#include "../kernel1/OSDefine.h"

#define HDC_PORT_DATA_REGISTER1					0x1F0
#define HDC_PORT_DATA_REGISTER2					0x170
#define HDC_PORT_ERROR_REGISTER1				0x1F1
#define HDC_PORT_ERROR_REGISTER2				0x171
#define HDC_PORT_SECTOR_COUNT_REGISTER1			0x1F2
#define HDC_PORT_SECTOR_COUNT_REGISTER2			0x172
#define HDC_PORT_SECTOR_NUMBER_REGISTER1		0x1F3
#define HDC_PORT_SECTOR_NUMBER_REGISTER2		0x173
#define HDC_PORT_CYLINDER_LSB_REGISTER1			0x1F4
#define HDC_PORT_CYLINDER_LSB_REGISTER2			0x174
#define HDC_PORT_CYLINDER_MSB_REGISTER1			0x1F5
#define HDC_PORT_CYLINDER_MSB_REGISTER2			0x175
#define HDC_PORT_DRIVE_HEAD_REGISTER1			0x1F6
#define HDC_PORT_DRIVE_HEAD_REGISTER2			0x176
#define HDC_PORT_STATUS_REGISTER1				0x1F7
#define HDC_PORT_STATUS_REGISTER2				0x177
#define HDC_PORT_COMMAND_REGISTER1				0x1F7
#define HDC_PORT_COMMAND_REGISTER2				0x177
#define HDC_PORT_DIGITAL_OUTPUT_REGISTER1		0x3F6
#define HDC_PORT_DIGITAL_OUTPUT_REGISTER2		0x376
#define HDC_PORT_DRIVE_ADDRESS_REGISTER1		0x3F7
#define HDC_PORT_DRIVE_ADDRESS_REGISTER2		0x377

#define HDC_COMMAND_READ						0x20
#define HDC_COMMAND_WRITE						0x30
#define HDC_COMMAND_DRIVE_DETECTION				0xEC

#define HDC_STATUS_BSY							0x80
#define HDC_STATUS_DRDY							0x40
#define HDC_STATUS_DF							0x20
#define HDC_STATUS_DSC							0x10
#define HDC_STATUS_DRQ							0x08
#define HDC_STATUS_CORR							0x04
#define HDC_STATUS_IDX							0x02
#define HDC_STATUS_ERR							0x01

#define HDC_DRIVE_HEAD_MODE_LBA					0xE0
#define HDC_DRIVE_HEAD_MODE_CHS					0xA0
#define HDC_DRIVE_HEAD_MASTER					0x00
#define HDC_DRIVE_HEAD_SLAVE					0x10

#define HDC_DIGITAL_OUTPUT_SRST					0x04
#define HDC_DIGITAL_OUTPUT_N_IEN				0x02

#pragma pack(push, 1)
typedef struct _HDDInfo{
	WORD conf;

	WORD cylinderNum;
	WORD reserved1;

	WORD headNum;
	WORD bytePerTrack;
	WORD bytePerSector;

	WORD sectorPerCylinder;
	WORD intersectorGap;
	WORD byteInPhaseLock;
	WORD numberOfVenderUniqueStatusWord;

	WORD serialNumber[10];
	WORD controllerType;
	WORD bufferSize;
	WORD numberOfECCBytes;
	WORD FirmwareRevision[4];

	WORD modelNumber[20];
	WORD reserved2[13];

	DWORD totalSectors;
	WORD reserved3[196];
}HDDInfo;
#pragma pack(pop)

BOOL readHDDInfo(BOOL isFirstHDD, BOOL isMaster, HDDInfo* hddInfo);
void changeHDDInterruptStatus(BOOL isFirst, BOOL isDisable);

#endif /*__HDCONTROLLOR_H__*/
