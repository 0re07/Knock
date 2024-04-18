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

	//衝突判定情報取得
	virtual Circle GetObjInfo(void) = 0;

	//位置情報の設定
	virtual void SetPos(Vector2D pos) = 0;

	//オブジェクトの種類の取得
	virtual ObjType GetObjType(void) = 0;

protected:

	//衝突判定
	Circle info_;

	int cnt_;
};

