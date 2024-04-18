#include "TutorialStage.h"
#include "FirstStage.h"
#include "SecondStage.h"
#include "ThirdStage.h"
#include "StageTitleView.h"

StageTitleView::StageTitleView(StageManager& stageMng, Transitor& transit) :Stage(stageMng, transit)
{
	Init();
}

StageTitleView::StageTitleView(StageManager& stageMng, Transitor& transit, int nextStageNum) : Stage(stageMng, transit)
{
	nextStageNum_ = nextStageNum;
	Init();
}

StageTitleView::~StageTitleView(void)
{
}

void StageTitleView::Init(void)
{
	stageTransitor_.Start();

	//描画フレーム数の設定
	titleDrawFrame_ = 60;

	//画像読み込み
	stageTitleImg_[0] = LoadGraph("./Data/Image/ChangeStage/Tutorial.png");
	stageTitleImg_[1] = LoadGraph("./Data/Image/ChangeStage/Stage1.png");
	stageTitleImg_[2] = LoadGraph("./Data/Image/ChangeStage/Stage2.png");
	stageTitleImg_[3] = LoadGraph("./Data/Image/ChangeStage/Stage3.png");
}

void StageTitleView::Update(Input& input)
{
	//描画フレーム数終了後ステージ遷移
	if (--titleDrawFrame_ < 0) {
		//設定されたステージへ遷移
		switch (nextStageNum_)
		{
		case 0:
			stageManager_.ChangeStage(std::make_shared<TutorialStage>(stageManager_, stageTransitor_));
			return;
		case 1:
			stageManager_.ChangeStage(std::make_shared<FirstStage>(stageManager_, stageTransitor_));
			return;
		case 2:
			stageManager_.ChangeStage(std::make_shared<SecondStage>(stageManager_, stageTransitor_));
			return;
		case 3:
			stageManager_.ChangeStage(std::make_shared<ThirdStage>(stageManager_, stageTransitor_));
			return;
		default:
			stageManager_.ChangeStage(std::make_shared<TutorialStage>(stageManager_, stageTransitor_));
			return;
		}
	}

	stageTransitor_.Update();
}

void StageTitleView::Draw(void)
{
	//設定されたステージのタイトル画像を描画
	DrawGraph(0, 0, stageTitleImg_[nextStageNum_], true);

	stageTransitor_.Draw();
}
