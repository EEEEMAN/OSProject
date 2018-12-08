all : bin/bootsector.bin
	
bin/bootsector.bin : masterBootRecord.asm
	@echo 
	@echo ================make bootsector.bin======================
	nasm masterBootRecord.asm -o $@ $(ASMFLAGS)
	@echo ================bootsector.bin created======================
	@echo 
	
clean :
	@echo
	@echo ================clean bootsector folder======================
	rm -f bin/*.*
	@echo ================bootsector folder cleaned======================
	@echo
	