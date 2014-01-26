#include "stdafx.h"
#include "EndingLayer.h"

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

	this->scheduleUpdate();
	setTouchEnabled(true); 

	CCSprite* sprite = CCSprite::create("texture/splash.png");
	sprite->setPosition(ccp(getContentSize().width/2, getContentSize().height/2));

	this->addChild(sprite);
	
	return true;
}

void EndingLayer::update(float dt)
{
}

void EndingLayer::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
	ExitProcess(0);
}