#include "stdafx.h"
#include "text_layer.h"
#include "game_world.h"
#include "TmxObject.h"
#include "player.h"
#include "custom_action.h"

#define FONT_NAME "Arial"
#define FONT_SIZE 18
#define LINE_HEIGHT 30

using namespace cocos2d;

TextLayer::TextLayer()
	: positionLabel(nullptr),
	tileCoordLabel(nullptr),
	customAction(nullptr),
	world(nullptr)
{
	for(int i = 0; i < 3; i++)
		heartSprite[i] = nullptr;

	for(int i = 0; i < 5; i++)
		specialGuage[i] = nullptr;

	specialBase = nullptr;
}

bool TextLayer::init()
{
	if(!CCLayer::init()) {
		return false;
	}
	this->scheduleUpdate();

	CCLabelTTF *label = CCLabelTTF::create("DEBUG",
                                            FONT_NAME,
                                            FONT_SIZE);
	label->setPosition(ccp(0, 768));
	label->setAnchorPoint(ccp(0, 1));
	this->addChild(label);
	label->setVisible(false);

	int count = 1;

	positionLabel = CCLabelTTF::create("positon", FONT_NAME, FONT_SIZE);
	positionLabel->setPosition(ccp(0, 768 - count * LINE_HEIGHT));
	positionLabel->setAnchorPoint(ccp(0, 1));
	this->addChild(positionLabel);
	positionLabel->setVisible(false);

	count++;

	tileCoordLabel = CCLabelTTF::create("tile coord", FONT_NAME, FONT_SIZE);
	tileCoordLabel->setPosition(ccp(0, 768 - count * LINE_HEIGHT));
	tileCoordLabel->setAnchorPoint(ccp(0, 1));
	this->addChild(tileCoordLabel);
	tileCoordLabel->setVisible(false);
	count++;

	hpLabel = CCLabelTTF::create("hp", FONT_NAME, FONT_SIZE);
	hpLabel->setPosition(ccp(0, 768 - count * LINE_HEIGHT));
	hpLabel->setAnchorPoint(ccp(0, 1));
	this->addChild(hpLabel);
	hpLabel->setVisible(false);
	count++;

	availCountLabel = CCLabelTTF::create("Avail Count", FONT_NAME, FONT_SIZE);
	availCountLabel->setPosition(ccp(0, 768 - count * LINE_HEIGHT));
	availCountLabel->setAnchorPoint(ccp(0, 1));
	this->addChild(availCountLabel);
	availCountLabel->setVisible(false);



	for(int i = 0; i < 3; i++)
	{
		heartSprite[i] = CCSprite::create("texture/heart.png");

		heartSprite[i]->setScale(0.1f);

		heartSprite[i]->setPosition(ccp((i + 1) * 35, 600));
		this->addChild(heartSprite[i]);
	}

	specialBase = CCSprite::create("texture/special_base.png");
	specialBase->setPosition(ccp(specialBase->getContentSize().width, 570));
	this->addChild(specialBase);

	for(int i = 0; i < 5; i++)
	{
		specialGuage[i] = CCSprite::create("texture/special_guage.png");
		specialGuage[i]->setPosition(ccp((i + 1) * specialGuage[i]->getContentSize().width, 570));
		this->addChild(specialGuage[i]);
	}

	preHP = 0;
	preSpecialCount = 0;
	return true;
}

void TextLayer::update(float dt)
{
	Player *player = (Player*)world->getObjectByType(OBJECT_PLAYER);
	assert(player != nullptr);

	CCPoint pos = player->getPosition();
	float tileX = pos.x / 32.0f;
	float tileY = pos.y / 32.0;

	char buffer[256];
	sprintf(buffer, "Pos : %.2f, %.2f", pos.x, pos.y);
	positionLabel->setString(buffer);

	sprintf(buffer, "Tile: %.2f, %.2f", tileX, tileY);
	tileCoordLabel->setString(buffer);

	sprintf(buffer, "HP  : %d / %.1f", player->hp, player->powerfulTime);
	hpLabel->setString(buffer);

	sprintf(buffer, "Avail: %d / %.1f", customAction->GetSpecialCount(), customAction->GetSpecialGap());
	availCountLabel->setString(buffer);

	if(preHP != player->hp)
	{
		preHP = player->hp;
		for(int i = 0; i < 3; i++)
		{
			if(i < preHP)
				heartSprite[i]->setVisible(true);
			else
				heartSprite[i]->setVisible(false);
		}
	}

	if(preSpecialCount != customAction->GetSpecialCount())
	{
		preSpecialCount = customAction->GetSpecialCount();
		for(int i = 0; i < 5; i++)
		{
			if(i < preSpecialCount)
				specialGuage[i]->setVisible(true);
			else
				specialGuage[i]->setVisible(false);
		}
	}

}
