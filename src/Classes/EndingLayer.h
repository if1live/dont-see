#pragma once

#include "GLES-Render.h"

class EndingLayer : public cocos2d::CCLayer {
public:
	EndingLayer();
	virtual ~EndingLayer();

	virtual bool init();
	static cocos2d::CCScene *scene();

	virtual void update(float dt);
	virtual void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);

	// implement the "static node()" method manually
    CREATE_FUNC(EndingLayer);

private:
	float m_logoShowingTime;
	bool m_sceneChangeOccur;

	cocos2d::CCSprite *sprite1;
	cocos2d::CCSprite *sprite2;
	cocos2d::CCSprite *sprite3;

};