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

	//座標取得
	const Vector2D& GetPos(void)const { return pos_; }

private:
	//状態遷移
	void (Camera::* _phase)(Vector2D targetPos);
	void TargetPhase(Vector2D targetPos);
	void MoveUpDownPhase(Vector2D targetPos);

	//追従対象
	Vector2D targetPos_;

	//カメラの座標
	Vector2D pos_;

	//移動範囲
	RECT moveArea_;

};

