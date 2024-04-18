#pragma once
#include <map>
#include <DxLib.h>
#include "../common/Vector2D.h"
#include "ObjectType.h"

class Object
{
public:

	Object(void);
	~Object(void);

	virtual void Init(void);
	virtual void Update(void);
	virtual void Draw(void)=0;
	virtual void Draw(const Vector2D& camOffset)=0;

	//�Փ˔�����擾
	virtual Circle GetObjInfo(void) = 0;

	//�ʒu���̐ݒ�
	virtual void SetPos(Vector2D pos) = 0;

	//�I�u�W�F�N�g�̎�ނ̎擾
	virtual ObjType GetObjType(void) = 0;

protected:

	//�Փ˔���
	Circle info_;

	int cnt_;
};

