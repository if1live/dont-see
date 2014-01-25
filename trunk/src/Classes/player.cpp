#include "stdafx.h"
#include "player.h"
#include "KeyboardDevice.h"
#include "game_world.h"
#include "b2_helper.h"

using namespace cocos2d;

Player* Player::create(cocos2d::CCDictionary* dict)
{
	Player* player = new Player(dict);
	player->autorelease();
	return player;
}

Player::Player(CCDictionary* dict)
	: TmxObject(dict, OBJECT_PLAYER), m_movingCool(0)
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
		//Move(dx, dy, m_movingCool);
		setVelocity(dx, dy);
	}
}

b2Body *Player::createBody()
{
	//box2d °´Ã¼µµ »ý¼º
	b2BodyDef bodyDef;
	bodyDef.position = px_to_mt_pos(ccp(m_x, m_y));
	bodyDef.type = b2_dynamicBody;
	bodyDef.userData = this;

	b2Body *body = GameWorld::sharedWorld()->b2_world->CreateBody(&bodyDef);

	b2CircleShape circle;
	circle.m_radius = px_to_mt_length(20);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;
	fixtureDef.density = 1;
	body->CreateFixture(&fixtureDef);

	return body;
}