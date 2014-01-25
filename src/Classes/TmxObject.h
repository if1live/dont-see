#pragma once

int safeReadIntValue(cocos2d::CCDictionary* dict, const char* key, int defaultValue = 0);
std::string safeReadStringValue(cocos2d::CCDictionary* dict, const char* key, const char* defaultValue = "");

class TmxObject : public cocos2d::CCLayer
{
public:
	TmxObject(cocos2d::CCDictionary* dict);

	virtual bool init();
	void Move(int dx, int dy, float animDelay = 0.0f);

protected:
	int m_x;
	int m_y;
	int m_speed;
	std::string m_textureName;
	cocos2d::CCSprite* m_sprite;

	// npc 목표 장소로 이동하기 위해 필요한 정보
	int m_width;
	int m_height;
	int m_moveDirection;
};
