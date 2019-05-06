#pragma once

#include "sdl_includes.h"
#include "Messages_decl.h"
#include <string>


/*
 *
 */
class ServerConnection {
public:
	ServerConnection();
	ServerConnection(TCPsocket conn);
	virtual ~ServerConnection();
	bool connect(const char* host, int port);

	bool ready();
	bool hasActivity();

	TCPsocket getSocket();
	msg::Message* recvMessage();
	bool sendMessage(const msg::Message* msg);
	void close();
private:
	bool connected_;
	TCPsocket conn_;
	Uint8 buffer_[1000];
	SDLNet_SocketSet socketSet_;
};

