#pragma once
#include<memory>
#include<list>
class Input;
class Stage;

class StageManager
{
public:
	/// <summary>
	/// 先頭の(Updateが呼ばれる)シーンを切り替える
	/// </summary>
	/// <param name="scene">切り替え先のシーン</param>
	void ChangeStage(std::shared_ptr<Stage> scene);
	/// <summary>
	/// スタックの頭のシーンを削除する
	/// ただし、スタック上に１つしかシーンがない場合は
	/// 削除しない
	/// </summary>
	/// <param name="scene"></param>
	/// <summary>
	void PopStage();
	/// シーンをプッシュする。スタックの数が増える
	/// 一番上Updateしか呼ばれません
	/// </summary>
	/// <param name="scene"></param>
	void PushStage(std::shared_ptr<Stage>scene);

	void Init();
	/// <summary>
	/// 持っているシーンのアップデートを呼びさす
	/// </summary>
	/// <param name="input"></param>
	void Update(Input& input);
	void Draw();

	bool EndStage();

private:
	/// <summary>
	/// 
	/// </summary>

	std::list<std::shared_ptr<Stage>> stages_;//現在進行中のステージ
};

