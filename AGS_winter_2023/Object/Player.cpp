#include "../Manager/Sound/SoundMng.h"
#include "../Manager/Sound/SoundApp.h"
#include "../Scene/Stage/common/TmxObj.h"
#include "../Utility/Utility.h"
#include "../common/Flame.h"
#include "Player.h"

#include "../_debug/_DebugConOut.h"
#include "../_debug/_DebugDispOut.h"

//���s�X�s�[�h
const float speed = 2.0f;

//�Ȃ����
const float power = 0.2f;

//�v���C���[�̑傫���ɍ��킹�����ƍ���
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
	//�����ʒu
	pos_ = { 0,0 };
	vel_ = { 0.0,0.0 };
	accel_ = { 0.0,0.0 };

	angle_ = 0.0f;
	radius_ = 50.0f;

	//���n�_�̐ݒ�
	landPos_ = pos_;

	//�V�[���h�̗L��
	shield_ = false;

	//��������
	alive_ = true;
	explosion_ = false;

	//�S�[������
	goal_ = false;

	//�I�u�W�F�N�g�Ƃ̏Փ˔���
	objHit_.hit = false;
	objHit_.type = ObjType::None;

	//�摜�̓ǂݍ���
	playerImg_ = LoadGraph("./Data/Image/Player/Player.png");
	deathPosImg_ = LoadGraph("./Data/Image/Player/death.png");
	LoadDivGraph("./Data/Image/Player/Shiled.png", 18, 6, 3, 64, 64, shiledEfImg_);
	LoadDivGraph("./Data/Image/Effect/StageHit.png", 60, 10, 6, 108, 108, hitEfImg_);
	LoadDivGraph("./Data/Image/Effect/explosion.png", 11, 11, 1, 96, 96, explosionEfImg_);
	LoadDivGraph("./Data/Image/Effect/sporn.png", 6, 6, 1, 32, 32, spornEfImg_);

	retryImg_ = LoadGraph("./Data/Image/Effect/retry.png");

	//���y
	lpSoundMng.GetSoundID("./Data/Sounds/Music/game.mp3", "game");

	//���ʉ��̓ǂݍ���
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

	//���S���W
	for (auto death : deathList_) {
		DrawRotaGraph(death.x, death.y, 0.5, 0.0, deathPosImg_, true);
	}

	//�v���C���[
	if (alive_) {
		DrawRotaGraph(static_cast<int>(pos_.x), static_cast<int>(pos_.y), defSize, angle_, playerImg_, true);

		//�X�|�[���G�t�F�N�g
		if (spornFrame_ > 0) {
			DrawRotaGraph(static_cast<int>(pos_.x), static_cast<int>(pos_.y), 4.0, 0.0,
				spornEfImg_[(SPORN_FRAME - spornFrame_) / 2], true);
			--spornFrame_;
		}
	}
	//�X�e�[�W�Փ˃G�t�F�N�g
	if (hitFrame_ > 0 && !goal_ && !explosion_) {
		DrawRotaGraph(static_cast<int>(pos_.x), static_cast<int>(pos_.y), 1.0, 0.0, hitEfImg_[(HIT_FRAME - hitFrame_) / 2], true);
		--hitFrame_;
	}


	//�V�[���h�G�t�F�N�g
	if (shiledFrame_ > 0 && !goal_) {
		DrawRotaGraph(static_cast<int>(pos_.x), static_cast<int>(pos_.y), 2.0, angle_, shiledEfImg_[(SHILED_FRAME - shiledFrame_) / 2], true);
		--shiledFrame_;
	}

	//�����i���S�j�G�t�F�N�g
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


	//�f�o�b�O�\��
	//DrawFormatString(0, 0, 0xffffff, "angle:%f", angle_);
	//DrawFormatString(0, 32, 0xffffff, "pos:{%f,%f}", pos_.x, pos_.y);
	//DrawFormatString(0, 64, 0xffffff, "accel:{%f,%f}", accel_.x, accel_.y);
	//DrawFormatString(0, 96, 0xffffff, "vel:{%f,%f}", vel_.x, vel_.y);

}

