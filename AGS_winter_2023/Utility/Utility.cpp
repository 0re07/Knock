#include <math.h>
#include "../common/Vector2D.h"
#include "Utility.h"

/// <summary>
/// 座標から角度を求める
/// </summary>
/// <param name="pos">座標①　行った先</param>
/// <param name="oldPos">座標②　行った元</param>
/// <returns>角度（rad）</returns>
float Utility::GetAngle(Vector2DDouble pos, Vector2DDouble oldPos)
{
	auto v = pos - oldPos;
	//移動のない場合は角度計算もしない
	if (v.x == 0.0 || v.y == 0.0) {
		return 0.0f;
	}

	float rad = static_cast<float>(atan2(pos.y - oldPos.y, pos.x - oldPos.x));
	return rad;
}

/// <summary>
/// 
/// </summary>
/// <param name="t_x1"></param>
/// <param name="t_y1"></param>
/// <param name="t_x2"></param>
/// <param name="t_y2"></param>
/// <returns></returns>
float Utility::DistanceSqrf(const float t_x1, const float t_y1, const float t_x2, const float t_y2)
{
	float dx = t_x2 - t_x1;
	float dy = t_y2 - t_y1;

	return (dx * dx) + (dy * dy);
}

/// <summary>
/// 四角形と円の衝突判定
/// </summary>
/// <param name="box">四角形の座標</param>
/// <param name="boxSize">四角形の横/縦幅</param>
/// <param name="circle">円の中心座標</param>
/// <param name="radius">円の半径</param>
/// <returns>衝突:true 衝突していないならfalse</returns>
bool Utility::CheckHit(const VECTOR box, const VECTOR boxSize, const VECTOR circle, const int radius)
{
	bool hit = false;

	return hit;
}

void Utility::DrawHitBox(const VECTOR box, const VECTOR boxSize)
{
	auto l_top = box.x - boxSize.x;	//左上
	auto l_bottum = box.y - boxSize.y;	//左下
	auto r_top = box.x + boxSize.x;	//右上
	auto r_bottum = box.y + boxSize.y;	//右下

	//四角形
	DrawBox(
		static_cast<int>(l_top), 
		static_cast<int>(l_bottum), 
		static_cast<int>(r_top), 
		static_cast<int>(r_bottum), 
		0xffffff, false);
}

