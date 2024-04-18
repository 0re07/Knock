#pragma once
#include "Scene.h"

const int MAX_PAGE = 2;

struct OparationInfo {
	//���ݑI������Ă��邩 
	//false:����Ă��Ȃ� true:����Ă���
	bool now;
	//�V�[���^�C�g���̉摜
	int oparatImg;
};


class OparationScene :
    public Scene
{
public:
	OparationScene(SceneManager& manager, Transitor& transit);
	~OparationScene(void);
	virtual void Update(Input& input)override;
	virtual void Draw() override;


private:
	void Select(Input& input);

	int count_;

	OparationInfo info_[MAX_PAGE];

	//�v���C���[�`��ʒu
	Vector2D pPos_;
	int vel_;
	double pAngle_;

	int playerImg_;

	int opImg_;
};

