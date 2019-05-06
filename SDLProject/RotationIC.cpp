#include "RotationIC.h"

#include "InputHandler.h"
RotationIC::RotationIC() :
		RotationIC(SDLK_LEFT, SDLK_RIGHT, 5) {
}

RotationIC::RotationIC(SDL_Keycode left, SDL_Keycode right, double angle) :
		left_(left), right_(right), angle_(angle) {
}

RotationIC::~RotationIC() {
}

void RotationIC::handleInput(Container* c, Uint32 time) {
	if (InputHandler::instance()->anyKeyDown()) {
		if (InputHandler::instance()->isKeyDown(right_)) {
			c->setRotation(c->getRotation() + angle_);
		} else if (InputHandler::instance()->isKeyDown(left_)) {
			c->setRotation(c->getRotation() - angle_);
		}
	}
}

