#pragma once

#include "TmxObject.h"

class Player : public TmxObject {
public:
	static Player* create(cocos2d::CCDictionary* dict);

	Player(cocos2d::CCDictionary* dict);

	virtual void update(float dt);
	virtual b2Body *createBody();

	bool canDamagable();
	void damage();
private:
	float m_movingCool;
	int hp;

	//���°��� ������ ���� �ð�
	float powerfulTime;
	bool gameOver;
};

