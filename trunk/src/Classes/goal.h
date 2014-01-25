#pragma once

#include "TmxObject.h"

class Goal : public TmxObject {
public:
	static Goal* create(cocos2d::CCDictionary *dict);

	Goal(cocos2d::CCDictionary *dict);

	virtual b2Body *createBody();
	virtual void update(float dt);

	void clearGame();

private:
	bool clearCalled;
};