/// <summary>
/// �J�����Ǐ]������ꍇ�̕`��
/// </summary>
/// <param name="camOffset">�J�����̃I�t�Z�b�g�l</param>
void Player::Draw(const Vector2D& camOffset)
{

	//���S���W
	for (auto death : deathList_) {
		DrawRotaGraph(death.x + camOffset.x, death.y + camOffset.y, 0.5, 0.0, deathPosImg_, true);
	}

	//�v���C���[
	if (alive_) {
		DrawRotaGraph(static_cast<int>(pos_.x + camOffset.x), static_cast<int>(pos_.y + camOffset.y), 
			defSize, angle_, playerImg_, true);
	}

	//�X�e�[�W�Փ˃G�t�F�N�g
	if (hitFrame_ > 0 && !goal_ && !explosion_) {
		DrawRotaGraph(static_cast<int>(pos_.x + camOffset.x), static_cast<int>(pos_.y + camOffset.y),
			1.0, 0.0, hitEfImg_[(HIT_FRAME - hitFrame_) / 2], true);
		--hitFrame_;
	}

	//�V�[���h�G�t�F�N�g
	if (shiledFrame_ > 0 && shield_ && !goal_) {
		DrawRotaGraph(static_cast<int>(pos_.x + camOffset.x), static_cast<int>(pos_.y + camOffset.y),
			1.0, angle_, shiledEfImg_[(SHILED_FRAME - shiledFrame_) / 2], true);
		--shiledFrame_;
	}

	//�����i���S�j�G�t�F�N�g
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


	//�f�o�b�O�\��
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
/// �ʏ�ړ�
/// </summary>
/// <param name=""></param>
void Player::MovePhase(Input& input)
{
	//�ړ�����
	auto VecMove = [&]() {
		//�������Ă����
		// ������
		if (input.IsPrassed("left"))
		{
			angle_ -= power;
		}
		// �E����
		if (input.IsPrassed("right"))
		{
			angle_ += power;
		}

		//���������u��
		//�X�y�[�X�L�[���������������
		if (input.IsPrassed("check"))
		{
			// ����
			accel_ = { cos(angle_ - DX_PI / 2.0f),sin(angle_ - DX_PI / 2.0f) };
			accel_ *= speed;
		}
		else {
			accel_ = {};
		}
	};
	VecMove();

	//�V�[���h����
	if (input.IsTriggerd("check") && IsHitShield()){
		_phase = &Player::ShiledPhase;
	}

	//�V�[���h�E���Ƃ̏Փ˔���
	if (IsHitLandingPoint()) {
		shield_ = false;
	}

	//���f���тƂ̏Փ˔���
	if (IsHitAsteroid(landPos_) ||				//���n�_���W�̎�
		!shield_ && IsHitAsteroid(pos_)) {		//�ʏ���W���V�[���h�����̎�
		_phase = &Player::DestroyPhase;
	}

	//�X�e�[�W�Ƃ̏Փ˔���
	ColBox::Size overlap;
	if (IsHitStage(overlap)) {

		//�����Ԃ�
		if (abs(overlap.w) > abs(overlap.h)) {
			vel_.y += overlap.h;
			
		}
		if (abs(overlap.w) < abs(overlap.h)) {
			vel_.x += overlap.w;
		}

		_phase = &Player::StageHitPhase;
	}

	//�����x�����Z
	vel_ += accel_;
	pos_ += vel_;
}

void Player::ShiledPhase(Input& input)
{
	//�V�[���h�L��
	shield_ = true;

	//�V�[���h�A�j���[�V�����ݒ�
	shiledFrame_ = SHILED_FRAME;

	//���n�_�������Ă������+�����ɍX�V
	accel_ = { cos(angle_ - DX_PI / 2.0f),sin(angle_ - DX_PI / 2.0f) };
	landPos_ = pos_ + accel_ * 300;

	_phase = &Player::MovePhase;
}

void Player::StageHitPhase(Input& input)
{

	//�Փ˃A�j���[�V�����t���[�����ݒ�
	if (hitFrame_ == 0) {
		hitFrame_ = HIT_FRAME;
	}

	accel_ = {};

	//���ʉ��Đ�
	lpSoundApp.PlayOnceSound("hit", true);

	_phase = &Player::MovePhase;
}

void Player::DestroyPhase(Input& input)
{
	//���S����
	alive_ = false;

	//�A�j���[�V�����ݒ�
	if (explosionFrame_ == 0 && !explosion_) {
		explosionFrame_ = EXPLOSION_FRAME;
		explosion_ = true;
	}

	//�ړ��ʂ��O�ɂ���
	accel_ = {};

	//���S���W���i�[
	deathList_.emplace_back(pos_);

	//���^�[���L�[�����ł�蒼��
	if (input.IsTriggerd("next")) {

		//�������W�֖߂�
		SetPosAngle(initPos_, initAngle_);

		//����
		alive_ = true;
		spornFrame_ = SPORN_FRAME;

		explosion_ = false;

		//�ړ����Ȃ���
		vel_ = {};
		accel_ = {};

		//�X�e�[�W�Փ˃A�j���[�V�����������p����Ȃ��悤�ɂ���
		hitFrame_ = 0;

		_phase = &Player::MovePhase;
	}
}

void Player::GoalPhase(Input& input)
{
	goal_ = true;

	accel_ = {};
	vel_ = {};

	//���ʉ��̍Đ�
	lpSoundApp.PlayOnceSound("goal", false);
}

/// <summary>
/// ��Q���Ƃ̏Փ˔���
/// </summary>
/// <param name="obj">�Փ˔���Ώ�</param>
/// <returns>true:�Փˁ@false:�Փ˂��Ă��Ȃ�</returns>
ObjHit Player::IsHitObj(Circle obj, ObjType type)
{
	ObjHit hitInfo_;

	objHit_.type = type;

	Vector2D overlap;

	//�s�����悩��s�������Ƃ�����
	float diffX = static_cast<float>(pos_.x - obj.pos.x);
	float diffY = static_cast<float>(pos_.y - obj.pos.y);

	// �Εӂ����߂�
	auto distance = hypotf(diffX, diffY);

	float overlapLength = radius_ + obj.radius - distance;
	if (overlapLength >= 0.0f)
	{
		overlap.x = pos_.x - obj.pos.x;
		overlap.y = pos_.y - obj.pos.y;

		overlap = overlap.Normalized() * overlapLength;

		//�Փ�
		objHit_.hit = true;

		//��Q��
		if (objHit_.type == ObjType::Obstacle) {
			_phase = &Player::DestroyPhase;
		}
		//�S�[��
		if (objHit_.type == ObjType::Goal) {
			_phase = &Player::GoalPhase;
		}
	}
	else
	{
		//�Փ˂��Ă��Ȃ�
		objHit_.hit = false;
	}

	hitInfo_.hit = objHit_.hit;
	hitInfo_.type = objHit_.type;

	return hitInfo_;
}

void Player::SetPosAngle( Vector2DDouble pos, float angle)
{
	//�����p�x���W���i�[
	initAngle_ = angle;
	initPos_ = pos;

	//���n�_�̐ݒ�
	landPos_ = pos;

	//���ۂ̏��֊i�[
	pos_ = pos;
	angle_ = angle;
}

/// <summary>
/// �X�e�[�W�Ƃ̏Փ˔���
/// </summary>
/// <param name="">�����Ԃ��̗�</param>
/// <returns>true:�Փˁ@false:�Փ˂��Ă��Ȃ�</returns>
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
/// ���f���тƂ̏Փ˔���
/// </summary>
/// <param name=""></param>
/// <returns>true:�Փˁ@false:�Փ˂��Ă��Ȃ�</returns>
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
			TRACE("�ՓˁF���f����\n");

			//�Փ�
			return true;
		}
	}

	return false;
}

/// <summary>
/// �V�[���h�����\���Ƃ̏Փ˔���
/// </summary>
/// <param name=""></param>
/// <returns>true:�Փˁ@false:�Փ˂��Ă��Ȃ�</returns>
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
			TRACE("�ՓˁF�V�[���h�����\���\n");

			//�Փ�
			return true;
		}
	}

	return false;
}

/// <summary>
/// �V�[���h�E���Ƃ̏Փ˔���
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
			TRACE("�ՓˁF�V�[���h�E���\n");

			//�Փ�
			return true;
		}
	}
	return false;
}
