#pragma once

#include <vector>

#include "ClientInfo.h"
#include "Vector2D.h"
#include "GameObject.h"

// you can replace these lines by corresponding
// includes once the classes are defined

class Asteroid;
class Bullet;

namespace msg {


struct Message {
	Message(msg::MessageType type, msg::ObjectId sender) :
		size_(sizeof(Message)), clientId_(0), type_(type), sender_(sender),destination_(msg::None) {
	}
	Message(msg::MessageType type, msg::ObjectId sender, msg::ObjectId destination, header_t_ size =
			sizeof(Message)) :
			size_(size),
			clientId_(ClientInfo::instance() == nullptr ? 0 : ClientInfo::instance() ->getClientId()),
			type_(type), sender_(sender), destination_(destination)  {
	}
	msg::header_t_ size_;
	int clientId_;
	msg::MessageType type_;
	msg::ObjectId sender_;
	msg::ObjectId destination_;
};

struct Shoot: public msg::Message {
	Shoot(msg::ObjectId sender, msg::ObjectId destination, Vector2D& pos, Vector2D& dir) :
	Message(msg::FIGHTER_SHOOT, sender, destination, sizeof(Shoot)) {
		posX_ = pos.getX();
		posY_ = pos.getY();
		dirX_ = dir.getX();
		dirY_ = dir.getY();
	}

	double posX_;
	double posY_;
	double dirX_;
	double dirY_;
};


// for network game
struct RemoteObjectInfo: public Message {
	RemoteObjectInfo(msg::ObjectId sender, msg::ObjectId destination, const Vector2D& pos, const Vector2D& vel, double rotation) :
			Message(REMOTE_OBJ_INFO, sender, destination, sizeof(RemoteObjectInfo)) {
		posX_ = pos.getX();
		posY_ = pos.getY();
		velX_ = vel.getX();
		velY_ = vel.getY();
		rotation_ = rotation;
	}
	double posX_;
	double posY_;
	double velX_;
	double velY_;
	double rotation_;
};

};
