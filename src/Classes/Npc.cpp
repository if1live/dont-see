#include "stdafx.h"
#include "Npc.h"

using namespace cocos2d;

Npc* Npc::create(cocos2d::CCDictionary* dict)
{
	Npc* npc = new Npc(dict);
	npc->autorelease();
	return npc;
}

Npc::Npc(CCDictionary* dict)
	: TmxObject(dict), m_movingCool(0)
{
}

bool Npc::init()
{
	if (!TmxObject::init())
		return false;

	m_startX = m_x;
	m_startY = m_y;
	m_endX = m_x + m_width;
	m_endY = m_y + m_height;
	return true;
}

void Npc::update(float dt)
{
	m_movingCool -= dt;
	if (m_movingCool <= 0)
	{
		int dx = 0, dy = 0;
		switch (m_moveDirection)
		{
		case 1: dy += m_speed; break;
		case 2: dx -= m_speed; break;
		case 3: dy -= m_speed; break;
		case 4: dx += m_speed; break;
		}

		m_movingCool = 0.3f;
		Move(dx, dy, m_movingCool);

		if (m_moveDirection == 1 && m_y > m_endY) m_moveDirection = 3;
		if (m_moveDirection == 2 && m_x < m_startX) m_moveDirection = 4;
		if (m_moveDirection == 3 && m_y < m_startY) m_moveDirection = 1;
		if (m_moveDirection == 4 && m_x > m_endX) m_moveDirection = 2;
	}
}
