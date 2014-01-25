#pragma once

#include "TmxObject.h"

class CollisionAnimationObject : public TmxObject {
public:
	static CollisionAnimationObject* create(cocos2d::CCDictionary* dict);

	CollisionAnimationObject(cocos2d::CCDictionary *dict);

	virtual b2Body *createBody();
	virtual void update(float dt);

	void runAnimation();
private:
};