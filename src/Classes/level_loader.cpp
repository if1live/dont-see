#include "stdafx.h"
#include "level_loader.h"
#include "TmxObject.h"
#include "player.h"
#include "game_world.h"
#include "Npc.h"
#include "b2_helper.h"
#include "collision_animation_object.h"
#include "goal.h"

using namespace cocos2d;

LevelLoader::LevelLoader(const char *mapfile, cocos2d::CCNode *layer, GameWorld *world)
	: mapfile(mapfile),
	layer(layer),
	world(world)
{
	
}


CCTMXTiledMap *LevelLoader::loadMap()
{
	// create a TMX map
	CCTMXTiledMap *map = CCTMXTiledMap::create(mapfile.data());
	layer->addChild(map, -1);
	return map;
}

void LevelLoader::enableTileGrid(CCTMXTiledMap *map)
{
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
}

Player *LevelLoader::registerPlayer(cocos2d::CCTMXTiledMap *map)
{
	//플레이어 추가
	std::vector<CCDictionary*> dicts;
	CCTMXObjectGroup* group = map->objectGroupNamed("objects");
	if (group != nullptr) {
		CCArray* array = group->getObjects();
		CCObject* object;
		CCARRAY_FOREACH(array, object) {
			CCDictionary* dict = (CCDictionary*)object;
			CCString* type = (CCString*)dict->objectForKey("type");

			std::string typeValue = safeReadStringValue(dict, "type");
			if (typeValue == "player") {
				dicts.push_back(dict);
			}
		}
	}
	CCDictionary* dict = nullptr;
	if (!dicts.empty()) {
		std::random_shuffle(dicts.begin(), dicts.end());
		dict = dicts.front();
	}

	Player *player = Player::create(world, dict);
	player->init();
	layer->addChild(player, -1);
	world->addTmxObject(player);
	return player;
}

void LevelLoader::registerNpc(cocos2d::CCTMXTiledMap *map)
{
	CCDictionary* dict = nullptr;
	CCTMXObjectGroup* group = map->objectGroupNamed("objects");

	//Npc 추가
	if (group != nullptr) {
		CCArray* array = group->getObjects();
		CCObject* object;
		CCARRAY_FOREACH(array, object) {
			CCDictionary* dict = (CCDictionary*)object;
			CCString* type = (CCString*)dict->objectForKey("type");

			std::string typeValue = safeReadStringValue(dict, "type");
			if (typeValue == "npc") {
				Npc* npc = Npc::create(world, dict);
				npc->init();
				layer->addChild(npc);
				world->addTmxObject(npc);
			}
		}
	}
}

void LevelLoader::registerGoal(cocos2d::CCTMXTiledMap *map)
{
	CCDictionary* dict = nullptr;
	CCTMXObjectGroup* group = map->objectGroupNamed("objects");

	//Npc 추가
	if (group != nullptr) {
		CCArray* array = group->getObjects();
		CCObject* object;
		CCARRAY_FOREACH(array, object) {
			CCDictionary* dict = (CCDictionary*)object;
			CCString* type = (CCString*)dict->objectForKey("type");

			std::string typeValue = safeReadStringValue(dict, "type");
			if (typeValue == "goal") {
				Goal* goal = Goal::create(world, dict);
				goal->init();
				layer->addChild(goal);
				world->addTmxObject(goal);
			}
		}
	}
}

void LevelLoader::registerCollisionBox(cocos2d::CCTMXTiledMap *map)
{
	CCTMXObjectGroup* group = map->objectGroupNamed("collisions");
	if (group != nullptr) {
		CCArray* array = group->getObjects();
		CCObject* object;
		CCARRAY_FOREACH(array, object) {
			CCDictionary* dict = (CCDictionary*)object;
			float x = safeReadFloatValue(dict, "x");
			float y = safeReadFloatValue(dict, "y");
			float width = safeReadFloatValue(dict, "width");
			float height = safeReadFloatValue(dict, "height");

			//box2d 객체도 생성
			b2BodyDef bodyDef;
			bodyDef.position = px_to_mt_pos(ccp(x + width/2, y + height/2));
			bodyDef.type = b2_staticBody;
			bodyDef.userData = nullptr;

			b2Body *body = world->b2_world->CreateBody(&bodyDef);

			b2PolygonShape  shape;
			shape.SetAsBox(px_to_mt_length(width) / 2, px_to_mt_length(height) / 2);

			b2FixtureDef fixtureDef;
			fixtureDef.shape = &shape;
			fixtureDef.density = 1;
			body->CreateFixture(&fixtureDef);
		}
	}
}

void LevelLoader::load()
{
	auto map = loadMap();
	//enableTileGrid(map);
	registerPlayer(map);
	registerNpc(map);
	registerCollisionBox(map);
	registerAnimate(map);
	registerGoal(map);
}

void LevelLoader::registerAnimate(cocos2d::CCTMXTiledMap *map)
{
	CCDictionary* dict = nullptr;
	CCTMXObjectGroup* group = map->objectGroupNamed("objects");

	//Npc 추가
	if (group != nullptr) {
		CCArray* array = group->getObjects();
		CCObject* object;
		CCARRAY_FOREACH(array, object) {
			CCDictionary* dict = (CCDictionary*)object;
			CCString* type = (CCString*)dict->objectForKey("type");

			std::string typeValue = safeReadStringValue(dict, "type");
			if (typeValue == "animate") {
				CollisionAnimationObject *obj = CollisionAnimationObject::create(world, dict);
				obj->init();
				layer->addChild(obj);
				world->addTmxObject(obj);
			}
		}
	}
}