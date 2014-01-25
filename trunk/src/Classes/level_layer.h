#pragma once

#include "GLES-Render.h"

class GameWorld;
class Player;
class VisionMask;
class TmxObject;

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

	void updateSound(float dt);

private:
	Player *player;
	VisionMask *masking;
	float soundTick;
	
	typedef std::map<TmxObject*, std::pair<cocos2d::CCSprite*, cocos2d::CCAction*>> SoundEffectObjectMap;
	SoundEffectObjectMap soundEffectObjectMap;

public:
	cocos2d::CCClippingNode *clipper;
	cocos2d::CCLayer *soundLayer;
};