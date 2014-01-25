#include "stdafx.h"
#include "text_layer.h"
#include "game_world.h"
#include "TmxObject.h"

#define FONT_NAME "Arial"
#define FONT_SIZE 18
#define LINE_HEIGHT 30

using namespace cocos2d;

TextLayer::TextLayer()
	: positionLabel(nullptr),
	tileCoordLabel(nullptr)
{
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

	int count = 1;

	positionLabel = CCLabelTTF::create("positon", FONT_NAME, FONT_SIZE);
	positionLabel->setPosition(ccp(0, 768 - count * LINE_HEIGHT));
	positionLabel->setAnchorPoint(ccp(0, 1));
	this->addChild(positionLabel);

	count++;

	tileCoordLabel = CCLabelTTF::create("tile coord", FONT_NAME, FONT_SIZE);
	tileCoordLabel->setPosition(ccp(0, 768 - count * LINE_HEIGHT));
	tileCoordLabel->setAnchorPoint(ccp(0, 1));
	this->addChild(tileCoordLabel);


	return true;
}

void TextLayer::update(float dt)
{
	TmxObject *player = GameWorld::sharedWorld()->getObjectByType(OBJECT_PLAYER);
	assert(player != nullptr);

	CCPoint pos = player->getPosition();
	float tileX = pos.x / 32.0f;
	float tileY = pos.y / 32.0;

	char buffer[256];
	sprintf(buffer, "Pos : %.2f, %.2f", pos.x, pos.y);
	positionLabel->setString(buffer);

	sprintf(buffer, "Tile: %.2f, %.2f", tileX, tileY);
	tileCoordLabel->setString(buffer);
}
