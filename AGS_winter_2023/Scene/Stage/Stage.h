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

	//�X�e�[�W�\��
	std::unique_ptr<TmxObj> tmxObj_;

	//�v���C���[
	std::unique_ptr<Player> player_;

	//�I�u�W�F�N�g
	std::list<std::shared_ptr<Object>> objList_;

	bool CreateObj(ObjType type);

	//�e���v���[�g�錾(��s�ڂ��{��)
	template<class ObjectType>
	bool CreateObj(ObjType type, bool alive);

	//��ʃT�C�Y
	Vector2D screenSize_;

	//�w�i
	int bImg_;

	int change_;

};

//�e���v���[�g
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
