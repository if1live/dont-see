#include "stdafx.h"
#include "contact_listener.h"
#include "TmxObject.h"
#include "collision_animation_object.h"
#include "goal.h"
#include "player.h"

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

	int typeA = objA->m_objType;
	int typeB = objB->m_objType;
	
	//player-소화전
	if(typeA == OBJECT_PLAYER && typeB == OBJECT_COLLISION_ANIMATION) {
		collision_player_vs_collision_object((Player*)objA, (CollisionAnimationObject*)objB);
	}
	if(typeA == OBJECT_COLLISION_ANIMATION && typeB == OBJECT_PLAYER) {
		collision_player_vs_collision_object((Player*)objB, (CollisionAnimationObject*)objA);
	}

	//최종도착점에 도달한 경우
	if(typeA == OBJECT_PLAYER && typeB == OBJECT_GOAL) {
		collision_player_vs_goal((Player*)objA, (Goal*)objB);
	}
	if(typeA == OBJECT_GOAL && typeB == OBJECT_PLAYER) {
		collision_player_vs_goal((Player*)objB, (Goal*)objA);
	}
}

void MyContactListener::EndContact(b2Contact *contact)
{
}

void collision_player_vs_collision_object(Player *player, CollisionAnimationObject *other)
{
	other->runAnimation();
	player->hp -= 1;
}


void collision_player_vs_goal(Player *player, Goal *goal)
{
	goal->clearGame();
}