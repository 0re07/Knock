#pragma once
#include <string>

#define lpSoundApp SoundApp::GetInstanse()

class SoundApp
{
public:
	//�ÓI�R���X�g���N�^�i��ɕK�v�j
	static SoundApp& GetInstanse()
	{
		static SoundApp sApp_Instance;
		return sApp_Instance;
	}

	//���̍Đ�
	void PlayOnceSound(std::string key, bool isPlayStart);	//��x�����Đ�			
	void PlayLoopSound(std::string key, bool isPlayStart);	//���[�v�Đ�

	void PauseSound(std::string key);						//�ꎞ��~
	void StopSound(std::string key);						//��~
	void ChengeVolumeSound(std::string key, int valume);	//���ʕύX

private:
	SoundApp();
	~SoundApp();

};

