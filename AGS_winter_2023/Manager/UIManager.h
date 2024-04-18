#pragma once
#include "../common/Vector2D.h"

const int VALUE = 6;

enum UIVALUE {
	LEFT,
	RIGHT,
	UP,
	DOWN,
	ENTER,
	SPACE,
};

class UIManager
{
public:
	UIManager();
	~UIManager();
	void Init(void);
	void Update(void);
	void Draw(Vector2D pos,double rate,UIVALUE value);

private:

	//‰æ‘œ
	int leftImg_[VALUE];
	int rightImg_[VALUE];
	int downImg_[VALUE];
	int upImg_[VALUE];
	int spaceImg_[VALUE];
	int enterImg_[VALUE];


	int cnt_;
};

