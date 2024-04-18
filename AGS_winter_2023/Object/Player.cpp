#include "../Manager/Sound/SoundMng.h"
#include "../Manager/Sound/SoundApp.h"
#include "../Scene/Stage/common/TmxObj.h"
#include "../Utility/Utility.h"
#include "../common/Flame.h"
#include "Player.h"

#include "../_debug/_DebugConOut.h"
#include "../_debug/_DebugDispOut.h"

//走行スピード
const float speed = 2.0f;

//曲がる力
const float power = 0.2f;

//プレイヤーの大きさに合わせた幅と高さ
const int width = 84;
const int height = 80;

const int abyssWidth = 10;
const int abyssHeight = 10;

const float defSize = 1.2f;

Player::Player(TmxObj& tmx) :tmxObj_(tmx)
{
	_phase =&Player::MovePhase;

	angle_ = 0.0f;
	radius_ = 0.0f;

	initAngle_ = 0;

	alive_ = true;
	explosion_ = false;
	goal_ = false;
	shield_ = false;

	playerImg_ = -1;
	for (int i = 0; i < HIT_FRAME; ++i) {
		hitEfImg_[i] = -1;
	}
	for (int i = 0; i < SHILED_FRAME; ++i) {
		shiledEfImg_[i] = -1;
	}
	for (int i = 0; i < EXPLOSION_FRAME; ++i) {
		explosionEfImg_[i] = -1;
	}
	for (int i = 0; i < SPORN_FRAME; ++i) {
		spornEfImg_[i] = -1;
	}
	deathPosImg_ = -1;
	retryImg_ = -1;

	objHit_.hit = false;
	objHit_.type = ObjType::None;

	hitFrame_ = 0;
	shiledFrame_ = 0;
	explosionFrame_ = 0;
	spornFrame_ = 0;
}

Player::~Player(void)
{
	deathList_.clear();
}

void Player::Init(void)
{
	//初期位置
	pos_ = { 0,0 };
	vel_ = { 0.0,0.0 };
	accel_ = { 0.0,0.0 };

	angle_ = 0.0f;
	radius_ = 50.0f;

	//着地点の設定
	landPos_ = pos_;

	//シールドの有無
	shield_ = false;

	//生死判定
	alive_ = true;
	explosion_ = false;

	//ゴール判定
	goal_ = false;

	//オブジェクトとの衝突判定
	objHit_.hit = false;
	objHit_.type = ObjType::None;

	//画像の読み込み
	playerImg_ = LoadGraph("./Data/Image/Player/Player.png");
	deathPosImg_ = LoadGraph("./Data/Image/Player/death.png");
	LoadDivGraph("./Data/Image/Player/Shiled.png", 18, 6, 3, 64, 64, shiledEfImg_);
	LoadDivGraph("./Data/Image/Effect/StageHit.png", 60, 10, 6, 108, 108, hitEfImg_);
	LoadDivGraph("./Data/Image/Effect/explosion.png", 11, 11, 1, 96, 96, explosionEfImg_);
	LoadDivGraph("./Data/Image/Effect/sporn.png", 6, 6, 1, 32, 32, spornEfImg_);

	retryImg_ = LoadGraph("./Data/Image/Effect/retry.png");

	//音楽
	lpSoundMng.GetSoundID("./Data/Sounds/Music/game.mp3", "game");

	//効果音の読み込み
	lpSoundMng.GetSoundID("./Data/Sounds/Sound/Player/hit.mp3", "hit");
	lpSoundMng.GetSoundID("./Data/Sounds/Sound/Player/goal.mp3", "goal");

	ui_.Init();
}

void Player::Update(Input& input)
{
	ui_.Update();

	(this->*_phase)(input);
}

