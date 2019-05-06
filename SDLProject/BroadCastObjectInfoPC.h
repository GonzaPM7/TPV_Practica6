#pragma once

#include "PhysicsComponent.h"
#include "Container.h"

/*
 *
 */
class BroadCastObjectInfoPC: public PhysicsComponent {
public:
	BroadCastObjectInfoPC();
	virtual ~BroadCastObjectInfoPC();
	virtual void update(Container* c, Uint32 time);
};

