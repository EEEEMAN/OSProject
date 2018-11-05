global isrDivideZero, isrDebugMode, isrNMI, isrINT3, isrOverflow, isrOverAddress
global isrNonExistCommand, isrNonExistDevice, isrContinuousException, isrCoprocessorError
global isrTSSError, isrOverSegment, isrStackSegmentError, isrViolidProtectRule, isrPageFault
global isrNonDefiled, isrFloatingError, isrAligndError, isrMachineCheckError, isrSIMDError
global isrVirtualizationError, isrSecurityError, isrTimerInterrupt, isrKeyboardInterrupt
global isrControlProtectionException
global isrDefault22, isrDefault23, isrDefault24, isrDefault25, isrDefault26
global isrDefault27, isrDefault28, isrDefault29, isrDefault31, isrDefault

extern defaultHandler, keyboardHandler, testTimerHandler, UnknownHandler

INTERRUPTSTACK	equ 0x3fffC

%macro SAVECONTEXT 0
	;mov dword[INTERRUPTSTACK], esp			;기존의 스택 포인터를 보존
	;mov esp, INTERRUPTSTACK					;인터럽트용 스택 공간을 새로 할당
	;모든 레지스터를 스택에 삽입
	pushad
	pushfd
	push gs
	push fs
	mov ax, es
	push ax
	mov ax, ds
	push ax

	;세그먼트 셀렉터 교체
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov gs, ax
	mov fs, ax
%endmacro

%macro LOADCONTEXT 0
	pop ax
	mov ds, ax
	pop ax
	mov es, ax
	pop fs
	pop gs
	popfd
	popad
	;mov esp, dword[INTERRUPTSTACK]
%endmacro

;;;;;;;;;;;;;;;;;;;;;;;;;;;ISR;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
isrDivideZero:
	SAVECONTEXT

	push 0				;인수(에러코드)
	push 0				;인수(인터럽트 번호)
	call defaultHandler
	add esp, 8			;함수호출 종료 후 인수를 비움

	LOADCONTEXT
	iret

isrDebugMode:
	SAVECONTEXT

	push 0
	push 1
	call defaultHandler
	add esp, 8

	LOADCONTEXT
	iret

isrNMI:
	SAVECONTEXT

	push 0
	push 2
	call defaultHandler
	add esp, 8

	LOADCONTEXT
	iret

isrINT3:
	SAVECONTEXT

	push 0
	push 3
	call defaultHandler
	add esp, 8

	LOADCONTEXT
	iret

isrOverflow:
	SAVECONTEXT

	push 0
	push 4
	call defaultHandler
	add esp, 8

	LOADCONTEXT
	iret

isrOverAddress:
	SAVECONTEXT

	push 0
	push 5
	call defaultHandler
	add esp, 8

	LOADCONTEXT
	iret

isrNonExistCommand:
	SAVECONTEXT

	push 0
	push 6
	call defaultHandler
	add esp, 8

	LOADCONTEXT
	iret

isrNonExistDevice:
	SAVECONTEXT

	push 0
	push 7
	call defaultHandler
	add esp, 8

	LOADCONTEXT
	iret

isrContinuousException:
	SAVECONTEXT

	mov eax, dword[INTERRUPTSTACK]
	push dword[eax]
	push 8
	call defaultHandler
	add esp, 8

	LOADCONTEXT
	add esp, 4			;에러코드를 비움
	iret

isrCoprocessorError:
	SAVECONTEXT

	push 0
	push 9
	call defaultHandler
	add esp, 8

	LOADCONTEXT
	iret

isrTSSError:
	SAVECONTEXT

	mov eax, dword[INTERRUPTSTACK]
	push dword[eax]
	push 10
	call defaultHandler
	add esp, 8

	LOADCONTEXT
	add esp, 4
	iret

isrOverSegment:
	SAVECONTEXT

	mov eax, dword[INTERRUPTSTACK]
	push dword[eax]
	push 11
	call defaultHandler
	add esp, 8

	LOADCONTEXT
	add esp, 4
	iret

isrStackSegmentError:
	SAVECONTEXT

	mov eax, dword[INTERRUPTSTACK]
	push dword[eax]
	push 12
	call defaultHandler
	add esp, 8

	LOADCONTEXT
	add esp, 4
	iret

isrViolidProtectRule:
	SAVECONTEXT

	mov eax, dword[INTERRUPTSTACK]
	push dword[eax]
	push 13
	call defaultHandler
	add esp, 8

	LOADCONTEXT
	add esp, 4
	iret

