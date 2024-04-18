#pragma once
#include "../Manager/UIManager.h"
#include "../common/Vector2D.h"

class Input;
class SceneManager;
class Transitor;

/// <summary>
/// シーンの規定クラス(抽象1クラス)
/// </summary>
class Scene
{
public:
	Scene(SceneManager& scene, Transitor& transit);
	virtual~Scene(void) {};//これ実は大事
	virtual void Update(Input& input) = 0;
	virtual void Draw(void) = 0;

protected:
	SceneManager& sceneManager_;
	Transitor& sceneTransitor_;

	//ウィンドウのサイズ
	Vector2D screenSize_;

	//背景
	int bgImg_;

	int cnt_;

	UIManager ui_;

};
