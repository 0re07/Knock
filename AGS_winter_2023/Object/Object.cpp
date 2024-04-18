#include "Object.h"

Object::Object(void)
{
	Init();
}

Object::~Object(void)
{
}

void Object::Init(void)
{
	cnt_ = 0;
}

void Object::Update(void)
{
	cnt_++;
}
