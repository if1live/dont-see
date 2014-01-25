#include "stdafx.h"
#include "b2_helper.h"

using namespace cocos2d;

b2Vec2 px_to_mt_pos(cocos2d::CCPoint &px_pos)
{
	float x = px_pos.x / PTM_RATIO;
	float y = px_pos.y / PTM_RATIO;
	return b2Vec2(x, y);
}

cocos2d::CCPoint mt_to_px_pos(const b2Vec2 &mt_pos)
{
	float x = mt_pos.x * PTM_RATIO;
	float y = mt_pos.y * PTM_RATIO;
	return ccp(x, y);
}

