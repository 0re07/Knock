#pragma once
#include "Stage.h"
#include "../SceneManager.h"

class ThirdStage : public Stage
{
public:
    ThirdStage(StageManager& stageMng, Transitor& transit);
    ~ThirdStage(void);
    void Init(void)override;
    void Update(Input& input)override;
    void Draw(void)override;

private:
    void DrawAsteroid(void);

    SceneManager sceneManager_;

    int cnt_;

    //¬˜f¯‘Ñ
    int asteroidBelt_;
    int asteroid_[4];
};

