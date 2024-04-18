#pragma once
#include "Scene.h"
#include<functional>
#include"../Input/KeyConfigScene.h"

class PauseScene :
    public Scene
{
private:
	using UpfdateFunc_t = void (PauseScene::*)(Input& input);
	
	//Update�֐��Ŏ��s�����֐����w�������|�C���^
	UpfdateFunc_t upfdateFunc_;

	void BeginUpdate(Input& input);//pause�\���܂ł̍X�V
	void NormalUpdate(Input& input);//�ʏ�X�V
	void EndUpdate(Input& input);//pause�����̍X�V

	using DrawFunc_t = void(PauseScene::*)();
	DrawFunc_t drawFunc_;

	void BeginDraw();//pause�\���܂ł̕`��
	void NormalDraw();//�ʏ�`��
	void EndDraw();//pause�����`��
	std::list< std::function<void(void)>> commandList_;

	float frame_ = 0;
public:
	PauseScene(SceneManager& manager, Transitor& transit);
	~PauseScene(void);

	virtual void Update(Input& input)override;
	virtual void Draw()override;

};

