#include <windows.h>
#include "detours.h"

// مؤشر للدالة الأصلية
static BOOL (WINAPI * TrueGetVolumeInformationA)(
    LPCSTR, LPSTR, DWORD, LPDWORD, LPDWORD, LPDWORD, LPSTR, DWORD
) = GetVolumeInformationA;

// دالة الـHook
BOOL WINAPI HookedGetVolumeInformationA(
    LPCSTR lpRootPathName,
    LPSTR  lpVolumeNameBuffer,
    DWORD  nVolumeNameSize,
    LPDWORD lpVolumeSerialNumber,
    LPDWORD lpMaximumComponentLength,
    LPDWORD lpFileSystemFlags,
    LPSTR  lpFileSystemNameBuffer,
    DWORD  nFileSystemNameSize
) {
    if (lpVolumeSerialNumber) {
        *lpVolumeSerialNumber = 0x1234ABCD;  // استبدل بالقيمة المطلوبة
    }
    return TRUE;
}

BOOL WINAPI DllMain(HINSTANCE hinst, DWORD reason, LPVOID reserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourAttach(&(PVOID&)TrueGetVolumeInformationA, HookedGetVolumeInformationA);
        DetourTransactionCommit();
    }
    else if (reason == DLL_PROCESS_DETACH) {
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourDetach(&(PVOID&)TrueGetVolumeInformationA, HookedGetVolumeInformationA);
        DetourTransactionCommit();
    }
    return TRUE;
}
