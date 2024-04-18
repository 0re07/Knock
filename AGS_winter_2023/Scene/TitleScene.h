#pragma once
#include "Scene.h"

const int MODE_VALUE = 2;

struct SelectSceneInfo {
	//�`��ʒu
	Vector2D pos;
	//���ݑI������Ă��邩 
	//false:����Ă��Ȃ� true:����Ă���
	bool now;
	//�V�[���^�C�g���̉摜
	int sceneImg;
};

class TitleScene :
    public Scene
{
public:
	TitleScene(SceneManager& manager, Transitor& transit);
	~TitleScene(void);
	virtual void Update(Input& input)override;
	virtual void Draw() override;

private:
	void Select(Input& input);

	SelectSceneInfo selectMode_[MODE_VALUE];

	//�I������Ă���\��
	int selectImg_;

	//�I������Ă���V�[���̔ԍ�
	int count_;

	//�^�C�g�����S�摜
	int titleImg_;

	//�����摜
	int starImg_[9];
};

