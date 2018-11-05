GDT.o: ../GDT.c ../GDT.h ../../kernel1/OSDefine.h ../Task.h ../asmfunc2.h
utility2.o: ../utility2.c ../utility2.h ../../kernel1/OSDefine.h
tetris.o: ../tetris.c ../tetris.h ../../kernel1/OSDefine.h ../PIT.h
PIC.o: ../PIC.c ../PIC.h ../../kernel1/OSDefine.h ../asmfunc2.h ../Task.h
IDT.o: ../IDT.c ../IDT.h ../../kernel1/OSDefine.h ../ISR.h ../asmfunc2.h \
 ../Task.h
keyboardControllor.o: ../keyboardControllor.c ../keyboardControllor.h \
 ../../kernel1/OSDefine.h ../asmfunc2.h ../Task.h
shell.o: ../shell.c ../shell.h ../console.h ../../kernel1/OSDefine.h \
 ../keyboardControllor.h ../utility2.h ../mString.h ../PCI.h ../PIT.h \
 ../asmfunc2.h ../Task.h ../mMemory.h ../mList.h ../mScheduler.h
mMemory.o: ../mMemory.c ../mMemory.h ../../kernel1/OSDefine.h \
 ../asmfunc2.h ../Task.h ../console.h
mScheduler.o: ../mScheduler.c ../mScheduler.h ../../kernel1/OSDefine.h \
 ../Task.h ../mList.h ../asmfunc2.h ../console.h ../mMemory.h
mString.o: ../mString.c ../mString.h ../../kernel1/OSDefine.h \
 ../console.h ../utility2.h
console.o: ../console.c ../console.h ../../kernel1/OSDefine.h \
 ../mString.h ../utility2.h ../asmfunc2.h ../Task.h
interruptHandler.o: ../interruptHandler.c ../interruptHandler.h \
 ../../kernel1/OSDefine.h ../console.h ../keyboardControllor.h \
 ../asmfunc2.h ../Task.h ../PIC.h ../PIT.h ../mString.h ../mScheduler.h \
 ../mList.h
mList.o: ../mList.c ../mList.h ../../kernel1/OSDefine.h ../mMemory.h
PCI.o: ../PCI.c ../PCI.h ../../kernel1/OSDefine.h ../asmfunc2.h ../Task.h
Task.o: ../Task.c ../Task.h ../../kernel1/OSDefine.h ../utility2.h \
 ../GDT.h ../console.h ../asmfunc2.h ../mScheduler.h ../mList.h
mainKernel.o: ../mainKernel.c ../console.h ../../kernel1/OSDefine.h \
 ../mainKernel.h ../GDT.h ../IDT.h ../PIC.h ../PIT.h ../asmfunc2.h \
 ../Task.h ../keyboardControllor.h ../mString.h ../utility2.h ../shell.h \
 ../mMemory.h ../mList.h ../mScheduler.h
PIT.o: ../PIT.c ../PIT.h ../../kernel1/OSDefine.h ../asmfunc2.h ../Task.h
