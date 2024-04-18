#pragma once
#include "Stage.h"

class StageTitleView :
    public Stage
{
public:
    StageTitleView(StageManager& stageMng, Transitor& transit);
    StageTitleView(StageManager& stageMng, Transitor& transit,int nextStageNum);
    ~StageTitleView(void);
    void Init(void)override;
    void Update(Input& input)override;
    void Draw(void)override;

private:
    //タイトル画像
    int stageTitleImg_[4];

    //タイトル表示ためのフレーム
    int titleDrawFrame_;
    bool title_;

    //次のステージの番号
    int nextStageNum_;

};

