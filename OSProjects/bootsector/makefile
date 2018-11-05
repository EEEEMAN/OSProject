all : bootsector.bin
	
bootsector.bin : MasterBootCode.asm
	@echo 
	@echo ================make bootsector.bin======================
	nasm MasterBootCode.asm -o $@
	@echo ================bootsector.bin created======================
	@echo 
	
clean :
	@echo
	@echo ================clean bootsector folder======================
	rm -f bootsector.bin
	rm -f bin/*.*
	@echo ================bootsector folder cleaned======================
	@echo
	