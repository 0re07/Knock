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
	//ƒ^ƒCƒgƒ‹ƒƒS‰æ‘œ
	int resultImg_;

	//‰¼‚Å“ü‚ê‚épush space
	int pushSpaceImg_;

};

