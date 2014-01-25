#pragma once

class Player;

class LevelLoader {
public:
	LevelLoader(const char *mapfile, cocos2d::CCNode *layer);

	cocos2d::CCTMXTiledMap *loadMap();

	void enableTileGrid(cocos2d::CCTMXTiledMap *map);
	Player *registerPlayer(cocos2d::CCTMXTiledMap *map);
	void registerNpc(cocos2d::CCTMXTiledMap *map);
	void registerCollisionBox(cocos2d::CCTMXTiledMap *map);

	void load();

private:
	std::string mapfile;
	cocos2d::CCNode *layer;
};