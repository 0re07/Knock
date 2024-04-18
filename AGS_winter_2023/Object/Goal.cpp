#include <DxLib.h>
#include "Goal.h"

Goal::Goal()
{
    for (int i = 0; i < 42; ++i) {
        goalImg_[i] = -1;
    }
}

Goal::~Goal()
{
}

void Goal::Init(void)
{
    cnt_ = 0;

    //�������W
    info_.pos = { 0,0 };
    info_.radius = 5.0f;

    //�摜�ǂݍ���
    LoadDivGraph("./Data/Image/Object/Goal.png", 42, 7, 6, 100, 100, goalImg_, true);
}

void Goal::Draw(void)
{
    //���g���ŋ����\����
    DrawRotaGraph(info_.pos.x, info_.pos.y, 2.5, 0.0, goalImg_[(cnt_ / 2) % 41], true);

    //�Փ˔���
    //DrawCircle(info_.pos.x-5, info_.pos.y-5, info_.radius, 0xff0000, false);
}

/// <summary>
/// �J�����Ǐ]������ꍇ�̕`��
/// </summary>
/// <param name="camOffset"></param>
void Goal::Draw(const Vector2D& camOffset)
{
    //���g���ŋ����\����
    DrawRotaGraph(
        info_.pos.x + camOffset.x, info_.pos.y + camOffset.y, 
        2.5, 0.0, goalImg_[(cnt_ / 2) % 41], true);
}

Circle Goal::GetObjInfo(void)
{
    return info_;
}

void Goal::SetPos(Vector2D pos)
{
    info_.pos = pos;
}

ObjType Goal::GetObjType(void)
{
    return ObjType::Goal;
}
