#include "stdafx.h"
#include "player.h"
#include "KeyboardDevice.h"

using namespace cocos2d;

Player* Player::create(cocos2d::CCDictionary* dict)
{
	Player* player = new Player(dict);
	player->autorelease();
	return player;
}

Player::Player(CCDictionary* dict)
	: m_x(0), m_y(0), m_movingCool(0)
{
	if (dict != nullptr)
	{
		m_x = ((CCString*)dict->objectForKey("x"))->intValue();
		m_y = ((CCString*)dict->objectForKey("y"))->intValue();
	}
}

Player::~Player()
{
}

bool Player::init()
{
	if(!CCLayer::init()) {
		return false;
	}

	playerSprite = CCSprite::create("texture/player.png");
	this->addChild(playerSprite);

	playerSprite->runAction(cocos2d::CCMoveBy::create(0, cocos2d::CCPoint(m_x, m_y)));

	scheduleUpdate();

	return true;
}

void Player::update(float dt)
{
	m_movingCool -= dt;
	if (m_movingCool <= 0)
	{
		int dx = 0, dy = 0;
		int keys = KeyboardDevice::sharedDirector()->GetKeys();
		if (keys & KeyW) dy += 10; 
		if (keys & KeyA) dx -= 10; 
		if (keys & KeyS) dy -= 10; 
		if (keys & KeyD) dx += 10; 

		m_movingCool = 0.3f;
		Move(dx, dy, m_movingCool);
	}
}

void Player::Move(int dx, int dy, float animDelay /* = 0 */)
{
	if (dx == 0 && dy == 0)
		return;

	m_x += dx;
	m_y += dy;
	playerSprite->runAction(cocos2d::CCMoveTo::create(animDelay, cocos2d::CCPoint(m_x, m_y)));
}

