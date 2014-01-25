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
	CCActionInterval *wait = CCActionInterval::create(1.0f);
    CCAction* action = CCSpawn::create(animate, wait, NULL);

    CCActionInterval* rep1 = (CCActionInterval*)action;
    CCAction* rep2 = CCRepeatForever::create(rep1);
	return rep2;
}