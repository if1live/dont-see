#pragma once

#include "GLES-Render.h"

class MenuLayer : public cocos2d::CCLayer {
public:
	MenuLayer();
	virtual ~MenuLayer();

	virtual bool init();
	static cocos2d::CCScene *scene();

	virtual void update(float dt);

	// implement the "static node()" method manually
    CREATE_FUNC(MenuLayer);

private:
	float m_logoShowingTime;
	bool m_sceneChangeOccur;
};