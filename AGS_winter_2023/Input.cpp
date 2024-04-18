#include "Input.h"
#include<DxLib.h>
#include<cassert>
#include<algorithm>


bool Input::GetCurrentInput(const std::string& input) const
{
	auto it = currentState_.find(input);
	if (it == currentState_.end())
	{
		return false;
	}
	return it->second;
}

bool Input::GetLastInput(const std::string& input) const
{
	auto it = lastState_.find(input);
	if (it == lastState_.end())
	{
		return false;
	}
	return it->second;
}

Input::Input()
{
	//���ӂ��Q�[���̖���(������)
	inputTable_["next"] = {
							{ InputType::keybord, KEY_INPUT_RETURN} ,
							{InputType::gamepad,PAD_INPUT_R } ,//pad��start
							};

	inputTable_["shift"] = {
							{ InputType::keybord, KEY_INPUT_LSHIFT} ,
							{ InputType::keybord, KEY_INPUT_RSHIFT} ,
							};


	inputTable_["pause"] = { 
							{InputType::keybord, KEY_INPUT_P},
							{ InputType::gamepad,PAD_INPUT_L } //pad��select
							};

	//�W�����v
	inputTable_["check"] = {
							{ InputType::keybord, KEY_INPUT_SPACE} ,
							{InputType::gamepad,PAD_INPUT_A} ,//pad��A
							};
	//��
	inputTable_["up"] = {
							{ InputType::keybord, KEY_INPUT_UP} ,
							{InputType::gamepad,PAD_INPUT_UP} ,//pad��A
	};

	//��
	inputTable_["down"] = {
							{ InputType::keybord, KEY_INPUT_DOWN} ,
							{InputType::gamepad,PAD_INPUT_DOWN} ,//pad��A
	};
	//�E
	inputTable_["right"] = {
							{ InputType::keybord, KEY_INPUT_RIGHT} ,
							{InputType::gamepad,PAD_INPUT_RIGHT} ,//pad��A
	};
	//��
	inputTable_["left"] = {
							{ InputType::keybord, KEY_INPUT_LEFT} ,
							{InputType::gamepad,PAD_INPUT_LEFT} ,//pad��A
	};

	currentState_.clear();
	for (const auto& record: inputTable_)
	{
		currentState_[record.first] = false;
	}

	excludeOnCongigList_.reserve(4);
	excludeOnCongigList_.push_back("left");
	excludeOnCongigList_.push_back("right");
	excludeOnCongigList_.push_back("up");
	excludeOnCongigList_.push_back("down");

}

void Input::Update()
{
	//�n�[�h�̓��͎��̂̓`�F�b�N���܂�
	char keycode[256];
	GetHitKeyStateAll(keycode);//�L�[�{�[�h����
	int padInfo = GetJoypadInputState(DX_INPUT_PAD1);//�p�b�h�P�ԓ���
	int mouseInfo = GetMouseInput();//�}�E�X����

	lastState_ = currentState_;//�X�V�O�̏����L�^
	//���ׂĂ̓o�^�ς݂̓��͂��`�F�b�N����
	for (const auto& record : inputTable_)
	{
		bool pressed = false;
		for (const auto& inputInfo : record.second)
		{
			//���͎�ʂɂ�Ē��ו����Ⴄ
			switch (inputInfo.type)
			{
			case InputType::keybord:
				pressed = keycode[inputInfo.inputID];
				break;
			case InputType::gamepad:
				pressed = padInfo &inputInfo.inputID;
				break;
			case InputType::mouse:
				pressed = mouseInfo & inputInfo.inputID;
				break;
			}
			//�P�ł�������Ă����烋�[�v���~�܂�
			if (pressed)//�����厖
			{
				break;
			}
		}
		currentState_[record.first] = pressed;
	}
}

bool Input::IsTriggerd(const std::string& input) const
{

	return !GetLastInput(input) && GetCurrentInput(input);
}

bool Input::IsPrassed(const std::string& input) const
{
	return GetCurrentInput(input);
}

void Input::RewriteInput(const std::string& key, const InputInfo& inputinfo){
	
	auto it = inputTable_.find(key);
	if (it == inputTable_.end())
	{
		assert(0 && "����Ȗ��߂͓o�^����Ă��܂���");
		return;
	}
	for (auto& record : it->second)
	{
		if (inputinfo.type == record.type)
		{
			record.inputID = inputinfo.inputID;
			return;
		}
	}
	//�V�K�o�^
	it->second.push_back(inputinfo);

}

const InputTable_t Input::GetInputTable() const
{
	auto ret = inputTable_;

	for (const auto& ex : excludeOnCongigList_)
	{
		ret.erase(ex);
	}

	return ret;
}
