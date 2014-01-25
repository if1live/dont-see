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
	SimpleAudioEngine::sharedEngine()->playEffect("/sound/effect/dog_bark.mp3");
}

SoundManager::~SoundManager()
{
}
