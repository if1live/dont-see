#include "stdafx.h"
#include "EndingLayer.h"
#include "SoundManager.h"
#include "MenuLayer.h"

using namespace cocos2d;

EndingLayer::~EndingLayer()
{
}

EndingLayer::EndingLayer()
	: m_logoShowingTime(0),
	m_sceneChangeOccur(false)
{
}

cocos2d::CCScene *EndingLayer::scene() 
{
	CCScene *scene = CCScene::create();
	CCLayer *layer = EndingLayer::create();
	scene->addChild(layer);
	return scene;
}

bool EndingLayer::init()
{
	if(!CCLayer::init()) {
		return false;
	}
	
	SoundManager::sharedManager()->PlayEffect(EFFECT_ENDING);

	this->scheduleUpdate();
	setTouchEnabled(true); 

	sprite1 = CCSprite::create("texture/ending_1.png");
	sprite1->setPosition(ccp(getContentSize().width/2, getContentSize().height/2));
	this->addChild(sprite1);
	sprite1->setVisible(false);

	sprite2 = CCSprite::create("texture/ending_2.png");
	sprite2->setPosition(ccp(getContentSize().width/2, getContentSize().height/2));
	this->addChild(sprite2);
	sprite2->setVisible(false);

	sprite3 = CCSprite::create("texture/ending_3.png");
	sprite3->setPosition(ccp(getContentSize().width/2, getContentSize().height/2));
	this->addChild(sprite3);
	sprite3->setVisible(false);

	return true;
}

void EndingLayer::update(float dt)
{
	m_logoShowingTime += dt;

	if(m_logoShowingTime > 6) {
		sprite3->setVisible(true);
	} else if(m_logoShowingTime > 3) {
		sprite2->setVisible(true);
	} else {
		sprite1->setVisible(true);
	}

	if(m_logoShowingTime >= 10) {
		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->replaceScene(CCTransitionFade::create(0.5, MenuLayer::scene()));
	}
}

void EndingLayer::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->replaceScene(CCTransitionFade::create(0.5, MenuLayer::scene()));
}