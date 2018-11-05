LD = x86_64-pc-linux-ld.exe -melf_i386 -T k1Linker -nostdlib -Map bin/kernel.map -e _entry
GCC = x86_64-pc-linux-gcc.exe -c -m32 -ffreestanding
OBJCOPY = x86_64-pc-linux-objcopy -j .text -j .data -j .rodata -j .bss -O binary -S
MAINFILE = kernel.o

COBJECTFILES = $(addprefix bin/, $(subst kernel.o, , $(notdir $(patsubst %.c,%.o,$(wildcard ./*.c)))))

all : dep kernel1.bin

dep:
	make -C bin -f ../makefile InternalDependency

kernel1.bin : bin/EntryPoint.bin bin/kernel1_noEntry.bin
	@echo
	@echo ================make kernel1.bin=========================
	cat $^ > $@
	@echo ================kernel1.bin created======================
	@echo

bin/kernel1_noEntry.bin : bin/kernel.elf
	@echo
	@echo ================make kernel1.bin=========================
	$(OBJCOPY) $^ $@
	@echo ================kernel1.bin created======================
	@echo

bin/EntryPoint.bin : EntryPoint.asm
	@echo
	@echo ================make EntryPoint======================
	nasm -o $@ $<
	@echo ================EntryPoint created======================
	@echo

bin/kernel.elf : bin/$(MAINFILE) bin/asmfunc.o $(COBJECTFILES)
	@echo
	@echo ================make kernel.elf======================
	$(LD) -o $@ $^
	@echo ================kernel.elf created======================
	@echo

bin/asmfunc.o : asmfunc.asm asmfunc.h
	@echo
	@echo ================make IOFunc.o======================
	nasm -f elf32 -o $@ $<
	@echo ================IOFunc.o created======================
	@echo

InternalDependency:
	$(GCC) -MM $(wildcard ../*.c) > Dependency.dsp
	
bin/%.o : %.c
	$(GCC) -o $@ $<

clean : 
	@echo
	@echo ================clean kernel1 folder======================
	rm -f kernel1.bin
	rm -f bin/*.*
	@echo ===============kernel1 folder cleaned======================
	@echo
	
ifeq (Dependency.dep, $(wildcard Dependency.dep))
	include Dependency.dep
endif