#include "stdafx.h"
#include "game_world.h"
#include "VisibleRect.h"
#include "TmxObject.h"
#include "b2_helper.h"

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

	
	b2_world->SetContactListener(&contactListener);

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
	for(int i = 0 ; i < tmxObjectList.size() ; i++) {
		auto obj = tmxObjectList[i];
		obj->m_body = nullptr;
	}

	CC_SAFE_DELETE(b2_world);
}

void GameWorld::update(float dt)
{
	int velocityIterations = 8;
    int positionIterations = 1;
	b2_world->Step(dt, velocityIterations, positionIterations);


	for(int i = 0 ; i < tmxObjectList.size() ; ++i) {
		TmxObject *obj = tmxObjectList[i];
		b2Vec2 mt_pos = obj->m_body->GetPosition();
		CCPoint px_pos = mt_to_px_pos(mt_pos);
		obj->setPosition(px_pos);
	}
}

std::vector<TmxObject*> GameWorld::nearBy(const CCPoint center, float minDistance, float maxDistance)
{
	std::vector<TmxObject*> objects;
	for (auto it = tmxObjectList.begin(); it != tmxObjectList.end(); ++it) {
		TmxObject* object = (*it);
		b2Vec2 mt_pos = object->m_body->GetPosition();
		CCPoint px_pos = mt_to_px_pos(mt_pos);
		float distance = center.getDistance(px_pos);
		if (minDistance <= distance && distance <= maxDistance) {
			objects.push_back(object);
		}
	}
	return objects;
}

void GameWorld::addTmxObject(TmxObject *obj)
{
	tmxObjectList.push_back(obj);
}

void GameWorld::removeTmxObject(TmxObject *obj)
{
	auto it = std::find(std::begin(tmxObjectList), std::end(tmxObjectList), obj);
	if (it != tmxObjectList.end())
		tmxObjectList.erase(it);
}

TmxObject *GameWorld::getObjectByType(int objType)
{
	for(size_t i = 0 ; i < tmxObjectList.size() ; ++i) {
		TmxObject *obj = tmxObjectList[i];
		if(obj->m_objType == objType) {
			return obj;
		}
	}
	return nullptr;
}