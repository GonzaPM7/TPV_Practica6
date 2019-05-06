#pragma once

#include "Observer.h"
#include "ServerConnection.h"
#include "Messages_defs.h"
#include "SDLGame.h"

/*
 *
 */
class NetworkMessenger : public Observer {
public:
	NetworkMessenger(SDLGame* game);
	virtual ~NetworkMessenger();
	virtual void receive(const void *sender, const msg::Message& msg);
	void update();
private:
	SDLGame* game_;
};

