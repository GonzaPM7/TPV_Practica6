#pragma once
#include "sdl_includes.h"
#include "ServerConnection.h"
#include <memory>
#include <iostream>

/*
 *
 */
class ClientInfo {
public:
	ClientInfo(char* host, int port);
	virtual ~ClientInfo();

	static inline void initInstance(char* host, int port) {
		if (instance_.get() == nullptr) {
			instance_.reset(new ClientInfo(host, port));
		}
	}

	static inline ClientInfo* instance() {
		return instance_.get();
	}

	inline ServerConnection* getConnection() {
		return &conn_;
	}

	inline Uint8 getClientId() {
		return clientId_;
	}

	inline bool isMaster() {
		return clientId_ == 0;
	}

	inline bool isMaster(int clientId) {
		return clientId == 0;
	}

private:
	static std::unique_ptr<ClientInfo> instance_;
	ServerConnection conn_;
	Uint8 clientId_;
};


