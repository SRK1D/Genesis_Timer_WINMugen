#pragma once
#include <windows.h>

namespace mem {
    bool overwriteProcessMemory(HANDLE proc, byte* dstAddress, byte* addressedBytes, size_t sizeOfBytes);
    char* readProcessMemory(HANDLE proc, byte* dstAddress, size_t sizeOfBytes);
}