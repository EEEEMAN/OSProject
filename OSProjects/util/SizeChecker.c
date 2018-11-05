#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>


//커널 사이즈를 읽고 이미지 파일의 2, 3번째 바이트에 저장
int main(int argc, char *argv[]){ //인수 : boot.img파일, 서브커널파일, 메인커널파일
	//커널 정보
	struct stat subkernelStat;
	struct stat kernelStat;

	//디스크립터
	int bootdesc = 0;
	int subkerneldesc = 0;
	int kerneldesc = 0;

	unsigned char subkernelSize = 0; //1차커널 사이즈를 저장하기 위한 변수
	unsigned char kernelSize = 0; //2차커널 사이즈를 저장하기 위한 변수

	//인수 체크
	if (argc != 4) {printf("argc error. %d\n", argc); exit(-1);}
	bootdesc = open(argv[1], O_WRONLY|O_BINARY);
	subkerneldesc = open(argv[2], O_WRONLY|O_BINARY);
	kerneldesc = open(argv[3], O_RDONLY|O_BINARY);
	if (bootdesc == -1){printf("%f not found\n", argv[1]); exit(-1);}
	if (subkerneldesc == -1){printf("%f not found\n", argv[2]); exit(-1);}
	if (kerneldesc == -1){printf("%f not found\n", argv[3]); exit(-1);}

	//커널 사이즈를 저장할 위치로 이동
	lseek(bootdesc, 2, SEEK_SET);

	//커널 사이즈를 기입
	stat(argv[2], &subkernelStat);
	stat(argv[3], &kernelStat);
	//섹터단위로변환
	subkernelSize = subkernelStat.st_size / 512;
	kernelSize = kernelStat.st_size / 512;
	printf("subkernel Size is %d sector\n", subkernelSize);
	printf("kernel Size is %d sector\n", kernelSize);
	write(bootdesc, &subkernelSize, 1);
	write(bootdesc, &kernelSize, 1);

	close(bootdesc);
	close(subkerneldesc);
	close(kerneldesc);
}
