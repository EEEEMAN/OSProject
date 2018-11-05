[bits 16]
org 0x8000

SECTION .text

_Entry:
	;보호모드 전환////////////////////////////////////////////////////////////
	lgdt [GDTR]
	cli
	mov eax, cr0
	or eax, 0x00000001
	mov cr0, eax

	jmp $+2
	nop
	nop

	jmp CodeDescriptor:ProtectedModeStart

;////////////////////////////여기부터 보호모드///////////////////////////////////////
[bits 32]

ProtectedModeStart:
	;레지스터 초기화
	mov bx, DataDescriptor
	mov ds, bx
	mov es, bx
	mov fs, bx
	mov gs, bx

	mov ss, bx
	xor esp, esp
	mov esp, 0x7bff
	mov ebp, esp

	jmp CodeDescriptor : C_LANGUAGE_START


;//////////////////////////////여기부터 GDT//////////////////////////////////////////
GDTR:
	dw GDT_END - GDT - 1
	;dd 0x10000
	dd GDT
GDT:
	NULLDescriptor equ 0x00
	dw 0x0000
	dw 0x0000
	db 0x00
	db 0x00
	db 0x00
	db 0x00

	CodeDescriptor equ 0x08
	dw 0xFFFF					;크기
	dw 0x0000					;기준주소
	db 0x00						;기준주소
	db 0x9A						;타입/S/DPL/P
	db 0xCF						;세그먼트 크기/AVL/L/DorB/G
	db 0x00						;기준주소

	DataDescriptor equ 0x10
	dw 0xFFFF
	dw 0x0000
	db 0x00
	db 0x92
	db 0xCF
	db 0x00
GDT_END:

C_LANGUAGE_START:
