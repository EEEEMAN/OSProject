GDT.o: ../GDT.c ../GDT.h ../../kernel1/OSDefine.h ../asmfunc2.h ../task.h
utility2.o: ../utility2.c ../utility2.h ../../kernel1/OSDefine.h
PIC.o: ../PIC.c ../PIC.h ../../kernel1/OSDefine.h ../asmfunc2.h ../task.h
IDT.o: ../IDT.c ../IDT.h ../../kernel1/OSDefine.h ../ISR.h ../asmfunc2.h \
 ../task.h
keyboardControllor.o: ../keyboardControllor.c ../keyboardControllor.h \
 ../../kernel1/OSDefine.h ../asmfunc2.h ../task.h
shell.o: ../shell.c ../shell.h ../console.h ../../kernel1/OSDefine.h \
 ../keyboardControllor.h ../utility2.h ../mString.h ../PCI.h ../PIT.h \
 ../asmfunc2.h ../task.h ../mMemory.h ../mList.h ../mScheduler.h
mMemory.o: ../mMemory.c ../mMemory.h ../../kernel1/OSDefine.h \
 ../asmfunc2.h ../task.h ../console.h
mScheduler.o: ../mScheduler.c ../mScheduler.h ../../kernel1/OSDefine.h \
 ../mList.h ../task.h ../asmfunc2.h ../console.h ../mMemory.h
mString.o: ../mString.c ../mString.h ../../kernel1/OSDefine.h \
 ../console.h ../utility2.h
console.o: ../console.c ../console.h ../../kernel1/OSDefine.h \
 ../mString.h ../utility2.h ../asmfunc2.h ../task.h
interruptHandler.o: ../interruptHandler.c ../interruptHandler.h \
 ../../kernel1/OSDefine.h ../console.h ../keyboardControllor.h \
 ../asmfunc2.h ../task.h ../PIC.h ../PIT.h ../mString.h ../mScheduler.h \
 ../mList.h
mList.o: ../mList.c ../mList.h ../../kernel1/OSDefine.h ../mMemory.h
PCI.o: ../PCI.c ../PCI.h ../../kernel1/OSDefine.h ../asmfunc2.h ../task.h
task.o: ../task.c ../utility2.h ../../kernel1/OSDefine.h ../GDT.h \
 ../console.h ../asmfunc2.h ../task.h ../mScheduler.h ../mList.h
HDControllor.o: ../HDControllor.c ../HDControllor.h \
 ../../kernel1/OSDefine.h ../asmfunc2.h ../task.h
mainKernel.o: ../mainKernel.c ../console.h ../../kernel1/OSDefine.h \
 ../mainKernel.h ../GDT.h ../IDT.h ../PIC.h ../PIT.h ../asmfunc2.h \
 ../task.h ../keyboardControllor.h ../mString.h ../utility2.h ../shell.h \
 ../mMemory.h ../mList.h ../mScheduler.h ../HDControllor.h
PIT.o: ../PIT.c ../PIT.h ../../kernel1/OSDefine.h ../asmfunc2.h ../task.h
