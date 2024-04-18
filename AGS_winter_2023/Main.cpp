#include<DxLib.h>
#include "Scene/Transition/PushTransitor.h"
#include "Scene/Transition/IrisTransitor.h"
#include "Scene/SceneManager.h"
#include "Scene/TitleScene.h"
#include "Scene/GameScene.h"
#include "Scene/SelectStageScene.h"
#include "Input.h"
using namespace std;

constexpr int ScreenSizeX = 1024;
constexpr int ScreenSizeY = 768;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//ウィンドウタブに任意の名前をつける
	SetWindowText("Knock! Knock! Capten! That's Awful!");

	//画面サイズを設定
	SetGraphMode(ScreenSizeX, ScreenSizeY, 32);

	ChangeWindowMode(true);
	if (DxLib_Init() == -1) {
		return -1;
	}

	SetDrawScreen(DX_SCREEN_BACK);

	IrisTransitor irisTransitor;
	PushTransitor pushTransitor;

	SceneManager sceneManager;

	//初期設定
	sceneManager.ChangeScene(make_shared<TitleScene>(sceneManager, irisTransitor));
	//デバッグ
	//sceneManager.ChangeScene(make_shared<GameScene>(sceneManager, irisTransitor));
	//sceneManager.ChangeScene(make_shared<SelectStageScene>(sceneManager, irisTransitor));

	Input input;

	while (ProcessMessage() != -1)
	{	
		input.Update();
		sceneManager.Update(input);
		sceneManager.Draw();
		ScreenFlip();
	}
	DxLib_End();
	return 0;
}