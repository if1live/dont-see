#include "stdafx.h"
#include "TmxObject.h"
#include "game_world.h"
#include "b2_helper.h"

using namespace cocos2d;

int safeReadIntValue(CCDictionary* dict, const char* key, int defaultValue /* = 0 */)
{
	if (dict == nullptr)
		return defaultValue;
	CCObject* object = dict->objectForKey(key);
	if (object == nullptr)
		return defaultValue;
	return ((CCString*)object)->intValue();
}

std::string safeReadStringValue(CCDictionary* dict, const char* key, const char* defaultValue /* = "" */)
{
	if (dict == nullptr)
		return defaultValue;
	CCObject* object = dict->objectForKey(key);
	if (object == nullptr)
		return defaultValue;
	return ((CCString*)object)->getCString();
}

TmxObject::TmxObject(CCDictionary* dict)
	: m_x(0), m_y(0), m_width(0), m_height(0), m_speed(0), m_body(nullptr)
{
	m_x = safeReadIntValue(dict, "x");
	m_y = safeReadIntValue(dict, "y");
	m_speed = safeReadIntValue(dict, "speed", 10);

	static const char* dummyTexture = "texture/player.png";
	m_textureName = safeReadStringValue(dict, "texture_name", dummyTexture);
	
	m_width = safeReadIntValue(dict, "width");
	m_height = safeReadIntValue(dict, "height");
	m_moveDirection = safeReadIntValue(dict, "dir");
}

TmxObject::~TmxObject()
{
	if(m_body != nullptr) {
		GameWorld::sharedWorld()->b2_world->DestroyBody(m_body);
		m_body = nullptr;
	}
}

bool TmxObject::init()
{
	if(!CCLayer::init()) {
		return false;
	}

	m_sprite = CCSprite::create(m_textureName.c_str());
	this->addChild(m_sprite);

	//TODO tmx 객체 타입에 따라서 다른 box2d 객체를 생성해서 연결해야한다
	
	//box2d 객체도 생성
	b2BodyDef bodyDef;
	bodyDef.position = px_to_mt_pos(ccp(m_x, m_y));
	bodyDef.type = b2_dynamicBody;
	bodyDef.userData = this;

	m_body = GameWorld::sharedWorld()->b2_world->CreateBody(&bodyDef);

	b2CircleShape circle;
	circle.m_radius = px_to_mt_length(20);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;
	fixtureDef.density = 1;
	m_body->CreateFixture(&fixtureDef);


	m_sprite->runAction(cocos2d::CCMoveTo::create(0, cocos2d::CCPoint(m_x, m_y)));

	scheduleUpdate();

	return true;
}
void TmxObject::Move(int dx, int dy, float animDelay /* = 0 */)
{
	if (dx == 0 && dy == 0)
		return;

	//CCLog("%d, %d", m_x, m_y);
	m_x += dx;
	m_y += dy;
	this->runAction(cocos2d::CCMoveTo::create(animDelay, cocos2d::CCPoint(m_x, m_y)));

}
