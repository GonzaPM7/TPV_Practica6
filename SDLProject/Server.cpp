#include "Server.h"

#include "ServerConnection.h"
Server::Server() :
		clients_(), masterSocket_(), socketSet_(), port_(0), stop_(true), running_(false) {
	mutex = SDL_CreateMutex();
	cond = SDL_CreateCond();
}

Server::~Server() {
	SDL_DestroyMutex(mutex);
	SDL_DestroyCond(cond);
	SDLNet_FreeSocketSet(socketSet_);
}

void Server::start(int port) {

	port_ = port;

	// some types of message that we use later
	msg::Message msg_connected(msg::CONNECTED, msg::Server);
	msg::Message* msg;

	// a variable that represents the address -- in this case only the port
	IPaddress ip;

	// fill in the address in 'ip' -- note that the 2nd parameter is 'nullptr'
	if (SDLNet_ResolveHost(&ip, nullptr, port_) < 0) {
		error();
	}

	// Since the host in 'ip' is 0 (we provided 'nullptr' above), SDLNet_TCP_Open starts
	// a server listening at the port specified in 'ip' and returns a socket for listening
	// to connection requests
	masterSocket_ = SDLNet_TCP_Open(&ip);
	if (!masterSocket_) {
		error();
	}

	// We want to use non-blocking communication, the way to do this is via a socket set.
	// We add sockets to this set and then we can ask if any socket in this has some
	// activity without blocking.
	// Non-blocking communication is the adequate one for video games!!
	socketSet_ = SDLNet_AllocSocketSet(1000);

	// add the masterSocket to the set
	SDLNet_TCP_AddSocket(socketSet_, masterSocket_);

	SDL_LockMutex(mutex);
	stop_ = false;
	running_ = true;
	SDL_UnlockMutex(mutex);

	while ( !stop_ ) {
		// The call to SDLNet_CheckSockets returns the number of sockets with activity
		// in socketSet. The 2nd parameter tells the method to wait up to SDL_MAX_UINT32
		// if there is no activity -- no need to put it 0 in this case since the server
		// does not do anything else. With 0 it would consume CPU unnecessarily
		if (SDLNet_CheckSockets(socketSet_, SDL_MAX_UINT32) > 0) {

			// if there is an activity in masterSocket we process it. Note that
			// before calling SDLNet_SocketReady we must have called SDLNet_CheckSockets
			if (SDLNet_SocketReady(masterSocket_)) {

				// accept the connection (activity on master socket is always a connection
				// request, sending and receiving data is done via the socket returned by
				// SDLNet_TCP_Accept. This way we can serve several clients ...
				TCPsocket client = SDLNet_TCP_Accept(masterSocket_);

				// look for the first free slot in the clients array
				Uint8 j = 0;
				while (j < clients_.size() && clients_[j] != nullptr)
					j++;

				if (j >= clients_.size()) {
					clients_.resize(j + 1); // if clients array is full add some space
				}

				cout << "SERVER: " << "Client " << static_cast<int>(j)
						<< " has connected ..." << endl;

				// We keep the connection at position j, and add the socket to the
				// sockets set so we can ask for activity later ...
				clients_[j] = new ServerConnection(client);
				SDLNet_TCP_AddSocket(socketSet_, client);

				// send the client her/his ID
				msg_connected.clientId_ = j;
				clients_[j]->sendMessage(&msg_connected);

			}

			// check activity from clients
			for (int i = 0; i < clients_.size(); i++) {
				if (clients_[i] != nullptr && clients_[i]->ready()) { //clients_[i]->ready()) {
						// receive a message from the i-th client
					msg = clients_[i]->recvMessage();

					if (msg == nullptr) {
						// either the client closed the connection, or something went wrong,
						// we disconnect the client
						SDLNet_TCP_DelSocket(socketSet_,
								clients_[i]->getSocket()); // remove it from set -- very important!!
						clients_[i]->close();
						delete clients_[i];
						clients_[i] = nullptr;
						cout << "SERVER: " << "Client " << i << " disconnected"
								<< endl;
					} else {
						// if no error, forward the message to all clients
						for (int j = 0; j < clients_.size(); j++) {
							if (i != j && clients_[j] != nullptr) {
								clients_[j]->sendMessage(msg); // normally we should check for error
							}
						}
					}

				}
			}
		}
	}

	for (int i = 0; i < clients_.size(); i++) {
		if (clients_[i] != nullptr) {
			clients_[i]->close();
			delete clients_[i];
		}
	}

	// close the master socket when we exit the loop
	SDLNet_TCP_Close(masterSocket_);

	SDL_LockMutex(mutex);
	running_ = false;
	SDL_CondSignal(cond);
	SDL_UnlockMutex(mutex);

}

void Server::stop() {
	SDL_LockMutex(mutex);
	stop_ = true;
	// try to connect to wake the server up in case it is sleeping
	ServerConnection c;
	c.connect("localhost", port_);
	SDL_CondWait(cond, mutex);
	while (running_) SDL_UnlockMutex(mutex);
}


void Server::error() {
	cout << "SERVER: " << "Error, " << SDLNet_GetError() << endl;
	exit(1);
}
