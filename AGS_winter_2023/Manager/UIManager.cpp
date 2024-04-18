#include <DxLib.h>
#include "UIManager.h"

UIManager::UIManager()
{
	Init();
}

UIManager::~UIManager()
{
}

void UIManager::Init(void)
{
	//画像
	//矢印キー
	LoadDivGraph("./Data/Image/UI/left.png", 6, 4, 2, 16, 16, leftImg_);
	LoadDivGraph("./Data/Image/UI/right.png", 6, 4, 2, 16, 16, rightImg_);
	LoadDivGraph("./Data/Image/UI/up.png", 6, 4, 2, 16, 16, upImg_);
	LoadDivGraph("./Data/Image/UI/down.png", 6, 4, 2, 16, 16, downImg_);
	//エンターキー
	LoadDivGraph("./Data/Image/UI/enter.png", 6, 4, 2, 32, 32, enterImg_);
	//スペースキー
	LoadDivGraph("./Data/Image/UI/space.png", 6, 3, 2, 80, 16, spaceImg_);

	cnt_ = 0;
}

void UIManager::Update(void)
{
	cnt_++;
}

void UIManager::Draw(Vector2D pos, double rate, UIVALUE value)
{
	switch (value)
	{
	case LEFT:
		DrawRotaGraph(pos.x, pos.y, rate, 0.0, leftImg_[(cnt_ / 6) % 6], true);
		break;
	case RIGHT:
		DrawRotaGraph(pos.x, pos.y, rate, 0.0, rightImg_[(cnt_ / 6) % 6], true);
		break;
	case UP:
		DrawRotaGraph(pos.x, pos.y, rate, 0.0, upImg_[(cnt_ / 6) % 6], true);
		break;
	case DOWN:
		DrawRotaGraph(pos.x, pos.y, rate, 0.0, downImg_[(cnt_ / 6) % 6], true);
		break;
	case ENTER:
		DrawRotaGraph(pos.x, pos.y, rate, 0.0, enterImg_[(cnt_ / 6) % 6], true);
		break;
	case SPACE:
		DrawRotaGraph(pos.x, pos.y, rate, 0.0, spaceImg_[(cnt_ / 6) %6], true);
		break;
	}
}
