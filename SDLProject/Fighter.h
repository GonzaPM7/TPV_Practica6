#pragma once

#include "Container.h"
#include "GunIC.h"
#include "ImageGC.h"
#include "NaturalMovePC.h"
#include "ReduceSpeedPC.h"
#include "RotationIC.h"
#include "ShowUpAtOppositeSidePC.h"
#include "ThrustIC.h"

/*
 *
 */
class Fighter: public Container {
public:
	Fighter(msg::ObjectId id, SDLGame* game);
	virtual ~Fighter();
	virtual void receive(const void* senderObj, const msg::Message& msg);

private:
	void initFighter();

	RotationIC rotation_;
	ImageGC fighterImage_;
	NaturalMovePC naturalMove_;
	ShowUpAtOppositeSidePC oppositeSide_;
	GunIC normalGun_;
	ThrustIC thrust_;
	ReduceSpeedPC reduceSpeed_;
};

