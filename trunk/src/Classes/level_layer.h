#pragma once

#include "GLES-Render.h"

class GameWorld;
class Player;
class VisionMask;

class LevelLayer : public cocos2d::CCLayer {
public:
	LevelLayer();

	virtual bool initWithMapfile(const char *mapfile);
	static cocos2d::CCScene *scene(const char *mapfile);

	virtual void update(float dt);
	virtual void draw();

	void initPhysics();
	void initMap(const char *mapfile);

	void addNewSpriteAtPosition(cocos2d::CCPoint p);
	//virtual void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);

	void updateCamera();
	void updateClipper(bool use);
	bool isClipperEnabled();

private:
	Player *player;
	VisionMask *masking;

public:
	cocos2d::CCClippingNode *clipper;
};