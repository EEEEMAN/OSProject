#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>

//파일 크기를 1섹터 크기에 맞기 조절
int main(int argc, char *argv[]){
	struct stat st;
	int kerneldescriptor = 0;

	//인수 체크
	if (argc != 2) {printf("argc error. %d\n", argc); exit(-1);}
	kerneldescriptor = open(argv[1], O_WRONLY|O_BINARY);
	if (kerneldescriptor == -1){printf("%f not found\n", argv[1]); exit(-1);}

	//파일 읽고 크기 체크
	stat(argv[1], &st);
	printf("file size is %d byte\n", st.st_size);

	//크기가 512로 나눠떨어지면 크기 조절할 필요 없음
	if (st.st_size % 512 == 0){
		printf("no need to change size.\n");
		return 0;
	}

	int afterSize = ((int)(st.st_size / 512) + 1) * 512;
	printf("change to %d byte\n", afterSize);

	if (ftruncate(kerneldescriptor, afterSize) != -1){
		printf("complete\n");
	}else{
		printf("error\n");
	}

	close(kerneldescriptor);
	return 0;
}
