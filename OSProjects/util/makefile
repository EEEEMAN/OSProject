all : SizeFixer.exe SizeChecker.exe OSInstaller.exe

SizeFixer.exe : SizeFixer.c
	@echo
	@echo =======Compile $@=================
	gcc -o $@ $^
	@echo========$@ Compiled================
	@echo
	
SizeChecker.exe : SizeChecker.c
	@echo
	@echo =======Compile $@=================
	gcc -o $@ $^
	@echo========$@ Compiled================
	@echo
	
OSInstaller.exe : OSInstaller.c
	@echo
	@echo =======Compile $@=================
	gcc -o $@ $^
	@echo========$@ Compiled================
	@echo
	
clean : 
	rm -f SizeFixer.exe
	rm -f SizeChecker.exe
	rm -f OSInstaller.exe