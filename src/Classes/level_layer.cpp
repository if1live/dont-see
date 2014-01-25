#include "stdafx.h"
#include "level_layer.h"

using namespace cocos2d;

cocos2d::CCScene *LevelLayer::scene() 
{
	CCScene *scene = CCScene::create();
	CCLayer *layer = LevelLayer::create();
	scene->addChild(layer);
	return scene;
}


bool LevelLayer::init()
{
	if(!CCLayer::init()) {
		return false;
	}

	// create a TMX map
	CCTMXTiledMap *map = CCTMXTiledMap::create("tilemap/desert.tmx");
	this->addChild(map);

	//디버깅용 타일 경계선 그리기
	// All the tiles by default will be aliased. If you want to create anti-alias tiles, you should do:
	// iterate over all the "layers" (atlas sprite managers)
	// and set them as 'antialias' 
	CCArray * pChildrenArray = map->getChildren();
	CCSpriteBatchNode* child = NULL;
	CCObject* pObject = NULL;
	CCARRAY_FOREACH(pChildrenArray, pObject) {
		child = (CCSpriteBatchNode*)pObject;

		if(!child) {
			break;
		}

		child->getTexture()->setAntiAliasTexParameters();
	}
	
	return true;
}
