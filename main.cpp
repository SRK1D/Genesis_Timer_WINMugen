#include "memory.h"
#include "procs.h"
#include "logger.h"
#include <iostream>
#include <string>

int main() {
    
    std::cout << '\n';
    log::info("GENESIS made by SRK1D");
    log::info("---");

    // Find the process ID for "winmugen.exe"
    int mugenPID = procs::findProcPIDByName(L"winmugen.exe");

    if (mugenPID == -1) {
        log::error("Could not find process...");
        return -1;
    }
    log::info("Mugen PID: " + std::to_string(mugenPID));

    // Find the module base address for "winmugen.exe"
    byte* mugenBaseAddress = procs::findBaseAddressByModuleName(mugenPID, L"winmugen.exe");
    if ((int)mugenBaseAddress == -1) {
        log::error("Could not find the base address of the targetted module...");
        return -1;
    }

    log::info("Module Base Address: " + std::to_string((int)mugenBaseAddress));

    // Open the process (winmugen.exe)
    HANDLE mugenProc = OpenProcess(PROCESS_ALL_ACCESS, false, mugenPID);
    if (!mugenProc) {
        log::error("Could not create an handler for the process MUGEN");
        return -1;
    }

    // This is the timer part of the game, going to remove it for infinite time allowed
    // Original code:-----------------------------------------------------------------------
    // winmugen.exe+1FDB8 - 8B 81 40BC0000        - mov eax,[ecx+0000BC40]
    // -------------------------------------------------------------------------------------

    // Overwritten code:--------------------------------------------------------------------
    // winmugen.exe+1FDB8 - B8 99090000           - mov eax, 0x001
    // winmugen.exe+1FDBD - 90                    - nop
    // -------------------------------------------------------------------------------------

    byte* instructionAddress = mugenBaseAddress + 0x1FDB8;
    byte newInstructions[] = { 0xB8, 0x01, 0x00, 0x00, 0x00, 0x90 };

    if (!mem::overwriteProcessMemory(mugenProc, instructionAddress, newInstructions, sizeof(newInstructions))) {
        log::error("Could not modify the bytes, maybe the permissions arent strong enough...");
        return -1;
    }

    log::info("Finished step: mov eax,[ecx+0000BC40] -> mov eax, 0x001!");
    return 0;
}