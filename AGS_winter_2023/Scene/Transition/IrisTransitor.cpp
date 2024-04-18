#include <math.h>
#include <DxLib.h>
#include "../../common/Vector2D.h"
#include "IrisTransitor.h"

IrisTransitor::IrisTransitor(bool irisOut, int interval, bool isTiled, int gHandle) 
	:Transitor(interval),irisOut_(irisOut),isTiled_(isTiled),gHandle_(gHandle)
{
	//ウィンドウサイズ
	Vector2D screenSize = { 1024,768 };

	//マスクレイヤーの作成
	handleForMaskScreen_ = MakeScreen(screenSize.x, screenSize.y, true);
	maskH_ = CreateMaskScreen();

	//ウィンドウの対角線の長さ
	diagonalLength_ = hypotf(screenSize.x, screenSize.y) / 2.0f;
}

IrisTransitor::~IrisTransitor()
{
	DeleteMaskScreen();
}

void IrisTransitor::Update()
{
	if (frame_ < interval_) {
		//++frame_;
		frame_+=2;
		SetDrawScreen(newRT_);
	}
	else if (frame_ == interval_) {
		SetDrawScreen(DX_SCREEN_BACK);
	}
}

void IrisTransitor::Draw()
{
	if (IsEnd()) {
		return;
	}

	auto rate = (float)frame_ / (float)interval_;
	int backRT = oldRT_;
	int maskedRT = newRT_;
	if (irisOut_) {
		backRT = newRT_;
		maskedRT = oldRT_;
		rate = 1.0f - rate;
	}
	//
	float radius = (diagonalLength_)*rate;
	SetDrawScreen(handleForMaskScreen_);
	ClearDrawScreen();

	Vector2D pos = { 1024 / 2,768 / 2 };
	DrawCircleAA(pos.x, pos.y, radius, 32, 0xffffff, true);

	//隠し関数(現在のグラフィックハンドルをマスクスクリーンに転送)
	SetMaskScreenGraph(handleForMaskScreen_);
	//描画領域を反転する
	SetMaskReverseEffectFlag(true);

	SetDrawScreen(DX_SCREEN_BACK);
	SetUseMaskScreenFlag(false);
	DrawGraph(0, 0, backRT, true);
	SetUseMaskScreenFlag(true);
	DrawGraph(0, 0, maskedRT, true);
	SetUseMaskScreenFlag(false);
}