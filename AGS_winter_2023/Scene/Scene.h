#pragma once
#include "../Manager/UIManager.h"
#include "../common/Vector2D.h"

class Input;
class SceneManager;
class Transitor;

/// <summary>
/// �V�[���̋K��N���X(����1�N���X)
/// </summary>
class Scene
{
public:
	Scene(SceneManager& scene, Transitor& transit);
	virtual~Scene(void) {};//������͑厖
	virtual void Update(Input& input) = 0;
	virtual void Draw(void) = 0;

protected:
	SceneManager& sceneManager_;
	Transitor& sceneTransitor_;

	//�E�B���h�E�̃T�C�Y
	Vector2D screenSize_;

	//�w�i
	int bgImg_;

	int cnt_;

	UIManager ui_;

};
