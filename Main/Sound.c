#include "Sound.h"

// Global variables
MCI_OPEN_PARMS mciOpenMusic;

int dwID;

// Functions
void PlayMusic(const char* musicFilePath, bool loop)
{
	int pathSize = MultiByteToWideChar(CP_ACP, 0, musicFilePath, -1, NULL, NULL);

	wchar_t* bgmPath = (wchar_t*)malloc(sizeof(WCHAR) * pathSize);

	MultiByteToWideChar(CP_ACP, 0, musicFilePath, strlen(musicFilePath) + 1, bgmPath, pathSize);

	mciOpenMusic.lpstrElementName = bgmPath;
	mciOpenMusic.lpstrDeviceType = L"mpegvideo";

	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpenMusic);

	dwID = mciOpenMusic.wDeviceID;

	mciSendCommand(dwID, MCI_PLAY, loop ? MCI_DGV_PLAY_REPEAT : MCI_NOTIFY, (DWORD)(LPVOID)&mciOpenMusic);

	free(bgmPath);
}

void RePlayMusic(bool loop)
{
	mciSendCommand(dwID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
	mciSendCommand(dwID, MCI_PLAY, loop ? MCI_DGV_PLAY_REPEAT : MCI_NOTIFY, (DWORD)(LPVOID)&mciOpenMusic);
}

void PauseMusic()
{
	mciSendCommand(dwID, MCI_PAUSE, MCI_WAIT, (DWORD)(LPVOID)NULL);
}

void UnpauseMusic()
{
	mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&mciOpenMusic);
}

void StopMusic()
{
	mciSendCommand(dwID, MCI_STOP, MCI_WAIT, (DWORD)(LPVOID)NULL);
}