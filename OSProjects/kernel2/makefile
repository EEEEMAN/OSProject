LD = x86_64-pc-linux-ld.exe -melf_i386 -T k2Linker -nostdlib -Map bin/kernel.map -e _entry
GCC = x86_64-pc-linux-gcc.exe -c -m32 -ffreestanding
OBJCOPY = x86_64-pc-linux-objcopy -j .text -j .data -j .rodata -j .bss -O binary -S
MAINFILE = mainKernel.o

COBJECTFILES = $(addprefix bin/, $(subst kernel.o, , $(notdir $(patsubst %.c,%.o,$(wildcard ./*.c)))))
ASMOBJECTFILES = $(addprefix bin/, $(notdir $(patsubst %.asm,%.o,$(wildcard ./*.asm))))

all : dep kernel2.bin

dep:
	make -C bin -f ../makefile InternalDependency

kernel2.bin : bin/kernel.elf
	@echo
	@echo ================make kernel2.bin=========================
	$(OBJCOPY) $^ $@
	@echo ================kernel2.bin created======================
	@echo

bin/kernel.elf : bin/$(MAINFILE) $(COBJECTFILES) $(ASMOBJECTFILES)
	@echo
	@echo ================make kernel.elf======================
	$(LD) -o $@ $^
	@echo ================kernel.elf created======================
	@echo

InternalDependency:
	$(GCC) -MM $(wildcard ../*.c) > Dependency.dsp
	
bin/%.o : %.c
	$(GCC) -o $@ $<
bin/%.o : %.asm
	nasm -f elf32 -o $@ $<

clean : 
	@echo
	@echo ================clean kernel2 folder======================
	rm -f kernel2.bin
	rm -f bin/*.*
	@echo ===============kernel2 folder cleaned======================
	@echo
	
ifeq (Dependency.dep, $(wildcard Dependency.dep))
	include Dependency.dep
endif