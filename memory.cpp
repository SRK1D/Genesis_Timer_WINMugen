#include "memory.h"

bool mem::overwriteProcessMemory(HANDLE proc, byte* dstAddress, byte* addressedBytes, size_t sizeOfBytes) {
    DWORD oldProtection;

    VirtualProtectEx(proc, dstAddress, sizeOfBytes, PAGE_EXECUTE_READWRITE, &oldProtection);
    if (oldProtection == NULL) {
        return false;
    }
    if (!WriteProcessMemory(proc, dstAddress, addressedBytes, sizeOfBytes, nullptr)) {
        return false;
    }
    VirtualProtectEx(proc, dstAddress, sizeOfBytes, oldProtection, nullptr);

    return true;
}

char* mem::readProcessMemory(HANDLE proc, byte* dstAddress, size_t sizeOfBytes) {
    char* bytesRead = new char[sizeOfBytes];
    ReadProcessMemory(proc, dstAddress, bytesRead, sizeOfBytes, nullptr);
    return bytesRead;
}