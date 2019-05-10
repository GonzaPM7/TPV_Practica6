#include "Fighter.h"
#include "Messages_defs.h"
#include "ClientInfo.h"


Fighter::Fighter(msg::ObjectId id, SDLGame* game) :
		Container(game), //
		fighterImage_(game->getServiceLocator()->getTextures()->getTexture(
						Resources::Airplanes), { 47, 90, 207, 250 }), normalGun_(
				SDLK_SPACE), broadcastInfoPC_(), bulletsFighterCollision_() {

	setWidth(40);
	setHeight(50);
	setId(id);
	setActive(false);

	addC(&fighterImage_);
	if ((ClientInfo::instance()->getClientId() == 0 && getId() == msg::Fighter_0) ||
		(ClientInfo::instance()->getClientId() == 1 && getId() == msg::Fighter_1))
	{
		addC(&naturalMove_);
		addC(&rotation_);
		addC(&oppositeSide_);
		addC(&normalGun_);
		addC(&thrust_);
		addC(&reduceSpeed_);
		addC(&broadcastInfoPC_);
	}

	if ((ClientInfo::instance()->getClientId() == 0 && getId() == msg::Fighter_0))
	{
		addC(&bulletsFighterCollision_);
	}

	initFighter();
}

Fighter::~Fighter() {
}

void Fighter::receive(const void* senderObj, const msg::Message& msg) {
	Container::receive(senderObj, msg); // to send to all components

	switch (msg.type_) {
	case msg::GAME_START:
		setActive(true);
		if ((ClientInfo::instance()->getClientId() == 0))
			globalSend(this, msg::FighterInfo(msg::Fighter_0, msg::Broadcast, this));
		break;
	case msg::STOP_GAME:
		setActive(false);
		break;
	case msg::GAME_OVER:
		setActive(false);
		break;
	case msg::REMOTE_OBJ_INFO:
		if ((ClientInfo::instance()->getClientId() != msg.clientId_ &&
			getId() == msg.sender_))
		{
			msg::RemoteObjectInfo message = static_cast<const msg::RemoteObjectInfo&>(msg);
			setPosition({ message.posX_, message.posY_ });
			setVelocity({ message.velX_, message.velY_ });
			setRotation(message.rotation_);
		}
		break;
	default:
		break;
	}
}

void Fighter::initFighter() {
	setVelocity(Vector2D(0.0, 0.0));

	if (getId() == msg::Fighter_0)
	{
		setPosition(
			Vector2D(getGame()->getWindowWidth() / 4 - getWidth() / 2,
				getGame()->getWindowHeight() / 2 - getHeight() / 2));
	}
	else
	{
		setPosition(
			Vector2D(getGame()->getWindowWidth()*3 / 4 - getWidth() / 2,
				getGame()->getWindowHeight() / 2 - getHeight() / 2));
	}
}

