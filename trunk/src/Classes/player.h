#pragma once

#include "TmxObject.h"

class Player : public TmxObject {
public:
	static Player* create(GameWorld *world, cocos2d::CCDictionary* dict);

	Player(GameWorld *world, cocos2d::CCDictionary* dict);

	virtual void update(float dt);
	virtual b2Body *createBody();

	bool canDamagable();
	void damage();
private:
	float m_movingCool;
	int hp;

	//얻어맞고난뒤 힘세고 강한 시간
	float powerfulTime;
	bool gameOver;

	//애니메이션 2프레임. 야매코딩
	cocos2d::CCSprite *ani_1;
};

