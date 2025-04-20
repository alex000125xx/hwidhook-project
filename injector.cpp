// injector.cpp
#include <windows.h>
#include <tlhelp32.h>
#include <iostream>

// يعثر على PID للعملية بالاسم
DWORD FindProcessId(const wchar_t* processName) {
    PROCESSENTRY32W pe32{};
    pe32.dwSize = sizeof(pe32);
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap == INVALID_HANDLE_VALUE) return 0;
    for (BOOL ok = Process32FirstW(hSnap, &pe32); ok; ok = Process32NextW(hSnap, &pe32)) {
        if (_wcsicmp(pe32.szExeFile, processName) == 0) {
            CloseHandle(hSnap);
            return pe32.th32ProcessID;
        }
    }
    CloseHandle(hSnap);
    return 0;
}

int wmain(int argc, wchar_t* argv[]) {
    if (argc != 3) {
        std::wcerr << L"Usage: Injector.exe <ProcessName.exe> <full\\path\\to\\hwidhook.dll>\n";
        return 1;
    }
    const wchar_t* procName = argv[1];
    const wchar_t* dllPath  = argv[2];
    DWORD pid = FindProcessId(procName);
    if (!pid) {
        std::wcerr << L"Process not found: " << procName << L"\n";
        return 1;
    }
    HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (!hProc) {
        std::wcerr << L"OpenProcess failed. Run as administrator?\n";
        return 1;
    }
    size_t size = (wcslen(dllPath) + 1) * sizeof(wchar_t);
    LPVOID alloc = VirtualAllocEx(hProc, nullptr, size, MEM_COMMIT, PAGE_READWRITE);
    WriteProcessMemory(hProc, alloc, dllPath, size, nullptr);

    HMODULE hKernel = GetModuleHandleW(L"kernel32.dll");
    FARPROC loadLib = GetProcAddress(hKernel, "LoadLibraryW");
    HANDLE hThread = CreateRemoteThread(hProc, nullptr, 0,
                                        (LPTHREAD_START_ROUTINE)loadLib,
                                        alloc, 0, nullptr);
    if (hThread) {
        WaitForSingleObject(hThread, INFINITE);
        CloseHandle(hThread);
        std::wcout << L"Injection succeeded.\n";
    } else {
        std::wcerr << L"CreateRemoteThread failed.\n";
    }
    VirtualFreeEx(hProc, alloc, 0, MEM_RELEASE);
    CloseHandle(hProc);
    return 0;
}
