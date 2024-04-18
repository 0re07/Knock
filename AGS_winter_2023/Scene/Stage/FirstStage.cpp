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

	//マップ
 	tmxObj_->LoadTMX("./tmx/Stage_1.tmx");

	//プレイヤー
	player_ = std::make_unique<Player>(*tmxObj_);
	player_->Init();

	//オブジェクトを作成する
	CreateObj(ObjType::Goal);
	CreateObj(ObjType::Obstacle);

	//座標設定
	player_->SetPosAngle({ 200.0 ,screenSize_.y - 150.0 }, 0.0f);

	for (auto& obj : objList_) {
		//ゴール
		if (obj->GetObjType() == ObjType::Goal) {
			obj->SetPos({ screenSize_.x - 200, screenSize_.y - 200 });
		}
		//障害物
		if (obj->GetObjType() == ObjType::Obstacle) {
			obj->SetPos({ screenSize_.x / 2, screenSize_.y / 2 - 200 });
		}
	}	

	//画像読み込み
	bImg_ = LoadGraph("./Data/Image/backGround/background_1.png");
}

void FirstStage::Update(Input& input)
{
	player_->Update(input);

	for (auto& obj : objList_) {
		obj->Update();

		//衝突判定
		auto result = player_->IsHitObj(obj->GetObjInfo(), obj->GetObjType());

		//ゴールに衝突している
		if (result.hit && result.type == ObjType::Goal) {
			//シーン遷移
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
	//背景描画
	DrawGraph(bPos.x, bPos.y, bImg_, true);

	//マップ
	const auto& worldArea = tmxObj_->GetWorldArea();
	const auto& tileSize = tmxObj_->GetTileSize();

	for (const auto& layer : tmxObj_->GetMapData())		//それぞれのレイヤーが終わるまで
	{
		for (int y = 0; y < worldArea.y; y++)
		{
			for (int x = 0; x < worldArea.x; x++)
			{
				if (x + y * worldArea.x < layer.second.size())		//範囲チェック
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
