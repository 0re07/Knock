#pragma once
#include<memory>
#include<list>
class Input;
class Stage;

class StageManager
{
public:
	/// <summary>
	/// �擪��(Update���Ă΂��)�V�[����؂�ւ���
	/// </summary>
	/// <param name="scene">�؂�ւ���̃V�[��</param>
	void ChangeStage(std::shared_ptr<Stage> scene);
	/// <summary>
	/// �X�^�b�N�̓��̃V�[�����폜����
	/// �������A�X�^�b�N��ɂP�����V�[�����Ȃ��ꍇ��
	/// �폜���Ȃ�
	/// </summary>
	/// <param name="scene"></param>
	/// <summary>
	void PopStage();
	/// �V�[�����v�b�V������B�X�^�b�N�̐���������
	/// ��ԏ�Update�����Ă΂�܂���
	/// </summary>
	/// <param name="scene"></param>
	void PushStage(std::shared_ptr<Stage>scene);

	void Init();
	/// <summary>
	/// �����Ă���V�[���̃A�b�v�f�[�g���Ăт���
	/// </summary>
	/// <param name="input"></param>
	void Update(Input& input);
	void Draw();

	bool EndStage();

private:
	/// <summary>
	/// 
	/// </summary>

	std::list<std::shared_ptr<Stage>> stages_;//���ݐi�s���̃X�e�[�W
};

