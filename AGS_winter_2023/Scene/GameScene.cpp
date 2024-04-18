#include <DxLib.h>
#include "../Input.h"
#include "Transition/Transitor.h"
#include "Transition/IrisTransitor.h"
#include "Stage/StageManager.h"
#include "Stage/ThirdStage.h"
#include "Stage/TutorialStage.h"
#include "Stage/StageTitleView.h"
#include "SceneManager.h"
#include "GameOverScene.h"
#include "PauseScene.h"
#include "GameScene.h"

/// <summary>
/// 最初（チュートリアルステージ）から
/// </summary>
/// <param name="manager">シーンの管理クラス</param>
/// <param name="transit">遷移表現の管理クラス</param>
GameScene::GameScene(SceneManager& manager, Transitor& transit) :Scene(manager, transit)
{
	//デバッグ
	//stageManager_.ChangeStage(std::make_shared<SecondStage>(stageManager_, transitor_));
	//stageManager_.ChangeStage(std::make_shared<ThirdStage>(stageManager_, transitor_));

	//初期ステージの設定
	//チュートリアルステージ:0
	stageManager_.ChangeStage(std::make_shared<StageTitleView>(stageManager_, transit,0));
	stageManager_.Init();
}

/// <summary>
/// 選択されたステージ
/// </summary>
/// <param name="manager">シーンの管理クラス</param>
/// <param name="transit">遷移表現の管理クラス</param>
/// <param name="stageNum">選択されたステージの番号</param>
GameScene::GameScene(SceneManager& manager, Transitor& transit, int stageNum) :Scene(manager, transit)
{
	sceneTransitor_.Start();

	//選択されたステージの設定
	stageManager_.ChangeStage(std::make_shared<StageTitleView>(stageManager_, transit, stageNum));
	stageManager_.Init();
}

GameScene::~GameScene(void)
{
}

void GameScene::Update(Input& input)
{

	//ポーズメニュー
	//if (input.IsTriggerd("pause"))
	//{
	//	sceneManager_.PushScene(std::make_shared<PauseScene>(sceneManager_, sceneTransitor_));
	//}

	stageManager_.Update(input);

	stageManager_.EndStage();

	sceneTransitor_.Update();
}

void GameScene::Draw()
{
	ClearDrawScreen();

	stageManager_.Draw();

	sceneTransitor_.Draw();
}
