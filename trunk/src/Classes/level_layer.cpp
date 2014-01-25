#include "stdafx.h"
#include "level_layer.h"
#include "VisibleRect.h"

#define PTM_RATIO (32.0f)

using namespace cocos2d;

LevelLayer::~LevelLayer()
{
	CC_SAFE_DELETE(world);
}

LevelLayer::LevelLayer()
	: world(nullptr),
	debugDraw(PTM_RATIO)
{
}

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

	this->setTouchEnabled( true );
	this->scheduleUpdate();
	this->initPhysics();

	// create a TMX map
	CCTMXTiledMap *map = CCTMXTiledMap::create("tilemap/desert.tmx");
	this->addChild(map, -1);
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

	playerSprite = CCSprite::create("texture/player.png");
	this->addChild(playerSprite);

	playerSprite->runAction(cocos2d::CCMoveBy::create(5.0f, cocos2d::CCPoint(100, 100)));

	CCLabelTTF *pLabel = CCLabelTTF::create("test",
                                            "Arial",
                                            18);
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    pLabel->setPosition(ccp(size.width/2, size.height/2));
    addChild(pLabel);
	
	return true;
}

void LevelLayer::update(float dt)
{
	int velocityIterations = 8;
    int positionIterations = 1;
	world->Step(dt, velocityIterations, positionIterations);

	
}

void LevelLayer::draw()
{
	CCLayer::draw();

	ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
    kmGLPushMatrix();
    world->DrawDebugData();
    kmGLPopMatrix();
}

void LevelLayer::initPhysics()
{
	//물리엔진 초기화
	b2Vec2 gravity;
	gravity.Set(0.0f, -5.0f);
	//메모리 누스 옮기기
	world = new b2World(gravity);
	world->SetAllowSleeping(true);
	world->SetContinuousPhysics(true);

	uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    //        flags += b2Draw::e_jointBit;
    //        flags += b2Draw::e_aabbBit;
    //        flags += b2Draw::e_pairBit;
    //        flags += b2Draw::e_centerOfMassBit;
    debugDraw.SetFlags(flags);
	world->SetDebugDraw(&debugDraw);
	

	// Define the ground body.
    b2BodyDef groundBodyDef;
	groundBodyDef.type = b2_staticBody;
    groundBodyDef.position.Set(0, 0); // bottom-left corner
	b2Body* groundBody = world->CreateBody(&groundBodyDef);

	// Define the ground box shape.
    b2EdgeShape groundBox;

    auto visibleRect = VisibleRect::getVisibleRect();
	float left = visibleRect.getMinX() / PTM_RATIO;
	float right = visibleRect.getMaxX() / PTM_RATIO;
	float bottom = visibleRect.getMinY() / PTM_RATIO;
	float top = visibleRect.getMaxY() / PTM_RATIO;
    groundBox.Set(b2Vec2(left, bottom), b2Vec2(right, bottom));
    groundBody->CreateFixture(&groundBox,0);

    // top
    groundBox.Set(b2Vec2(left, top), b2Vec2(right, top));
    groundBody->CreateFixture(&groundBox,0);

    // left
    groundBox.Set(b2Vec2(left, top), b2Vec2(left, bottom));
    groundBody->CreateFixture(&groundBox,0);

    // right
    groundBox.Set(b2Vec2(right, bottom), b2Vec2(right, top));
    groundBody->CreateFixture(&groundBox,0);
}



void LevelLayer::addNewSpriteAtPosition(CCPoint p)
{
    CCLOG("Add sprite %0.2f x %02.f",p.x,p.y);
    
    // Define the dynamic body.
    //Set up a 1m squared box in the physics world
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(p.x/PTM_RATIO, p.y/PTM_RATIO);

    b2Body *body = world->CreateBody(&bodyDef);
    
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