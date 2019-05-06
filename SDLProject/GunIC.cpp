#include "GunIC.h"

#include "InputHandler.h"
#include "Messages_defs.h"

GunIC::GunIC(SDL_Keycode ctrlKey) :
		ctrlKey_(ctrlKey) {
}

GunIC::~GunIC() {
}

void GunIC::handleInput(Container* c, Uint32 time) {
	if (InputHandler::instance()->isKeyDown(ctrlKey_)) {
		// add a bullet

		Vector2D p = c->getPosition()
				+ Vector2D(c->getWidth() / 2, c->getHeight() / 2)
				+ Vector2D(0, -(c->getHeight() / 2 + 5.0)).rotate(
						c->getRotation());
		Vector2D d = Vector2D(0, -1).rotate(c->getRotation());

		c->globalSend(this, msg::Shoot(c->getId(), msg::Broadcast,p,d));
	}

}
