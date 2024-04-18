#pragma once
#include "Stage.h"

class FirstStage :
    public Stage
{
public:
    FirstStage(StageManager& stageMng, Transitor& transit);
    ~FirstStage(void);
    void Init(void)override;
    void Update(Input& input)override;
    void Draw(void)override;
    

};

