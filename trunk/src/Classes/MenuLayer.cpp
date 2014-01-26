#include "stdafx.h"
#include "MenuLayer.h"
#include "level_layer.h"

using namespace cocos2d;

MenuLayer::~MenuLayer()
{
}

MenuLayer::MenuLayer()
	: m_logoShowingTime(0),
	m_sceneChangeOccur(false)
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
	setTouchEnabled(true); 

	CCSprite* sprite = CCSprite::create("texture/splash.png");
	sprite->setPosition(ccp(getContentSize().width/2, getContentSize().height/2));

	this->addChild(sprite);
	
	return true;
}

void MenuLayer::update(float dt)
{
	m_logoShowingTime += dt;
	if (m_logoShowingTime > 5 && m_sceneChangeOccur == false) {
		m_sceneChangeOccur = true;
		CCDirector* pDirector = CCDirector::sharedDirector();
		//const char *mapfile = "tilemap/MAP_1.tmx";
		const char *mapfile = "tilemap/MAP_0.tmx";
		pDirector->replaceScene(CCTransitionFade::create(0.5, LevelLayer::scene(mapfile)));
	}
}

void MenuLayer::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
	if (!m_sceneChangeOccur) {
		m_sceneChangeOccur = true;

		CCDirector* pDirector = CCDirector::sharedDirector();
		const char *mapfile = "tilemap/MAP_0.tmx";
		pDirector->replaceScene(CCTransitionFade::create(0.5, LevelLayer::scene(mapfile)));
	}
}