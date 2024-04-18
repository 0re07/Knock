#pragma once
#include "Scene.h"
class GameOverScene :
    public Scene
{
public:
	GameOverScene(SceneManager& manager, Transitor& transit);
	~GameOverScene(void);
	virtual void Update(Input& input)override;
	virtual void Draw() override;

private:
	//�^�C�g�����S�摜
	int resultImg_;

	//���œ����push space
	int pushSpaceImg_;

};

