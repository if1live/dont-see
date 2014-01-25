#include "stdafx.h"
#include "custom_action.h"

Custom_action::Custom_action():specialCountMax(3),specialGapMax(10.f)
{
	specialCount = 0;
	specialGap = 0.f;
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
	}
}