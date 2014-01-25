#pragma once

#include "GLES-Render.h"
#include "contact_listener.h"

class TmxObject;

class GameWorld {
public:
	static GameWorld* sharedWorld() {
		static GameWorld world;
		return &world;
	}

	GameWorld();
	~GameWorld();

	void update(float dt);

	void addTmxObject(TmxObject *obj);
	void removeTmxObject(TmxObject *obj);

	TmxObject *getObjectByType(int objType);

public:
	GLESDebugDraw debugDraw;
	MyContactListener contactListener;
	b2World *b2_world;

	std::vector<TmxObject*> tmxObjectList;
};