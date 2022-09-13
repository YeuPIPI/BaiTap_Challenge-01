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
#include <string>]
#include <process.h>
using namespace std;

int main() {
	DWORD PID;
	cout << "Nhap:";
	cin >> PID;
	DWORD process_id = PID;
	const auto explorer = OpenProcess(PROCESS_TERMINATE, false, process_id);
	TerminateProcess(explorer, 1);
	CloseHandle(explorer);
	return 0;
}