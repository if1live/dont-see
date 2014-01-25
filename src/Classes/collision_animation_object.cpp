#include "stdafx.h"
#include "collision_animation_object.h"
#include "game_world.h"
#include "b2_helper.h"
#include "TmxObject.h"

using namespace cocos2d;

CollisionAnimationObject* CollisionAnimationObject::create(cocos2d::CCDictionary* dict)
{
	CollisionAnimationObject* npc = new CollisionAnimationObject(dict);
	npc->autorelease();
	return npc;
}

CollisionAnimationObject::CollisionAnimationObject(cocos2d::CCDictionary *dict)
	: TmxObject(dict, OBJECT_COLLISION_ANIMATION)
{
}

b2Body *CollisionAnimationObject::createBody()
{
	b2BodyDef bodyDef;
	bodyDef.position = px_to_mt_pos(ccp(m_x + 16, m_y + 16));
	bodyDef.type = b2_staticBody;
	bodyDef.userData = this;

	b2Body *body = GameWorld::sharedWorld()->b2_world->CreateBody(&bodyDef);

	b2CircleShape circle;
	circle.m_radius = 0.5f;

	b2FixtureDef fixtureDef;
	fixtureDef.density = 1.0f;
	fixtureDef.shape = &circle;

	body->CreateFixture(&fixtureDef);

	return body;
}
void CollisionAnimationObject::update(float dt)
{
}
