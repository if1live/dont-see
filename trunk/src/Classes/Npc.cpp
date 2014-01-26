#include "stdafx.h"
#include "Npc.h"
#include "game_world.h"
#include "b2_helper.h"
#include "action_helper.h"

using namespace cocos2d;

Npc* Npc::create(GameWorld *world, cocos2d::CCDictionary* dict)
{
	Npc* npc = new Npc(world, dict);
	npc->autorelease();
	return npc;
}

Npc::Npc(GameWorld *world, CCDictionary* dict)
	: TmxObject(world, dict, OBJECT_NPC), m_movingCool(0)
{
	attach = CCSprite::create("texture/walk_men_1.png");
	this->addChild(attach);

	CCAction *action = create_ai_animation();
	attach->runAction(action);
}

bool Npc::init()
{
	if (!TmxObject::init())
		return false;

	startPos = ccp(m_x, m_y);
	endPos = ccp(
		startPos.x + m_width,
		startPos.y + m_height);

	m_sprite->setVisible(false);

	return true;
}

void Npc::update(float dt)
{
	m_movingCool -= dt;
	if (m_movingCool <= 0)
	{
		int dx = 0, dy = 0;
		switch (m_moveDirection)
		{
		case 1: dy += m_speed; break;
		case 2: dx -= m_speed; break;
		case 3: dy -= m_speed; break;
		case 4: dx += m_speed; break;
		}

		int px = getPositionX();
		int py = getPositionY();
		if (m_moveDirection == 1 || m_moveDirection == 3) {
			if (px != startPos.x && std::abs(px - startPos.x) > 16) {
				dx = px > startPos.x ? -1 * m_speed : m_speed;
			}
		}
		if (m_moveDirection == 2 || m_moveDirection == 4) {
			if (py != startPos.y && std::abs(py - startPos.y) > 16) {
				dy = py > startPos.y ? -1 * m_speed : m_speed;
			}
		}

		m_movingCool = 0.3f;
		setVelocity(dx, dy);

		const CCPoint& currPos = getPosition();
		if (m_moveDirection == 1 && currPos.y > endPos.y) m_moveDirection = 3;
		if (m_moveDirection == 2 && currPos.x < startPos.x) m_moveDirection = 4;
		if (m_moveDirection == 3 && currPos.y < startPos.y) m_moveDirection = 1;
		if (m_moveDirection == 4 && currPos.x > endPos.x) m_moveDirection = 2;
	}


	//속도를 이동방향으로 갖다쓰기
	b2Vec2 dir = m_body->GetLinearVelocity();
	float rad = atan2(dir.x, dir.y);
	attach->setRotation(CC_RADIANS_TO_DEGREES(rad));
}

b2Body *Npc::createBody()
{
	//box2d 객체도 생성
	b2BodyDef bodyDef;
	bodyDef.position = px_to_mt_pos(ccp(m_x, m_y));
	bodyDef.type = b2_dynamicBody;
	bodyDef.userData = this;

	b2Body *body = world->b2_world->CreateBody(&bodyDef);

	b2CircleShape circle;
	circle.m_radius = px_to_mt_length(20);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;
	fixtureDef.density = 1;
	body->CreateFixture(&fixtureDef);

	return body;
}