#include "stdafx.h"
#include "vision_mask.h"
#include "MouseDevice.h"
#include "KeyboardDevice.h"
#include <cmath>
#include "custom_action.h"

const float lightEnabledTime = 5.0f;

using namespace cocos2d;

VisionMask::VisionMask()
	: centerMasking(nullptr),
	lightMasking(nullptr),
	lightEnabled(false),
	customAction(nullptr),
	lightTime(0)
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
		lightTime = lightEnabledTime;
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
		if(lightEnabled == false && customAction->GetSpecialCount() > 0) {
			enableLight(true);
			customAction->specialCount -= 1;
		}
	}
	else
	{
		enableLight(false);
	}

	lightTime -= 1/60.0f;
	if(lightTime < 0 && lightEnabled == true) {
		enableLight(false);
	}

	return;
}