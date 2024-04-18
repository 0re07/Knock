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

//�f���̑傫��
const double defSize = 1.0;
const double midSize = 1.5;
const double maxSize = 4.5;

SelectStageScene::SelectStageScene(SceneManager& manager, Transitor& transit) :Scene(manager, transit)
{
	sceneTransitor_.Start();

	//������
	//Tutorial�Ƀt�H�[�J�X
	select_[0].now = true;
	select_[0].size = midSize;

	//�����ʒu�̐ݒ�
	for (int i = 0; i < STAGE_VALUE; ++i) {
		select_[i].pos = { 200 + (200 * i),screenSize_.y / 2 };
		select_[i].decision = false;
	}

	for (int i = 1; i < STAGE_VALUE; ++i) {
		//�I������Ă��邩
		select_[i].now = false;

		//�傫��
		select_[i].size = defSize;
	}

	//�摜�ǂݍ���
	//�w�i
	bgImg_ = LoadGraph("./Data/Image/backGround/Select.png");

	//�X�e�[�W�^�C�g��
	title_[0] = LoadGraph("./Data/Image/Planet/top_Tutorial.png");
	title_[1] = LoadGraph("./Data/Image/Planet/top_Stage1.png");
	title_[2] = LoadGraph("./Data/Image/Planet/top_Stage2.png");
	title_[3] = LoadGraph("./Data/Image/Planet/top_Stage3.png");
	
	//�f��
	LoadDivGraph("./Data/Image/Planet/Tutorial_s.png", 50, 50, 1, 100, 100, select_[0].planetImg, true);
	LoadDivGraph("./Data/Image/Planet/Stage1_s.png", 50, 50, 1, 200, 200, select_[1].planetImg, true);
	LoadDivGraph("./Data/Image/Planet/Stage2_s.png", 50, 50, 1, 200, 200, select_[2].planetImg, true);
	LoadDivGraph("./Data/Image/Planet/Stage3_s.png", 50, 50, 1, 150, 150, select_[3].planetImg, true);

	count_ = 0;

	change_ = 60;

	//���y
	lpSoundMng.GetSoundID("./Data/Sounds/Music/stageSelect.wav", "stageSelectScene");

	//���ʉ�
	lpSoundMng.GetSoundID("./Data/Sounds/Sound/SelectStage/Stage.mp3", "stage");
	lpSoundMng.GetSoundID("./Data/Sounds/Sound/SelectStage/StageSelect.mp3", "selectStage");
}

SelectStageScene::~SelectStageScene(void)
{
}

void SelectStageScene::Update(Input& input)
{
	cnt_++;

	//�X�e�[�W�I��
	Select(input);

	//SPACE�L�[�Ō���
 	if (input.IsTriggerd("next") || select_[count_].decision) {

		select_[count_].decision = true;

		//BGM�̒�~
		lpSoundApp.StopSound("stageSelectScene");

		//�X�e�[�W��ݒ�
		if (select_[count_].size == maxSize && change_ < 0) {
			//�V�[���J��
			sceneManager_.ChangeScene(std::make_shared<GameScene>(sceneManager_, sceneTransitor_, count_));
			return;
		}
	}

	//BGM�̍Đ�
	lpSoundApp.PlayLoopSound("stageSelectScene", false);

	sceneTransitor_.Update();
}

void SelectStageScene::Draw()
{
	ClearDrawScreen();

	//�w�i
	DrawGraph(0, 0, bgImg_, true);

	//�f��
	for (int i = 0; i < STAGE_VALUE; ++i) {
		if (!select_[i].decision) {
			//Stage1~4
			DrawRotaGraph(select_[i].pos.x, select_[i].pos.y, select_[i].size, 0.0, select_[i].planetImg[(cnt_ / 5) % 50], true);
		}
	}

	//�I�����ꂽ�f��
	if (select_[count_].decision) {
		DrawRotaGraph(screenSize_.x / 2, screenSize_.y / 2, select_[count_].size, 0.0, select_[count_].planetImg[(cnt_ / 5) % 50], true);
		DrawGraph(0, 0, title_[count_], true);
	}

	sceneTransitor_.Draw();
}

/// <summary>
/// �X�e�[�W�I��
/// </summary>
/// <param name="input">���͏��</param>
void SelectStageScene::Select(Input& input)
{

	//���肳�ꂽ��
	if (select_[count_].decision) {

		//���ʉ��Đ�
		lpSoundApp.PlayOnceSound("stage", false);

		--change_;
		if (select_[count_].size < maxSize) {
			select_[count_].size += 0.5;
		}
		return;
	}

	//���E�L�[�ŃX�e�[�W��I��
	if (input.IsTriggerd("left")) {
		count_--;
		//�͈͐���
		if (count_ < 0) {
			count_ = 0;
		}

		//�X�e�[�W�I��
		select_[count_].now = true;

		//��O�ɑI�����Ă����f����I�����Ă��Ȃ���Ԃ֖߂�
		select_[count_ + 1].size = defSize;
		select_[count_ + 1].now = false;

		//���ʉ��Đ�
		lpSoundApp.PlayOnceSound("selectStage", true);
	}
	if (input.IsTriggerd("right")) {
		count_++;
		//�͈͐���
		if (count_ > STAGE_VALUE - 1) {
			count_ = STAGE_VALUE - 1;
		}

		//�X�e�[�W�I��
		select_[count_].now = true;

		//��O�ɑI�����Ă����f����I�����Ă��Ȃ���Ԃ֖߂�
		select_[count_ - 1].size = defSize;
		select_[count_ - 1].now = false;
		//���ʉ��Đ�
		lpSoundApp.PlayOnceSound("selectStage", true);
	}

	//�f����I��
	if (select_[count_].now && !select_[count_].decision) {
		select_[count_].size = midSize;
	}
	else {
		//�I������Ă��Ȃ�
		//���̏�Ԃ֖߂�
		select_[count_].size = defSize;
	}

}
