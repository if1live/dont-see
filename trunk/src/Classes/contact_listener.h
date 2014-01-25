#pragma once

class Player;
class CollisionAnimationObject;
class Goal;

class MyContactListener : public b2ContactListener {
public:
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact *contact);
};

void collision_player_vs_collision_object(Player *player, CollisionAnimationObject *other);
void collision_player_vs_goal(Player *player, Goal *goal);