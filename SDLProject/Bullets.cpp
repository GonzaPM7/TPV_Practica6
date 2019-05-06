#include "Bullets.h"
#include "Messages_defs.h"

Bullets::Bullets(SDLGame* game) :
		GameObjectPool(game),
		bulletImage_(game->getServiceLocator()->getTextures()->getTexture(Resources::WhiteRect)) {
	for (Bullet *b : getAllObjects()) {
		b->addC(&naturalMove_);
		b->addC(&deactivate_);
		b->addC(&bulletImage_);

	}

}

Bullets::~Bullets() {
}

void Bullets::shoot(Vector2D pos, Vector2D vel, double width, double height) {

	Bullet *b = getUnusedObject();
	if (b != nullptr) {
		b->setPosition( pos - Vector2D(width/2, height));
		b->setVelocity(vel);
		b->setRotation( Vector2D(0,-1).angle(vel));
		b->setWidth(width);
		b->setHeight(height);
		b->setActive(true);
		getGame()->getServiceLocator()->getAudios()->playChannel(Resources::GunShot, 0);
	}
}

void Bullets::receive(const void* senderObj, const msg::Message& msg) {
	Container::receive(senderObj, msg);

	switch ( msg.type_) {

	case msg::FIGHTER_SHOOT: {
		const msg::Shoot& m = static_cast<const msg::Shoot&>(msg);
		shoot(Vector2D(m.posX_,m.posY_),Vector2D(m.dirX_,m.dirY_)*5,1,5);
		break;
	}

	default:
		break;
	}
}
