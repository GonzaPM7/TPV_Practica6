#include "DeactivateOnBorderExit.h"

DeactivateOnBorderExit::DeactivateOnBorderExit() {

}

DeactivateOnBorderExit::~DeactivateOnBorderExit() {
}

void DeactivateOnBorderExit::update(Container* c, Uint32 time) {
	Vector2D p = c->getPosition();
	if (p.getX() >= c->getGame()->getWindowWidth() ||
		p.getX() + c->getWidth() <= 0 ||
		p.getY() >= c->getGame()->getWindowHeight() ||
		p.getY() + c->getHeight() <= 0) {
			c->setActive(false);
	}
}
