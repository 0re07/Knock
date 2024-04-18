#include "Stage.h"
#include "StageManager.h"

void StageManager::ChangeStage(std::shared_ptr<Stage> stage)
{
	if (stages_.empty())
	{
		stages_.push_front(stage);
	}
	else
	{
		stages_.front() = (stage);
	}
}

void StageManager::PopStage()
{
	if (stages_.size() > 1)
	{
		stages_.pop_front();
	}
}

void StageManager::PushStage(std::shared_ptr<Stage> stage)
{
	stages_.push_front(stage);
}

void StageManager::Init()
{
	auto rit = stages_.rbegin();
	for (; rit != stages_.rend(); rit++) {
		(*rit)->Init();
	}
}

void StageManager::Update(Input& input)
{
	if (!stages_.empty())
	{
		stages_.front()->Update(input);
	}
}

void StageManager::Draw()
{
	auto rit = stages_.rbegin();
	for (; rit != stages_.rend(); rit++) {
		(*rit)->Draw();
	}
}

bool StageManager::EndStage()
{
	//if () {
	//	return true;
	//}
	return false;
}
