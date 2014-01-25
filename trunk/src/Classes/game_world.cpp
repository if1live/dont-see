#include "stdafx.h"
#include "game_world.h"
#include "VisibleRect.h"

GameWorld::GameWorld()
	: b2_world(nullptr),
	debugDraw(PTM_RATIO)
{

	//물리엔진 초기화
	b2Vec2 gravity;
	gravity.Set(0.0f, 0.0f);
	b2_world = new b2World(gravity);
	b2_world->SetAllowSleeping(true);
	b2_world->SetContinuousPhysics(true);

	uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    //        flags += b2Draw::e_jointBit;
    //        flags += b2Draw::e_aabbBit;
    //        flags += b2Draw::e_pairBit;
    //        flags += b2Draw::e_centerOfMassBit;
    debugDraw.SetFlags(flags);
	b2_world->SetDebugDraw(&debugDraw);
	
	/*
	// Define the ground body.
    b2BodyDef groundBodyDef;
	groundBodyDef.type = b2_staticBody;
    groundBodyDef.position.Set(0, 0); // bottom-left corner
	b2Body* groundBody = b2_world->CreateBody(&groundBodyDef);

	// Define the ground box shape.
    b2EdgeShape groundBox;

    auto visibleRect = VisibleRect::getVisibleRect();
	float left = visibleRect.getMinX() / PTM_RATIO;
	float right = visibleRect.getMaxX() / PTM_RATIO;
	float bottom = visibleRect.getMinY() / PTM_RATIO;
	float top = visibleRect.getMaxY() / PTM_RATIO;
    groundBox.Set(b2Vec2(left, bottom), b2Vec2(right, bottom));
    groundBody->CreateFixture(&groundBox,0);

    // top
    groundBox.Set(b2Vec2(left, top), b2Vec2(right, top));
    groundBody->CreateFixture(&groundBox,0);

    // left
    groundBox.Set(b2Vec2(left, top), b2Vec2(left, bottom));
    groundBody->CreateFixture(&groundBox,0);

    // right
    groundBox.Set(b2Vec2(right, bottom), b2Vec2(right, top));
    groundBody->CreateFixture(&groundBox,0);
	*/
}


GameWorld::~GameWorld()
{
	CC_SAFE_DELETE(b2_world);
}

void GameWorld::update(float dt)
{
	int velocityIterations = 8;
    int positionIterations = 1;
	b2_world->Step(dt, velocityIterations, positionIterations);

}
