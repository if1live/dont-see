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

	for(int i = 0 ; i < 12 ; i++) {
		char buf[256];
		sprintf(buf, "texture/ending_%d.png", i+1);
		spriteList[i] = CCSprite::create(buf);
		spriteList[i]->setPosition(ccp(getContentSize().width/2, getContentSize().height/2));
		this->addChild(spriteList[i]);
		spriteList[i]->setVisible(false);
	}

	return true;
}

void EndingLayer::update(float dt)
{
	m_logoShowingTime += dt;

	int spriteIndex = (int)m_logoShowingTime;
	if(spriteIndex >= 12) {
		spriteIndex = 11;
	}
	spriteList[spriteIndex]->setVisible(true);

	if(m_logoShowingTime >= 12) {
		CCDirector* pDirector = CCDirector::sharedDirector();
		pDirector->replaceScene(CCTransitionFade::create(0.5, MenuLayer::scene()));
	}
}

void EndingLayer::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->replaceScene(CCTransitionFade::create(0.5, MenuLayer::scene()));
}