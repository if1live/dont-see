#pragma once

class Npc : public cocos2d::CCLayer {
public:
	static Npc* create(cocos2d::CCDictionary* dict);

	Npc(cocos2d::CCDictionary* dict);
	~Npc();

	virtual bool init();

private:
	int m_x, m_y;
};

