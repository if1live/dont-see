#include "stdafx.h"
#include "SimpleAudioEngine.h"
#include "SoundManager.h"

using namespace CocosDenshion;

SoundManager* SoundManager::sharedManager()
{
	static SoundManager staticManager;

	return &staticManager;
}

SoundManager::SoundManager()
{
	strcpy(effectSoundFile[EFFECT_DOG], "/sound/effect/dog_bark.mp3");
	strcpy(effectSoundFile[EFFECT_SPECIAL_INC], "/sound/effect/special_get.mp3");
	strcpy(effectSoundFile[EFFECT_MAN_SCREAM], "/sound/effect/man_scream.mp3");
	strcpy(effectSoundFile[EFFECT_TRASH_CRASH], "/sound/effect/trash_crash.mp3");
	strcpy(effectSoundFile[EFFECT_WATER], "/sound/effect/waterfall.mp3");
	strcpy(effectSoundFile[EFFECT_STICK], "/sound/effect/stick.mp3");
	for(int i = 0; i < EFFECT_MAX; i++)
	{
		effectSoundID[i] = 0;

		SimpleAudioEngine::sharedEngine()->preloadEffect(effectSoundFile[i]);
		effectSoundInterval[i] = 2.0f;
	}

	//SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("/sound/background/bg01.mp3");
}

SoundManager::~SoundManager()
{
	SimpleAudioEngine::sharedEngine()->stopAllEffects();
	for(int i = 0; i < EFFECT_MAX; i++)
	{
		SimpleAudioEngine::sharedEngine()->unloadEffect(effectSoundFile[i]);
	}
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	SimpleAudioEngine::sharedEngine()->end();
}

void SoundManager::PlayEffect(int index)
{
	if(index >= EFFECT_MAX)
		return;

	if(effectSoundState[index] > 0.f)
		return;
	effectSoundID[index] = SimpleAudioEngine::sharedEngine()->playEffect(effectSoundFile[index]);
	effectSoundState[index] = effectSoundInterval[index];
}

void SoundManager::Update(float dt)
{
	for(int i = 0; i < EFFECT_MAX; i++)
	{
		if(effectSoundState[i] > 0.f)
		{
			effectSoundState[i] -= dt;
		}
	}
}

void SoundManager::PlayBG(int index)
{
	if(index >= BG_MAX)
		return;

	bg_index = index;
	switch(index)
	{
	case BG_MAIN:
			SimpleAudioEngine::sharedEngine()->playBackgroundMusic("/sound/background/bg01.mp3", true);
		break;
	case BG_TITLE:
			SimpleAudioEngine::sharedEngine()->playBackgroundMusic("/sound/background/bg_title.mp3", true);
		break;
	}
}