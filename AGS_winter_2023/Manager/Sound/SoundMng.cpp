#include <DxLib.h>
#include "SoundMng.h"

#include "../../_debug/_DebugConOut.h"
#include "../../_debug/_DebugConOut.h"

const VecInt& SoundMng::GetSoundID(std::string key)
{
	if (soundMap_.count(key) == 0)
	{
		GetSoundID(key, key);
	}
	return soundMap_[key];
}

//�t�@�C�����A�t�@�C���ǂݍ���œ���Ă���Ƃ��ɖ��O����
const VecInt& SoundMng::GetSoundID(std::string f_name, std::string key)
{

	if (soundMap_.count(key) == 0)
	{
		soundMap_[key].resize(1);
		soundMap_[key][0] = LoadSoundMem(f_name.c_str());
	}
	return soundMap_[key];
}

SoundMng::SoundMng()
{
}

SoundMng::~SoundMng()
{
}
