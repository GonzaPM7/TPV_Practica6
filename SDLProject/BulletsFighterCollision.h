#pragma once
#include "PhysicsComponent.h"
#include "Fighter.h"
#include "Bullets.h"

class BulletsFighterCollision :
	public PhysicsComponent
{
private:
	GameObject* fighter_ = nullptr;
	const vector<Bullet*>* bullets_ = nullptr;
public:
	BulletsFighterCollision();
	~BulletsFighterCollision();

	virtual void update(Container* c, Uint32 time);

	virtual void receive(Container* c, const msg::Message& msg);
};

