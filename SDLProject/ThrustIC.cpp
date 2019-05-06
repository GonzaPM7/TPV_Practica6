#include "ThrustIC.h"

#include "InputHandler.h"
ThrustIC::ThrustIC() :
		ThrustIC(SDLK_UP) {
}

ThrustIC::ThrustIC(SDL_Keycode ctrlKey) :
		ctrlKey_(ctrlKey) {
}

ThrustIC::~ThrustIC() {
}

void ThrustIC::handleInput(Container* c, Uint32 time) {
	if (InputHandler::instance()->anyKeyDown()) {
		if (InputHandler::instance()->isKeyDown(ctrlKey_)) {
			Vector2D v = c->getVelocity()
					+ (Vector2D(0, -1).rotate(c->getRotation()) * 0.5);
			if ( v.magnitude() >= 2) {
				v = v.normalize()*2;
			}
			c->setVelocity(v);
		}
	}
}
