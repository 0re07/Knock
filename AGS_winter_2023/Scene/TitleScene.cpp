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

	//������
	for (int i = 0; i < MODE_VALUE; ++i) {
		selectMode_[i].pos = { 0,0 };
	}
	selectMode_[0].now = true;
	selectMode_[1].now = false;

	//�摜
	//�V�[���^�C�g��
	selectMode_[0].sceneImg = LoadGraph("./Data/Image/Title/gameStart.png");
	selectMode_[1].sceneImg = LoadGraph("./Data/Image/Title/selectStage.png");

	//�I��
	selectImg_ = LoadGraph("./Data/Image/Title/select.png");

	//����
	LoadDivGraph("./Data/Image/Title/star.png", 9, 9, 1, 128, 128, starImg_);

	//�^�C�g�����S
	titleImg_ = LoadGraph("./Data/Image/Title/title.png");

	//�w�i
	bgImg_ = LoadGraph("./Data/Image/backGround/Select.png");

	count_ = 0;

	//���y
	lpSoundMng.GetSoundID("./Data/Sounds/Music/title.wav", "title");
	//���ʉ�
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

	//���[�h�I��
	Select(input);

	//�V�[���J�ڐ挈��
	if (input.IsTriggerd("next")) {

		//������ʉ�
		lpSoundApp.PlayOnceSound("mode", false);

		//BGM�̍Đ��X�g�b�v
		lpSoundApp.StopSound("title");

		//���[�h�I��
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

	//BGM���[�v�Đ�
	lpSoundApp.PlayLoopSound("title", false);

	ui_.Update();

	sceneTransitor_.Update();

}

void TitleScene::Draw()
{
	ClearDrawScreen();

	//�w�i
	DrawGraph(0, 0, bgImg_, true);

	//����
	DrawRotaGraph(200, 200, 1.5, 0.0, starImg_[(cnt_ / 5) % 10], true);
	DrawRotaGraph(600, 500, 1.5, 0.0, starImg_[(cnt_ / 3) % 20], true);

	//�^�C�g�����S
	DrawGraph(0, 0, titleImg_, true);

		//�I������Ă���V�[���^�C�g���������\��
	if (selectMode_[count_].now) {
		DrawGraph(selectMode_[count_].pos.x, selectMode_[count_].pos.y + 130 * count_, selectImg_, true);
	}

	//�V�[���^�C�g��
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
	//���E�L�[�ŃX�e�[�W��I��
	if (input.IsTriggerd("up")) {
		count_--;
		//�͈͐���
		if (count_ < 0) {
			count_ = 0;
		}

		//�X�e�[�W�I��
		selectMode_[count_].now = true;

		//��O�ɑI�����Ă����V�[����I�����Ă��Ȃ���Ԃ֖߂�
		selectMode_[count_ + 1].now = false;

		//���ʉ��Đ�
		lpSoundApp.PlayOnceSound("selectMode", true);
	}
	if (input.IsTriggerd("down")) {
		count_++;
		//�͈͐���
		if (count_ > MODE_VALUE - 1) {
			count_ = MODE_VALUE - 1;
		}

		//�X�e�[�W�I��
		selectMode_[count_].now = true;

		//��O�ɑI�����Ă����V�[����I�����Ă��Ȃ���Ԃ֖߂�
		selectMode_[count_ - 1].now = false;

		//���ʉ��Đ�
		lpSoundApp.PlayOnceSound("selectMode", true);
	}
}
