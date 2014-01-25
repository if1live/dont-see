#include "stdafx.h"
#include "player.h"

using namespace cocos2d;

Player::Player(int x, int y)
	: m_x(x), m_y(y)
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

	playerSprite->runAction(cocos2d::CCMoveBy::create(5.0f, cocos2d::CCPoint(m_x, m_y)));


	return true;
}