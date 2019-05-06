#include "Fighter.h"
#include "Messages_defs.h"
#include "ClientInfo.h"

Fighter::Fighter(msg::ObjectId id, SDLGame* game) :
		Container(game), //
		fighterImage_(game->getServiceLocator()->getTextures()->getTexture(
						Resources::Airplanes), { 47, 90, 207, 250 }), normalGun_(
				SDLK_SPACE) {

	setWidth(40);
	setHeight(50);
	setId(id);
	setActive(true);

	addC(&fighterImage_);
	addC(&naturalMove_);
	addC(&rotation_);
	addC(&oppositeSide_);
	addC(&normalGun_);
	addC(&thrust_);
	addC(&reduceSpeed_);

	initFighter();
}

Fighter::~Fighter() {
}

void Fighter::receive(const void* senderObj, const msg::Message& msg) {
	Container::receive(senderObj, msg); // to send to all components

	switch (msg.type_) {
	default:
		break;
	}
}

void Fighter::initFighter() {
	setVelocity(Vector2D(0.0, 0.0));
	setPosition(
			Vector2D(getGame()->getWindowWidth() / 2 - getWidth() / 2,
					getGame()->getWindowHeight() / 2 - getHeight() / 2));
}

