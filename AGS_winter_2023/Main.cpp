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
	//�E�B���h�E�^�u�ɔC�ӂ̖��O������
	SetWindowText("Knock! Knock! Capten! That's Awful!");

	//��ʃT�C�Y��ݒ�
	SetGraphMode(ScreenSizeX, ScreenSizeY, 32);

	ChangeWindowMode(true);
	if (DxLib_Init() == -1) {
		return -1;
	}

	SetDrawScreen(DX_SCREEN_BACK);

	IrisTransitor irisTransitor;
	PushTransitor pushTransitor;

	SceneManager sceneManager;

	//�����ݒ�
	sceneManager.ChangeScene(make_shared<TitleScene>(sceneManager, irisTransitor));
	//�f�o�b�O
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