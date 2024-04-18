#pragma once
#include <memory>
#include "Stage/StageManager.h"
#include "Scene.h"

class ThirdStage;

class GameScene :
    public Scene
{
public:
	GameScene(SceneManager& manager, Transitor& transit);
	GameScene(SceneManager& manager, Transitor& transit, int stageNum);
	~GameScene(void);
	virtual void Update(Input& input)override;
	virtual void Draw() override;

private:
	StageManager stageManager_;

	std::unique_ptr<ThirdStage> result_;

};

