#include <DxLib.h>
#include "../../Object/Obstacle.h"
#include "../../Object/Goal.h"
#include "Stage.h"

Stage::Stage(StageManager& stageMng, Transitor& transit):stageManager_(stageMng),stageTransitor_(transit)
{
	//背景
	bImg_ = -1;

	screenSize_ = { 1024,768 };

	tmxObj_ = std::make_unique<TmxObj>();

	change_ = 60;
}

bool Stage::CreateObj(ObjType type) {

	//メンバー関数テンプレート
	switch (type)
	{
	case ObjType::None:
		return false;
	case ObjType::Goal:
		CreateObj<Goal>(type, false);
		break;
	case ObjType::Obstacle:
		CreateObj<Obstacle>(type, false);
		break;
	default:
		return false;
	}

	return true;
}