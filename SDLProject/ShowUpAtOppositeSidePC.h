#pragma once

#include "PhysicsComponent.h"

/*
 *
 */
class ShowUpAtOppositeSidePC: public PhysicsComponent {
public:
	ShowUpAtOppositeSidePC();
	ShowUpAtOppositeSidePC(bool vertical, bool horizental);
	virtual ~ShowUpAtOppositeSidePC();
	virtual void update(Container* c, Uint32 time);
private:
	bool vertical_;
	bool horizental_;
};

