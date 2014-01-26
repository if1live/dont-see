#pragma once

#include "GLES-Render.h"

class MenuLayer : public cocos2d::CCLayer {
public:
	MenuLayer();
	virtual ~MenuLayer();

	virtual bool init();
	static cocos2d::CCScene *scene();

	virtual void update(float dt);
	virtual void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);

	// implement the "static node()" method manually
    CREATE_FUNC(MenuLayer);

private:
	cocos2d::CCSprite *btn1;
	cocos2d::CCSprite *btn2;
	
	float m_logoShowingTime;
	bool m_sceneChangeOccur;
};