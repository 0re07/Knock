#include "../common/Vector2D.h"
#include "Obstacle.h"

const int radius = 32;

Obstacle::Obstacle(void)
{
	img_ = -1;
}

Obstacle::~Obstacle(void)
{
}

void Obstacle::Init(void)
{
	//初期位置：左上
	info_.pos = { 0,0 };
	info_.radius = 30.0f;

	//画像読み込み
	img_ = LoadGraph("Data/Image/Object/Obstacle.png");
}

void Obstacle::Draw(void)
{
	//白枠線で強調表示※
	DrawRotaGraph(info_.pos.x, info_.pos.y, 2.8, (cnt_ / 10) % 50, img_, true);

	//障害物の衝突判定
	//DrawCircle(info_.pos.x-5, info_.pos.y-5, info_.radius, 0xffff00, false);
}

void Obstacle::Draw(const Vector2D& camOffset)
{
	//白枠線で強調表示※
	DrawRotaGraph(info_.pos.x + camOffset.x, info_.pos.y + camOffset.y, 2.8, (cnt_ / 10) % 50, img_, true);
}

Circle Obstacle::GetObjInfo(void)
{
	return info_;
}

void Obstacle::SetPos(Vector2D pos)
{
	info_.pos = pos;
}

ObjType Obstacle::GetObjType(void)
{
	return ObjType::Obstacle;
}
