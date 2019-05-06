#pragma once

#include "Component.h"
#include "Container.h"
#include "sdl_includes.h"

/*
 *
 */
class PhysicsComponent: virtual public Component {
public:
	PhysicsComponent();
	virtual ~PhysicsComponent();
	virtual void update(Container* c, Uint32 time) = 0;
};

