#include "stdafx.h"
#include "player.h"

using namespace cocos2d;

Player::Player()
{
}

Player::~Player()
{
}

bool Player::init()
{
	if(!CCLayer::init()) {
		return false;
	}

	CCSprite *playerSprite = CCSprite::create("texture/player.png");
	this->addChild(playerSprite);

	playerSprite->runAction(cocos2d::CCMoveBy::create(5.0f, cocos2d::CCPoint(100, 100)));


	return true;
}