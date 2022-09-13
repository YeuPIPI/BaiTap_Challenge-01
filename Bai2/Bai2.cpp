#include <windows.h>
#include <process.h>
#include <Tlhelp32.h>
//#include <winbase.h>
#include <string.h>
#include<iostream>
#include< tchar.h >
using namespace std;


void KILL_PROCESS_ID(DWORD process_id) {
	
	const auto explorer = OpenProcess(PROCESS_TERMINATE, false, process_id);
	TerminateProcess(explorer, 1);
	CloseHandle(explorer);
	
}


void Kill_Process_ByName(const wstring& processName)
{
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
	PROCESSENTRY32 pEntry;
	pEntry.dwSize = sizeof(pEntry);
	BOOL hRes = Process32First(hSnapShot, &pEntry);
	while (hRes)
	{
		if (!processName.compare(pEntry.szExeFile))
		{
			HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0,
				(DWORD)pEntry.th32ProcessID);
			if (hProcess != NULL)
			{
				TerminateProcess(hProcess, 9);
				CloseHandle(hProcess);
			}
		}
		hRes = Process32Next(hSnapShot, &pEntry);
	}
	CloseHandle(hSnapShot);
}
int main() {
	cout << "---------TerminateProcess--------------" << endl;
	while (true) {
		cout << "1.DUNG TIEN TRINH BANG PID." << endl;
		cout << "2.DUNG TIEN TRINH BANG ten tien trinh." << endl;
		cout << "3.THOAT." << endl;
		int select;
		cout << "Nhap lua chon : ";
		cin >> select;
		if (select == 1) {
			cout << "Nhap PID:";
			DWORD process_id;
			cin >> process_id;
			KILL_PROCESS_ID(process_id);
		}
		if (select == 2) {
			string  a;
			cout << "Nhap ten tien trinh : ";
			cin >> a;
			wstring ws(a.begin(), a.end());
			Kill_Process_ByName(ws);
		}
		if (select == 3) {
			break;
		}
	}
	return 0;
}