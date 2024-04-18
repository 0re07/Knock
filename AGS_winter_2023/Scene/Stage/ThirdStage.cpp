#include <DxLib.h>
#include "../../Object/Goal.h"
#include "StageTitleView.h"
#include "ThirdStage.h"

ThirdStage::ThirdStage(StageManager& stageMng, Transitor& transit) :Stage(stageMng, transit)
{
	Init();
}

ThirdStage::~ThirdStage(void)
{
}

void ThirdStage::Init(void)
{
	stageTransitor_.Start();

	//�}�b�v
	tmxObj_->LoadTMX("./tmx/Stage_3.tmx");

	//�v���C���[
	player_ = std::make_unique<Player>(*tmxObj_);
	player_->Init();

	//�S�[��
	CreateObj(ObjType::Goal);

	//���W�ݒ�
	player_->SetPosAngle({ 200.0 ,150.0 }, 89.5f);

	for (auto& obj : objList_) {
		//�S�[��
		if (obj->GetObjType() == ObjType::Goal) {
			obj->SetPos({ 200 ,screenSize_.y - 150 });
		}
	}

	//�摜�ǂݍ���
	bImg_ = LoadGraph("./Data/Image/backGround/background_3.png");

	asteroidBelt_ = LoadGraph("./Data/Image/asteroid belt/asteroid belt.png");
	asteroid_[0] = LoadGraph("./Data/Image/asteroid belt/asteroid_1.png");
	asteroid_[1] = LoadGraph("./Data/Image/asteroid belt/asteroid_2.png");
	asteroid_[2] = LoadGraph("./Data/Image/asteroid belt/asteroid_3.png");
	asteroid_[3] = LoadGraph("./Data/Image/asteroid belt/asteroid_4.png");

	cnt_ = 0;
}

void ThirdStage::Update(Input& input)
{
	cnt_++;

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
					stageManager_.ChangeStage(std::make_shared<StageTitleView>(stageManager_, stageTransitor_,0));
					return;
				}
			}
		}
	}

	stageTransitor_.Update();
}

void ThirdStage::Draw(void)
{
	ClearDrawScreen();

	auto bPos = player_->GetPos() / bgGap;

	//�w�i�`��
	DrawGraph(bPos.x, bPos.y, bImg_, true);

	//���f����
	DrawRotaGraph(560, 135, 1.7f, 0.0, asteroidBelt_, true);
	DrawRotaGraph(560, 620, 1.7f, 180.0, asteroidBelt_, true);

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

	//���f��
	DrawAsteroid();

	//��Q���ƃS�[��
	for (auto& obj : objList_) {
		obj->Draw();
	}

	//�v���C���[
	player_->Draw();

	stageTransitor_.Draw();
}

void ThirdStage::DrawAsteroid(void)
{
	//��
	DrawRotaGraph(540, 100, 1.0f, (cnt_ / 20) % 10, asteroid_[0], true);
	DrawRotaGraph(500, 165, 1.0f, (cnt_ / 20) % 5, asteroid_[1], true);
	DrawRotaGraph(580, 200, 1.0f, (cnt_ / 20) % 2, asteroid_[2], true);
	DrawRotaGraph(620, 80, 1.0f, (cnt_ / 20) % 2, asteroid_[2], true);
	DrawRotaGraph(600, 140, 1.0f, (cnt_ / 20) % 3, asteroid_[3], true);

	//��
	DrawRotaGraph(600, 600, 1.0f, (cnt_ / 20) % 8, asteroid_[0], true);
	DrawRotaGraph(560, 660, 1.0f, (cnt_ / 20) % 5, asteroid_[1], true);
	DrawRotaGraph(560, 560, 1.0f, (cnt_ / 20) % 2, asteroid_[2], true);
	DrawRotaGraph(520, 590, 1.0f, (cnt_ / 20) % 3, asteroid_[3], true);

}
