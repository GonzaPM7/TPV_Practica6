#include "ReduceSpeedPC.h"

ReduceSpeedPC::ReduceSpeedPC() {
}

ReduceSpeedPC::~ReduceSpeedPC() {
}

void ReduceSpeedPC::update(Container* c, Uint32 time) {
	c->setVelocity( c->getVelocity()*0.995 );
}
