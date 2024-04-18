#pragma once
#include "Object.h"

class Obstacle :public Object
{
public:
	Obstacle(void);
	~Obstacle(void);

	void Init(void)override;
	void Draw(void)override;
	void Draw(const Vector2D& camOffset)override;

	//���擾
	Circle GetObjInfo(void)override;

	//�I�u�W�F�N�g�̎�ނ̎擾
	ObjType GetObjType(void)override;

	//���W���i�[
	void SetPos(Vector2D pos)override;


private:
	int img_;
};

