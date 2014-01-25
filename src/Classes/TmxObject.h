#pragma once

int safeReadIntValue(cocos2d::CCDictionary* dict, const char* key, int defaultValue = 0);
std::string safeReadStringValue(cocos2d::CCDictionary* dict, const char* key, const char* defaultValue = "");

class TmxObject : public cocos2d::CCLayer
{
public:
	TmxObject(cocos2d::CCDictionary* dict);
	virtual ~TmxObject();

	virtual bool init();
	void Move(int dx, int dy, float animDelay = 0.0f);
	void setVelocity(float x, float y);

	virtual b2Body *createBody() = 0;

protected:
	int m_x;
	int m_y;
	int m_speed;
	std::string m_textureName;
	cocos2d::CCSprite* m_sprite;
	b2Body *m_body;

	// npc ��ǥ ��ҷ� �̵��ϱ� ���� �ʿ��� ����
	int m_width;
	int m_height;
	int m_moveDirection;
};
