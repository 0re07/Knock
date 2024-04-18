#pragma once
#include "Object.h"

class Goal :public Object
{
public:
	Goal();
	~Goal();
	void Init(void)override;
	void Draw(void)override;
	//カメラ追従がある場合の描画
	void Draw(const Vector2D& camOffset)override;

	//座標情報格納
	void SetPos(Vector2D pos)override;

	//情報取得
	Circle GetObjInfo(void)override;

	//オブジェクトの種類の取得
	ObjType GetObjType(void)override;

private:
	int goalImg_[42];
};

