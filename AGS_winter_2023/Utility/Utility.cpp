#include <math.h>
#include "../common/Vector2D.h"
#include "Utility.h"

/// <summary>
/// ���W����p�x�����߂�
/// </summary>
/// <param name="pos">���W�@�@�s������</param>
/// <param name="oldPos">���W�A�@�s������</param>
/// <returns>�p�x�irad�j</returns>
float Utility::GetAngle(Vector2DDouble pos, Vector2DDouble oldPos)
{
	auto v = pos - oldPos;
	//�ړ��̂Ȃ��ꍇ�͊p�x�v�Z�����Ȃ�
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
/// �l�p�`�Ɖ~�̏Փ˔���
/// </summary>
/// <param name="box">�l�p�`�̍��W</param>
/// <param name="boxSize">�l�p�`�̉�/�c��</param>
/// <param name="circle">�~�̒��S���W</param>
/// <param name="radius">�~�̔��a</param>
/// <returns>�Փ�:true �Փ˂��Ă��Ȃ��Ȃ�false</returns>
bool Utility::CheckHit(const VECTOR box, const VECTOR boxSize, const VECTOR circle, const int radius)
{
	bool hit = false;

	return hit;
}

void Utility::DrawHitBox(const VECTOR box, const VECTOR boxSize)
{
	auto l_top = box.x - boxSize.x;	//����
	auto l_bottum = box.y - boxSize.y;	//����
	auto r_top = box.x + boxSize.x;	//�E��
	auto r_bottum = box.y + boxSize.y;	//�E��

	//�l�p�`
	DrawBox(
		static_cast<int>(l_top), 
		static_cast<int>(l_bottum), 
		static_cast<int>(r_top), 
		static_cast<int>(r_bottum), 
		0xffffff, false);
}

