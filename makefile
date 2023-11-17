all:
	@echo "Please either use \"make windows\" or \"make linux\""

linux:
ifneq ("$(wildcard *.exe)", "")
	@echo "--> Deleting file"
	@rm -rf genesis.exe
endif

	@echo "--> Compiling necessary *.cpp files"
	@g++ logger.cpp main.cpp memory.cpp procs.cpp -w -o genesis

windows:
ifneq ("$(wildcard *.exe)", "")
	@echo "--> Deleting file"
	@del /Q genesis.exe
endif

	@echo "--> Compiling necessary %*%.cpp files"
	@g++ logger.cpp main.cpp memory.cpp procs.cpp -w -o genesis
