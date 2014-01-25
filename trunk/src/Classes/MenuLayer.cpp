#include "stdafx.h"
#include "MenuLayer.h"
#include "level_layer.h"

using namespace cocos2d;

MenuLayer::~MenuLayer()
{
}

MenuLayer::MenuLayer()
	: m_logoShowingTime(0)
{
}

cocos2d::CCScene *MenuLayer::scene() 
{
	CCScene *scene = CCScene::create();
	CCLayer *layer = MenuLayer::create();
	scene->addChild(layer);
	return scene;
}

bool MenuLayer::init()
{
	if(!CCLayer::init()) {
		return false;
	}

	this->scheduleUpdate();

	CCSprite* sprite = CCSprite::create("texture/splash.png");
	sprite->setPosition(ccp(getContentSize().width/2, getContentSize().height/2));

	this->addChild(sprite);

	return true;
}

void MenuLayer::update(float dt)
{
	m_logoShowingTime += dt;
	if (m_logoShowingTime > 3) {
		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->replaceScene(CCTransitionFade::create(0.5, LevelLayer::scene()));
	}
}
