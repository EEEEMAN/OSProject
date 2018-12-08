include config

BOOTFILE = boot.img

ifeq ($(GUIMODE), y)
	CFLAGS := -DDEBUGMODE
	ASMFLAGS := -dDEBUGMODE
else
	CFLAGS :=
	ASMFLAGS :=
endif

all : build

build : 
	@echo
	@echo ================build start======================
	make sizeCheck
	@echo ================build complete====================
	@echo

$(BOOTFILE) : makeBootsector sizefix
	@echo
	@echo ================make $(BOOTFILE)======================
	cat bootsector/bin/bootsector.bin kernel1/bin/kernel1.bin kernel2/bin/kernel2.bin > $@
	@echo ================$(BOOTFILE) created====================
	@echo

makeBootsector : 
	@echo
	@echo ================make bootsector======================
	make -C bootsector ASMFLAGS=$(ASMFLAGS)
	@echo ================bootsector created====================
	@echo
	
makeKernel1 :
	@echo
	@echo ================make kernel1======================
	make -C kernel1
	@echo ================kernel1 created====================
	@echo
	
makeKernel2 :
	@echo
	@echo ================make kernel2======================
	make -C kernel2 CFLAGS=$(CFLAGS)
	@echo ================kernel2 created====================
	@echo
	
makeSizeFixer : 
	@echo
	@echo ================make util======================
	make -C util
	@echo ================util created====================
	@echo

sizefix : makeKernel1 makeKernel2 makeSizeFixer
	@echo
	@echo ================kernel1.bin Size Fix======================
	util/SizeFixer.exe kernel1/bin/kernel1.bin
	@echo ================kernel1.bin Size Fixed====================
	@echo
	@echo
	@echo ================kernel2.bin Size Fix======================
	util/SizeFixer.exe kernel2/bin/kernel2.bin
	@echo ================kernel2.bin Size Fixed====================
	@echo
	
sizeCheck : $(BOOTFILE) sizefix
	@echo
	@echo ================kernel Size Check======================
	util/SizeChecker.exe $(BOOTFILE) kernel1/bin/kernel1.bin kernel2/bin/kernel2.bin
	@echo ================kernel1 Size Checked====================
	@echo

install : build
	@echo
	@echo ================kernel install start=====================
	util/OSInstaller.exe $(BOOTFILE)
	@echo ================kernel1 install complete====================
	@echo

clean:
	@echo
	@echo ================clean all folder======================
	rm -f $(BOOTFILE)
	make -C bootsector clean
	make -C kernel1 clean
	make -C kernel2 clean
	make -C util clean
	@echo ================all folder cleaned======================
	@echo