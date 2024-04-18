#include <DxLib.h>
#include "../../common/Vector2D.h"
#include "PushTransitor.h"

PushTransitor::PushTransitor(TransitDirection dir, int interval)
{
	direction_ = dir;
}

void PushTransitor::Update()
{
	if (frame_ < interval_) {
		++frame_;
		SetDrawScreen(newRT_);
	}
	else if (frame_ == interval_) {
		SetDrawScreen(DX_SCREEN_BACK);
	}
}

void PushTransitor::Draw()
{
	if (IsEnd()) {
		return;
	}
	const Vector2D wsize = { 1024,768 };
	SetDrawScreen(DX_SCREEN_BACK);
	auto rate = (float)frame_ / (float)interval_;

	//最終的に新画面が0に来るようにminusoneを用意する
	auto minusone = rate - 1.0f;
	int endX = 0;
	int endY = 0;
	switch (direction_) {
	case TransitDirection::left:
		endX = -wsize.x;
		break;
	case TransitDirection::right:
		endX = wsize.x;
		break;
	case TransitDirection::up:
		endY = -wsize.y;
		break;
	case TransitDirection::down:
		endY = wsize.y;
		break;
	}

	DrawGraph(endX * rate, endY * rate, oldRT_, true);
	DrawGraph(endX * minusone, endY * minusone, newRT_, true);
}
