#include <DxLib.h>
#include "../Input.h"
#include "Transition/Transitor.h"
#include "TitleScene.h"
#include "SceneManager.h"
#include "GameOverScene.h"

GameOverScene::GameOverScene(SceneManager& manager, Transitor& transit):Scene(manager,transit)
{
	sceneTransitor_.Start();

	//É^ÉCÉgÉãÉçÉS
	resultImg_ = LoadGraph("./Data/Image/Result/result.png");

	//âºÅ¶
	pushSpaceImg_ = LoadGraph("./Data/Image/Result/pushSpace.png");

	//îwåi
	bgImg_ = LoadGraph("./Data/Image/backGround/Select.png");
}

GameOverScene::~GameOverScene(void)
{
}

void GameOverScene::Update(Input& input)
{
	cnt_++;

	if (input.IsTriggerd("check")) {
		sceneManager_.ChangeScene(std::make_shared<TitleScene>(sceneManager_, sceneTransitor_));
	}

	sceneTransitor_.Update();

}

void GameOverScene::Draw()
{
	ClearDrawScreen();

	//DrawString(50, 50, "GameOverScene", 0xffffff);

	//îwåi
	DrawGraph(0, 0, bgImg_, true);

	//É^ÉCÉgÉãÉçÉS
	DrawGraph(0, 0, resultImg_, true);

	if ((cnt_ / 30) % 2) {
		//âºÅ¶
		DrawGraph(0, 0, pushSpaceImg_, true);
	}

	sceneTransitor_.Draw();

}
