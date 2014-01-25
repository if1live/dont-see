#pragma once

class LevelLayer : public cocos2d::CCLayer {
public:
	virtual bool init();
	static cocos2d::CCScene *scene();

	// implement the "static node()" method manually
    CREATE_FUNC(LevelLayer);
};