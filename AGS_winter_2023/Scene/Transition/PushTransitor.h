#pragma once
#include "Transitor.h"

class PushTransitor :
    public Transitor
{
private:
	TransitDirection direction_;//プッシュ方向
public:
	//PushTransitor(PushDirection dir = TransitDirection::up, int interval = 60);
	PushTransitor(TransitDirection dir = TransitDirection::up, int interval = 60);
	virtual void Update() override;
	virtual void Draw() override;
};

