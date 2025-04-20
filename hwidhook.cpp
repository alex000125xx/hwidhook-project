// hwidhook.cpp
#include <windows.h>
#include "detours.h"

// pointer للدالة الأصلية (مثال لو البرنامج يستدعي GetComputerNameA أو دوال أخرى)
// هنا سنخدع أي استدعاء لـ GetComputerNameA لتُعيد الـHWID كسلسلة
static BOOL (WINAPI * TrueGetComputerNameA)(LPSTR, LPDWORD) = GetComputerNameA;

// القيمة التي نريد أن يراها البرنامج كـHWID
static const char fakeHwid[] = "45d6eb786a3cda50de154b374f578be6c9e324263bb4c090f1b7075923244152";

// الدالة التي سنركبها بدلاً من GetComputerNameA
BOOL WINAPI HookedGetComputerNameA(LPSTR lpBuffer, LPDWORD nSize) {
    size_t len = strlen(fakeHwid);
    if (lpBuffer && *nSize > len) {
        memcpy(lpBuffer, fakeHwid, len + 1);
        *nSize = (DWORD)len;
        return TRUE;
    }
    // fallback للوظيفة الأصلية لو الحجم غير كافٍ
    return TrueGetComputerNameA(lpBuffer, nSize);
}

BOOL WINAPI DllMain(HINSTANCE hinst, DWORD reason, LPVOID reserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourAttach(&(PVOID&)TrueGetComputerNameA, HookedGetComputerNameA);
        DetourTransactionCommit();
    }
    else if (reason == DLL_PROCESS_DETACH) {
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourDetach(&(PVOID&)TrueGetComputerNameA, HookedGetComputerNameA);
        DetourTransactionCommit();
    }
    return TRUE;
}
