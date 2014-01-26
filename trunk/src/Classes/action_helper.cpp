#include "stdafx.h"
#include "action_helper.h"

using namespace cocos2d;

cocos2d::CCAction *create_circle_sonar()
{
	// 스프라이트 시트의 위치정보 파일을 읽어들인다.
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("animation/sound_round.plist");
    
    CCArray* animFrames = CCArray::createWithCapacity(15);
    
    char str[100] = {0};
    for(int i = 1; i <=5 ; i++) {
        sprintf(str, "sound_round_%d.png", i);
        CCSpriteFrame* frame = cache->spriteFrameByName( str );
        animFrames->addObject(frame);
    }
    
    // 애니메이션 만들기
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

cocos2d::CCAction *create_arc_sonar(int dir)
{
	const char* sprite_basename = "";
	switch (dir) {
	case 1: sprite_basename = "sound_wifi_SW"; break;
	case 2: sprite_basename = "sound_wifi_NW"; break;
	case 3: sprite_basename = "sound_wifi_NE"; break;
	case 4: sprite_basename = "sound_wifi_SE"; break;
	}
	
	char str[100] = {0};

	// 스프라이트 시트의 위치정보 파일을 읽어들인다.
	sprintf(str, "animation/%s.plist", sprite_basename);
	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile(str);

	CCArray* animFrames = CCArray::createWithCapacity(15);

	for(int i = 1; i <=9 ; i++) {
		sprintf(str, "%s_%d.png", sprite_basename, i % 3 + 1);
		CCSpriteFrame* frame = cache->spriteFrameByName( str );
		animFrames->addObject(frame);
	}

	// 애니메이션 만들기
	CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames, 0.2f);
	CCAnimate *animate = CCAnimate::create(animation);
	CCHide *hide = CCHide::create();
	CCAction* action = CCSequence::create(animate, hide, NULL);
	CCActionInterval* rep1 = (CCActionInterval*)action;
	
	return rep1;
}
