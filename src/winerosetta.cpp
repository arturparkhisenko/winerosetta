#include <windows.h>
#include <stdint.h>
#include <stdio.h>
#include <d3d9.h>
#include <ShlObj.h> // Include for SHGetKnownFolderPath

LONG WINAPI
VectoredHandler1(
    struct _EXCEPTION_POINTERS *ExceptionInfo
    )
{
    if (ExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_ILLEGAL_INSTRUCTION) {
        auto context = ExceptionInfo->ContextRecord;

        if (*reinterpret_cast<uint16_t*>(context->Eip) == 0xD063) {
            // emulate arpl    ax, dx
            /*
IF RPL bits(0,1) of DEST < RPL bits(0,1) of SRC
THEN
   ZF := 1;
   RPL bits(0,1) of DEST := RPL bits(0,1) of SRC;
ELSE
   ZF := 0;
FI;            
            */
            auto dest = reinterpret_cast<uint16_t*>(&context->Eax);
            auto src = reinterpret_cast<uint16_t*>(&context->Edx);
            if ((*dest & 3) < (*src & 3)) {
                context->EFlags |= 0x40; // set ZF
                *dest = (*dest & ~3) | (*src & 3);
            } else {
                context->EFlags &= ~0x40; // clear ZF
            }

            context->Eip += 2;

            return EXCEPTION_CONTINUE_EXECUTION;
        }

        // .text:006FA876 DC D8                                               fcomp   st
        if (*reinterpret_cast<uint16_t*>(context->Eip) == 0xD8DC) {
            DWORD oldProtect;
            VirtualProtect(reinterpret_cast<void*>(context->Eip), 2, PAGE_EXECUTE_READWRITE, &oldProtect);
            *reinterpret_cast<uint16_t*>(context->Eip) = 0xD8D8; // fcomp st0
            VirtualProtect(reinterpret_cast<void*>(context->Eip), 2, PAGE_EXECUTE_READ, &oldProtect);
            return EXCEPTION_CONTINUE_EXECUTION;
        }

        char buffer[256];
        sprintf(buffer, "Exception: %08X at %08X", ExceptionInfo->ExceptionRecord->ExceptionCode, context->Eip);
        MessageBoxA(NULL, buffer, "Win32", MB_OK);
    }
    return EXCEPTION_CONTINUE_SEARCH;
}


BOOL WINAPI DllMain(HMODULE module, DWORD reason, LPVOID reserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(module);
        TCHAR module_path[MAX_PATH];
        if (GetModuleFileName(module, module_path, MAX_PATH)) {
            LoadLibrary(module_path);
        }        
        AddVectoredExceptionHandler(1, VectoredHandler1);
    }
    return TRUE;
}

using Direct3DCreate9_t = decltype(&Direct3DCreate9);
extern "C" auto WINAPI export_Direct3DCreate9(UINT SDKVersion) -> IDirect3D9* {
    HMODULE d3d9;
    PWSTR system32_path = nullptr;
    HRESULT hr = SHGetKnownFolderPath(FOLDERID_System, 0, NULL, &system32_path);
    if (SUCCEEDED(hr)) {
        char d3d9_path[MAX_PATH];
        sprintf(d3d9_path, "%S\\d3d9.dll", system32_path);
        d3d9 = LoadLibraryEx(d3d9_path, 0, LOAD_WITH_ALTERED_SEARCH_PATH);
        CoTaskMemFree(system32_path);
    }    
    static Direct3DCreate9_t original_Direct3DCreate9 = (Direct3DCreate9_t) GetProcAddress(d3d9, "Direct3DCreate9");


    return original_Direct3DCreate9(SDKVersion);
}
