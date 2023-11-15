
all:
ifneq ("$(wildcard *.exe)", "")
	@echo "--> Deleting file"
	@rm -rf genesis.exe
endif

	@echo "--> Compiling necessary *.cpp files"
	@g++ logger.cpp main.cpp memory.cpp procs.cpp -o genesis