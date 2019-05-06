#pragma once

#include "PhysicsComponent.h"

/*
 *
 */
class NaturalMovePC: public PhysicsComponent {
public:
	NaturalMovePC();
	virtual ~NaturalMovePC();
	virtual void update(Container* c, Uint32 time);
};

