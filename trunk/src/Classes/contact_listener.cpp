#include "stdafx.h"
#include "contact_listener.h"
#include "TmxObject.h"
#include "collision_animation_object.h"
#include "goal.h"
#include "player.h"
#include "Npc.h"
#include "action_helper.h"
#include "SoundManager.h"

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

	//npc랑 부딪친 경우
	if(typeA == OBJECT_PLAYER && typeB == OBJECT_NPC) {
		collision_player_vs_npc((Player*)objA, (Npc*)objB);
	}
	if(typeA == OBJECT_NPC && typeB == OBJECT_PLAYER) {
		collision_player_vs_npc((Player*)objB, (Npc*)objA);
	}
}

void MyContactListener::EndContact(b2Contact *contact)
{
}

void collision_player_vs_collision_object(Player *player, CollisionAnimationObject *other)
{
	if(player->canDamagable() == false) {
		return;
	}
	other->runAnimation();
	player->damage();
}


void collision_player_vs_goal(Player *player, Goal *goal)
{
	if(goal->clearCalled == false) {
		goal->clearGame();
	}
}

void collision_player_vs_npc(Player *player, Npc *npc)
{
	if(player->canDamagable() == false) {
		return;
	}
	player->damage();
	SoundManager::sharedManager()->PlayEffect(EFFECT_MAN_SCREAM);
}