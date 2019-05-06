#include "ShowUpAtOppositeSidePC.h"

ShowUpAtOppositeSidePC::ShowUpAtOppositeSidePC() :
		ShowUpAtOppositeSidePC(true, true) {
}

ShowUpAtOppositeSidePC::ShowUpAtOppositeSidePC(bool vertical, bool horizental) :
		vertical_(vertical), horizental_(horizental) {
}

ShowUpAtOppositeSidePC::~ShowUpAtOppositeSidePC() {
}

void ShowUpAtOppositeSidePC::update(Container* c, Uint32 time) {

	Vector2D p = c->getPosition();

	if (horizental_) {
		if (p.getX() >= c->getGame()->getWindowWidth()) {
			p.setX(1 - c->getWidth() );
		} else if (p.getX() + c->getWidth() <= 0) {
			p.setX(c->getGame()->getWindowWidth());
		}
	}

	if (vertical_) {
		if (p.getY() >= c->getGame()->getWindowHeight()) {
			p.setY(1 - c->getHeight() );
		} else if (p.getY() + c->getHeight() <= 0) {
			p.setY(c->getGame()->getWindowHeight());
		}
	}

	c->setPosition(p);

}
