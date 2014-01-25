#include "stdafx.h"
#include "contact_listener.h"
#include "TmxObject.h"
#include "collision_animation_object.h"

using namespace cocos2d;

void MyContactListener::BeginContact(b2Contact* contact)
{
	b2Body *bodyA = contact->GetFixtureA()->GetBody();
	if(bodyA->GetUserData() == nullptr) {
		return;
	}
	
	b2Body *bodyB = contact->GetFixtureB()->GetBody();
	if(bodyB->GetUserData() == nullptr) {
		return;
	}

	TmxObject *objA = (TmxObject*)bodyA->GetUserData();
	TmxObject *objB = (TmxObject*)bodyB->GetUserData();

	//player-¼ÒÈ­Àü
	int typeA = objA->m_objType;
	int typeB = objB->m_objType;

	if(typeA == OBJECT_PLAYER && typeB == OBJECT_COLLISION_ANIMATION) {
		collision_player_vs_collision_object((Player*)objA, (CollisionAnimationObject*)objB);
	}
	if(typeA == OBJECT_COLLISION_ANIMATION && typeB == OBJECT_PLAYER) {
		collision_player_vs_collision_object((Player*)objB, (CollisionAnimationObject*)objA);
	}
}

void MyContactListener::EndContact(b2Contact *contact)
{
}

void collision_player_vs_collision_object(Player *player, CollisionAnimationObject *other)
{
	other->runAnimation();
}
