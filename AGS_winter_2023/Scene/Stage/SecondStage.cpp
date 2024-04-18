#include "../../Object/Camera.h"
#include "../../Object/Object.h"
#include "StageTitleView.h"
#include "SecondStage.h"

const Vector2D DrawOffSet = { 512 ,384 };

SecondStage::SecondStage(StageManager& stageMng, Transitor& transit):Stage(stageMng,transit)
{
	Init();
}

SecondStage::~SecondStage(void)
{
}

void SecondStage::Init(void)
{
	stageTransitor_.Start();

	//マップ
	tmxObj_->LoadTMX("./tmx/Stage_2.tmx");

	//プレイヤー
	player_ = std::make_unique<Player>(*tmxObj_);
	player_->Init();

	//追従カメラ
	camera_ = std::make_unique<Camera>();
	//カメラを初期化
	camera_->Init(tmxObj_->GetWorldArea() * tmxObj_->GetTileSize());

	//オブジェクトを作成する
	CreateObj(ObjType::Goal);
	CreateObj(ObjType::Obstacle);

	//座標設定
	player_->SetPosAngle({ screenSize_.x - 250.0 + DrawOffSet.x , screenSize_.y * 2 - 180.0 + DrawOffSet.y }, 180.6f);

	for (auto& obj : objList_) {
		//ゴール
		if (obj->GetObjType() == ObjType::Goal) {
			obj->SetPos({ 200 + DrawOffSet.x, screenSize_.y / 2 - 200 + DrawOffSet.y });
		}
		//障害物
		if (obj->GetObjType() == ObjType::Obstacle) {
			obj->SetPos({ screenSize_.x  - 200 + DrawOffSet.x, 200 + DrawOffSet.y });
		}
	}

	//画像読み込み
	bImg_ = LoadGraph("./Data/Image/backGround/background_2.png");
}

void SecondStage::Update(Input& input)
{
	player_->Update(input);

	for (auto& obj : objList_) {
		obj->Update();

		//衝突判定
		auto result = player_->IsHitObj(obj->GetObjInfo(), obj->GetObjType());

		//衝突している
		if (result.hit) {
			//ゴール
			if (result.type == ObjType::Goal) {
				//ステージ遷移
				if (--change_ < 0) {
					stageManager_.ChangeStage(std::make_shared<StageTitleView>(stageManager_, stageTransitor_,3));
					return;
				}
			}
		}
	}

	//カメラを再接続する
	camera_->Recconect(player_->GetPos());

	camera_->Update();

	stageTransitor_.Update();
}

void SecondStage::Draw(void)
{
	ClearDrawScreen();

	auto bPos = player_->GetPos() / (bgGap - 30);
	//背景描画
	DrawGraph(bPos.x, bPos.y, bImg_, true);

	auto cameraOffset = (screenSize_ / 2) - camera_->GetPos();

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
							x * tileSize.x + cameraOffset.x,
							y * tileSize.y + cameraOffset.y,
							lpImageMng.GetID(tmxObj_->GetMapKey())[gid],
							true);
					}
				}
			}
		}
	}

	for (auto& obj : objList_) {
		obj->Draw(cameraOffset);
	}

	player_->Draw(cameraOffset);

	stageTransitor_.Draw();
}
