#include <math.h>
#include "ColBox.h"

#include "../_debug/_DebugConOut.h"
#include "../_debug/_DebugDispOut.h"

bool ColBox::CheckCollision(Box box, Collision collision,Size& overlap)
{
	Box box2;
	box2.pos.x = collision.first.x + collision.second.x / 2;
	box2.pos.y = collision.first.y + collision.second.y / 2;
	box2.size.w = collision.second.x;
	box2.size.h = collision.second.y;

	//�Փ˂��Ă��Ȃ�
	if (abs(box.pos.x - box2.pos.x) >= (box.size.w + box2.size.w) / 2 ||
		abs(box.pos.y - box2.pos.y) >= (box.size.h + box2.size.h) / 2)
	{
		return false;
	}

	//TRACE("�Փ�\n");

	//�ǂꂾ���d�Ȃ��Ă��邩
	if (box.pos.x < box2.pos.x) {
		overlap.w = box2.Left() - box.Right();
	}
	else {
		overlap.w = box2.Right() - box.Left();
	}
	if (box.pos.y < box2.pos.y) {
		overlap.h = box2.Top() - box.Bottom();
	}
	else {
		overlap.h = box2.Bottom() - box.Top();
	}

	return true;
}

bool ColBox::CheckCollision(Box box, Collision collision)
{
	Box box2;
	box2.pos.x = collision.first.x + collision.second.x / 2;
	box2.pos.y = collision.first.y + collision.second.y / 2;
	box2.size.w = collision.second.x;
	box2.size.h = collision.second.y;

	//�Փ˂��Ă��Ȃ�
	if (abs(box.pos.x - box2.pos.x) >= (box.size.w + box2.size.w) / 2 ||
		abs(box.pos.y - box2.pos.y) >= (box.size.h + box2.size.h) / 2)
	{
		return false;
	}

	//TRACE("�Փ�\n");

	return true;
}

bool ColBox::CheckCollision(Box box, Collision collision, Vector2DDouble& hitPos)
{
	Box box2;
	box2.pos.x = collision.first.x + collision.second.x / 2;
	box2.pos.y = collision.first.y + collision.second.y / 2;
	box2.size.w = collision.second.x;
	box2.size.h = collision.second.y;

	//�Փ˂��Ă��Ȃ�
	if (abs(box.pos.x - box2.pos.x) >= (box.size.w + box2.size.w) / 2 ||
		abs(box.pos.y - box2.pos.y) >= (box.size.h + box2.size.h) / 2)
	{
		return false;
	}

	//TRACE("�Փ�\n");

	Size overlap = { 0.0f,0.0f };
	if (box.pos.x < box2.pos.x) {
		overlap.w = box2.Left() - box.Right();
		hitPos.x = box2.Left();
	}
	else {
		overlap.w = box2.Right() - box.Left();
		hitPos.x = box2.Right();
	}
	if (box.pos.y < box2.pos.y) {
		overlap.h = box2.Top() - box.Bottom();
		hitPos.y = box2.Top();
	}
	else {
		overlap.h = box2.Bottom() - box.Top();
		hitPos.y = box2.Bottom();
	}

	return true;
}
