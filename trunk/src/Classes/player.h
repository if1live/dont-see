#pragma once

class Player : public cocos2d::CCLayer {
public:
	Player(int x, int y);
	~Player();

	virtual bool init();

private:
	int m_x, m_y;
};

