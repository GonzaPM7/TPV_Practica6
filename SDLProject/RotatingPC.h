#pragma once

#include "PhysicsComponent.h"

/*
 *
 */
class RotatingPC: public PhysicsComponent {
public:
	RotatingPC();
	RotatingPC(double angle);
	virtual ~RotatingPC();
	virtual void update(Container* c, Uint32 time);
private:
	double angle_;
};

