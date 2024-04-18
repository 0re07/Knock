#pragma once
#include "Object.h"

class Goal :public Object
{
public:
	Goal();
	~Goal();
	void Init(void)override;
	void Draw(void)override;
	//�J�����Ǐ]������ꍇ�̕`��
	void Draw(const Vector2D& camOffset)override;

	//���W���i�[
	void SetPos(Vector2D pos)override;

	//���擾
	Circle GetObjInfo(void)override;

	//�I�u�W�F�N�g�̎�ނ̎擾
	ObjType GetObjType(void)override;

private:
	int goalImg_[42];
};

