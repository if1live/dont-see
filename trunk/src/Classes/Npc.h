#pragma once

#include "TmxObject.h"

class Npc : public TmxObject {
public:
	static Npc* create(cocos2d::CCDictionary* dict);

	Npc(cocos2d::CCDictionary* dict);

	virtual bool init();
	virtual void update(float dt);

	virtual b2Body *createBody();

private:
	float m_movingCool;

	int m_startX; int m_endX;
	int m_startY; int m_endY;
};

