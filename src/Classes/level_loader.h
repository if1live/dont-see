#pragma once

class Player;
class GameWorld;

class LevelLoader {
public:
	LevelLoader(const char *mapfile, cocos2d::CCNode *layer, GameWorld *world);

	cocos2d::CCTMXTiledMap *loadMap();

	void enableTileGrid(cocos2d::CCTMXTiledMap *map);
	Player *registerPlayer(cocos2d::CCTMXTiledMap *map);
	void registerNpc(cocos2d::CCTMXTiledMap *map);
	void registerCollisionBox(cocos2d::CCTMXTiledMap *map);
	void registerAnimate(cocos2d::CCTMXTiledMap *map);
	void registerGoal(cocos2d::CCTMXTiledMap *map);

	void load();

private:
	std::string mapfile;
	cocos2d::CCNode *layer;
	GameWorld *world;
};