#include <DxLib.h>
#include "../../Object/Object.h"
#include "StageTitleView.h"
#include "FirstStage.h"

FirstStage::FirstStage(StageManager& stageMng, Transitor& transit) :Stage(stageMng,transit)
{
	Init();
}

FirstStage::~FirstStage(void)
{
}

void FirstStage::Init(void)
{
	stageTransitor_.Start();

	//�}�b�v
 	tmxObj_->LoadTMX("./tmx/Stage_1.tmx");

	//�v���C���[
	player_ = std::make_unique<Player>(*tmxObj_);
	player_->Init();

	//�I�u�W�F�N�g���쐬����
	CreateObj(ObjType::Goal);
	CreateObj(ObjType::Obstacle);

	//���W�ݒ�
	player_->SetPosAngle({ 200.0 ,screenSize_.y - 150.0 }, 0.0f);

	for (auto& obj : objList_) {
		//�S�[��
		if (obj->GetObjType() == ObjType::Goal) {
			obj->SetPos({ screenSize_.x - 200, screenSize_.y - 200 });
		}
		//��Q��
		if (obj->GetObjType() == ObjType::Obstacle) {
			obj->SetPos({ screenSize_.x / 2, screenSize_.y / 2 - 200 });
		}
	}	

	//�摜�ǂݍ���
	bImg_ = LoadGraph("./Data/Image/backGround/background_1.png");
}

void FirstStage::Update(Input& input)
{
	player_->Update(input);

	for (auto& obj : objList_) {
		obj->Update();

		//�Փ˔���
		auto result = player_->IsHitObj(obj->GetObjInfo(), obj->GetObjType());

		//�S�[���ɏՓ˂��Ă���
		if (result.hit && result.type == ObjType::Goal) {
			//�V�[���J��
			if (--change_<0) {
				stageManager_.ChangeStage(std::make_shared<StageTitleView>(stageManager_, stageTransitor_, 2));
				return;
			}
		}
	}

	stageTransitor_.Update();
}

void FirstStage::Draw(void)
{
	ClearDrawScreen();

	auto bPos = player_->GetPos() / bgGap;
	//�w�i�`��
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
