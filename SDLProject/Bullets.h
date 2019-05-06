#pragma once

#include "Bullet.h"
#include "DeactivateOnBorderExit.h"
#include "GameObjectPool.h"
#include "ImageGC.h"
#include "NaturalMovePC.h"

/*
 *
 */
class Bullets: public GameObjectPool<Bullet,10> {
public:
	Bullets(SDLGame* game);
	virtual ~Bullets();
	void shoot(Vector2D pos, Vector2D vel, double width, double height);
	void receive(const void* senderObj, const msg::Message& msg);

private:
	NaturalMovePC naturalMove_;
	DeactivateOnBorderExit deactivate_;
	ImageGC bulletImage_;
};

