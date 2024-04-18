#pragma once
#include "../Scene/Scene.h"
#include"../Input.h"

/// <summary>
/// キーコンフィグのためのシーン
/// </summary>
class KeyConfigScene :
    public Scene
{
private:
	InputTable_t inputTable_;
	std::vector<std::pair<std::string, std::wstring >>commandStringList;
	void CreateCommandStringList(const InputTable_t& table);
public:
	KeyConfigScene(SceneManager& manager, Transitor& transit);
	~KeyConfigScene() {};
	virtual void Update(Input& input)override;
	virtual void Draw() override;

};

