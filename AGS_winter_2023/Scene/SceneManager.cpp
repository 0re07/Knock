#include"Scene.h"
#include "SceneManager.h"

void SceneManager::ChangeScene(std::shared_ptr<Scene> scene)
{
	if (scenes_.empty())
	{
		scenes_.push_front(scene);
	}
	else 
	{
		scenes_ .front() = (scene);
	}
}

void SceneManager::Update(Input& input)
{
	if (!scenes_.empty())
	{
		scenes_.front()->Update(input);
	}

}

void SceneManager::Draw()
{
	auto rit = scenes_.rbegin();
	for (; rit != scenes_.rend(); rit++) {
		(*rit)->Draw();
	}
}

void SceneManager::PopScene()
{
	if (scenes_.size() > 1)
	{
		scenes_.pop_front();
	}	
}

void SceneManager::PushScene(std::shared_ptr<Scene>scene)
{
	scenes_.push_front(scene);
}
