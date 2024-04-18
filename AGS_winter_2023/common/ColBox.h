#pragma once
#include "Vector2D.h"
#include "Collision.h"

class ColBox
{
public:
	struct Size {
		double w;
		double h;
	};

	struct Box {
		Vector2DDouble pos;
		Size size = { 0.0,0.0 };

		float Left() { return static_cast<float>(pos.x - size.w / 2); }
		float Top() { return static_cast<float>(pos.y - size.h / 2); }
		float Right() { return static_cast<float>(pos.x + size.w / 2); }
		float Bottom() { return static_cast<float>(pos.y + size.h / 2); }
	};

	bool CheckCollision(Box box, Collision collision, Size& overlap);
	bool CheckCollision(Box box, Collision collision);
	bool CheckCollision(Box box, Collision collision, Vector2DDouble& hitPos);
 
};

