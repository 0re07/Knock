#pragma once
#include <memory>
#include <DxLib.h>
#include "../Manager/UIManager.h"
#include "../common/Vector2D.h"
#include "../common/ColBox.h"
#include "../Input.h"
#include "ObjectType.h"

struct ObjHit {
	bool hit;
	ObjType type;
};

class TmxObj;
class Controller;

const int SHILED_FRAME = 24;
const int HIT_FRAME = 60;
const int EXPLOSION_FRAME = 11;
const int SPORN_FRAME = 6;

class Player
{
public:
	Player(TmxObj& tmx);
	~Player(void);

	void Init(void);
	void Update(Input& input);
	void Draw(void);
	void Draw(const Vector2D& camOffset);

	//オブジェクトとの衝突判定
	ObjHit IsHitObj(Circle obj, ObjType type);

	//座標と角度格納
	void SetPosAngle(Vector2DDouble pos, float angle);

	//座標取得
	Vector2D GetPos(void);

private:
	//状態遷移
	void (Player::* _phase)(Input& input);
	void MovePhase(Input& input);
	void ShiledPhase(Input& input);
	void StageHitPhase(Input& input);
	void DestroyPhase(Input& input);
	void GoalPhase(Input& input);
	
	//ステージとの衝突判定
	bool IsHitStage(ColBox::Size& overlap);

	//小惑星帯との衝突判定
	bool IsHitAsteroid(Vector2DDouble pos);

	//シールド装着可能区域との衝突判定
	bool IsHitShield(void);

	//シールド脱区域（着地点）との衝突判定
	bool IsHitLandingPoint(void);

	//マップ表示
	TmxObj& tmxObj_;

	//UI
	UIManager ui_;
	int retryImg_;

	Vector2DDouble pos_;
	float angle_;	//描画の角度
	float radius_;	//オブジェクトとの衝突判定半径

	//初期状態
	Vector2DDouble initPos_;
	float initAngle_;

	Vector2DDouble vel_;	//移動量
	Vector2DDouble accel_;	//加速量

	//着地点
	Vector2DDouble landPos_;

	//プレイヤー画像
	int playerImg_;		

	//エフェクト画像
	int shiledEfImg_[SHILED_FRAME];
	int hitEfImg_[HIT_FRAME];
	int explosionEfImg_[EXPLOSION_FRAME];
	int spornEfImg_[SPORN_FRAME];

	//アニメーション再生時間
	int shiledFrame_;
	int hitFrame_;
	int explosionFrame_;
	int spornFrame_;

	//ステージとの衝突判定
	Vector2DDouble stgHitPos_;

	//オブジェクトとの衝突関連
	ObjHit objHit_;

	//死亡した座標ログ
	std::list<Vector2DDouble> deathList_;
	int deathPosImg_;

	//プレイヤー表示
	//true:生存 false:死亡
	bool alive_;

	//爆発したか
	bool explosion_;

	//ゴールしたか
	bool goal_;

	//シールド処理有無
	bool shield_;

};

