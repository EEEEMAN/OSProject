[BITS 32]
SECTION .text

global jumpToMainKernel, setCR3Register, activePaging, activeA20Gate

;//void jumpToMainKernel();
jumpToMainKernel:
	xor esp, esp
	mov esp, 0x1ffffc
	mov ebp, esp
	jmp 0x08:0x600000
	jmp $

;//void setCR3Register(DWORD pageAddress);
setCR3Register:
	push ebp
	mov ebp, esp

	mov eax, [ebp + 8]
	mov cr3, eax

	pop ebp
	ret

;//void activePaging();
activePaging:
	mov eax, cr4
	or eax, 0x10
	mov cr4, eax

	mov eax, cr0
	or eax, 0x80000000
	mov cr0, eax
	ret

;//void activeA20Gate();
activeA20Gate:
