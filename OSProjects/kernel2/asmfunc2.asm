[bits 32]

global in8bits, out8bits
global in32bits, out32bits
global loadIDT, loadGDT, loadTR
global enableInterrupt, disableInterrupt, hltCall
global taskswitch, getEFLAGS, setEFLAGS
global getCR0Register, setCR0Register, memoryTest
global getInterruptStatus, setInterruptStatus

;BYTE in8bits(WORD port);
in8bits:
	push ebp
	mov ebp, esp
	push edx

	xor edx, edx
	mov edx, dword[ebp + 8]
	xor eax, eax
	in al, dx

	pop edx
	pop ebp
	ret

;void out8bits(WORD port, BYTE data);
out8bits:
	push ebp
	mov ebp, esp
	push edx
	push eax

	xor edx, edx
	mov edx, dword[ebp + 8]
	xor eax, eax
	mov eax, dword[ebp + 12]
	out dx, al

	pop eax
	pop edx
	pop ebp
	ret

;DWORD in32bits(WORD port)
in32bits:
	push ebp
	mov ebp, esp
	push edx

	xor edx, edx
	mov edx, dword[ebp + 8]
	xor eax, eax
	in eax, dx

	pop edx
	pop ebp
	ret

;void out32bits(WORD port, DWORD data)
out32bits:
	push ebp
	mov ebp, esp
	push edx
	push eax

	xor edx, edx
	mov edx, dword[ebp + 8]
	xor eax, eax
	mov eax, dword[ebp + 12]
	out dx, eax

	pop eax
	pop edx
	pop ebp
	ret

;void loadIDT(WORD size, DWORD address)
loadIDT:
	push ebp
	mov ebp, esp
	push eax

	xor eax, eax
	mov ax, [ebp + 8]
	mov [IDT_SIZE], ax
	mov eax, [ebp + 12]
	mov [IDT_ADDRESS], eax
	lidt [IDT]

	pop eax
	pop ebp
	ret
IDT:
	IDT_SIZE	dw	0x0000
	IDT_ADDRESS	dd	0x00000000

enableInterrupt:
	sti			;인터럽트 활성화
	ret

disableInterrupt:
	cli			;인터럽트 비활성화
	ret

hltCall:
	hlt
	ret

;;void loadGDT(WORD size, DWORD address);
loadGDT:
	push ebp
	mov ebp, esp
	push eax

	xor eax, eax
	mov ax, [ebp + 8]
	mov [GDT_SIZE], ax
	mov eax, [ebp + 12]
	mov [GDT_ADDRESS], eax
	lgdt [GDT]

	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:flush_seg
	nop
	nop
	flush_seg:

	pop eax
	pop ebp
	ret
GDT:
	GDT_SIZE	dw	0x0000
	GDT_ADDRESS	dd	0x00000000

;void loadTR(int offset);
loadTR:
	push ebp
	mov ebp, esp
	push eax

	mov eax, [ebp + 8]
	ltr ax

	pop eax
	pop ebp
	ret

;void taskswitch(int eip, int cs);
taskswitch:
	jmp far [esp + 4]
	ret

getEFLAGS:
	pushfd
	pop eax

	ret

;void setEFLAGS(DWORD eflags);
setEFLAGS:
	push ebp
	mov ebp, esp
	push eax

	mov eax, dword[ebp + 8]
	push eax
	popfd

	pop eax
	pop ebp
	ret

;DWORD getCR0Register();
getCR0Register:
	mov eax, cr0
	ret

;void setCR0Register(DWORD CR0);
setCR0Register:
	push ebp
	mov ebp, esp
	push eax

	mov eax, dword[ebp + 8]
	mov cr0, eax

	pop eax
	pop ebp
	ret

;BOOL getInterruptStatus();
getInterruptStatus:
	push eax

	pushfd
	pop eax
	shr eax, 9

	pop eax
;void setInterruptStatus(BOOL status);
setInterruptStatus:
	push ebp
	mov ebp, esp
	push eax
	push ecx

	xor eax, eax
	mov eax, [ebp + 8]
	pushfd
	pop ecx
	or ecx, eax
	push ecx
	popfd

	pop ecx
	pop eax
	pop ebp
	ret

;DWORD memoryTest(DWORD start, DWORD end);
memoryTest:
	push ebp
	mov ebp, esp

	push edi
	push esi
	push ebx
	mov esi, 0xaa55aa55
	mov edi, 0x55aa55aa
	mov eax, [ebp + 8]

MEMORY_TEST_LOOP:
	mov ebx, eax
	add ebx, 0xffc	;4kb중 가장 끝의 1바이트만을 체크하도록 조정
	mov edx, [ebx]
	mov [ebx], esi
	xor dword [ebx], 0xffffffff
	cmp edi, [ebx]
	jne MEMORY_TEST_END
	xor dword [ebx], 0xffffffff
	cmp esi, [ebx]
	jne MEMORY_TEST_END
	mov [ebx], edx
	add eax, 0x1000		;4bp단위로 검사
	cmp eax, [ebp + 12]
	jbe MEMORY_TEST_LOOP
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret

MEMORY_TEST_END:
	mov [ebx], edx
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
