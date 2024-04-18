#pragma once
#include "Scene.h"

const int MAX_PAGE = 2;

struct OparationInfo {
	//現在選択されているか 
	//false:されていない true:されている
	bool now;
	//シーンタイトルの画像
	int oparatImg;
};


class OparationScene :
    public Scene
{
public:
	OparationScene(SceneManager& manager, Transitor& transit);
	~OparationScene(void);
	virtual void Update(Input& input)override;
	virtual void Draw() override;


private:
	void Select(Input& input);

	int count_;

	OparationInfo info_[MAX_PAGE];

	//プレイヤー描画位置
	Vector2D pPos_;
	int vel_;
	double pAngle_;

	int playerImg_;

	int opImg_;
};

