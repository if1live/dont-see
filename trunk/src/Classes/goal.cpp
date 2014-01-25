#include "stdafx.h"
#include "goal.h"
#include "game_world.h"
#include "b2_helper.h"

using namespace cocos2d;


Goal* Goal::create(cocos2d::CCDictionary *dict)
{
	Goal *goal = new Goal(dict);
	goal->autorelease();
	return goal;
}

Goal::Goal(cocos2d::CCDictionary *dict)
	: TmxObject(dict, OBJECT_GOAL), clearCalled(false)
{
}

b2Body *Goal::createBody()
{
	b2BodyDef bodyDef;
	bodyDef.position = px_to_mt_pos(ccp(m_x + m_width/2, m_y + m_height/2));
	bodyDef.type = b2_staticBody;
	bodyDef.userData = this;

	b2Body *body = GameWorld::sharedWorld()->b2_world->CreateBody(&bodyDef);

	b2PolygonShape box;
	box.SetAsBox(px_to_mt_length(m_width)/2, px_to_mt_length(m_height)/2);

	b2FixtureDef fixtureDef;
	fixtureDef.isSensor = true;
	fixtureDef.shape = &box;
	body->CreateFixture(&fixtureDef);

	return body;
}


void Goal::update(float dt)
{
	//목적지는 이미지가 따로 없다
	m_sprite->setVisible(false);
}

void Goal::clearGame()
{
	if(clearCalled == false) {
		clearCalled = true;
	}
	printf("clear game");
}