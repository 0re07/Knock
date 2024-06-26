#include <DxLib.h>
#include "./SoundMng.h"
#include "SoundApp.h"

/// <param name="isPlayStart">停止後に最初から再生するか（true:再生する false:再生しない）</param>
void SoundApp::PlayOnceSound(std::string key, bool isPlayStart)
{
	PlaySoundMem(lpSoundMng.GetSoundID(key)[0], DX_PLAYTYPE_BACK, isPlayStart);
}

void SoundApp::PlayLoopSound(std::string key, bool isPlayStart)
{
	PlaySoundMem(lpSoundMng.GetSoundID(key)[0], DX_PLAYTYPE_LOOP, isPlayStart);
}

void SoundApp::StopSound(std::string key)
{
	StopSoundMem(lpSoundMng.GetSoundID(key)[0]);
}

SoundApp::SoundApp()
{
}

SoundApp::~SoundApp()
{
}
