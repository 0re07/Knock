#include <DxLib.h>
#include "../../common/Vector2D.h"
#include "Transitor.h"

void Transitor::Start()
{
	//const auto& size = Application::GetInstance().GetWindowSize();
	Vector2D size = { 1024,768 };

	oldRT_ = MakeScreen(size.x, size.y);
	newRT_ = MakeScreen(size.x, size.y);

	int result = GetDrawScreenGraph(0, 0, size.x, size.y, oldRT_);
	frame_ = 0;
}

Transitor::~Transitor()
{
	DeleteGraph(oldRT_);
	DeleteGraph(newRT_);
}

bool
Transitor::IsEnd() const
{
	return frame_ >= interval_;
}