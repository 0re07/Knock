#include <DxLib.h>
#include "../Manager/Sound/SoundMng.h"
#include "../Manager/Sound/SoundApp.h"
#include "../Input.h"
#include "Stage/TutorialStage.h"
#include "Stage/FirstStage.h"
#include "Stage/SecondStage.h"
#include "Stage/ThirdStage.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "SelectStageScene.h"

//惑星の大きさ
const double defSize = 1.0;
const double midSize = 1.5;
const double maxSize = 4.5;

SelectStageScene::SelectStageScene(SceneManager& manager, Transitor& transit) :Scene(manager, transit)
{
	sceneTransitor_.Start();

	//初期化
	//Tutorialにフォーカス
	select_[0].now = true;
	select_[0].size = midSize;

	//初期位置の設定
	for (int i = 0; i < STAGE_VALUE; ++i) {
		select_[i].pos = { 200 + (200 * i),screenSize_.y / 2 };
		select_[i].decision = false;
	}

	for (int i = 1; i < STAGE_VALUE; ++i) {
		//選択されているか
		select_[i].now = false;

		//大きさ
		select_[i].size = defSize;
	}

	//画像読み込み
	//背景
	bgImg_ = LoadGraph("./Data/Image/backGround/Select.png");

	//ステージタイトル
	title_[0] = LoadGraph("./Data/Image/Planet/top_Tutorial.png");
	title_[1] = LoadGraph("./Data/Image/Planet/top_Stage1.png");
	title_[2] = LoadGraph("./Data/Image/Planet/top_Stage2.png");
	title_[3] = LoadGraph("./Data/Image/Planet/top_Stage3.png");
	
	//惑星
	LoadDivGraph("./Data/Image/Planet/Tutorial_s.png", 50, 50, 1, 100, 100, select_[0].planetImg, true);
	LoadDivGraph("./Data/Image/Planet/Stage1_s.png", 50, 50, 1, 200, 200, select_[1].planetImg, true);
	LoadDivGraph("./Data/Image/Planet/Stage2_s.png", 50, 50, 1, 200, 200, select_[2].planetImg, true);
	LoadDivGraph("./Data/Image/Planet/Stage3_s.png", 50, 50, 1, 150, 150, select_[3].planetImg, true);

	count_ = 0;

	change_ = 60;

	//音楽
	lpSoundMng.GetSoundID("./Data/Sounds/Music/stageSelect.wav", "stageSelectScene");

	//効果音
	lpSoundMng.GetSoundID("./Data/Sounds/Sound/SelectStage/Stage.mp3", "stage");
	lpSoundMng.GetSoundID("./Data/Sounds/Sound/SelectStage/StageSelect.mp3", "selectStage");
}

SelectStageScene::~SelectStageScene(void)
{
}

void SelectStageScene::Update(Input& input)
{
	cnt_++;

	//ステージ選択
	Select(input);

	//SPACEキーで決定
 	if (input.IsTriggerd("next") || select_[count_].decision) {

		select_[count_].decision = true;

		//BGMの停止
		lpSoundApp.StopSound("stageSelectScene");

		//ステージを設定
		if (select_[count_].size == maxSize && change_ < 0) {
			//シーン遷移
			sceneManager_.ChangeScene(std::make_shared<GameScene>(sceneManager_, sceneTransitor_, count_));
			return;
		}
	}

	//BGMの再生
	lpSoundApp.PlayLoopSound("stageSelectScene", false);

	sceneTransitor_.Update();
}

void SelectStageScene::Draw()
{
	ClearDrawScreen();

	//背景
	DrawGraph(0, 0, bgImg_, true);

	//惑星
	for (int i = 0; i < STAGE_VALUE; ++i) {
		if (!select_[i].decision) {
			//Stage1~4
			DrawRotaGraph(select_[i].pos.x, select_[i].pos.y, select_[i].size, 0.0, select_[i].planetImg[(cnt_ / 5) % 50], true);
		}
	}

	//選択された惑星
	if (select_[count_].decision) {
		DrawRotaGraph(screenSize_.x / 2, screenSize_.y / 2, select_[count_].size, 0.0, select_[count_].planetImg[(cnt_ / 5) % 50], true);
		DrawGraph(0, 0, title_[count_], true);
	}

	sceneTransitor_.Draw();
}

/// <summary>
/// ステージ選択
/// </summary>
/// <param name="input">入力情報</param>
void SelectStageScene::Select(Input& input)
{

	//決定されたら
	if (select_[count_].decision) {

		//効果音再生
		lpSoundApp.PlayOnceSound("stage", false);

		--change_;
		if (select_[count_].size < maxSize) {
			select_[count_].size += 0.5;
		}
		return;
	}

	//左右キーでステージを選択
	if (input.IsTriggerd("left")) {
		count_--;
		//範囲制限
		if (count_ < 0) {
			count_ = 0;
		}

		//ステージ選択
		select_[count_].now = true;

		//一つ前に選択していた惑星を選択していない状態へ戻す
		select_[count_ + 1].size = defSize;
		select_[count_ + 1].now = false;

		//効果音再生
		lpSoundApp.PlayOnceSound("selectStage", true);
	}
	if (input.IsTriggerd("right")) {
		count_++;
		//範囲制限
		if (count_ > STAGE_VALUE - 1) {
			count_ = STAGE_VALUE - 1;
		}

		//ステージ選択
		select_[count_].now = true;

		//一つ前に選択していた惑星を選択していない状態へ戻す
		select_[count_ - 1].size = defSize;
		select_[count_ - 1].now = false;
		//効果音再生
		lpSoundApp.PlayOnceSound("selectStage", true);
	}

	//惑星を選択
	if (select_[count_].now && !select_[count_].decision) {
		select_[count_].size = midSize;
	}
	else {
		//選択されていない
		//元の状態へ戻す
		select_[count_].size = defSize;
	}

}
