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

	//���W����p�x�����߂�
	float GetAngle(Vector2DDouble pos, Vector2DDouble oldPos);

	//
	float DistanceSqrf(const float t_x1, const float t_y1, const float t_x2, const float t_y2);

	//�l�p�`�Ɖ~�̏Փ˔���
	bool CheckHit(const VECTOR box, const VECTOR boxSize, const VECTOR circle, const int radius);

	//�Փ˔���p�l�p�`�`��
	void DrawHitBox(const VECTOR box, const VECTOR boxSize);
};

