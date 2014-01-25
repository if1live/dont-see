#pragma once

#include "GLES-Render.h"

class GameWorld {
public:
	static GameWorld* sharedWorld() {
		static GameWorld world;
		return &world;
	}

	GameWorld();
	~GameWorld();

	void update(float dt);

public:
	GLESDebugDraw debugDraw;
	b2World *b2_world;
};