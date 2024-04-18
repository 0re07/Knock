#pragma once
#include <memory>
#include "../../Object/Object.h"
#include "../../Object/Player.h"
#include "../../Input.h"
#include "../Transition/Transitor.h"
#include "common/TmxObj.h"
#include "StageManager.h"

const int bgGap = 100.0;

class Stage
{
public:
	Stage(StageManager& stageMng, Transitor& transit);
	virtual ~Stage(void){};
	virtual void Init(void) {};
	virtual void Update(Input& input) {};
	virtual void Draw(void) {};

protected:
	StageManager& stageManager_;
	Transitor& stageTransitor_;

	//ステージ表示
	std::unique_ptr<TmxObj> tmxObj_;

	//プレイヤー
	std::unique_ptr<Player> player_;

	//オブジェクト
	std::list<std::shared_ptr<Object>> objList_;

	bool CreateObj(ObjType type);

	//テンプレート宣言(二行目が本体)
	template<class ObjectType>
	bool CreateObj(ObjType type, bool alive);

	//画面サイズ
	Vector2D screenSize_;

	//背景
	int bImg_;

	int change_;

};

//テンプレート
template<class ObjectType>
inline bool Stage::CreateObj(ObjType type, bool alive)
{
	if (alive)
	{
		return true;
	}

	objList_.emplace_back(std::make_unique<ObjectType>());

	for (auto& obj : objList_) {
		obj->Init();
	}

	return true;
}
