#include "stdafx.h"
#include "collision_animation_object.h"
#include "game_world.h"
#include "b2_helper.h"
#include "TmxObject.h"
#include "action_helper.h"
#include "SoundManager.h"

using namespace cocos2d;

CollisionAnimationObject* CollisionAnimationObject::create(GameWorld *world, cocos2d::CCDictionary* dict)
{
	CollisionAnimationObject* npc = new CollisionAnimationObject(world, dict);
	npc->autorelease();
	return npc;
}

CollisionAnimationObject::CollisionAnimationObject(GameWorld *world, cocos2d::CCDictionary *dict)
	: TmxObject(world, dict, OBJECT_COLLISION_ANIMATION)
{
}

b2Body *CollisionAnimationObject::createBody()
{
	b2BodyDef bodyDef;
	bodyDef.position = px_to_mt_pos(ccp(m_x + 16, m_y + 16));
	bodyDef.type = b2_staticBody;
	bodyDef.userData = this;

	b2Body *body = world->b2_world->CreateBody(&bodyDef);

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

void CollisionAnimationObject::runAnimation()
{
	if(m_textureName == "texture\\fire.png") {
		CCAction *act = create_fire_animation();
		m_sprite->runAction(act);

		SoundManager::sharedManager()->PlayEffect(EFFECT_WATER);
	}

	if(m_textureName == "texture\\trash.png") {
		int mode = rand() % 2;
		CCAction *act = create_trash_animation(mode);
		m_sprite->runAction(act);

		//¾²·¹±âÅë ¾þ´Â ¼Ò¸®
		//¾þÀº ¾²·¹±âÅëÀ» ¶Ç °È¾îÂ÷´Â¼À Ä¡°í ³ÀµÐ´Ù
		SoundManager::sharedManager()->PlayEffect(EFFECT_TRASH_CRASH);
	}
}