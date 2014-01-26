#pragma once

#include "GLES-Render.h"
#include "contact_listener.h"

class TmxObject;

class GameWorld {
public:
	//static GameWorld* sharedWorld();

	GameWorld();
	~GameWorld();

	void update(float dt);
	std::vector<TmxObject*> nearBy(const cocos2d::CCPoint center, float minDistance, float maxDistance);

	void addTmxObject(TmxObject *obj);
	void removeTmxObject(TmxObject *obj);

	TmxObject *getObjectByType(int objType);

public:
	GLESDebugDraw debugDraw;
	MyContactListener contactListener;
	b2World *b2_world;

	std::vector<TmxObject*> tmxObjectList;
};