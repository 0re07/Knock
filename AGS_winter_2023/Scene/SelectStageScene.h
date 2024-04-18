#pragma once
#include <string>
#include "../common/Vector2D.h"
#include "Stage/StageManager.h"
#include "Scene.h"

const int STAGE_VALUE = 4;

struct SelectStageInfo {
	//描画位置
	Vector2D pos;
	//現在選択されているか 
	//false:されていない true:されている
	bool now;		
	//決定されたか
	bool decision;
	//惑星の画像
	int planetImg[50];
	//惑星の大きさ
	double size;
};

class SelectStageScene :
    public Scene
{
public:
	SelectStageScene(SceneManager& manager, Transitor& transit);
	~SelectStageScene(void);
	virtual void Update(Input& input)override;
	virtual void Draw() override;

private:
	//ステージ選択処理
	void Select(Input& input);

	StageManager stageManager_;

	//各惑星の情報統括
	SelectStageInfo select_[STAGE_VALUE];

	//ステージタイトル画像
	int title_[STAGE_VALUE];

	//選択されている惑星の番号
	int count_;

	//シーン遷移の余裕を持たせる
	int change_;
};

