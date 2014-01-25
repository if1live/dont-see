#include "stdafx.h"
#include "vision_mask.h"

using namespace cocos2d;

VisionMask::VisionMask()
	: centerMasking(nullptr),
	lightMasking(nullptr),
	lightEnabled(true)
{
}

VisionMask::~VisionMask()
{
}

void VisionMask::enableLight(bool light)
{
	lightEnabled = light; 
	if(light) {
		centerMasking->setVisible(false);
		lightMasking->setVisible(true);
	} else {
		centerMasking->setVisible(true);
		lightMasking->setVisible(false);
	}
}

bool VisionMask::init()
{
	if(!CCLayer::init()) {
		return false;
	}

	centerMasking = CCSprite::create("texture/mask_default.png");
	lightMasking = CCSprite::create("texture/mask_default.png");

	this->addChild(centerMasking);
	this->addChild(lightMasking);

	//auto rect = CCDirector::sharedDirector()->getWinSize();
	//CCPoint center(rect.width / 2, rect.height / 2);
	//centerMasking->setPosition(center);
	//lightMasking->setPosition(center);

	enableLight(lightEnabled);

	return true;
}
