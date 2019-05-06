#pragma once

#include "PhysicsComponent.h"

/*
 *
 */
class ReduceSpeedPC: public PhysicsComponent {
public:
	ReduceSpeedPC();
	virtual ~ReduceSpeedPC();
	virtual void update(Container* c, Uint32 time);
};