void Player::Draw(void)
{
	//DrawCircle(landPos_.x, landPos_.y, 10.0f, 0xff0000, true);

	//死亡座標
	for (auto death : deathList_) {
		DrawRotaGraph(death.x, death.y, 0.5, 0.0, deathPosImg_, true);
	}

	//プレイヤー
	if (alive_) {
		DrawRotaGraph(static_cast<int>(pos_.x), static_cast<int>(pos_.y), defSize, angle_, playerImg_, true);

		//スポーンエフェクト
		if (spornFrame_ > 0) {
			DrawRotaGraph(static_cast<int>(pos_.x), static_cast<int>(pos_.y), 4.0, 0.0,
				spornEfImg_[(SPORN_FRAME - spornFrame_) / 2], true);
			--spornFrame_;
		}
	}
	//ステージ衝突エフェクト
	if (hitFrame_ > 0 && !goal_ && !explosion_) {
		DrawRotaGraph(static_cast<int>(pos_.x), static_cast<int>(pos_.y), 1.0, 0.0, hitEfImg_[(HIT_FRAME - hitFrame_) / 2], true);
		--hitFrame_;
	}


	//シールドエフェクト
	if (shiledFrame_ > 0 && !goal_) {
		DrawRotaGraph(static_cast<int>(pos_.x), static_cast<int>(pos_.y), 2.0, angle_, shiledEfImg_[(SHILED_FRAME - shiledFrame_) / 2], true);
		--shiledFrame_;
	}

	//爆発（死亡）エフェクト
	if (!alive_ && explosionFrame_ > 0) {
		DrawRotaGraph(
			static_cast<int>(pos_.x), static_cast<int>(pos_.y),1.2, 0.0, explosionEfImg_[(EXPLOSION_FRAME - explosionFrame_) / 2], true);
		--explosionFrame_;
	}

	if(!alive_) {
		//Retry
		DrawGraph(0, 0, retryImg_, true);
		ui_.Draw({ 1024 / 2 - 300,768 / 2 +30 }, 4.0, UIVALUE::ENTER);
	}


	//デバッグ表示
	//DrawFormatString(0, 0, 0xffffff, "angle:%f", angle_);
	//DrawFormatString(0, 32, 0xffffff, "pos:{%f,%f}", pos_.x, pos_.y);
	//DrawFormatString(0, 64, 0xffffff, "accel:{%f,%f}", accel_.x, accel_.y);
	//DrawFormatString(0, 96, 0xffffff, "vel:{%f,%f}", vel_.x, vel_.y);

}

/// <summary>
/// カメラ追従がある場合の描画
/// </summary>
/// <param name="camOffset">カメラのオフセット値</param>
void Player::Draw(const Vector2D& camOffset)
{

	//死亡座標
	for (auto death : deathList_) {
		DrawRotaGraph(death.x + camOffset.x, death.y + camOffset.y, 0.5, 0.0, deathPosImg_, true);
	}

	//プレイヤー
	if (alive_) {
		DrawRotaGraph(static_cast<int>(pos_.x + camOffset.x), static_cast<int>(pos_.y + camOffset.y), 
			defSize, angle_, playerImg_, true);
	}

	//ステージ衝突エフェクト
	if (hitFrame_ > 0 && !goal_ && !explosion_) {
		DrawRotaGraph(static_cast<int>(pos_.x + camOffset.x), static_cast<int>(pos_.y + camOffset.y),
			1.0, 0.0, hitEfImg_[(HIT_FRAME - hitFrame_) / 2], true);
		--hitFrame_;
	}

	//シールドエフェクト
	if (shiledFrame_ > 0 && shield_ && !goal_) {
		DrawRotaGraph(static_cast<int>(pos_.x + camOffset.x), static_cast<int>(pos_.y + camOffset.y),
			1.0, angle_, shiledEfImg_[(SHILED_FRAME - shiledFrame_) / 2], true);
		--shiledFrame_;
	}

	//爆発（死亡）エフェクト
	if (!alive_ && explosionFrame_ > 0) {
		DrawRotaGraph(static_cast<int>(pos_.x + camOffset.x), static_cast<int>(pos_.y + camOffset.y),
			1.2, 0.0, explosionEfImg_[(EXPLOSION_FRAME - explosionFrame_) / 2], true);
		--explosionFrame_;
	}

	if (!alive_) {
		//Retry
		DrawGraph(0, 0, retryImg_, true);
		ui_.Draw({ 1024 / 2 - 300,768 / 2 + 30 }, 4.0, UIVALUE::ENTER);
	}


	//デバッグ表示
	//DrawFormatString(0, 0, 0xffffff, "angle:%f", angle_);
	//DrawFormatString(0 + camOffset.x , 32 +  camOffset.y, 0xffffff, "pos:{%f,%f}", pos_.x, pos_.y);
	//DrawFormatString(0 + camOffset.x , 900 +  camOffset.y, 0xffffff, "pos:{%f,%f}", pos_.x, pos_.y);
	//DrawFormatString(0, 64, 0xffffff, "accel:{%f,%f}", accel_.x, accel_.y);
	//DrawFormatString(0, 96, 0xffffff, "vel:{%f,%f}", vel_.x, vel_.y);

}

