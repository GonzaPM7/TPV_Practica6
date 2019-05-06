#pragma once

#include <iostream>
#include "Messages_defs.h"
#include "sdl_includes.h"
#include "ServerConnection.h"
#include <vector>

using namespace std;

/*
 *
 */
class Server {
public:
	Server();
	virtual ~Server();
	void start(int port);
	void stop();
private:
	void error();

	vector<ServerConnection*> clients_;
	TCPsocket masterSocket_;
	SDLNet_SocketSet socketSet_;


	int port_;
	volatile bool stop_;
	volatile bool running_;

	SDL_cond *cond;
	SDL_mutex *mutex;

};

