[Bits 16]
org 0x7c00

jmp BootCodeStart

SUB_KERNEL_SIZE		db	0xee						;1차커널 사이즈. 단위:섹터
MAIN_KERNEL_SIZE	db	0xee						;2차커널 사이즈. 단위:섹터

BootCodeStart:
	;레지스터 초기화
	xor eax, eax
	xor ebx, ebx
	xor ecx, ebx
	xor edx, ebx

	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	mov sp, 0x7bfe

	mov si, msgRegisterInitComp
	call DisplayMessage16

	call ActiveA20Gate

	mov esi, 0x01							;LBA번호
	mov ecx, 0x8000							;0x8000에 저장
	mov dl, byte[SUB_KERNEL_SIZE]			;읽을 섹터 수
	call ReadSector

	mov si, msgKernel1LoadComp
	call DisplayMessage16

	xor eax, eax
	mov al, 0x10         		 			   ;DAP 크기
	mov [0x7e00], al
	mov al, 0x00								;안씀
	mov [0x7e01], al
	mov al, byte[MAIN_KERNEL_SIZE]   			;읽을 섹터 수
	mov [0x7e02], ax

	mov ax, 0x0000							;저장할 메모리 주소
	mov [0x7e04], ax
	mov ax, 0x3000
	mov [0x7e06], ax

	xor eax, eax
	mov al, byte[SUB_KERNEL_SIZE]			;읽을 섹터 LBA 번호
	inc al
	mov [0x7e08], eax

	mov dl, 0x80
	mov ax, 0x0000
	mov ds, ax
	mov ax, 0x7e00
	mov si, ax
	mov ah, 0x42
	int 0x13

	mov	si, msgKernel2LoadComp
	call DisplayMessage16

	jmp 0x8000
	hlt

DisplayMessage16: ; si:메시지
	PUSH	AX
	PUSH	BX
_StartDispMsg:
	LODSB
	OR	AL, AL
	JZ	_DONE
	MOV	AH, 0x0E
	MOV	BH, 0x00
	MOV	BL, 0x07
	INT	0x10
	JMP	_StartDispMsg
_DONE:
	POP	BX
	POP	AX
	RET

ReadSector: ;섹터 읽기. si : 읽을 섹터 LBA 번호, ecx : 저장할 메모리 주소 edx : 읽을 섹터 수
	push si
	push ecx
	push eax
	push edx

	xor eax, eax
	mov al, 0x10            ;DAP 크기
	mov [0x7e00], al
	mov al, 0x00			;안씀
	mov [0x7e01], al
	;mov ax, 0x05			;읽을 섹터 수
	mov ax, dx   			;읽을 섹터 수
	mov [0x7e02], ax
	mov eax, ecx			;저장할 메모리 주소
	mov [0x7e04], eax
	xor eax, eax
	mov ax, si				;읽을 섹터 LBA 번호
	mov [0x7e08], eax

	mov dl, 0x80
	mov ax, 0x0000
	mov ds, ax
	mov ax, 0x7e00
	mov si, ax
	mov ah, 0x42
	int 0x13
	jnc ReadComp
	mov si, msgErr
	call DisplayMessage16
	hlt
ReadComp:
	pop edx
	pop eax
	pop ecx
	pop si
	ret

ActiveA20Gate:
	mov ax, 0x2401
	int 0x15
	jnc _A20SUCCESS
_A20FAIL:
	in al, 0x92
	or al, 0x02
	and al, 0xfe
	out 0x92, al
_A20SUCCESS:
	ret

msgRegisterInitComp		db "Register initialize complete...", 0x00
msgKernel1LoadComp		db "subKernel load Complete...", 0x00
msgKernel2LoadComp		db "mainKernel load Complete...", 0x00
msgErr					db	"Error...", 0x00

times 446 - ($ - $$) db 0

bBootIndicator					db		0x80		;부탕 가능한 파티션이면 0x80 아니면 0x00
bStartingHeader					db 		0x20		;도스시절 필드
wStartingSectorAndCylinder		dw 		0x0021		;도스시절 필드
bSystemID						db 		0x0c		;시스템 타입. 0x0B 또는 0x0C
bEndingHeader					db 		0xfe		;도스시절 필드
wEndingSectorAndCylinder		dw 		0xccff		;도스시절 필드
dwRelativeSector				dd 		0x00000800	;파티션이 시작되는 섹터
dwTotalSector					dd 		0x00ee8400	;총 파티션의 크기

TIMES 510 - ($ - $$) DB 0

DW 0xAA55
