#include "stdafx.h"
#include "action_helper.h"

using namespace cocos2d;

cocos2d::CCAction *create_circle_sonar()
{
	// ��������Ʈ ��Ʈ�� ��ġ���� ������ �о���δ�.
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("animation/sound_round.plist");
    
    CCArray* animFrames = CCArray::createWithCapacity(15);
    
    char str[100] = {0};
    for(int i = 1; i <=5 ; i++) {
        sprintf(str, "sound_round_%d.png", i);
        CCSpriteFrame* frame = cache->spriteFrameByName( str );
        animFrames->addObject(frame);
    }
    
    // �ִϸ��̼� �����
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames, 0.1f);
    CCAnimate *animate = CCAnimate::create(animation);
	CCActionInterval *wait = CCActionInterval::create(3.0f);
    CCAction* action = CCSpawn::create(animate, wait, NULL);

    CCActionInterval* rep1 = (CCActionInterval*)action;
    CCAction* rep2 = CCRepeat::create(rep1, 3);
	return rep2;
}

cocos2d::CCAction *create_fire_animation()
{
	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("animation/fire.plist");

	CCArray *frames = CCArray::createWithCapacity(4);

	char buffer[256];
	for(int i = 2 ; i <= 3 ; ++i) {
		sprintf(buffer, "fire_%d.png", i);
		CCSpriteFrame *frame = cache->spriteFrameByName(buffer);
		frames->addObject(frame);
	}

	CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames, 0.1f);
	CCAnimate *animate = CCAnimate::create(animation);
	CCAction *action = CCSpawn::create(animate, NULL);

	CCActionInterval *rep1 = (CCActionInterval*)action;
	CCAction *rep2 = CCRepeatForever::create(rep1);
	return rep2;
}


cocos2d::CCAction *create_trash_animation(int mode)
{
	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("animation/trash_can.plist");

	CCArray *frames = CCArray::createWithCapacity(4);

	assert(mode == 1 || mode == 0);
	char buffer[256];
	sprintf(buffer, "trash_can_%d.png", mode + 1);
	CCSpriteFrame *frame = cache->spriteFrameByName(buffer);
	frames->addObject(frame);

	CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames, 0.1f);
	CCAnimate *animate = CCAnimate::create(animation);
	CCAction *action = CCSpawn::create(animate, NULL);
	return action;
}

cocos2d::CCAction *create_blink_animation(float duration)
{
	CCBlink *blink = CCBlink::create(duration, duration / 0.08f);
	return blink;
}