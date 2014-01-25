#include "stdafx.h"
#include "level_layer.h"
#include "game_world.h"
#include "player.h"
#include "vision_mask.h"
#include "KeyboardDevice.h"
#include "MouseDevice.h"
#include "TmxObject.h"
#include "Npc.h"
#include "vision_clipper.h"
#include "b2_helper.h"
#include "collision_animation_object.h"
#include "action_helper.h"
#include "level_loader.h"

using namespace cocos2d;

enum {
	Level_Scene,
	Level_Clipper,
	Level_Layer,
};

LevelLayer::LevelLayer()
	: player(nullptr)
	, masking(nullptr)
{
}

cocos2d::CCScene *LevelLayer::scene() 
{
	CCScene *scene = CCScene::create();
	scene->setTag(Level_Scene);

	LevelLayer *layer = (LevelLayer*)LevelLayer::create();
	layer->setTag(Level_Layer);

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCClippingNode* clipper = VisionClipper::create();
	clipper->setTag(Level_Layer);
	clipper->setPosition(ccp(size.width/2, size.height/2));
	
	clipper->addChild(layer);	scene->addChild(clipper);
	//scene->addChild(layer);

	layer->clipper = clipper;
	layer->updateClipper(false);
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
	MouseDevice::sharedDevice()->Update();

	if (KeyboardDevice::sharedDevice()->GetKeys() == Key2)
	{
		this->updateClipper(!this->isClipperEnabled());
	}

	updateCamera();
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
	// create a TMX map
	LevelLoader loader("tilemap/MAP_1.tmx", this);
	loader.load();
	player = (Player*)GameWorld::sharedWorld()->getObjectByType(OBJECT_PLAYER);

	//ī�޶� �⺻ ��ġ�� �̵���Ű��
	//���̾� �ʱ�ȭ�Ҷ� ���� ���� ������ ����� ������ ���
	updateCamera();

	//��ȭ�� �ӽ÷� �߰�
	//ȿ���� �ִϸ��̼� �׽�Ʈ�� �־��
	CCSprite *empty = CCSprite::create("texture/empty.png");
	this->addChild(empty);
	empty->setPosition(ccp(-50, 100));
	CCAction *sonarAction = create_circle_sonar();
	empty->runAction(sonarAction);


	//��ȭ�� �ִϸ��̼�
	CCSprite *empty1 = CCSprite::create("texture/empty.png");
	this->addChild(empty1);
	empty1->setPosition(ccp(-50, 0));
	CCAction *fireAction = create_fire_animation();
	empty1->runAction(fireAction);

	{
		CCDictionary tempDict;
		tempDict.setObject(CCString::create("32"), "x");
		tempDict.setObject(CCString::create("32"), "y");
		CollisionAnimationObject *obj = CollisionAnimationObject::create(&tempDict);
		obj->init();
		this->addChild(obj, -1);
		GameWorld::sharedWorld()->addTmxObject(obj);
	}
}

void LevelLayer::updateCamera()
{
	//�÷��̾��� ��ġ��ŭ ȭ���� �ݴ�� �̵�
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCPoint camPos;
	if(isClipperEnabled()) {
		;
	} else {
		camPos = CCPoint(winSize.width/2, winSize.height/2);
	}
	
	if(player != nullptr) {
		CCPoint playerPos = player->getPosition();
		camPos.x -= playerPos.x;
		camPos.y -= playerPos.y;
	}
	this->setPosition(camPos);
}

bool LevelLayer::isClipperEnabled()
{
	if(this->getParent() == nullptr) {
		return false;
	}

	if(this->getParent()->getTag() == Level_Scene) {
		return false;
	} else {
		return true;
	}
}

void LevelLayer::updateClipper(bool use)
{
	if(use) {
		if(isClipperEnabled()) {
			// Ŭ���۸� ����� ��-���̾� �� ������ ���
			// ��-Ŭ����-���̾� �� �ٲ۴�
			CCNode *scene = this->getParent();
			this->removeFromParentAndCleanup(false);

			scene->addChild(clipper);
			clipper->addChild(this);

		} else {
			;
		}
	} else {
		if(isClipperEnabled()) {
			// Ŭ���۸� �Ⱦ���� �ϰ� ��-Ŭ����-���̾�� ������ ���
			// ��-���̾�� �ٲ۴�
			CCNode *scene = this->getParent()->getParent();
			this->getParent()->removeFromParentAndCleanup(false);
			this->removeFromParentAndCleanup(false);

			scene->addChild(this);
		}
	}
}