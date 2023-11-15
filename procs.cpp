#include "procs.h"
#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>

int procs::findProcPIDByName(const wchar_t* procName) {
    // Creates a PROCESSENTRY32W to hold information from a snapshot of processes on the computer
    PROCESSENTRY32W processInfo;
    processInfo.dwSize = sizeof(PROCESSENTRY32W);

    HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    // If it could not get even the first process, close the handle and return 0
    if (!Process32FirstW(processesSnapshot, &processInfo)) {
        CloseHandle(processesSnapshot);
        return -1;
    }
    
    // Compares wchar[] using "wide char string ignore case compare"
    // If it is indeed valid, close the handle and return the PID
    if (_wcsicmp(processInfo.szExeFile, procName) == 0) {
        CloseHandle(processesSnapshot);
        return processInfo.th32ProcessID;
    }

    while (Process32NextW(processesSnapshot, &processInfo)) {
        // Compares wchar[] using "wide char string ignore case compare"
        // If it is indeed valid, close the handle and return the PID
        if (_wcsicmp(processInfo.szExeFile, procName) == 0) {
            CloseHandle(processesSnapshot);
            return processInfo.th32ProcessID;
        }
    }

    // If it is not in the process list, return -1
    return -1;
}

byte* procs::findBaseAddressByModuleName(int procID, const wchar_t* moduleName) {
    // Sets up the variable that will get the data about the modules of a specified process
    MODULEENTRY32W modules;
    modules.dwSize = sizeof(MODULEENTRY32W);

    HANDLE modulesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, procID);
    if (!Module32FirstW(modulesSnapshot, &modules)) {
        CloseHandle(modulesSnapshot);
    }

    // Compares module name with the following module, a product from iteration thru the modules of a process using its PID
    // Closes the handle and returns the base address if needed :D
    if (_wcsicmp(modules.szModule, moduleName) == 0) {
        CloseHandle(modulesSnapshot);
        return modules.modBaseAddr;
    }

    while (Module32NextW(modulesSnapshot, &modules)) {
        if (_wcsicmp(modules.szModule, moduleName) == 0) {
            CloseHandle(modulesSnapshot);
            return modules.modBaseAddr;
        }
    }

    // If it doesnt find anything, return -1
    return (byte*)-1;
}