#pragma once

#include "wchar.h"
#include <Windows.h>

namespace procs {
    int findProcPIDByName(const wchar_t* procName);
    byte* findBaseAddressByModuleName(int procID, const wchar_t* moduleName);
}