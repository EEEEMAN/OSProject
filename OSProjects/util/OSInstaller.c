#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <dirent.h>

void getMBR(const char* devName);
unsigned char writePTE(const char* imgName);
unsigned char installImage(const char* devName, const char* imgName);

//완성된 이미지파일을 실제 USB에 넣는 프로그램
int main(int argc, char *argv[]) { //인수 : 이미지파일 이름
	char deviceList[10][1024] = { 0, };
	DIR* devDir;
	struct dirent* devDirList;
	int devCount = 0; //검색된 장치 수
	int i = 0;
	char imgName = { 0, };
	int selectedDeviceNum = -1;

	//인수 체크
	if (argc != 2) {
		printf("argc error. %d\n", argc);
		exit(-1);
	}

	////////////////장치 리스트 가져오기/////////////////////////////////
	devDir = opendir("/dev");
	while (devDirList = readdir(devDir)) {
		if (devDirList->d_name[0] == 's' && devDirList->d_name[1] == 'd') {
			if (devDirList->d_name[2] != 'a') {
				strcpy(deviceList[devCount], "/dev/");
				strcat(deviceList[devCount], devDirList->d_name);
				devCount++;
			}
		}
	}
	closedir(devDir);
	////////////////////////////////////////////////////////////////////

	while (!(selectedDeviceNum >= 0 && selectedDeviceNum < devCount)) {
		printf("select device.\n");
		for (i = 0; i < devCount; i++) {
			printf("%d:%s\n", i, deviceList[i]);
		}
		scanf("%d", &selectedDeviceNum);
	}

	printf("extracting mbr from %s\n", deviceList[selectedDeviceNum]);
	getMBR(deviceList[selectedDeviceNum]);

	if (writePTE(argv[1]) == 0) {
		printf("error...\n");
		exit(-1);
	}

	installImage(deviceList[0], argv[1]);
}

//장치의 MBR을 읽어서 파일로 만드는 함수
void getMBR(const char* devName) {
	char command[1024];
	sprintf(command, "sudo dd if=%s of=/MBR.bin bs=512 count=1", devName);
	printf("%s\n", command);
	if (system(command) == -1) {
		printf("%s's mbr load error...\n", devName);
	}
	printf("%s's mbr load complete.\n", devName);
}

unsigned char writePTE(const char* imgName) {
	int imgDescriptor;
	int MBRDescriptor;
	unsigned char pte[16];
	int i, j;

	imgDescriptor = open(imgName, O_WRONLY | O_BINARY);
	if (imgDescriptor == -1) {
		printf("%s not found\n", imgName);
		return 0;
	}
	MBRDescriptor = open("/MBR.bin", O_RDONLY | O_BINARY);
	if (MBRDescriptor == -1) {
		printf("MBR.bin not found\n");
		return 0;
	}

	lseek(MBRDescriptor, 0x01be, SEEK_SET);
	lseek(imgDescriptor, 0x01be, SEEK_SET);
	for (j = 0; j < 4; j++) {
		read(MBRDescriptor, pte, 16);

		//mbr인지 체크
		if (!(pte[0] == 0x80 || pte[0] == 0x00)) {
			printf("0x%x is not 0x80 or 0x00. cannot found MBR.\n", pte[0]);
			close(imgDescriptor);
			close(MBRDescriptor);
			return 0;
		}

		printf("partition table entry%d write start\n", j+1);
		for (i = 0; i < 16; i++) {
			printf("%x", pte[i]);
		}
		printf("\n");

		write(imgDescriptor, pte, 16);
	}

	close(imgDescriptor);
	close(MBRDescriptor);

	printf("partition table entry write complete\n");
	return 1;
}

unsigned char installImage(const char* devName, const char* imgName) {
	int imgDescriptor;
	struct stat imgStat;
	char command[1024];

//이미지파일 사이즈 구하기
	imgDescriptor = open(imgName, O_RDONLY | O_BINARY);
	stat(imgName, &imgStat);
	printf("imageFile size is %dByte.\n", imgStat.st_size);

	sprintf(command, "sudo dd if=%s of=/dev/sdb bs=%d count=1", imgName,
			imgStat.st_size);
	printf("%s\n", command);

	if (system(command) == -1) {
		return 0;
	}
	return 1;
}
