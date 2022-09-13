
#include<Windows.h>
#include<stdio.h>
#include<iostream>
#include<psapi.h>
#include<wchar.h>
#include<string>
#include<tlhelp32.h>
#include<tchar.h>
#include<tlhelp32.h>
#include<tchar.h>
#include <cstdio>
#include <windows.h>
#include <tlhelp32.h>
#include <string>
using namespace std;
void PrintProcessNameAndID(DWORD processID)
{
    TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");
    // Get a handle to the process.  
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
        PROCESS_VM_READ,
        FALSE, processID);
    // Get the process name.
    if (NULL != hProcess)
    {
        HMODULE hMod;
        DWORD cbNeeded;
        if (EnumProcessModules(hProcess, &hMod, sizeof(hMod),
            &cbNeeded))
        {
            GetModuleBaseName(hProcess, hMod, szProcessName,   /// API
                sizeof(szProcessName) / sizeof(TCHAR));
            //_tprintf(TEXT("%s  PID:%u\n"),szProcessName, processID);
        }
    }
    _tprintf(TEXT("%s  PID:%u\n"), szProcessName, processID);
    //_tprintf(TEXT("%s  PID:%u\n"), szProcessName, processID);
   //cout << (&szProcessName) << "PID:" << processID << endl;
    
    CloseHandle(hProcess);
}
DWORD FindProcessId(const std::wstring& processName)
{
    PROCESSENTRY32 processInfo;
    processInfo.dwSize = sizeof(processInfo);

    HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    if (processesSnapshot == INVALID_HANDLE_VALUE) {
        return 0;
    }

    Process32First(processesSnapshot, &processInfo);
    if (!processName.compare(processInfo.szExeFile))
    {
        CloseHandle(processesSnapshot);
        return processInfo.th32ProcessID;
    }

    while (Process32Next(processesSnapshot, &processInfo))
    {
        if (!processName.compare(processInfo.szExeFile))
        {
            CloseHandle(processesSnapshot);
            return processInfo.th32ProcessID;
        }
    }

    CloseHandle(processesSnapshot);
    return 0;
}
std::string ProcessIdToName(DWORD processId)
{
    std::string ret;
    HANDLE handle = OpenProcess(
        PROCESS_QUERY_LIMITED_INFORMATION,
        FALSE,
        processId   
    );
    if (handle)
    {
        DWORD buffSize = 1024;
        CHAR buffer[1024];
        if (QueryFullProcessImageNameA(handle, 0, buffer, &buffSize))
        {
            ret = buffer;
        }
        else
        {
            printf("Error GetModuleBaseNameA : %lu", GetLastError());
        }
        CloseHandle(handle);
    }
    else
    {
        printf("Error OpenProcess : %lu", GetLastError());
    }
    return ret;
}
int GetCurrentThreadCount()
{
    // first determine the id of the current process
    DWORD const  id = GetCurrentProcessId();

    // then get a process list snapshot.
    HANDLE const  snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);

    // initialize the process entry structure.
    PROCESSENTRY32 entry = { 0 };
    entry.dwSize = sizeof(entry);

    // get the current process info.
    BOOL  ret = true;
    ret = Process32First(snapshot, &entry);
    while (ret && entry.th32ProcessID != id) {
        ret = Process32Next(snapshot, &entry);
    }
    CloseHandle(snapshot);
    return ret
        ? entry.cntThreads
        : -1;
}
int main(void)
{
    // Get the list of process identifiers.
    DWORD aProcesses[1024], cbNeeded, cProcesses;
    unsigned int i;
    if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
    {
        return 1;
    }
    // Calculate how many process identifiers were returned.
    cProcesses = cbNeeded / sizeof(DWORD);
    // Print the name and process identifier for each process.
    cout << "Image Name " << " PID" << endl;
    for (i = 0; i < cProcesses; i++)
        {
    
        if (aProcesses[i] != 0)
        {

            PrintProcessNameAndID(aProcesses[i]);
        }
    }
    DWORD a = FindProcessId(L"explorer.exe");
    cout << a << endl;
    int TEST = GetCurrentThreadCount();
    cout << TEST << endl;
    system("PAUSE");
    return 0;
    
}

