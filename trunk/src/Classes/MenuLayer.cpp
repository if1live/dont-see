#include "stdafx.h"
#include "MenuLayer.h"
#include "level_layer.h"

#include "SoundManager.h"

using namespace cocos2d;

//const char *mapfile = "tilemap/MAP_1.tmx";
const char *mapfile = "tilemap/MAP_0.tmx";

MenuLayer::~MenuLayer()
{
}

MenuLayer::MenuLayer()
	: m_logoShowingTime(0),
	m_sceneChangeOccur(false),
	btn1(nullptr),
	btn2(nullptr)
{
	SoundManager::sharedManager()->PlayBG(BG_TITLE);
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

	CCSprite* sprite = CCSprite::create("texture/main.png");
	sprite->setPosition(ccp(getContentSize().width/2, getContentSize().height/2));

	this->addChild(sprite);

	btn1 = CCSprite::create("texture/main_bt1.png");
	btn2 = CCSprite::create("texture/main_bt2.png");
	this->addChild(btn1);
	this->addChild(btn2);
	btn1->setVisible(false);
	btn2->setVisible(false);
	
	CCPoint pos = ccp(850, 510);
	btn1->setPosition(pos);
	btn2->setPosition(pos);

	
	return true;
}

void MenuLayer::update(float dt)
{
	m_logoShowingTime += dt;
	if (m_logoShowingTime > 5 && m_sceneChangeOccur == false) {
		m_sceneChangeOccur = true;
		CCDirector* pDirector = CCDirector::sharedDirector();
		
		pDirector->replaceScene(CCTransitionFade::create(0.5, LevelLayer::scene(mapfile)));
		SoundManager::sharedManager()->PlayBG(BG_MAIN);
	}

	if(int(m_logoShowingTime * 2) % 2 == 0) {
		btn1->setVisible(false);
		btn2->setVisible(true);
	} else {
		btn1->setVisible(true);
		btn2->setVisible(false);
	}
}

void MenuLayer::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
	if (!m_sceneChangeOccur) {
		m_sceneChangeOccur = true;

		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->replaceScene(CCTransitionFade::create(0.5, LevelLayer::scene(mapfile)));
		SoundManager::sharedManager()->PlayBG(BG_MAIN);
	}
}