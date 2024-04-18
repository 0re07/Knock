#include<DxLib.h>
#include "../Input.h"
#include "../Input/KeyConfigScene.h"
#include "SceneManager.h"
#include "PauseScene.h"

constexpr int change_interval =30;
constexpr int pause_width = 400; 
constexpr int pause_height = 300; 

PauseScene::PauseScene(SceneManager& manager, Transitor& transit) :Scene(manager,transit)
{
	upfdateFunc_ = &PauseScene::BeginUpdate;
	drawFunc_ = &PauseScene::BeginDraw;
}

PauseScene::~PauseScene(void)
{
}

void PauseScene::Update(Input& input)
{
	(this->*upfdateFunc_)(input);
}

void PauseScene::Draw()
{
	//関数ポインタを呼び出している
	(this->*drawFunc_)();
		
}

void PauseScene::BeginUpdate(Input& input)
{

	if (++frame_ >= change_interval)
	{
		upfdateFunc_ = &PauseScene::NormalUpdate;
		drawFunc_ = &PauseScene::NormalDraw;
		commandList_.push_back([]() {
			DrawString(100, 100, "Change to Normal", 0xffffff);
			});
	}
}

void PauseScene::NormalUpdate(Input& input)
{
	if (input.IsTriggerd("pause"))
	{
		upfdateFunc_ = &PauseScene::EndUpdate;
		drawFunc_ = &PauseScene::EndDraw;
		frame_ = 0;
	}
	else if (input.IsTriggerd("keyconfig"))
	{
		sceneManager_.PushScene(std::make_shared<KeyConfigScene>(sceneManager_, sceneTransitor_));
	}

}

void PauseScene::EndUpdate(Input& input)
{
	if (++frame_ >= change_interval)
	{
		sceneManager_.PopScene();
	}
}

void PauseScene::BeginDraw()
{
	float rate = static_cast<float>(frame_) / static_cast<float>(change_interval);
	DrawBox(90, 90, 90 + pause_width, 90+pause_height*rate, 0xffffff, false);
	DrawString(100, 100, "Pouse", 0xffffff);

}


void PauseScene::NormalDraw()
{	
	DrawString(100, 100, "Pouse Scene", 0xffffff);
	DrawBox(90, 90, 90 + pause_width, 90 + pause_height , 0xffffff, false);

}

void PauseScene::EndDraw()
{	
	float rate = static_cast<float>(frame_) / static_cast<float>(change_interval);
	DrawBox(90, 90, 90 + pause_width,90+ pause_height * (1.0f-rate), 0xffffff, false);
	DrawString(100, 100, "P", 0xffffff);

	for (auto& cmd : commandList_)
	{
		cmd();
	}
}
