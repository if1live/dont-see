#include "stdafx.h"
#include "player.h"
#include "KeyboardDevice.h"
#include "game_world.h"
#include "b2_helper.h"
#include "action_helper.h"
#include "EndingLayer.h"
#include "MenuLayer.h"
#include "MouseDevice.h"

#define POWERFUL_TIME (1.0f)

using namespace cocos2d;

Player* Player::create(GameWorld *world, cocos2d::CCDictionary* dict)
{
	Player* player = new Player(world, dict);
	player->autorelease();
	return player;
}

Player::Player(GameWorld *world, CCDictionary* dict)
	: TmxObject(world, dict, OBJECT_PLAYER), m_movingCool(0), hp(3), powerfulTime(0), gameOver(false), ani_1(nullptr)
{
	ani_1 = CCSprite::create("texture/walk copy_1.png");
	this->addChild(ani_1);
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
		if (hp > 0) {
			setVelocity(dx, dy);
		}

		if(dx == 0 && dy == 0) {
			ani_1->stopAllActions();
		} else {
			if(ani_1->numberOfRunningActions() == 0) {
				CCAction *act = create_player_animation();
				ani_1->runAction(act);
			}
		}
	}

	if(hp <= 0) {
		//HP가 0이하면 게임이 끝난다
		if (!gameOver) {
			gameOver = true;

			CCDirector* pDirector = CCDirector::sharedDirector();
			//pDirector->replaceScene(CCTransitionFade::create(0.5, EndingLayer::scene()));
			pDirector->replaceScene(CCTransitionFade::create(0.5, MenuLayer::scene()));
		}
	}

	powerfulTime -= dt;
	if(powerfulTime < 0) {
		powerfulTime = 0.0f;
	}

	m_sprite->setVisible(false);

	//처다보는 방향돌리기
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
	ani_1->setRotation(angle);
}

b2Body *Player::createBody()
{
	//box2d 객체도 생성
	b2BodyDef bodyDef;
	bodyDef.position = px_to_mt_pos(ccp(m_x, m_y));
	bodyDef.type = b2_dynamicBody;
	bodyDef.userData = this;

	b2World *b2_world = world->b2_world;
	b2Body *body = b2_world->CreateBody(&bodyDef);

	b2CircleShape circle;
	circle.m_radius = px_to_mt_length(20);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;
	fixtureDef.density = 1;
	body->CreateFixture(&fixtureDef);

	return body;
}

bool Player::canDamagable()
{
	if(powerfulTime <= 0.0f) {
		return true;
	}
	return false;
}

void Player::damage()
{
	powerfulTime = POWERFUL_TIME;
	hp -= 1;
	CCAction *blink = create_blink_animation(POWERFUL_TIME - 0.1f);
	this->runAction(blink);
}