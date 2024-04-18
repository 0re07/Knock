#include<DxLib.h>
#include "../Manager/Sound/SoundMng.h"
#include "../Manager/Sound/SoundApp.h"
#include "../Input.h"
#include "../Input/KeyConfigScene.h"
#include "../Input/StringUtility.h"
#include "Transition/Transitor.h"
#include "SceneManager.h"
#include "SelectStageScene.h"
#include "OparationScene.h"
#include "TitleScene.h"

TitleScene::TitleScene(SceneManager& manager, Transitor& transit) :Scene(manager, transit)
{
	sceneTransitor_.Start();

	//初期化
	for (int i = 0; i < MODE_VALUE; ++i) {
		selectMode_[i].pos = { 0,0 };
	}
	selectMode_[0].now = true;
	selectMode_[1].now = false;

	//画像
	//シーンタイトル
	selectMode_[0].sceneImg = LoadGraph("./Data/Image/Title/gameStart.png");
	selectMode_[1].sceneImg = LoadGraph("./Data/Image/Title/selectStage.png");

	//選択
	selectImg_ = LoadGraph("./Data/Image/Title/select.png");

	//流星
	LoadDivGraph("./Data/Image/Title/star.png", 9, 9, 1, 128, 128, starImg_);

	//タイトルロゴ
	titleImg_ = LoadGraph("./Data/Image/Title/title.png");

	//背景
	bgImg_ = LoadGraph("./Data/Image/backGround/Select.png");

	count_ = 0;

	//音楽
	lpSoundMng.GetSoundID("./Data/Sounds/Music/title.wav", "title");
	//効果音
	lpSoundMng.GetSoundID("./Data/Sounds/Sound/Title/Mode.mp3", "mode");
	lpSoundMng.GetSoundID("./Data/Sounds/Sound/Title/ModeSelect.mp3", "selectMode");

	ui_.Init();

}

TitleScene::~TitleScene(void)
{
}

void TitleScene::Update(Input& input)
{
	cnt_++;

	//モード選択
	Select(input);

	//シーン遷移先決定
	if (input.IsTriggerd("next")) {

		//決定効果音
		lpSoundApp.PlayOnceSound("mode", false);

		//BGMの再生ストップ
		lpSoundApp.StopSound("title");

		//モード選択
		switch (count_)
		{
		default:
			sceneManager_.ChangeScene(std::make_shared<OparationScene>(sceneManager_, sceneTransitor_));
			return;
		case 0:
			sceneManager_.ChangeScene(std::make_shared<OparationScene>(sceneManager_, sceneTransitor_));
			return;
		case 1:
			sceneManager_.ChangeScene(std::make_shared<SelectStageScene>(sceneManager_, sceneTransitor_));
			return;
		}
	}

	//BGMループ再生
	lpSoundApp.PlayLoopSound("title", false);

	ui_.Update();

	sceneTransitor_.Update();

}

void TitleScene::Draw()
{
	ClearDrawScreen();

	//背景
	DrawGraph(0, 0, bgImg_, true);

	//流星
	DrawRotaGraph(200, 200, 1.5, 0.0, starImg_[(cnt_ / 5) % 10], true);
	DrawRotaGraph(600, 500, 1.5, 0.0, starImg_[(cnt_ / 3) % 20], true);

	//タイトルロゴ
	DrawGraph(0, 0, titleImg_, true);

		//選択されているシーンタイトルを強調表示
	if (selectMode_[count_].now) {
		DrawGraph(selectMode_[count_].pos.x, selectMode_[count_].pos.y + 130 * count_, selectImg_, true);
	}

	//シーンタイトル
	for (int i = 0; i < MODE_VALUE; ++i) {
		DrawGraph(selectMode_[i].pos.x, selectMode_[i].pos.y, selectMode_[i].sceneImg, true);
	}

	ui_.Draw({ screenSize_.x - 50,screenSize_.y - 100 }, 2.0, UIVALUE::UP);
	ui_.Draw({ screenSize_.x - 50,screenSize_.y - 80 }, 2.0, UIVALUE::DOWN);
	ui_.Draw({ screenSize_.x - 50,screenSize_.y - 30 }, 1.2, UIVALUE::ENTER);

	sceneTransitor_.Draw();
}

void TitleScene::Select(Input& input)
{
	//左右キーでステージを選択
	if (input.IsTriggerd("up")) {
		count_--;
		//範囲制限
		if (count_ < 0) {
			count_ = 0;
		}

		//ステージ選択
		selectMode_[count_].now = true;

		//一つ前に選択していたシーンを選択していない状態へ戻す
		selectMode_[count_ + 1].now = false;

		//効果音再生
		lpSoundApp.PlayOnceSound("selectMode", true);
	}
	if (input.IsTriggerd("down")) {
		count_++;
		//範囲制限
		if (count_ > MODE_VALUE - 1) {
			count_ = MODE_VALUE - 1;
		}

		//ステージ選択
		selectMode_[count_].now = true;

		//一つ前に選択していたシーンを選択していない状態へ戻す
		selectMode_[count_ - 1].now = false;

		//効果音再生
		lpSoundApp.PlayOnceSound("selectMode", true);
	}
}
