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
/// �ŏ��i�`���[�g���A���X�e�[�W�j����
/// </summary>
/// <param name="manager">�V�[���̊Ǘ��N���X</param>
/// <param name="transit">�J�ڕ\���̊Ǘ��N���X</param>
GameScene::GameScene(SceneManager& manager, Transitor& transit) :Scene(manager, transit)
{
	//�f�o�b�O
	//stageManager_.ChangeStage(std::make_shared<SecondStage>(stageManager_, transitor_));
	//stageManager_.ChangeStage(std::make_shared<ThirdStage>(stageManager_, transitor_));

	//�����X�e�[�W�̐ݒ�
	//�`���[�g���A���X�e�[�W:0
	stageManager_.ChangeStage(std::make_shared<StageTitleView>(stageManager_, transit,0));
	stageManager_.Init();
}

/// <summary>
/// �I�����ꂽ�X�e�[�W
/// </summary>
/// <param name="manager">�V�[���̊Ǘ��N���X</param>
/// <param name="transit">�J�ڕ\���̊Ǘ��N���X</param>
/// <param name="stageNum">�I�����ꂽ�X�e�[�W�̔ԍ�</param>
GameScene::GameScene(SceneManager& manager, Transitor& transit, int stageNum) :Scene(manager, transit)
{
	sceneTransitor_.Start();

	//�I�����ꂽ�X�e�[�W�̐ݒ�
	stageManager_.ChangeStage(std::make_shared<StageTitleView>(stageManager_, transit, stageNum));
	stageManager_.Init();
}

GameScene::~GameScene(void)
{
}

void GameScene::Update(Input& input)
{

	//�|�[�Y���j���[
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
