#include "ClientInfo.h"
#include "Messages_defs.h"
#include "ServerConnection.h"

std::unique_ptr<ClientInfo> ClientInfo::instance_;

ClientInfo::ClientInfo(char* host, int port) {

	conn_.connect(host, port);
	msg::Message* m = conn_.recvMessage();

	if ( m == nullptr || m->type_ != msg::CONNECTED ) {
		cout << "Something went wrong while connecting to server ..." << endl;
		exit(1);
	}

	clientId_ = m->clientId_;
}

ClientInfo::~ClientInfo() {
}

