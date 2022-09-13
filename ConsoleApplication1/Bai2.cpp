#include<Windows.h>
#include<stdio.h>
#include<iostream>
#include<psapi.h>
#include<wchar.h>
#include<string>
#include<tlhelp32.h>
#include<tchar.h>
#include<windows.h>
#include<tlhelp32.h>
#include<tchar.h>
using namespace std;
DWORD MyGetProcessId(LPCTSTR ProcessName) // non-conflicting function name
{
    PROCESSENTRY32 pt;
    HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    pt.dwSize = sizeof(PROCESSENTRY32);
    if (Process32First(hsnap, &pt)) { // must call this first
        do {
            if (!lstrcmpi(pt.szExeFile, ProcessName)) {
                CloseHandle(hsnap);
                return pt.th32ProcessID;
            }
        } while (Process32Next(hsnap, &pt));
    }
    CloseHandle(hsnap); // close handle on failure
    return 0;
}

/*int main()
{

    DWORD pid = MyGetProcessId(TEXT("svchost.exe"));
    cout << pid;
    if (pid == 0) { printf("error 1"); getchar(); }//error
    return 0;
}*/