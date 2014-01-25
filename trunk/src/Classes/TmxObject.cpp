#include "stdafx.h"
#include "TmxObject.h"
#include "game_world.h"

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
	: m_x(0), m_y(0), m_width(0), m_height(0), m_speed(0)
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

bool TmxObject::init()
{
	if(!CCLayer::init()) {
		return false;
	}

	m_sprite = CCSprite::create(m_textureName.c_str());
	this->addChild(m_sprite);

	// Define the dynamic body.
	//Set up a 1m squared box in the physics world
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(m_x/PTM_RATIO, m_y/PTM_RATIO);

	b2Body *body = GameWorld::sharedWorld()->b2_world->CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(.5f, .5f);//These are mid points for our 1m box

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	body->CreateFixture(&fixtureDef);

	m_sprite->runAction(cocos2d::CCMoveTo::create(0, cocos2d::CCPoint(m_x, m_y)));

	scheduleUpdate();

	return true;
}

void TmxObject::Move(int dx, int dy, float animDelay /* = 0 */)
{
	if (dx == 0 && dy == 0)
		return;

	CCLog("%d, %d", m_x, m_y);
	m_x += dx;
	m_y += dy;
	m_sprite->runAction(cocos2d::CCMoveTo::create(animDelay, cocos2d::CCPoint(m_x, m_y)));
}

