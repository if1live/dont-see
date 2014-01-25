#include "stdafx.h"
#include "Npc.h"

using namespace cocos2d;

Npc* Npc::create(cocos2d::CCDictionary* dict)
{
	Npc* npc = new Npc(dict);
	npc->autorelease();
	return npc;
}

Npc::Npc(CCDictionary* dict)
	: m_x(0), m_y(0)
{
	if (dict != nullptr)
	{
		m_x = ((CCString*)dict->objectForKey("x"))->intValue();
		m_y = ((CCString*)dict->objectForKey("y"))->intValue();
	}
}

Npc::~Npc()
{
}

bool Npc::init()
{
	if(!CCLayer::init()) {
		return false;
	}

	CCSprite *npcSprite = CCSprite::create("texture/npc.png");
	this->addChild(npcSprite);

	// npcSprite->runAction(cocos2d::CCMoveTo::create(5.0f, cocos2d::CCPoint(m_x, m_y)));

	return true;
}