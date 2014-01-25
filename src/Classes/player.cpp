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
	: TmxObject(dict), m_movingCool(0)
{
}

void Player::update(float dt)
{
	m_movingCool -= dt;
	if (m_movingCool <= 0)
	{
		int dx = 0, dy = 0;
		int keys = KeyboardDevice::sharedDevice()->GetKeys();
		if (keys & KeyW) dy += m_speed;
		if (keys & KeyA) dx -= m_speed;
		if (keys & KeyS) dy -= m_speed;
		if (keys & KeyD) dx += m_speed;

		m_movingCool = 0.3f;
		Move(dx, dy, m_movingCool);
	}
}
