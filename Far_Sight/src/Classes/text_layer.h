#pragma once

class Custom_action;
class GameWorld;

class TextLayer : public cocos2d::CCLayer {
public:
	TextLayer();
	virtual bool init();
	virtual void update(float dt);

	CREATE_FUNC(TextLayer);

	cocos2d::CCLabelTTF *positionLabel;
	cocos2d::CCLabelTTF *tileCoordLabel;
	cocos2d::CCLabelTTF *hpLabel;
	cocos2d::CCLabelTTF *availCountLabel;

	Custom_action *customAction;
	GameWorld *world;

	cocos2d::CCSprite *heartSprite[3];
	cocos2d::CCSprite *specialGuage[5];
	cocos2d::CCSprite *specialBase;

	int preHP;
	int preSpecialCount;
};
