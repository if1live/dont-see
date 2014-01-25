#pragma once


class TextLayer : public cocos2d::CCLayer {
public:
	virtual bool init();
	virtual void update(float dt);

	CREATE_FUNC(TextLayer);
};