Vector2D Player::GetPos(void)
{
	Vector2D returnPos;

	returnPos.x = static_cast<int>(pos_.x);
	returnPos.y = static_cast<int>(pos_.y);

	return returnPos;
}

/// <summary>
/// 通常移動
/// </summary>
/// <param name=""></param>
void Player::MovePhase(Input& input)
{
	//移動処理
	auto VecMove = [&]() {
		//押下している間
		// 左向き
		if (input.IsPrassed("left"))
		{
			angle_ -= power;
		}
		// 右向き
		if (input.IsPrassed("right"))
		{
			angle_ += power;
		}

		//押下した瞬間
		//スペースキーを押下したら加速
		if (input.IsPrassed("check"))
		{
			// 加速
			accel_ = { cos(angle_ - DX_PI / 2.0f),sin(angle_ - DX_PI / 2.0f) };
			accel_ *= speed;
		}
		else {
			accel_ = {};
		}
	};
	VecMove();

	//シールド処理
	if (input.IsTriggerd("check") && IsHitShield()){
		_phase = &Player::ShiledPhase;
	}

	//シールド脱区域との衝突判定
	if (IsHitLandingPoint()) {
		shield_ = false;
	}

	//小惑星帯との衝突判定
	if (IsHitAsteroid(landPos_) ||				//着地点座標の時
		!shield_ && IsHitAsteroid(pos_)) {		//通常座標かつシールド無効の時
		_phase = &Player::DestroyPhase;
	}

	//ステージとの衝突判定
	ColBox::Size overlap;
	if (IsHitStage(overlap)) {

		//押し返す
		if (abs(overlap.w) > abs(overlap.h)) {
			vel_.y += overlap.h;
			
		}
		if (abs(overlap.w) < abs(overlap.h)) {
			vel_.x += overlap.w;
		}

		_phase = &Player::StageHitPhase;
	}

	//加速度を加算
	vel_ += accel_;
	pos_ += vel_;
}

void Player::ShiledPhase(Input& input)
{
	//シールド有効
	shield_ = true;

	//シールドアニメーション設定
	shiledFrame_ = SHILED_FRAME;

	//着地点を向いている方向+距離に更新
	accel_ = { cos(angle_ - DX_PI / 2.0f),sin(angle_ - DX_PI / 2.0f) };
	landPos_ = pos_ + accel_ * 300;

	_phase = &Player::MovePhase;
}

void Player::StageHitPhase(Input& input)
{

	//衝突アニメーションフレーム数設定
	if (hitFrame_ == 0) {
		hitFrame_ = HIT_FRAME;
	}

	accel_ = {};

	//効果音再生
	lpSoundApp.PlayOnceSound("hit", true);

	_phase = &Player::MovePhase;
}

void Player::DestroyPhase(Input& input)
{
	//死亡判定
	alive_ = false;

	//アニメーション設定
	if (explosionFrame_ == 0 && !explosion_) {
		explosionFrame_ = EXPLOSION_FRAME;
		explosion_ = true;
	}

	//移動量を０にする
	accel_ = {};

	//死亡座標を格納
	deathList_.emplace_back(pos_);

	//リターンキー押下でやり直し
	if (input.IsTriggerd("next")) {

		//初期座標へ戻す
		SetPosAngle(initPos_, initAngle_);

		//復活
		alive_ = true;
		spornFrame_ = SPORN_FRAME;

		explosion_ = false;

		//移動をなくす
		vel_ = {};
		accel_ = {};

		//ステージ衝突アニメーションが引き継がれないようにする
		hitFrame_ = 0;

		_phase = &Player::MovePhase;
	}
}

