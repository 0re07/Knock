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

	//�I�u�W�F�N�g�Ƃ̏Փ˔���
	ObjHit IsHitObj(Circle obj, ObjType type);

	//���W�Ɗp�x�i�[
	void SetPosAngle(Vector2DDouble pos, float angle);

	//���W�擾
	Vector2D GetPos(void);

private:
	//��ԑJ��
	void (Player::* _phase)(Input& input);
	void MovePhase(Input& input);
	void ShiledPhase(Input& input);
	void StageHitPhase(Input& input);
	void DestroyPhase(Input& input);
	void GoalPhase(Input& input);
	
	//�X�e�[�W�Ƃ̏Փ˔���
	bool IsHitStage(ColBox::Size& overlap);

	//���f���тƂ̏Փ˔���
	bool IsHitAsteroid(Vector2DDouble pos);

	//�V�[���h�����\���Ƃ̏Փ˔���
	bool IsHitShield(void);

	//�V�[���h�E���i���n�_�j�Ƃ̏Փ˔���
	bool IsHitLandingPoint(void);

	//�}�b�v�\��
	TmxObj& tmxObj_;

	//UI
	UIManager ui_;
	int retryImg_;

	Vector2DDouble pos_;
	float angle_;	//�`��̊p�x
	float radius_;	//�I�u�W�F�N�g�Ƃ̏Փ˔��蔼�a

	//�������
	Vector2DDouble initPos_;
	float initAngle_;

	Vector2DDouble vel_;	//�ړ���
	Vector2DDouble accel_;	//������

	//���n�_
	Vector2DDouble landPos_;

	//�v���C���[�摜
	int playerImg_;		

	//�G�t�F�N�g�摜
	int shiledEfImg_[SHILED_FRAME];
	int hitEfImg_[HIT_FRAME];
	int explosionEfImg_[EXPLOSION_FRAME];
	int spornEfImg_[SPORN_FRAME];

	//�A�j���[�V�����Đ�����
	int shiledFrame_;
	int hitFrame_;
	int explosionFrame_;
	int spornFrame_;

	//�X�e�[�W�Ƃ̏Փ˔���
	Vector2DDouble stgHitPos_;

	//�I�u�W�F�N�g�Ƃ̏Փˊ֘A
	ObjHit objHit_;

	//���S�������W���O
	std::list<Vector2DDouble> deathList_;
	int deathPosImg_;

	//�v���C���[�\��
	//true:���� false:���S
	bool alive_;

	//����������
	bool explosion_;

	//�S�[��������
	bool goal_;

	//�V�[���h�����L��
	bool shield_;

};

