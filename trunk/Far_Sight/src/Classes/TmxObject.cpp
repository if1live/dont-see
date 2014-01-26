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

float safeReadFloatValue(CCDictionary* dict, const char* key, float defaultValue /* = 0 */)
{
	if (dict == nullptr)
		return defaultValue;
	CCObject* object = dict->objectForKey(key);
	if (object == nullptr)
		return defaultValue;
	return ((CCString*)object)->floatValue();
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

TmxObject::TmxObject(GameWorld *world, CCDictionary* dict, int objType)
	: m_x(0), m_y(0), m_width(0), m_height(0), m_speed(0), m_body(nullptr), m_objType(objType), world(world)
{
	m_x = safeReadIntValue(dict, "x");
	m_y = safeReadIntValue(dict, "y");
	m_speed = safeReadIntValue(dict, "speed", 100);

	static const char* dummyTexture = "texture/player.png";
	m_textureName = safeReadStringValue(dict, "texture_name", dummyTexture);
	
	m_width = safeReadIntValue(dict, "width");
	m_height = safeReadIntValue(dict, "height");
	m_moveDirection = safeReadIntValue(dict, "dir");
}

TmxObject::~TmxObject()
{
	if(m_body != nullptr) {
		world->b2_world->DestroyBody(m_body);
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

	m_body = createBody();

	scheduleUpdate();

	return true;
}

void TmxObject::setVelocity(float x, float y)
{
	b2Vec2 mt_vec = px_to_mt_pos(ccp(x, y));
	m_body->SetLinearVelocity(mt_vec);
}

bool TmxObject::noiseable()
{
	switch(m_objType) {
	case OBJECT_GOAL:
	case OBJECT_COLLISION_ANIMATION:
	case OBJECT_PLAYER:
		return false;
	case OBJECT_NPC:
		return true;
	default:
		assert(false);
	}
	return false;
}