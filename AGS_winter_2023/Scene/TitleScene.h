#pragma once
#include "Scene.h"

const int MODE_VALUE = 2;

struct SelectSceneInfo {
	//描画位置
	Vector2D pos;
	//現在選択されているか 
	//false:されていない true:されている
	bool now;
	//シーンタイトルの画像
	int sceneImg;
};

class TitleScene :
    public Scene
{
public:
	TitleScene(SceneManager& manager, Transitor& transit);
	~TitleScene(void);
	virtual void Update(Input& input)override;
	virtual void Draw() override;

private:
	void Select(Input& input);

	SelectSceneInfo selectMode_[MODE_VALUE];

	//選択されている表示
	int selectImg_;

	//選択されているシーンの番号
	int count_;

	//タイトルロゴ画像
	int titleImg_;

	//流星画像
	int starImg_[9];
};

