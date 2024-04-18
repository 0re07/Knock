#pragma once
#include "Scene.h"
#include<functional>
#include"../Input/KeyConfigScene.h"

class PauseScene :
    public Scene
{
private:
	using UpfdateFunc_t = void (PauseScene::*)(Input& input);
	
	//Update関数で実行される関数を指し示すポインタ
	UpfdateFunc_t upfdateFunc_;

	void BeginUpdate(Input& input);//pause表示までの更新
	void NormalUpdate(Input& input);//通常更新
	void EndUpdate(Input& input);//pause解除の更新

	using DrawFunc_t = void(PauseScene::*)();
	DrawFunc_t drawFunc_;

	void BeginDraw();//pause表示までの描画
	void NormalDraw();//通常描画
	void EndDraw();//pause解除描画
	std::list< std::function<void(void)>> commandList_;

	float frame_ = 0;
public:
	PauseScene(SceneManager& manager, Transitor& transit);
	~PauseScene(void);

	virtual void Update(Input& input)override;
	virtual void Draw()override;

};

