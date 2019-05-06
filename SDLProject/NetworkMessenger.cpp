#include "NetworkMessenger.h"

#include "ClientInfo.h"

NetworkMessenger::NetworkMessenger(SDLGame* game) :
		game_(game) {
}

NetworkMessenger::~NetworkMessenger() {
}

void NetworkMessenger::receive(const void *sender, const msg::Message& msg) {
	ClientInfo::instance()->getConnection()->sendMessage(&msg);
}

void NetworkMessenger::update() {
	while (ClientInfo::instance()->getConnection()->hasActivity()) {
		msg::Message* msg = ClientInfo::instance()->getConnection()->recvMessage();
		if (msg != nullptr) {
			game_->send(this, *msg);
		}

	}
}

