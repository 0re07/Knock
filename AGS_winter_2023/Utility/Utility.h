#pragma once
#include <DxLib.h>
#include "../common/Vector2D.h"

class Utility
{
public:
	static Utility& GetInstance(void)
	{
		static Utility u_Instance;
		return u_Instance;
	}

	//座標から角度を求める
	float GetAngle(Vector2DDouble pos, Vector2DDouble oldPos);

	//
	float DistanceSqrf(const float t_x1, const float t_y1, const float t_x2, const float t_y2);

	//四角形と円の衝突判定
	bool CheckHit(const VECTOR box, const VECTOR boxSize, const VECTOR circle, const int radius);

	//衝突判定用四角形描画
	void DrawHitBox(const VECTOR box, const VECTOR boxSize);
};

