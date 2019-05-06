#include "ServerConnection.h"
#include "Messages_defs.h"

ServerConnection::ServerConnection() :
		connected_(false), conn_(), buffer_(), socketSet_() {
}

ServerConnection::ServerConnection(TCPsocket conn) :
		connected_(true), conn_(conn), buffer_() {
	socketSet_ = SDLNet_AllocSocketSet(1);
	SDLNet_TCP_AddSocket(socketSet_, conn_);
}

ServerConnection::~ServerConnection() {
	close();
}

bool ServerConnection::connect(const char* host, int port) {
	if (connected_)
		close();

	// a variable that represents the address of the server we want to connect to
	IPaddress ip;

	// fill in the address address in ip
	if (SDLNet_ResolveHost(&ip, host, port) < 0) {
		return false;
	}

	conn_ = SDLNet_TCP_Open(&ip);
	if (!conn_) {
		return false;
	}

	connected_ = true;

	socketSet_ = SDLNet_AllocSocketSet(1);
	SDLNet_TCP_AddSocket(socketSet_, conn_);

	return true;
}

msg::Message* ServerConnection::recvMessage() {
	if (!connected_)
		return nullptr;

	int result;

	// read the header, which indicates the message size
	int bytesRead = 0;
	while (bytesRead < sizeof(msg::header_t_)) {
		result = SDLNet_TCP_Recv(conn_, buffer_ + bytesRead,
				sizeof(msg::header_t_) - bytesRead);
		if (result < 1)
			return nullptr;
		else {
			bytesRead += result;
		}
	}
	msg::header_t_ msgSize = *((msg::header_t_*) buffer_);

	// read message
	while (bytesRead < msgSize) {
		result = SDLNet_TCP_Recv(conn_, buffer_ + bytesRead,
				msgSize - bytesRead);
		if (result < 1)
			return nullptr;
		else {
			bytesRead += result;
		}
	}

	return (msg::Message*) buffer_;
}

bool ServerConnection::sendMessage(const msg::Message* msg) {
	if (!connected_)
		return false;

	int result = SDLNet_TCP_Send(conn_, (char*) msg, msg->size_);
	if (result != msg->size_)
		return false;

	return true;
}

bool ServerConnection::ready() {
	return connected_ && SDLNet_SocketReady(conn_);
}

bool ServerConnection::hasActivity() {
	return connected_ && SDLNet_CheckSockets(socketSet_, 0) > 0 && SDLNet_SocketReady(conn_);
}

TCPsocket ServerConnection::getSocket() {
	return conn_;
}

void ServerConnection::close() {
	if (connected_) {
		SDLNet_TCP_Close(conn_);
		SDLNet_FreeSocketSet(socketSet_);
		connected_ = false;
	}
}
