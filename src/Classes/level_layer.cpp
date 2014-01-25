#include "stdafx.h"
#include "level_layer.h"
#include "game_world.h"
#include "player.h"
#include "vision_mask.h"
#include "KeyboardDevice.h"
#include "TmxObject.h"
#include "Npc.h"
#include "vision_clipper.h"

using namespace cocos2d;

LevelLayer::LevelLayer()
	: player(nullptr)
	, masking(nullptr)
{
}

cocos2d::CCScene *LevelLayer::scene() 
{
	CCScene *scene = CCScene::create();
	CCLayer *layer = LevelLayer::create();
	
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCClippingNode* clipper = VisionClipper::create();
	clipper->setPosition(ccp(size.width/2, size.height/2));
	clipper->addChild(layer);
	scene->addChild(clipper);
	return scene;
}


bool LevelLayer::init()
{
	if(!CCLayer::init()) {
		return false;
	}

	this->setTouchEnabled( true );
	this->scheduleUpdate();
	this->initPhysics();
	this->initMap();

	CCLabelTTF *pLabel = CCLabelTTF::create("test",
                                            "Arial",
                                            18);
	this->addChild(pLabel);
	/*
	*/

	return true;
}

void LevelLayer::update(float dt)
{
	GameWorld::sharedWorld()->update(dt);
	KeyboardDevice::sharedDevice()->Update();
}

void LevelLayer::draw()
{
	CCLayer::draw();

	ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
    kmGLPushMatrix();
	GameWorld::sharedWorld()->b2_world->DrawDebugData();
    kmGLPopMatrix();
}

void LevelLayer::initPhysics()
{
	GameWorld::sharedWorld();
}



void LevelLayer::addNewSpriteAtPosition(CCPoint p)
{
    CCLOG("Add sprite %0.2f x %02.f",p.x,p.y);
    
    // Define the dynamic body.
    //Set up a 1m squared box in the physics world
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(p.x/PTM_RATIO, p.y/PTM_RATIO);

    b2Body *body = GameWorld::sharedWorld()->b2_world->CreateBody(&bodyDef);
    
    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(.5f, .5f);//These are mid points for our 1m box
    
    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;    
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);    
    
#if CC_ENABLE_BOX2D_INTEGRATION
    CCNode *parent = this->getChildByTag(kTagParentNode);
    
    //We have a 64x64 sprite sheet with 4 different 32x32 images.  The following code is
    //just randomly picking one of the images
    int idx = (CCRANDOM_0_1() > .5 ? 0:1);
    int idy = (CCRANDOM_0_1() > .5 ? 0:1);
    CCPhysicsSprite *sprite = CCPhysicsSprite::createWithTexture(m_pSpriteTexture,CCRectMake(32 * idx,32 * idy,32,32));
    //parent->addChild(sprite);
    //sprite->setB2Body(body);
    //sprite->setPTMRatio(PTM_RATIO);
    sprite->setPosition( ccp( p.x, p.y) );
#endif
}


void LevelLayer::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    //Add a new body/atlas sprite at the touched location
    CCSetIterator it;
    CCTouch* touch;

    for( it = touches->begin(); it != touches->end(); it++) 
    {
        touch = (CCTouch*)(*it);
        if(!touch)
            break;

        CCPoint location = touch->getLocation();
        addNewSpriteAtPosition( location );
    }
}

void LevelLayer::initMap()
{
	CCDrawNode* shape = CCDrawNode::create();
	
	CCPoint pts[4];
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	pts[0] = ccp( 0, 0);
	pts[1] = ccp( 0, size.height/2);
	pts[2] = ccp( size.width/2 - 1, size.height/2);
	pts[3] = ccp( size.width/2 - 1, 0);
	
	shape->drawPolygon(pts, 4, ccc4f(1, 1, 1, 1), 0, ccc4f(1, 0, 0, 1));

	// add shape in stencil
	CCClippingNode* clip = CCClippingNode::create();
	//clip->setAnchorPoint(ccp(0.5, 0.5));
	clip->setAnchorPoint(ccp(0.5, 0.5));
	clip->setPosition( ccp(size.width/4,size.height/4) );
	clip->setStencil(shape);
	this->addChild(clip);
	/*
	// setup content
	CCSprite* pSprite = CCSprite::create("HelloWorld.png");
	pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	clip->addChild(pSprite);
	*/
	// create a TMX map
	CCTMXTiledMap *map = CCTMXTiledMap::create("tilemap/desert.tmx");
	clip->addChild(map, -1);


	CCSprite *sp = CCSprite::create("texture/mask_default.png");
	sp->setPosition(ccp(size.width/4,size.height/4));

	clip->addChild(sp, 0);
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
	
	//플레이어 추가
	CCDictionary* dict = nullptr;
	CCTMXObjectGroup* group = map->objectGroupNamed("objects");
	if (group != nullptr) {
		dict = group->objectNamed("player");
	}

	player = Player::create(dict);
	player->init();
	this->addChild(player, -1);

	//Npc 추가
	if (group != nullptr) {
		CCArray* array = group->getObjects();
		CCObject* object;
		CCARRAY_FOREACH(array, object) {
			CCDictionary* dict = (CCDictionary*)object;
			CCString* type = (CCString*)dict->objectForKey("type");

			std::string typeValue = safeReadStringValue(dict, "type");
			if (typeValue == "npc") {
				Npc* npc = Npc::create(dict);
				npc->init();
				this->addChild(npc);
			}
		}
	}

	CCDictionary tempDict;
	tempDict.setObject(CCString::create("100"), "x");
	tempDict.setObject(CCString::create("100"), "y");
	tempDict.setObject(CCString::create("100"), "width");
	tempDict.setObject(CCString::create("100"), "height");
	tempDict.setObject(CCString::create("10"), "speed");
	tempDict.setObject(CCString::create("1"), "dir");
	
	Npc* npc = Npc::create(&tempDict);
	npc->init();
	this->addChild(npc, -1);
}