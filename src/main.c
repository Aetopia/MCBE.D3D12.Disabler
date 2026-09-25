#include <MinHook.h>
#include <d3dcommon.h>

PEXCEPTION_HANDLER g_CxxFrameHandler = {};

PVOID __wrap_memcpy(PVOID dst, PVOID src, SIZE_T count)
{
    __movsb(dst, src, count);
    return dst;
}

PVOID __wrap_memset(PVOID dst, BYTE data, SIZE_T count)
{
    __stosb(dst, data, count);
    return dst;
}

__declspec(dllexport) EXCEPTION_DISPOSITION __CxxFrameHandler4(PVOID except, PVOID rn, PVOID context, PVOID dc)
{
    return g_CxxFrameHandler(except, rn, context, dc);
}

HRESULT D3D12CreateDevice(PVOID adapter, D3D_FEATURE_LEVEL level, PVOID iid, PVOID device)
{
    return DXGI_ERROR_UNSUPPORTED;
}

BOOL DllMain(HINSTANCE instance, DWORD reason, PVOID reserved)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(instance);

        HMODULE ucrt = GetModuleHandleW(L"UCRTBASE");
        g_CxxFrameHandler = (PVOID)GetProcAddress(ucrt, "__CxxFrameHandler4");

        HMODULE d3d12 = LoadLibraryExW(L"D3D12", NULL, LOAD_LIBRARY_SEARCH_SYSTEM32);
        HMODULE target = (PVOID)GetProcAddress(d3d12, "D3D12CreateDevice");

        MH_Initialize();
        MH_CreateHook(target, D3D12CreateDevice, NULL);
        MH_EnableHook(target);
    }
    return TRUE;
}