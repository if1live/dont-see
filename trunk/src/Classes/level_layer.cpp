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

#include "SoundManager.h"
#include "custom_action.h"
#include "text_layer.h"

using namespace cocos2d;

enum {
	Level_Scene,
	Level_Clipper,
	Level_Layer,
};

LevelLayer::LevelLayer()
	: player(nullptr)
	, masking(nullptr)
	, soundTick(0)
	, world(new GameWorld())
{
	custom_action = new Custom_action();
}
LevelLayer::~LevelLayer()
{
	delete(world);
	world = nullptr;
}

cocos2d::CCScene *LevelLayer::scene(const char *mapfile)
{
	CCScene *scene = CCScene::create();
	scene->setTag(Level_Scene);

	LevelLayer *layer = new LevelLayer();
	layer->initWithMapfile(mapfile);
	layer->autorelease();
	layer->setTag(Level_Layer);

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCClippingNode* clipper = VisionClipper::create();
	clipper->setTag(Level_Layer);
	clipper->setPosition(ccp(size.width/2, size.height/2));
	
	clipper->addChild(layer);	scene->addChild(clipper);
	//scene->addChild(layer);

	layer->clipper = clipper;
	layer->updateClipper(false);

	CCSprite *maskOuter = CCSprite::create("texture/mask_2.png");
	scene->addChild(maskOuter);
	maskOuter->setAnchorPoint(ccp(0.5, 0.5));
	maskOuter->setPosition(ccp(size.width/2, size.height/2));
	maskOuter->setScale(1.2);

	//masking
	VisionMask *visionMasking = VisionMask::create();
	layer->masking = visionMasking;
	scene->addChild(visionMasking);
	visionMasking->setPosition(ccp(size.width/2, size.height/2+15));

	layer->soundLayer = CCLayer::create();
	scene->addChild(layer->soundLayer);

	//개발시 사용할 정보 보여줄 레이어
	TextLayer *textLayer = (TextLayer*)TextLayer::create();
	textLayer->customAction = layer->custom_action;
	textLayer->world = layer->world;
	scene->addChild(textLayer);

	//우클릭 허용은 카운터가 존재한다
	visionMasking->customAction = layer->custom_action;


	return scene;
}


bool LevelLayer::initWithMapfile(const char *mapfile)
{
	if(!CCLayer::init()) {
		return false;
	}

	this->setTouchEnabled( true );
	this->scheduleUpdate();
	this->initMap(mapfile);


	return true;
}

void LevelLayer::update(float dt)
{
	world->update(dt);
	KeyboardDevice::sharedDevice()->Update();
	MouseDevice::sharedDevice()->Update();

	updateCamera();

	const float minViewRadius = 100;
	const float maxViewRadius = 400;
	const CCPoint& layerPos = getPosition();
	std::vector<TmxObject*> nearObjects = world->nearBy(player->getPosition(), minViewRadius, maxViewRadius);
	for (auto it = nearObjects.begin(); it != nearObjects.end(); ++it) {
		TmxObject* nearObject = (*it);
		if(nearObject->noiseable() == false) {
			continue;
		}

		auto mapIt = soundEffectObjectMap.find(nearObject);
		if (mapIt == soundEffectObjectMap.end()) {
			CCPoint resultPos = nearObject->getPosition() + layerPos;

			//소화전 임시로 추가
			//효과용 애니메이션 테스트로 넣어보자
			CCSprite *empty = CCSprite::create("texture/empty.png");
			soundLayer->addChild(empty);
			empty->setPosition(resultPos);
			CCAction *sonarAction = create_circle_sonar();
			empty->runAction(sonarAction);
			sonarAction->retain();

			soundEffectObjectMap.insert(std::make_pair(nearObject, std::make_pair(empty, sonarAction)));
		} else {
			mapIt->second.first->setPosition(mapIt->first->getPosition() + layerPos);
		}
	}

	for (auto it = soundEffectObjectMap.begin(); it != soundEffectObjectMap.end(); ) {
		if (it->second.second->isDone()) {
			it->second.second->release();
			it = soundEffectObjectMap.erase(it);
		}
		else ++it;
	}
	
	masking->Update();

	custom_action->Update(dt);
	updateSound(dt);
}

