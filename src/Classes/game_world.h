#pragma once

#include "GLES-Render.h"

class GameWorld {
public:
	GameWorld();
	~GameWorld();

	void update(float dt);

public:
	GLESDebugDraw debugDraw;
	b2World *b2_world;
};