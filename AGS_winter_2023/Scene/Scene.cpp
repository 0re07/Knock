#include "Scene.h"

Scene::Scene(SceneManager& scene, Transitor& transit) :sceneManager_(scene),sceneTransitor_(transit)
{
	screenSize_ = { 1024,768 };
	bgImg_ = -1;
	cnt_ = 0;

}

