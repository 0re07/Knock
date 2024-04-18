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
	//タイトルロゴ画像
	int resultImg_;

	//仮で入れるpush space
	int pushSpaceImg_;

};

