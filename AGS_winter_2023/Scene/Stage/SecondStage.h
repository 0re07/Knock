#pragma once
#include "Stage.h"

class Camera;

class SecondStage :
    public Stage
{
public:
    SecondStage(StageManager& stageMng, Transitor& transit);
    ~SecondStage(void);
    void Init(void)override;
    void Update(Input& input)override;
    void Draw(void)override;

private:
    std::unique_ptr<Camera> camera_;

    int backMaskImg_;
};

