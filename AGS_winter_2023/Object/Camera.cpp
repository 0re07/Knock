#include "Player.h"
#include "Camera.h"

Camera::Camera()
{
    moveArea_ = { 0,0,0,0 };
}

Camera::~Camera()
{
}

bool Camera::Init(const Vector2D& worldSize)
{
    //_phase = &Camera::TargetPhase;

    Vector2D winSize = { 1024,768 };
    GetWindowSize(&winSize.x, &winSize.y);    //�E�B���h�E�̑傫�����擾

    //Left,Top,Right,Bottom�̏��Ɋi�[
    moveArea_ = { winSize.x / 2,winSize.y / 2,
                   worldSize.x - winSize.x / 2,worldSize.y - winSize.y / 2 };

    pos_.x = moveArea_.left;
    pos_.y = moveArea_.bottom;

    return false;
}

void Camera::Update(void)
{
    if (targetPos_.x >= moveArea_.left && targetPos_.x <= moveArea_.right)
    {
        pos_.x = targetPos_.x;
    }
    if (targetPos_.y >= moveArea_.top && targetPos_.y >= moveArea_.bottom)
    {
        pos_.y = targetPos_.y;
    }
   // (this->*_phase)(targetPos);
}

void Camera::Recconect(Vector2D targetPos)
{
    targetPos_ = targetPos;
    pos_ = targetPos_;
}

/// <summary>
/// �v���C���[�𒆐S�Ƃ��ăJ�����ړ�
/// </summary>
/// <param name=""></param>
void Camera::TargetPhase(Vector2D targetPos)
{
    Vector2D view = { 1024, 768 };
    Vector2D offset;
    offset.x = view.x / 1.0f - targetPos.x;
    offset.y = view.y / 2.0f - targetPos.y;
    //offset.x = (view.x / 4.0f) * 2.0f - targetPos.x;
    //offset.y = (view.y / 2.0f) - targetPos.y;

    pos_ = offset;

    if (targetPos.y >= moveArea_.top && targetPos.y <= moveArea_.bottom)
    {
        _phase = &Camera::MoveUpDownPhase;
    }
}

/// <summary>
/// �v���C���[����ʊO�Ɉړ�������J�����ړ�
/// </summary>
/// <param name=""></param>
void Camera::MoveUpDownPhase(Vector2D targetPos)
{
    if (targetPos.x >= moveArea_.left && targetPos.x <= moveArea_.right)
    {
        pos_.x = targetPos.x;
    }
    if (targetPos.y >= moveArea_.top && targetPos.y <= moveArea_.bottom)
    {
        pos_.y = targetPos.y;
    }

    _phase = &Camera::TargetPhase;

}