void LevelLayer::updateSound(float dt)
{
	int currentKeys = KeyboardDevice::sharedDevice()->GetKeys();
	int preKeys = KeyboardDevice::sharedDevice()->GetPreKeys();

	if( (currentKeys & KeyLButton) != 0 && (preKeys & KeyLButton) == 0 && custom_action->TryDecreaseSpecialCount())
	{
		SoundManager::sharedManager()->PlayEffect(EFFECT_DOG);

		// 골 지점과 위치를 계산하여 개소리 위치 표시를 해준다.
		TmxObject* goalObject = world->getObjectByType(OBJECT_GOAL);
		if (goalObject != nullptr) {
			CCPoint playerPos = player->getPosition();
			CCPoint goalPos = goalObject->getPosition();
			CCPoint p = goalPos - playerPos;
			float angle = 0;
			if(p.x < 0)
			{
				angle = atan(float(p.y)/p.x * -1) * 180 / M_PI;
				angle += 270;
			}
			else
			{
				angle = atan(float(p.y)/p.x * -1) * 180 / M_PI;
				angle += 90;
			}
			int barkDiv = 0;
			if (angle <= 90) barkDiv = 1;
			else if (angle <= 180) barkDiv = 2;
			else if (angle <= 270) barkDiv = 3;
			else if (angle <= 360) barkDiv = 4;

			CCSize winSize = CCDirector::sharedDirector()->getWinSize();
			CCPoint camPos(winSize.width/2, winSize.height/2);
			switch (barkDiv) {
			case 1: camPos.x += 150; camPos.y += 150; break;
			case 2: camPos.x += 150; camPos.y -= 150; break;
			case 3: camPos.x -= 150; camPos.y -= 150; break;
			case 4: camPos.x -= 150; camPos.y += 150; break;
			}

			CCSprite *empty = CCSprite::create("texture/empty.png");
			soundLayer->addChild(empty);
			empty->setPosition(camPos);
			CCAction *sonarAction = create_arc_sonar(barkDiv);
			empty->runAction(sonarAction);
		}
	}

	if (custom_action->TrySpecialSound()) {
		SoundManager::sharedManager()->PlayEffect(EFFECT_SPECIAL_INC);
	}

	SoundManager::sharedManager()->Update(dt);
}

void LevelLayer::draw()
{
	CCLayer::draw();

	ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
    kmGLPushMatrix();
	world->b2_world->DrawDebugData();
    kmGLPopMatrix();
}

void LevelLayer::addNewSpriteAtPosition(CCPoint p)
{
    CCLOG("Add sprite %0.2f x %02.f",p.x,p.y);
    
    // Define the dynamic body.
    //Set up a 1m squared box in the physics world
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(p.x/PTM_RATIO, p.y/PTM_RATIO);

    b2Body *body = world->b2_world->CreateBody(&bodyDef);
    
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

/*
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


		int a = touch->getID();

        CCPoint location = touch->getLocation();
        addNewSpriteAtPosition( location );
    }
}
*/

void LevelLayer::initMap(const char *mapfile)
{
	// create a TMX map
	LevelLoader loader(mapfile, this, world);
	loader.load();
	player = (Player*)world->getObjectByType(OBJECT_PLAYER);

	//카메라를 기본 위치로 이동시키기
	//레이어 초기화할때 같이 하지 않으면 끊기는 느낌이 든다
	updateCamera();
}

void LevelLayer::updateCamera()
{
	//플레이어의 위치만큼 화면을 반대로 이동
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

	camPos.x = (int)camPos.x;
	camPos.y = (int)camPos.y;
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
			// 클리퍼를 쓸라고 씬-레이어 로 구성된 경우
			// 씬-클리퍼-레이어 로 바꾼다
			CCNode *scene = this->getParent();
			this->removeFromParentAndCleanup(false);

			scene->addChild(clipper);
			clipper->addChild(this);

		} else {
			;
		}
	} else {
		if(isClipperEnabled()) {
			// 클리퍼를 안쓸라고 하고 씬-클리퍼-레이어로 구성된 경우
			// 씬-레이어로 바꾼다
			CCNode *scene = this->getParent()->getParent();
			this->getParent()->removeFromParentAndCleanup(false);
			this->removeFromParentAndCleanup(false);

			scene->addChild(this);
		}
	}
}