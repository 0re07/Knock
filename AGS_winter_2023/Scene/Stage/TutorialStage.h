#pragma once
#include "Stage.h"

class TutorialStage :
    public Stage
{
public:
    TutorialStage(StageManager& stageMng, Transitor& transit);
    ~TutorialStage(void);
    void Init(void)override;
    void Update(Input& input)override;
    void Draw(void)override;

};

