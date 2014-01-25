#include "stdafx.h"
#include "text_layer.h"

using namespace cocos2d;

bool TextLayer::init()
{
	if(!CCLayer::init()) {
		return false;
	}

	CCLabelTTF *label = CCLabelTTF::create("test",
                                            "Arial",
                                            18);
	label->setPosition(ccp(0, 768));
	label->setAnchorPoint(ccp(0, 1));
	this->addChild(label);

	return true;
}

void TextLayer::update(float dt)
{
}
