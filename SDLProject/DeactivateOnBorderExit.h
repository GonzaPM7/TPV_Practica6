#pragma once

#include "PhysicsComponent.h"

/*
 *
 */
class DeactivateOnBorderExit: public PhysicsComponent {
public:
	DeactivateOnBorderExit();
	virtual ~DeactivateOnBorderExit();
	virtual void update(Container* c, Uint32 time);
};

