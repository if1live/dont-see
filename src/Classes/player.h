#pragma once

class Player : public cocos2d::CCLayer {
public:
	static Player* create(cocos2d::CCDictionary* dict);

	Player(cocos2d::CCDictionary* dict);
	~Player();

	virtual bool init();
	virtual void update(float dt);
	void Move(int dx, int dy, float animDelay = 0.0f);

private:
	cocos2d::CCSprite *playerSprite;
	int m_x, m_y;
	float m_movingCool;
};

