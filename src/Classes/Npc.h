#pragma once

#include "TmxObject.h"

class Npc : public TmxObject {
public:
	static Npc* create(GameWorld *world, cocos2d::CCDictionary* dict);

	Npc(GameWorld *world, cocos2d::CCDictionary* dict);

	virtual bool init();
	virtual void update(float dt);

	virtual b2Body *createBody();

private:
	float m_movingCool;

	cocos2d::CCPoint startPos, endPos;
};

