#pragma once

#include "GLES-Render.h"

class GameWorld;
class Player;

class LevelLayer : public cocos2d::CCLayer {
public:
	LevelLayer();
	virtual ~LevelLayer();

	virtual bool init();
	static cocos2d::CCScene *scene();

	virtual void update(float dt);
	virtual void draw();

	void initPhysics();
	void addNewSpriteAtPosition(cocos2d::CCPoint p);
	virtual void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
	
	// implement the "static node()" method manually
    CREATE_FUNC(LevelLayer);


	int setUserDirection(int argDir);
	int getUserDirection();

private:
	GameWorld *gameWorld;
	Player *player;
	void keyUpdate();

	int m_direction;

};