#pragma once		
#include <map>
#include <vector>
#include <string>
#include "../../common/Vector2D.h"

#define lpSoundMng SoundMng::GetInstanse()

using VecInt = std::vector<int>;

class SoundMng
{
public:
	//�ÓI�R���X�g���N�^�i��ɕK�v�j
	static SoundMng& GetInstanse()
	{
		static SoundMng s_Instance;
		return s_Instance;
	}

	const VecInt& GetSoundID(std::string key);			//���ۂɎg�p����Ƃ��͂����ŌĂяo��
	const VecInt& GetSoundID(std::string f_name, std::string key);		

private:
	SoundMng();
	~SoundMng();

	std::map<std::string, VecInt> soundMap_;

};


