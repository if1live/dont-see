#include "stdafx.h"
#include "level_layer.h"
#include "game_world.h"

using namespace cocos2d;

LevelLayer::~LevelLayer()
{
	CC_SAFE_DELETE(gameWorld);
}

LevelLayer::LevelLayer()
	: gameWorld(nullptr)
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
	gameWorld->update(dt);

}

void LevelLayer::draw()
{
	CCLayer::draw();

	ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
    kmGLPushMatrix();
	gameWorld->b2_world->DrawDebugData();
    kmGLPopMatrix();
}

void LevelLayer::initPhysics()
{
	gameWorld = new GameWorld();
}



void LevelLayer::addNewSpriteAtPosition(CCPoint p)
{
    CCLOG("Add sprite %0.2f x %02.f",p.x,p.y);
    
    // Define the dynamic body.
    //Set up a 1m squared box in the physics world
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(p.x/PTM_RATIO, p.y/PTM_RATIO);

    b2Body *body = gameWorld->b2_world->CreateBody(&bodyDef);
    
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