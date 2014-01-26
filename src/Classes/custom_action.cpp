#include "stdafx.h"
#include "custom_action.h"

Custom_action::Custom_action()
	: specialCountMax(3)
	, specialGapMax(5.0f)
{
	specialCount = specialCountMax;
	specialGap = 0.f;
	specialSoundFlag = false;
}

Custom_action::~Custom_action()
{
}

bool Custom_action::TryDecreaseSpecialCount()
{
	if(specialCount <= 0)
		return false;

	specialCount--;
	return true;
}

int Custom_action::GetSpecialCount()
{
	return specialCount;
}

float Custom_action::GetSpecialGap()
{
	return specialGap;
}

void Custom_action::Update(float dt)
{
	if(specialCount < specialCountMax)
		specialGap += dt;

	if(specialGap >= specialGapMax)
	{
		specialGap = 0.f;
		specialCount++;
		specialSoundFlag = true;
	}
}

bool Custom_action::TrySpecialSound()
{
	if(specialSoundFlag == true)
	{
		specialSoundFlag = false;
		return true;
	}

	return false;
}