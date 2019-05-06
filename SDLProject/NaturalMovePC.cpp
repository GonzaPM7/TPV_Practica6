#include "NaturalMovePC.h"

#include "Container.h"

NaturalMovePC::NaturalMovePC() {
}

NaturalMovePC::~NaturalMovePC() {
}

void NaturalMovePC::update(Container* c, Uint32 time) {
	c->setPosition( c->getPosition()+c->getVelocity());
}
