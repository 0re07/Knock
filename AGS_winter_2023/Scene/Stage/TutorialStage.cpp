#include "../../Object/Object.h"
#include "StageTitleView.h"
#include "TutorialStage.h"

TutorialStage::TutorialStage(StageManager& stageMng, Transitor& transit):Stage(stageMng,transit)
{
	Init();
}

TutorialStage::~TutorialStage(void)
{
}

void TutorialStage::Init(void)
{
	stageTransitor_.Start();

	//�}�b�v
	tmxObj_->LoadTMX("./tmx/Tutorial.tmx");

	//�v���C���[
	player_ = std::make_unique<Player>(*tmxObj_);
	player_->Init();

	//�S�[��
	CreateObj(ObjType::Goal);

	//���W�ݒ�
	player_->SetPosAngle({ 200.0,screenSize_.y - 150.0 },19.8f);
	
	for (auto& obj : objList_) {
		//�S�[��
		if (obj->GetObjType() == ObjType::Goal) {
			obj->SetPos({ screenSize_.x - 200, 200 });
		}
	}

	//�摜�ǂݍ���
	bImg_ = LoadGraph("./Data/Image/backGround/background_0.png");

}

void TutorialStage::Update(Input& input)
{
	player_->Update(input);

	//�Փ˔���
	for (auto& obj : objList_) {
		obj->Update();

		//�Փ˔���
		auto result = player_->IsHitObj(obj->GetObjInfo(), obj->GetObjType());

		//�Փ˂��Ă���
		if (result.hit) {
			//�S�[��
			if (result.type == ObjType::Goal) {

				//�V�[���J��
				if (--change_ < 0) {
					stageManager_.ChangeStage(std::make_shared<StageTitleView>(stageManager_, stageTransitor_, 1));
					return;
				}
			}
		}
	}

	stageTransitor_.Update();
}

void TutorialStage::Draw(void)
{
	ClearDrawScreen();

	auto bPos = player_->GetPos() / bgGap;
	//�w�i�`��
	//DrawGraph(0, 0, bImg_, true);
	DrawGraph(bPos.x, bPos.y, bImg_, true);

	//�}�b�v
	const auto& worldArea = tmxObj_->GetWorldArea();
	const auto& tileSize = tmxObj_->GetTileSize();

	for (const auto& layer : tmxObj_->GetMapData())		//���ꂼ��̃��C���[���I���܂�
	{
		for (int y = 0; y < worldArea.y; y++)
		{
			for (int x = 0; x < worldArea.x; x++)
			{
				if (x + y * worldArea.x < layer.second.size())		//�͈̓`�F�b�N
				{
					auto gid = layer.second[x + y * worldArea.x];
					if (gid >= 0)
					{
						DrawGraph(
							x * tileSize.x,
							y * tileSize.y,
							lpImageMng.GetID(tmxObj_->GetMapKey())[gid],
							true);
					}
				}
			}
		}
	}

	for (auto& obj : objList_) {
		obj->Draw();
	}

	player_->Draw();

	stageTransitor_.Draw();
}
