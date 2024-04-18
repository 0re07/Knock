#include <DxLib.h>
#include "../Input.h"
#include "Transition/Transitor.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "OparationScene.h"

OparationScene::OparationScene(SceneManager& manager, Transitor& transit) :Scene(manager, transit)
{
	sceneTransitor_.Start();

	count_ = 0;

	pPos_ = { screenSize_.x / 2 - 200,screenSize_.y / 2-38 };
	pAngle_ = 0.0;
	vel_ = 0;

	//説明画像
	info_[0].oparatImg = LoadGraph("./Data/Image/oparation/oparat_1.png");
	info_[1].oparatImg = LoadGraph("./Data/Image/oparation/oparat_2.png");

	//プレイヤー
	playerImg_ = LoadGraph("./Data/Image/Player/Player.png");

	//背景
	bgImg_ = LoadGraph("./Data/Image/backGround/Select.png");

	opImg_ = LoadGraph("./Data/Image/oparation/op.png");

	ui_.Init();
}

OparationScene::~OparationScene(void)
{
}

void OparationScene::Update(Input& input)
{
	ui_.Update();

	//選択
	Select(input);

	//上へ
	if (input.IsTriggerd("check")) {
		vel_ += 5;
	}
	pPos_.y -= vel_;

	//左右
	if (input.IsPrassed("left")) {
		pAngle_-=0.1;
	}
	if (input.IsPrassed("right")) {
		pAngle_+=0.1;
	}

	//ステージを設定
	if (input.IsTriggerd("next") && count_ == MAX_PAGE) {
		//シーン遷移
		sceneManager_.ChangeScene(std::make_shared<GameScene>(sceneManager_, sceneTransitor_, 0));
		return;
	}

	sceneTransitor_.Update();
}

void OparationScene::Draw()
{
	ClearDrawScreen();

	//背景
	DrawGraph(0, 0, bgImg_, true);

	//モード選択
	switch (count_)
	{
	default:
		DrawGraph(0, 0, info_[0].oparatImg, true);
		return;
	case 0:
		DrawGraph(0, 0, info_[0].oparatImg, true);

		//プレイヤー描画
		//左
		DrawGraph(pPos_.x, pPos_.y, playerImg_, true);
		//右
		DrawRotaGraph(screenSize_.x / 2 + 200, screenSize_.y / 2, 1.0, pAngle_, playerImg_, true);

		//ボタン
		ui_.Draw({ 300,260 },1.2, UIVALUE::SPACE);
		ui_.Draw({ 630,260 },2.0, UIVALUE::LEFT);
		ui_.Draw({ 680,260 },2.0, UIVALUE::RIGHT);

		return;
	case 1:
		DrawGraph(0, 0, info_[1].oparatImg, true);
		ui_.Draw({ 180,220 }, 1.5, UIVALUE::SPACE);

		return;
	}

	//UI
	DrawGraph(0, 0, opImg_, true);
	ui_.Draw({ screenSize_.x - 100,screenSize_.y - 20 }, 1.2, UIVALUE::ENTER);

	sceneTransitor_.Draw();
}

void OparationScene::Select(Input& input)
{
	//左右キーでステージを選択
	if (input.IsTriggerd("shift")) {
		count_--;
		//範囲制限
		if (count_ < 0) {
			count_ = 0;
		}

		//ステージ選択
		info_[count_].now = true;

		//一つ前に選択していたシーンを選択していない状態へ戻す
		info_[count_ + 1].now = false;

		//初期化
		pPos_ = { screenSize_.x / 2 - 200,screenSize_.y / 2 - 38 };
		pAngle_ = 0.0;
		vel_ = 0;
	}
	if (input.IsTriggerd("next")) {
		count_++;
		//範囲制限
		if (count_ > MAX_PAGE) {
			count_ = MAX_PAGE;
		}

		//ステージ選択
		info_[count_].now = true;

		//一つ前に選択していたシーンを選択していない状態へ戻す
		info_[count_ - 1].now = false;
	}

}