void Player::GoalPhase(Input& input)
{
	goal_ = true;

	accel_ = {};
	vel_ = {};

	//効果音の再生
	lpSoundApp.PlayOnceSound("goal", false);
}

/// <summary>
/// 障害物との衝突判定
/// </summary>
/// <param name="obj">衝突判定対象</param>
/// <returns>true:衝突　false:衝突していない</returns>
ObjHit Player::IsHitObj(Circle obj, ObjType type)
{
	ObjHit hitInfo_;

	objHit_.type = type;

	Vector2D overlap;

	//行った先から行ったもとを引く
	float diffX = static_cast<float>(pos_.x - obj.pos.x);
	float diffY = static_cast<float>(pos_.y - obj.pos.y);

	// 斜辺を求める
	auto distance = hypotf(diffX, diffY);

	float overlapLength = radius_ + obj.radius - distance;
	if (overlapLength >= 0.0f)
	{
		overlap.x = pos_.x - obj.pos.x;
		overlap.y = pos_.y - obj.pos.y;

		overlap = overlap.Normalized() * overlapLength;

		//衝突
		objHit_.hit = true;

		//障害物
		if (objHit_.type == ObjType::Obstacle) {
			_phase = &Player::DestroyPhase;
		}
		//ゴール
		if (objHit_.type == ObjType::Goal) {
			_phase = &Player::GoalPhase;
		}
	}
	else
	{
		//衝突していない
		objHit_.hit = false;
	}

	hitInfo_.hit = objHit_.hit;
	hitInfo_.type = objHit_.type;

	return hitInfo_;
}

void Player::SetPosAngle( Vector2DDouble pos, float angle)
{
	//初期角度座標を格納
	initAngle_ = angle;
	initPos_ = pos;

	//着地点の設定
	landPos_ = pos;

	//実際の情報へ格納
	pos_ = pos;
	angle_ = angle;
}

/// <summary>
/// ステージとの衝突判定
/// </summary>
/// <param name="">押し返しの量</param>
/// <returns>true:衝突　false:衝突していない</returns>
bool Player::IsHitStage(ColBox::Size& overlap)
{
	for (const auto& col : tmxObj_.GetColList())
	{
		ColBox::Box box;
		box.pos = pos_;
		box.size.w = width;
		box.size.h = height;

		if (tmxObj_.col_.CheckCollision(box, col, overlap))
		{
			return true;
		}
	}

	return false;
}

/// <summary>
/// 小惑星帯との衝突判定
/// </summary>
/// <param name=""></param>
/// <returns>true:衝突　false:衝突していない</returns>
bool Player::IsHitAsteroid(Vector2DDouble pos)
{
	for (const auto& col : tmxObj_.GetAbyssColList())
	{
		ColBox::Box box;
		box.pos = pos;
		box.size.w = abyssWidth;
		box.size.h = abyssHeight;

		ColBox::Size overlap;
		if (tmxObj_.col_.CheckCollision(box, col, overlap))
		{
			TRACE("衝突：小惑星帯\n");

			//衝突
			return true;
		}
	}

	return false;
}

/// <summary>
/// シールド装着可能区域との衝突判定
/// </summary>
/// <param name=""></param>
/// <returns>true:衝突　false:衝突していない</returns>
bool Player::IsHitShield(void)
{
	for (const auto& col : tmxObj_.GetJumpColList())
	{
		ColBox::Box box;
		box.pos = pos_;
		box.size.w = width;
		box.size.h = height;

		ColBox::Size overlap;
		if (tmxObj_.col_.CheckCollision(box, col, overlap))
		{
			TRACE("衝突：シールド装着可能区域\n");

			//衝突
			return true;
		}
	}

	return false;
}

/// <summary>
/// シールド脱区域との衝突判定
/// </summary>
/// <param name=""></param>
/// <returns></returns>
bool Player::IsHitLandingPoint(void)
{
	for (const auto& col : tmxObj_.GetFallColList())
	{
		ColBox::Box box;
		box.pos = pos_;
		box.size.w = width;
		box.size.h = height;

		ColBox::Size overlap;
		if (tmxObj_.col_.CheckCollision(box, col, overlap))
		{
			TRACE("衝突：シールド脱区域\n");

			//衝突
			return true;
		}
	}
	return false;
}
