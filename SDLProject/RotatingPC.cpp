#include "RotatingPC.h"

RotatingPC::RotatingPC() : RotatingPC(2.0) {
}

RotatingPC::RotatingPC(double angle) : angle_(angle) {
}

RotatingPC::~RotatingPC() {
}

void RotatingPC::update(Container* c, Uint32 time) {
	c->setRotation( fmod(c->getRotation()+angle_,360) );
}
