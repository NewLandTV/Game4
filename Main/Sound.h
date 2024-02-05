#ifndef __SOUND_H__
#define __SOUND_H__

#include <stdbool.h>
#include <Windows.h>
#include <mmsystem.h>
#include <Digitalv.h>

#pragma comment(lib, "winmm.lib")

// Functions
void PlayMusic(const char* musicFilePath, bool loop);
void RePlayMusic(bool loop);
void PauseMusic();
void UnpauseMusic();
void StopMusic();

#endif