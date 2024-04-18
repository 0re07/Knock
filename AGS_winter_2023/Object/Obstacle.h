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

	//情報取得
	Circle GetObjInfo(void)override;

	//オブジェクトの種類の取得
	ObjType GetObjType(void)override;

	//座標情報格納
	void SetPos(Vector2D pos)override;


private:
	int img_;
};

