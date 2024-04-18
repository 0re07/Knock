#include <DxLib.h>
#include "./SoundMng.h"
#include "SoundApp.h"

/// <param name="isPlayStart">��~��ɍŏ�����Đ����邩�itrue:�Đ����� false:�Đ����Ȃ��j</param>
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
