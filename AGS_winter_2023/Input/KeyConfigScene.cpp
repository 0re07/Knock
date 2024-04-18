#include "KeyConfigScene.h"
#include"../Input.h"
#include"../Scene/SceneManager.h"
#include"StringUtility.h"
#include<DxLib.h>

void KeyConfigScene::CreateCommandStringList(const InputTable_t& table)
{
	commandStringList.clear();
	commandStringList.reserve(table.size());
	for (const auto& record : table)
	{
		commandStringList.push_back(
			std::make_pair(
				record.first,
				StringUtility::StringToWstring(record.first)
			));
	}
}

KeyConfigScene::KeyConfigScene(SceneManager& manager, Transitor& transit) :Scene(manager, transit)
{
}

void KeyConfigScene::Update(Input& input)
{
	if (inputTable_.empty())
	{
		inputTable_ = input.GetInputTable();
		CreateCommandStringList(inputTable_);
	}

	if (inputTable_.empty())
	{
		inputTable_ = input.GetInputTable();
	}

	if (input.IsTriggerd("keyconfig"))
	{
		sceneManager_.PopScene();
	}
	else
	{
		if (input.IsPrassed("keyconfig"))
		{
			return;
		}
		char keycode[255]={};
		int pad = GetJoypadInputState(DX_INPUT_PAD1);
		int mouse = GetMouseInput();
		int pressedKeycode = -1;
		for (int i = 0; i < 255; ++i)
		{
			if (keycode[i])
			{
				pressedKeycode = i;
				break;
			}
		}

		if (pressedKeycode!=-1)
		{
			InputInfo info = { InputType::keybord,pressedKeycode };
			input.RewriteInput("jump", info);
		}
		else if (pad)
		{
			InputInfo info = { InputType::gamepad,pad };
			input.RewriteInput("jump", info);
		}
		else if (mouse)
		{
			InputInfo info = { InputType::mouse,mouse };
			input.RewriteInput("jump", info);
		}
	}
}

void KeyConfigScene::Draw()
{
	//地の色
	DrawBox(0, 0, 640, 480, 0x0088ee, true);
	//白枠
	DrawBox(0, 0, 640, 480, 0xffffff, false);


	//LoadGraph(L"nn.png");
	DrawString(10, 10, "キーコンフィグ", 0xffffff, true);

	int y = 30;
	for (const auto& pair : commandStringList)
	{
		//DrawFormatStringのためにワイド文字列に変換する
		//なので、ベクタをwstringにしておく
		DrawFormatString(50, y, 0xffffff,
				"コマンド%s", pair.second.c_str());
		y += 20;

		auto& record = inputTable_[pair.first];
		int x = 60;
		for (const auto& inputInfo : record)
		{
			std::wstring strKey = L"";
			switch (inputInfo.type) {
			case InputType::keybord:
				if (KEY_INPUT_A <= inputInfo.inputID && inputInfo.inputID <= KEY_INPUT_Z) 
				{
					char al = 'A' + inputInfo.inputID - KEY_INPUT_A;
					std::string str;
					str += al;
					strKey= StringUtility::StringToWstring(str);
					DrawFormatString(60, y, 0xffffff,
						"keyBD=%2x", strKey);

				}
				else 
				{
					DrawFormatString(60, y, 0xffffff,
							"keyBD=%2x",inputInfo.inputID );
				}
				break;
			case InputType::gamepad:
				DrawFormatString(60, y, 0xffffff,
					"GamePad=%2x", inputInfo.inputID);
				break;
			case InputType::mouse:
				DrawFormatString(60, y, 0xffffff,
					"Mouse=%2x", inputInfo.inputID);
				break;
			}
		}

		y += 25;

	}
}
