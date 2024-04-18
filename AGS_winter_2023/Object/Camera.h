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

	//À•Wæ“¾
	const Vector2D& GetPos(void)const { return pos_; }

private:
	//ó‘Ô‘JˆÚ
	void (Camera::* _phase)(Vector2D targetPos);
	void TargetPhase(Vector2D targetPos);
	void MoveUpDownPhase(Vector2D targetPos);

	//’Ç]‘ÎÛ
	Vector2D targetPos_;

	//ƒJƒƒ‰‚ÌÀ•W
	Vector2D pos_;

	//ˆÚ“®”ÍˆÍ
	RECT moveArea_;

};

