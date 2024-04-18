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
    //�^�C�g���摜
    int stageTitleImg_[4];

    //�^�C�g���\�����߂̃t���[��
    int titleDrawFrame_;
    bool title_;

    //���̃X�e�[�W�̔ԍ�
    int nextStageNum_;

};

