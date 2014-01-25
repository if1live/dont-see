#pragma once


class TextLayer : public cocos2d::CCLayer {
public:
	TextLayer();
	virtual bool init();
	virtual void update(float dt);

	CREATE_FUNC(TextLayer);

	cocos2d::CCLabelTTF *positionLabel;
	cocos2d::CCLabelTTF *tileCoordLabel;
};
