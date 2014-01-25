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
	for(int i = 0; i < EFFECT_MAX; i++)
	{
		effectSoundID[i] = 0;

		SimpleAudioEngine::sharedEngine()->preloadEffect(effectSoundFile[i]);
		effectSoundInterval[i] = 2.0f;
	}
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