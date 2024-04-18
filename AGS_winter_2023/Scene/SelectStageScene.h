#pragma once
#include <string>
#include "../common/Vector2D.h"
#include "Stage/StageManager.h"
#include "Scene.h"

const int STAGE_VALUE = 4;

struct SelectStageInfo {
	//�`��ʒu
	Vector2D pos;
	//���ݑI������Ă��邩 
	//false:����Ă��Ȃ� true:����Ă���
	bool now;		
	//���肳�ꂽ��
	bool decision;
	//�f���̉摜
	int planetImg[50];
	//�f���̑傫��
	double size;
};

class SelectStageScene :
    public Scene
{
public:
	SelectStageScene(SceneManager& manager, Transitor& transit);
	~SelectStageScene(void);
	virtual void Update(Input& input)override;
	virtual void Draw() override;

private:
	//�X�e�[�W�I������
	void Select(Input& input);

	StageManager stageManager_;

	//�e�f���̏�񓝊�
	SelectStageInfo select_[STAGE_VALUE];

	//�X�e�[�W�^�C�g���摜
	int title_[STAGE_VALUE];

	//�I������Ă���f���̔ԍ�
	int count_;

	//�V�[���J�ڂ̗]�T����������
	int change_;
};

