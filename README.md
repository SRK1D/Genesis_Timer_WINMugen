# Genesis M.U.G.E.N tool for timer
#### 🔴It is only for windows, sorry mac and linux users🔴

## How does it work?
- It tries to find M.U.G.E.N running by using a snapshot of all processes using [tlhelp32.h](https://learn.microsoft.com/en-us/windows/win32/api/tlhelp32/)
- If found M.U.G.E.N, it will try to find the module called "winmugen.exe"
- If again, found "winmugen.exe", it will get its base address, doing: `winmugenBaseAddress + 0x1FDB8` to find the damage bytes
- It will make the address readable and writeable using [VirtualProtectEx](https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-virtualprotectex) and save the old protection
- It will after that, write to the process memory using [WriteProcessMemory](https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-writeprocessmemory)
- It will put back the old protection using again VirtualProtectEx

## Why is this even a thing?
Well I got bored from using python, hence why I started working on this project, it is really small but it fits well what I am currently able to do

## How do I compile it?
If you use "CMD", do:
`make windows`
If you use "CMDer" or any other type of "emulators", do:
`make linux`

## With more precision, what does it write and where?
Here is  your answer:
```
    // winmugen.exe base address: 0x40000
    // Original code:-----------------------------------------------------------------------
    // winmugen.exe+1FDB8 - 8B 81 40BC0000        - mov eax,[ecx+0000BC40]
    // -------------------------------------------------------------------------------------

    // Overwritten code:--------------------------------------------------------------------
    // winmugen.exe+1FDB8 - B8 99090000           - mov eax, 0x001
    // winmugen.exe+1FDBD - 90                    - nop
    // -------------------------------------------------------------------------------------
```

## How to get MUGEN?
Download WINMugen here: [WINMugen.zip](https://mugenarchive.com/forums/downloads.php?do=file&id=267-winmugen-plus-2007-elecbyte-rouhei-anonynous-hacker&act=down&actionhash=guest)

## Project date
Was made in **november 2023**
