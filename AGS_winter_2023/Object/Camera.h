#pragma once
#include<memory>
#include<Dxlib.h>
#include"../common/Vector2D.h"

class Player;

class Camera
{
public:
	Camera();
	~Camera();
	bool Init(const Vector2D& worldSize);
	void Update(void);
	void Recconect(Vector2D targetPos);

	//���W�擾
	const Vector2D& GetPos(void)const { return pos_; }

private:
	//��ԑJ��
	void (Camera::* _phase)(Vector2D targetPos);
	void TargetPhase(Vector2D targetPos);
	void MoveUpDownPhase(Vector2D targetPos);

	//�Ǐ]�Ώ�
	Vector2D targetPos_;

	//�J�����̍��W
	Vector2D pos_;

	//�ړ��͈�
	RECT moveArea_;

};

