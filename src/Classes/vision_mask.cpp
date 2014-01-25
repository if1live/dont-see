#include "stdafx.h"
#include "vision_mask.h"
#include "MouseDevice.h"
#include "KeyboardDevice.h"
#include <cmath>

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
	lightMasking = CCSprite::create("texture/mask_3.png");
	
	this->addChild(centerMasking);
	this->addChild(lightMasking);
	
	//auto rect = CCDirector::sharedDirector()->getWinSize();
	//CCPoint center(rect.width / 2, rect.height / 2);
	//centerMasking->setPosition(center);
	//lightMasking->setPosition(center);

	enableLight(lightEnabled);

	return true;
}

void VisionMask::Update()
{
	POINT p = MouseDevice::sharedDevice()->GetMousePos();
	float angle = 0;
	if(p.x < 0)
	{
		angle = atan(float(p.y)/p.x * -1) * 180 / M_PI;
		angle += 270;
	}
	else
	{
		angle = atan(float(p.y)/p.x * -1) * 180 / M_PI;
		angle += 90;
	}
	centerMasking->setRotation(angle);
	lightMasking->setRotation(angle);
	//CCLOG("%f", angle);


	int keys = KeyboardDevice::sharedDevice()->GetKeys();

	if(keys & KeyRButton)
	{
		enableLight(true);
	}
	else
	{
		enableLight(false);
	}
	return;
}