isrPageFault:
	SAVECONTEXT

	mov eax, dword[INTERRUPTSTACK]
	push dword[eax]
	push 14
	call defaultHandler
	add esp, 8

	LOADCONTEXT
	add esp, 4
	iret

isrNonDefiled:
	SAVECONTEXT

	push 0
	push 15
	call defaultHandler
	add esp, 8

	LOADCONTEXT
	iret

isrFloatingError:
	SAVECONTEXT

	push 0
	push 16
	call defaultHandler
	add esp, 8

	LOADCONTEXT
	iret

isrAligndError:
	SAVECONTEXT

	mov eax, dword[INTERRUPTSTACK]
	push dword[eax]
	push 17
	call defaultHandler
	add esp, 8

	LOADCONTEXT
	add esp, 4
	iret

isrMachineCheckError:
	SAVECONTEXT

	push 0
	push 18
	call defaultHandler
	add esp, 8

	LOADCONTEXT
	iret

isrSIMDError:
	SAVECONTEXT

	push 0
	push 19
	call defaultHandler
	add esp, 8

	LOADCONTEXT
	iret

isrVirtualizationError:
	SAVECONTEXT

	push 0
	push 20
	call defaultHandler
	add esp, 8

	LOADCONTEXT
	iret

isrControlProtectionException:
	SAVECONTEXT

	push 0				;인수(에러코드)
	push 21				;인수(인터럽트 번호)
	call defaultHandler
	add esp, 8			;함수호출 종료 후 인수를 비움

	LOADCONTEXT
	iret

isrDefault22:
	SAVECONTEXT

	push 0				;인수(에러코드)
	push 22				;인수(인터럽트 번호)
	call defaultHandler
	add esp, 8			;함수호출 종료 후 인수를 비움

	LOADCONTEXT
	iret

isrDefault23:
	SAVECONTEXT

	push 0				;인수(에러코드)
	push 23				;인수(인터럽트 번호)
	call defaultHandler
	add esp, 8			;함수호출 종료 후 인수를 비움

	LOADCONTEXT
	iret

isrDefault24:
	SAVECONTEXT

	push 0				;인수(에러코드)
	push 24				;인수(인터럽트 번호)
	call defaultHandler
	add esp, 8			;함수호출 종료 후 인수를 비움

	LOADCONTEXT
	iret

isrDefault25:
	SAVECONTEXT

	push 0				;인수(에러코드)
	push 25				;인수(인터럽트 번호)
	call defaultHandler
	add esp, 8			;함수호출 종료 후 인수를 비움

	LOADCONTEXT
	iret

isrDefault26:
	SAVECONTEXT

	push 0				;인수(에러코드)
	push 26				;인수(인터럽트 번호)
	call defaultHandler
	add esp, 8			;함수호출 종료 후 인수를 비움

	LOADCONTEXT
	iret

isrDefault27:
	SAVECONTEXT

	push 0				;인수(에러코드)
	push 27				;인수(인터럽트 번호)
	call defaultHandler
	add esp, 8			;함수호출 종료 후 인수를 비움

	LOADCONTEXT
	iret

isrDefault28:
	SAVECONTEXT

	push 0				;인수(에러코드)
	push 28				;인수(인터럽트 번호)
	call defaultHandler
	add esp, 8			;함수호출 종료 후 인수를 비움

	LOADCONTEXT
	iret

isrDefault29:
	SAVECONTEXT

	push 0				;인수(에러코드)
	push 29				;인수(인터럽트 번호)
	call defaultHandler
	add esp, 8			;함수호출 종료 후 인수를 비움

	LOADCONTEXT
	iret

isrDefault31:
	SAVECONTEXT

	push 0				;인수(에러코드)
	push 31				;인수(인터럽트 번호)
	call defaultHandler
	add esp, 8			;함수호출 종료 후 인수를 비움

	LOADCONTEXT
	iret

isrSecurityError:
	SAVECONTEXT

	mov eax, dword[INTERRUPTSTACK]
	push dword[eax]
	push 30
	call defaultHandler
	add esp, 8

	LOADCONTEXT
	add esp, 4
	iret

isrTimerInterrupt:
	SAVECONTEXT

	call testTimerHandler

	LOADCONTEXT
	iret

isrKeyboardInterrupt:
	SAVECONTEXT

	call keyboardHandler

	LOADCONTEXT
	iret

isrDefault:
	SAVECONTEXT

	call UnknownHandler

	LOADCONTEXT
	iret
